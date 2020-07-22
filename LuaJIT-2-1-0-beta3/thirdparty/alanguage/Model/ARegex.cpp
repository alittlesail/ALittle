#include "ARegex.h"

ARegex::ARegex(const std::string& rule) : m_rule(rule)
{
	m_rule_error.clear();

	size_t offset = 0;
	m_node.type = ARegexType::T_OPTION;
	CompileOption(m_rule, offset, m_node, m_rule_error);
}

bool ARegex::Match(const char* src, int& length)
{
	length = 0;
	return MatchNodeRepeated(src, m_node, length);
}

bool ARegex::MatchNode(const char* src, const ARegexNode& node, int& length)
{
	if (src[length] == 0) return false;
	char c = src[length];

	if (node.type == ARegexType::T_CHAR)
	{
		if (node.value == c)
		{
			++length;
			return true;
		}
		return false;
	}
	
	if (node.type == ARegexType::T_CHARSET)
	{
		bool check = false;
		if (node.char_set_type == ARegexCharSetType::CST_ALL)
		{
			check = true;
		}
		else if (node.char_set_type == ARegexCharSetType::CST_CUSTOM)
		{
			check = node.char_set.find(c) != node.char_set.end();
		}
		else if (node.char_set_type == ARegexCharSetType::CST_A)
		{
			check = c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
		}
		else if (node.char_set_type == ARegexCharSetType::CST_D)
		{
			check = c >= '0' && c <= '9';
		}
		else if (node.char_set_type == ARegexCharSetType::CST_W)
		{
			check = c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9' || c == '_';
		}
		else if (node.char_set_type == ARegexCharSetType::CST_DOT)
		{
			check = c != '\n';
		}

		if (node.negate == ARegexNegateType::NNT_TRUE)
		{
			if (!check)
			{
				++length;
				return true;
			}
		}
		else
		{
			if (check)
			{
				++length;
				return true;
			}
		}

		return false;
	}
	else if (node.type == ARegexType::T_OPTION)
	{
		for (auto& child : node.childs)
		{
			// 保存临时值
			int length_temp = length;
			if (MatchNodeRepeated(src, child, length_temp))
			{
				// 如果有取反，那么直接返回失败
				if (node.negate == ARegexNegateType::NNT_TRUE)
					return false;

				length = length_temp;
				return true;
			}
		}

		if (node.negate == ARegexNegateType::NNT_TRUE)
		{
			length += 1;
			return true;
		}

		return false;
	}
	else if (node.type == ARegexType::T_LIST)
	{
		for (auto& child : node.childs)
		{
			if (!MatchNodeRepeated(src, child, length))
				return false;
		}
		return true;
	}
	return false;
}

bool ARegex::MatchNodeRepeated(const char* src, const ARegexNode& node, int& length)
{
	if (node.repeat == ARegexRepeatType::NRT_NONE || node.repeat == ARegexRepeatType::NRT_ONE)
	{
		return MatchNode(src, node, length);
	}
	else if (node.repeat == ARegexRepeatType::NRT_ONE_OR_NOT)
	{
		int length_temp = length;
		if (MatchNode(src, node, length_temp))
			length = length_temp;
		return true;
	}
	else if (node.repeat == ARegexRepeatType::NRT_NOT_OR_MORE)
	{
		while (true)
		{
			int length_temp = length;
			if (MatchNode(src, node, length_temp))
				length = length_temp;
			else
				break;
		}
		return true;
	}
	else if (node.repeat == ARegexRepeatType::NRT_AT_LEAST_ONE)
	{
		if (!MatchNode(src, node, length)) return false;

		while (true)
		{
			int length_temp = length;
			if (MatchNode(src, node, length_temp))
				length = length_temp;
			else
				break;
		}
		return true;
	}
	return false;
}

bool ARegex::CompileOption(const std::string& rule, size_t& offset, ARegexNode& node, std::string& error)
{
	node.childs.push_back(ARegexNode());
	auto* list = &node.childs.back();
	list->type = ARegexType::T_LIST;

	// 循环
	while (offset < rule.size())
	{
		char c = rule[offset];
		char next_c = 0;
		if (offset + 1 < rule.size()) next_c = rule[offset + 1];
		
		if (c == '[')
		{
			list->childs.push_back(ARegexNode());
			ARegexNode& child = list->childs.back();
			child.type = ARegexType::T_CHARSET;
			child.char_set_type = ARegexCharSetType::CST_CUSTOM;

			++offset;
			if (!CompileCustomSet(rule, offset, child, error)) return false;
			++offset;
		}
		else if (c == ']')
		{
			error = "error close char ] in group, offset:" + offset;
			return false;
		}
		else if (c == '|')
		{
			node.childs.push_back(ARegexNode());
			list = &node.childs.back();
			list->type = ARegexType::T_LIST;

			++offset;
		}
		else if (c == '!')
		{
			if (next_c != '(')
			{
				error = "next char must be ( after !, offset:" + offset;
				return false;
			}
			++offset;
		}
		else if (c == '(')
		{
			list->childs.push_back(ARegexNode());
			ARegexNode& child = list->childs.back();
			child.type = ARegexType::T_OPTION;
			if (offset > 0 && rule[offset - 1] == '!')
				child.negate = ARegexNegateType::NNT_TRUE;

			++offset;
			if (!CompileOption(rule, offset, child, error)) return false;
			++offset;
		}
		else if (c == ')')
		{
			return true;
		}
		else if (c == '%')
		{
			// 特殊规则
			if (next_c == 'w' || next_c == 'a' || next_c == 'd')
			{
				list->childs.push_back(ARegexNode());
				ARegexNode& child = list->childs.back();
				child.type = ARegexType::T_CHARSET;
				if (next_c == 'w')
					child.char_set_type = ARegexCharSetType::CST_W;
				else if (next_c == 'a')
					child.char_set_type = ARegexCharSetType::CST_A;
				else if (next_c == 'd')
					child.char_set_type = ARegexCharSetType::CST_D;
				else
				{
					error = "error char after %, offset:" + std::to_string(offset);
					return false;
				}
				++offset;
			}
			else
			{
				list->childs.push_back(ARegexNode());
				ARegexNode& child = list->childs.back();
				child.type = ARegexType::T_CHAR;
				if (next_c == 'a') child.value = '\a';
				else if (next_c == 'b') child.value = '\b';
				else if (next_c == 'f') child.value = '\f';
				else if (next_c == 'n') child.value = '\n';
				else if (next_c == 'r') child.value = '\r';
				else if (next_c == 't') child.value = '\t';
				else if (next_c == 'v') child.value = '\v';
				else if (next_c != 0) child.value = next_c;
				else
				{
					error = "error char after %, offset:" + std::to_string(offset);
					return false;
				}
				++offset;
			}

			++offset;
		}
		else if (c == '.')
		{
			list->childs.push_back(ARegexNode());
			ARegexNode& child = list->childs.back();
			child.type = ARegexType::T_CHARSET;
			child.char_set_type = ARegexCharSetType::CST_DOT;

			++offset;
		}
		else
		{
			list->childs.push_back(ARegexNode());
			ARegexNode& child = list->childs.back();
			child.type = ARegexType::T_CHAR;
			child.value = c;

			++offset;
		}

		if (list->childs.size() > 0 && offset < rule.size())
		{
			if (rule[offset] == '*') list->childs.back().repeat = ARegexRepeatType::NRT_NOT_OR_MORE;
			if (rule[offset] == '+') list->childs.back().repeat = ARegexRepeatType::NRT_AT_LEAST_ONE;
			if (rule[offset] == '?') list->childs.back().repeat = ARegexRepeatType::NRT_ONE_OR_NOT;

			if (list->childs.back().repeat != ARegexRepeatType::NRT_NONE)
				++offset;
		}
	}

	if (node.childs.size() > 0 && node.childs.back().childs.empty())
		node.childs.pop_back();

	if (node.childs.empty())
	{
		error += "empty group";
		return false;
	}
	return true;
}

bool ARegex::CompileCustomSet(const std::string& rule, size_t& offset, ARegexNode& node, std::string& error)
{
	if (offset >= rule.size())
	{
		error = "custom set not complete";
		return false;
	}

	// 检查是否取反
	if (rule[offset] == '^')
	{
		node.negate = ARegexNegateType::NNT_TRUE;
		++offset;
	}

	bool has_dot = false;
	while (offset < rule.size())
	{
		char c = rule[offset];
		char next_c = 0;
		if (offset + 1 < rule.size()) next_c = rule[offset + 1];
		char next_next_c = 0;
		if (offset + 2 < rule.size()) next_next_c = rule[offset + 2];

		if (c == '[')
		{
			error = "custom set can't not nested custom set";
			return false;
		}
		else if (c == '(')
		{
			error = "custom set can't not nested group";
			return false;
		}
		else if (c == ']')
		{
			if (has_dot)
			{
				if (node.char_set.find('\n') != node.char_set.end())
					node.char_set_type = ARegexCharSetType::CST_ALL;
				else
					node.char_set_type = ARegexCharSetType::CST_DOT;
				node.char_set.clear();
			}
			return true;
		}
		else if (c == '%')
		{
			if (next_c == 'a') node.char_set.insert('\a');
			else if (next_c == 'b') node.value += '\b';
			else if (next_c == 'f') node.value += '\f';
			else if (next_c == 'n') node.value += '\n';
			else if (next_c == 'r') node.value += '\r';
			else if (next_c == 't') node.value += '\t';
			else if (next_c == 'v') node.value += '\v';
			else if (next_c == 'w')
			{
				for (char i = '0'; i <= '9'; ++i)
					node.char_set.insert(i);
				for (char i = 'a'; i <= 'z'; ++i)
					node.char_set.insert(i);
				for (char i = 'A'; i <= 'Z'; ++i)
					node.char_set.insert(i);
				node.char_set.insert('_');
			}
			else if (next_c == 'd')
			{
				for (char i = '0'; i <= '9'; ++i)
					node.char_set.insert(i);
			}
			else if (next_c == 'a')
			{
				for (char i = 'a'; i <= 'z'; ++i)
					node.char_set.insert(i);
				for (char i = 'A'; i <= 'Z'; ++i)
					node.char_set.insert(i);
			}
			else if (next_c != 0)
			{
				node.char_set.insert(next_c);
			}
			++offset;
		}
		else if (c >= '0' && c <= '9')
		{
			if (next_c == '-' && next_next_c >= '0' && next_next_c <= '9')
			{
				for (char i = c; i <= next_next_c; ++i)
					node.char_set.insert(i);
				offset += 2;
			}
			else
			{
				node.char_set.insert(c);
			}
		}
		else if (c >= 'a' && c <= 'z')
		{
			if (next_c == '-' && next_next_c >= 'a' && next_next_c <= 'z')
			{
				for (char i = c; i <= next_next_c; ++i)
					node.char_set.insert(i);
				offset += 2;
			}
			else
			{
				node.char_set.insert(c);
			}
		}
		else if (c >= 'A' && c <= 'Z')
		{
			if (next_c == '-' && next_next_c >= 'A' && next_next_c <= 'Z')
			{
				for (char i = c; i <= next_next_c; ++i)
					node.char_set.insert(i);
				offset += 2;
			}
			else
			{
				node.char_set.insert(c);
			}
		}
		else if (c == '.')
		{
			has_dot = true;
		}
		else
		{
			node.char_set.insert(c);
		}

		++offset;
	}

	error = "custom set not complete";
	return false;
}
