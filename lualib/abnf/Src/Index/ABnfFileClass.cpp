
#include "ABnfFileClass.h"
#include "alanguage/Src/Model/ABnf.h"
#include "alanguage/Src/Index/ABnfProject.h"
#include "alanguage/Src/Model/ABnfNodeElement.h"

ABnfFileClass::ABnfFileClass(ABnfProject* project, const std::string& full_path, const char* text, size_t len, bool in_ui)
	: ABnfFile(project, "", full_path, text, len, in_ui)
{
}

// ���·�������
void ABnfFileClass::UpdateAnalysis()
{
    m_root = nullptr;
    m_rule.clear();
    
    if (m_in_ui)
        m_root = GetProject()->RefABnfUI().Analysis(this);
    else
    {
        m_root = GetProject()->RefABnf().Analysis(this);

        if (m_root != nullptr)
        {
            m_index.clear();
            CollectIndex(m_root);
            CollectRule();
        }
    }
}

void ABnfFileClass::CollectIndex(const ABnfNodeElementPtr& node)
{
    if (node->GetNodeType() == "Id")
    {
        const auto& value = node->GetElementText();
        m_index[value].insert(node);
    }

    for (const auto& child : node->GetChilds())
    {
        auto node_child = std::dynamic_pointer_cast<ABnfNodeElement>(child);
        if (node_child != nullptr)
            CollectIndex(node_child);
    }
}

// �ռ�����ID
void ABnfFileClass::CollectRule()
{
    std::string comment;
    for (const auto& element : m_root->GetChilds())
    {
        if (element->GetNodeType() == "LineComment" || element->GetNodeType() == "BlockComment")
            comment = element->GetElementText();

        if (element->GetNodeType() != "Expression") continue;

        auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
        ABnfElementPtr id = nullptr;
        ABnfElementPtr value = nullptr;
        for (const auto& child : node->GetChilds())
        {
            if (child->GetNodeType() == "Id")
                id = child;
            else if (child->GetNodeType() == "Node")
                value = child;
        }
        if (id == nullptr) continue;
        if (value == nullptr) continue;
        const auto& id_value = id->GetElementText();

        m_rule[id_value][node] = comment;
        comment.clear();
    }
}

void ABnfFileClass::CollectCompile(const ABnfElementPtr& element, CollectCompileInfo& info, bool multi) const
{
    if (element->GetNodeType() == "List")
    {
        const auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
        if (node == nullptr) return;

        std::vector<CollectCompileInfo> option_list;
        option_list.push_back(info);
        CollectCompileInfo& leaf_or_group = option_list.back();
        for (const auto& child : node->GetChilds())
        {
            if (child->GetNodeType() == "Option")
            {
                option_list.push_back(info);
                CollectCompileInfo& option = option_list.back();
                CollectCompile(child, option, multi);
            }
            else
            {
                CollectCompile(child, leaf_or_group, multi);
            }
        }

        for (auto& option : option_list)
        {
            if (option.has_string > info.has_string)
                info.has_string = option.has_string;
            if (option.has_key > info.has_key)
                info.has_key = option.has_key;
            if (option.has_regex > info.has_regex)
                info.has_regex = option.has_regex;

            for (auto& pair : option.id_map)
            {
                auto it = info.id_map.find(pair.first);
                if (it != info.id_map.end())
                {
                    if (pair.second > it->second)
                        it->second = pair.second;
                }
                else
                {
                    info.id_map[pair.first] = pair.second;
                }
            }
        }
    }
    else if (element->GetNodeType() == "Option" || element->GetNodeType() == "Node")
    {
        const auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
        if (node == nullptr) return;

        for (const auto& child : node->GetChilds())
            CollectCompile(child, info, multi);
    }
    else if (element->GetNodeType() == "Group" || element->GetNodeType() == "Leaf")
    {
        const auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
        if (node == nullptr) return;

        if (multi == false)
        {
            ABnfElementPtr tail_node = nullptr;
            for (const auto& child : node->GetChilds())
            {
                if (child->GetNodeType() == "NodeTail")
                    tail_node = child;
            }

            if (tail_node != nullptr)
            {
                const auto tail_value = tail_node->GetElementText();
                multi = tail_value.find('+') == 0 || tail_value.find('*') == 0;
            }
        }

        for (const auto& child : node->GetChilds())
            CollectCompile(child, info, multi);
    }
    else if (element->GetNodeType() == "Id")
    {
        int cur_count = 0;
        const auto it = info.id_map.find(element->GetElementText());
        if (it != info.id_map.end()) cur_count = it->second;

        info.id_map[element->GetElementText()] = cur_count + (multi ? 2 : 1);
        return;
    }
    else if (element->GetNodeType() == "String")
    {
        info.has_string = info.has_string + (multi ? 2 : 1);
    }
    else if (element->GetNodeType() == "Key")
    {
        info.has_key = info.has_key + (multi ? 2 : 1);
    }
    else if (element->GetNodeType() == "Regex")
    {
        info.has_regex = info.has_regex + (multi ? 2 : 1);
    }
}

static std::string ABnfElementTemplateHpp =
"#ifndef _ALITTLE_@@LANGUAGE@@@@NAME@@Element_H_\n"
"#define _ALITTLE_@@LANGUAGE@@@@NAME@@Element_H_\n"
"\n"
"#include <memory>\n"
"#include <vector>\n"
"#include <string>\n"
"#include \"../../alanguage/Model/ABnfNodeElement.h\"\n"
"\n"
"@@ELEMENT_DEFINE@@"
"\n"
"class @@LANGUAGE@@@@NAME@@Element : public ABnfNodeElement\n"
"{\n"
"public:\n"
"    @@LANGUAGE@@@@NAME@@Element(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)\n"
"        : ABnfNodeElement(factory, file, line, col, offset, type) { }\n"
"    virtual ~@@LANGUAGE@@@@NAME@@Element() { }\n"
"\n"
"@@ELEMENT_GET_CHILD@@"
"};\n"
"\n"
"#endif // _ALITTLE_@@LANGUAGE@@@@NAME@@Element_H_\n";
static std::string ABnfElementTemplateCpp =
"#include \"@@LANGUAGE@@@@NAME@@Element.h\"\n"
"\n"
"@@ELEMENT_INCLUDE@@"
"\n"
"@@ELEMENT_GET_CHILD@@"
"\n";
static std::string ABnfGetChildTemplateHpp =
"private:\n"
"    bool m_flag_@@NAME@@ = false;\n"
"    std::shared_ptr<@@LANGUAGE@@@@NAME@@Element> m_cache_@@NAME@@;\n"
"public:\n"
"    std::shared_ptr<@@LANGUAGE@@@@NAME@@Element> Get@@NAME@@();\n";
static std::string ABnfGetChildTemplateCpp =
"std::shared_ptr<@@LANGUAGE@@@@NAME@@Element> @@LANGUAGE@@@@CLASS_NAME@@Element::Get@@NAME@@()\n"
"{\n"
"    if (m_flag_@@NAME@@) return m_cache_@@NAME@@;\n"
"    m_flag_@@NAME@@ = true;\n"
"    for (auto& child : m_childs)\n"
"    {\n"
"        auto node = std::dynamic_pointer_cast<@@LANGUAGE@@@@NAME@@Element>(child);\n"
"        if (node != nullptr)\n"
"        {\n"
"            m_cache_@@NAME@@ = node;\n"
"            break;\n"
"        }\n"
"    }\n"
"    return m_cache_@@NAME@@;\n"
"}\n";
static std::string ABnfGetChildListTemplateHpp =
"private:\n"
"    bool m_flag_@@NAME@@ = false;\n"
"    std::vector<std::shared_ptr<@@LANGUAGE@@@@NAME@@Element>> m_list_@@NAME@@;\n"
"public:\n"
"    const std::vector<std::shared_ptr<@@LANGUAGE@@@@NAME@@Element>>& Get@@NAME@@List();\n";
static std::string ABnfGetChildListTemplateCpp =
"const std::vector<std::shared_ptr<@@LANGUAGE@@@@NAME@@Element>>& @@LANGUAGE@@@@CLASS_NAME@@Element::Get@@NAME@@List()\n"
"{\n"
"    if (m_flag_@@NAME@@) return m_list_@@NAME@@;\n"
"    m_flag_@@NAME@@ = true;\n"
"    for (auto& child : m_childs)\n"
"    {\n"
"        auto node = std::dynamic_pointer_cast<@@LANGUAGE@@@@NAME@@Element>(child);\n"
"        if (node != nullptr)\n"
"            m_list_@@NAME@@.push_back(node);\n"
"    }\n"
"    return m_list_@@NAME@@;\n"
"}\n";
static std::string ABnfKeyElementTemplate =
"#ifndef _ALITTLE_@@LANGUAGE@@KeyElement_H_\n"
"#define _ALITTLE_@@LANGUAGE@@KeyElement_H_\n"
"\n"
"#include \"../../alanguage/Model/ABnfKeyElement.h\"\n"
"\n"
"class @@LANGUAGE@@KeyElement : public ABnfKeyElement\n"
"{\n"
"public:\n"
"    @@LANGUAGE@@KeyElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)\n"
"        : ABnfKeyElement(factory, file, line, col, offset, type) { }\n"
"    virtual ~@@LANGUAGE@@KeyElement() { }\n"
"};\n"
"\n"
"#endif // _ALITTLE_@@LANGUAGE@@KeyElement_H_\n";
static std::string ABnfStringElementTemplate =
"#ifndef _ALITTLE_@@LANGUAGE@@StringElement_H_\n"
"#define _ALITTLE_@@LANGUAGE@@StringElement_H_\n"
"\n"
"#include \"../../alanguage/Model/ABnfStringElement.h\"\n"
"\n"
"class @@LANGUAGE@@StringElement : public ABnfStringElement\n"
"{\n"
"public:\n"
"    @@LANGUAGE@@StringElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)\n"
"        : ABnfStringElement(factory, file, line, col, offset, type) { }\n"
"    virtual ~@@LANGUAGE@@StringElement() { }\n"
"};\n"
"\n"
"#endif // _ALITTLE_@@LANGUAGE@@StringElement_H_\n";
static std::string ABnfRegexElementTemplate =
"#ifndef _ALITTLE_@@LANGUAGE@@RegexElement_H_\n"
"#define _ALITTLE_@@LANGUAGE@@RegexElement_H_\n"
"\n"
"#include \"../../alanguage/Model/ABnfRegexElement.h\"\n"
"\n"
"class @@LANGUAGE@@RegexElement : public ABnfRegexElement\n"
"{\n"
"public:\n"
"    @@LANGUAGE@@RegexElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type, const std::shared_ptr<ARegex>& regex)\n"
"        : ABnfRegexElement(factory, file, line, col, offset, type, regex) { }\n"
"    virtual ~@@LANGUAGE@@RegexElement() { }\n"
"};\n"
"\n"
"#endif // _ALITTLE_@@LANGUAGE@@RegexElement_H_\n";
static std::string ABnfFactoryTemplate =
"#ifndef _ALITTLE_@@LANGUAGE@@Factory_H_\n"
"#define _ALITTLE_@@LANGUAGE@@Factory_H_\n"
"\n"
"#include \"../../alanguage/Index/ABnfFactory.h\"\n"
"#include \"@@LANGUAGE@@KeyElement.h\"\n"
"#include \"@@LANGUAGE@@StringElement.h\"\n"
"#include \"@@LANGUAGE@@RegexElement.h\"\n"
"@@ELEMENT_INCLUDE@@"
"\n"
"#include <unordered_map>\n"
"#include <functional>\n"
"#include <string>\n"
"\n"
"class @@LANGUAGE@@Factory : public ABnfFactory\n"
"{\n"
"    std::unordered_map<std::string, std::function<std::shared_ptr<ABnfNodeElement>(ABnfFactory*, ABnfFile*, int, int, int, const std::string&)>> m_create_map;\n"
"public:\n"
"    @@LANGUAGE@@Factory()\n"
"    {\n"
"@@ELEMENT_ADD_CREATE@@\n"
"    }\n"

"    std::shared_ptr<ABnfNodeElement> CreateNodeElement(ABnfFile* file, int line, int col, int offset, const std::string& type) override\n"
"    {\n"
"        auto it = m_create_map.find(type);\n"
"        if (it == m_create_map.end()) return nullptr;\n"
"        return it->second(this, file, line, col, offset, type);\n"
"    }\n"

"    std::shared_ptr<ABnfKeyElement> CreateKeyElement(ABnfFile* file, int line, int col, int offset, const std::string& type) override\n"
"    {\n"
"        return std::make_shared<@@LANGUAGE@@KeyElement>(this, file, line, col, offset, type);\n"
"    }\n"

"    std::shared_ptr<ABnfStringElement> CreateStringElement(ABnfFile* file, int line, int col, int offset, const std::string& type) override\n"
"    {\n"
"        return std::make_shared<@@LANGUAGE@@StringElement>(this, file, line, col, offset, type);\n"
"    }\n"

"    std::shared_ptr<ABnfRegexElement> CreateRegexElement(ABnfFile* file, int line, int col, int offset, const std::string& type, const std::shared_ptr<ARegex>& regex) override\n"
"    {\n"
"        return std::make_shared<@@LANGUAGE@@RegexElement>(this, file, line, col, offset, type, regex);\n"
"    }\n"
"};\n"
"\n"
"#endif // _ALITTLE_@@LANGUAGE@@Factory_H_\n";

std::string ABnfFileClass::Generate(int version, const std::string& target_path, const std::string& language_name)
{
    AnalysisText(version);

    if (m_root == nullptr) return "syntax error";
    if (HasError()) return "Please fix the error before generating";

    std::string add_new_buffer;
    std::vector<std::string> element_include_list;
    for (auto& rule : m_rule)
    {
        ABnfNodeElementPtr node = nullptr;
        for (auto& e : rule.second)
        {
            if (node != nullptr)
                return "count of " + rule.first + " is " + std::to_string(rule.second.size());

            node = e.first;
        }
        if (node == nullptr)
            return "count of " + rule.first + " is " + std::to_string(rule.second.size());

        ABnfNodeElementPtr value = nullptr;
        for (const auto& child : node->GetChilds())
        {
            if (child->GetNodeType() == "Node" && std::dynamic_pointer_cast<ABnfNodeElement>(child))
                value = std::dynamic_pointer_cast<ABnfNodeElement>(child);
        }
        if (value == nullptr)
            return rule.first + " is not a ABnfNodeElement";

        CollectCompileInfo info;
        CollectCompile(value, info, false);

        // ���￪ʼ����
        std::string buffer_hpp = ABnfElementTemplateHpp;
        std::string buffer_cpp = ABnfElementTemplateCpp;

        // �滻Э������
        buffer_hpp = ABnfFactory::ReplaceAll(buffer_hpp, "@@LANGUAGE@@", language_name);
        buffer_hpp = ABnfFactory::ReplaceAll(buffer_hpp, "@@NAME@@", rule.first);

        buffer_cpp = ABnfFactory::ReplaceAll(buffer_cpp, "@@LANGUAGE@@", language_name);
        buffer_cpp = ABnfFactory::ReplaceAll(buffer_cpp, "@@NAME@@", rule.first);

        add_new_buffer += "        m_create_map[\"" + rule.first + "\"] = [](ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type) -> std::shared_ptr<ABnfNodeElement> { return std::make_shared<" + language_name + rule.first + "Element>(factory, file, line, col, offset, type); };\n";
        element_include_list.push_back("#include \"" + language_name + rule.first + "Element.h\"\n");

        std::string element_define;
        std::string element_include;

        std::string get_child_buffer_hpp;
        std::string get_child_buffer_cpp;
        for (auto& id_pair : info.id_map)
        {
            if (id_pair.second == 1)
            {
                get_child_buffer_hpp += ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfGetChildTemplateHpp, "@@LANGUAGE@@", language_name), "@@NAME@@", id_pair.first);
                get_child_buffer_cpp += ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfGetChildTemplateCpp, "@@LANGUAGE@@", language_name), "@@NAME@@", id_pair.first), "@@CLASS_NAME@@", rule.first);
            }
            else if (id_pair.second > 1)
            {
                get_child_buffer_hpp += ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfGetChildListTemplateHpp, "@@LANGUAGE@@", language_name), "@@NAME@@", id_pair.first);
                get_child_buffer_cpp += ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfGetChildListTemplateCpp, "@@LANGUAGE@@", language_name), "@@NAME@@", id_pair.first), "@@CLASS_NAME@@", rule.first);
            }

            if (id_pair.second > 0)
            {
                element_define += "class " + language_name + id_pair.first + "Element;\n";
                element_include += "#include \"" + language_name + id_pair.first + "Element.h\"\n";
            }
        }

        if (info.has_key == 1)
        {
            get_child_buffer_hpp += ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfGetChildTemplateHpp, "@@LANGUAGE@@", language_name), "@@NAME@@", "Key");
            get_child_buffer_cpp += ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfGetChildTemplateCpp, "@@LANGUAGE@@", language_name), "@@NAME@@", "Key"), "@@CLASS_NAME@@", rule.first);
        }
        else if (info.has_key > 1)
        {
            get_child_buffer_hpp += ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfGetChildListTemplateHpp, "@@LANGUAGE@@", language_name), "@@NAME@@", "Key");
            get_child_buffer_cpp += ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfGetChildListTemplateCpp, "@@LANGUAGE@@", language_name), "@@NAME@@", "Key"), "@@CLASS_NAME@@", rule.first);
        }

        if (info.has_key > 0)
        {
            element_define += "class " + language_name + "KeyElement;\n";
            element_include += "#include \"" + language_name + "KeyElement.h\"\n";
        }

        if (info.has_string == 1)
        {
            get_child_buffer_hpp += ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfGetChildTemplateHpp, "@@LANGUAGE@@", language_name), "@@NAME@@", "String");
            get_child_buffer_cpp += ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfGetChildTemplateCpp, "@@LANGUAGE@@", language_name), "@@NAME@@", "String"), "@@CLASS_NAME@@", rule.first);
        }
        else if (info.has_string > 1)
        {
            get_child_buffer_hpp += ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfGetChildListTemplateHpp, "@@LANGUAGE@@", language_name), "@@NAME@@", "String");
            get_child_buffer_cpp += ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfGetChildListTemplateCpp, "@@LANGUAGE@@", language_name), "@@NAME@@", "String"), "@@CLASS_NAME@@", rule.first);
        }

        if (info.has_string > 0)
        {
            element_define += "class " + language_name + "StringElement;\n";
            element_include += "#include \"" + language_name + "StringElement.h\"\n";
        }

        if (info.has_regex == 1)
        {
            get_child_buffer_hpp += ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfGetChildTemplateHpp, "@@LANGUAGE@@", language_name), "@@NAME@@", "Regex");
            get_child_buffer_cpp += ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfGetChildTemplateCpp, "@@LANGUAGE@@", language_name), "@@NAME@@", "Regex"), "@@CLASS_NAME@@", rule.first);
        }
        else if (info.has_regex > 1)
        {
            get_child_buffer_hpp += ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfGetChildListTemplateHpp, "@@LANGUAGE@@", language_name), "@@NAME@@", "Regex");
            get_child_buffer_cpp += ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfGetChildListTemplateCpp, "@@LANGUAGE@@", language_name), "@@NAME@@", "Regex"), "@@CLASS_NAME@@", rule.first);
        }

        if (info.has_regex > 0)
        {
            element_define += "class " + language_name + "RegexElement;\n";
            element_include += "#include \"" + language_name + "RegexElement.h\"\n";
        }

        buffer_hpp = ABnfFactory::ReplaceAll(buffer_hpp, "@@ELEMENT_GET_CHILD@@", get_child_buffer_hpp);
        buffer_hpp = ABnfFactory::ReplaceAll(buffer_hpp, "@@ELEMENT_DEFINE@@", element_define);

        buffer_cpp = ABnfFactory::ReplaceAll(buffer_cpp, "@@ELEMENT_GET_CHILD@@", get_child_buffer_cpp);
        buffer_cpp = ABnfFactory::ReplaceAll(buffer_cpp, "@@ELEMENT_INCLUDE@@", element_include);

        std::string file_path_hpp = target_path + "/" + language_name + rule.first + "Element.h";
        std::string file_path_cpp = target_path + "/" + language_name + rule.first + "Element.cpp";

        if (!ABnfFactory::WriteAllText(file_path_hpp, buffer_hpp))
            return file_path_hpp + " generate failed!";
        if (!ABnfFactory::WriteAllText(file_path_cpp, buffer_cpp))
            return file_path_cpp + " generate failed!";
    }

    {
        // ����KeyElement
        std::string buffer = ABnfFactory::ReplaceAll(ABnfKeyElementTemplate, "@@LANGUAGE@@", language_name);
        std::string file_path = target_path + "/" + language_name + "KeyElement.h";
        if (!ABnfFactory::WriteAllText(file_path, buffer))
            return file_path + " generate failed!";
    }

    {
        // ����StringElement
        std::string buffer = ABnfFactory::ReplaceAll(ABnfStringElementTemplate, "@@LANGUAGE@@", language_name);
        std::string file_path = target_path + "/" + language_name + "StringElement.h";
        if (!ABnfFactory::WriteAllText(file_path, buffer))
            return file_path + " generate failed!";
    }

    {
        // ����RegexElement
        std::string buffer = ABnfFactory::ReplaceAll(ABnfRegexElementTemplate, "@@LANGUAGE@@", language_name);
        std::string file_path = target_path + "/" + language_name + "RegexElement.h";
        if (!ABnfFactory::WriteAllText(file_path, buffer))
            return file_path + " generate failed!";
    }

    {
        // ����Factory
        std::string buffer = ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfFactory::ReplaceAll(ABnfFactoryTemplate, "@@LANGUAGE@@", language_name), "@@ELEMENT_ADD_CREATE@@", add_new_buffer), "@@ELEMENT_INCLUDE@@", ABnfFactory::Join(element_include_list, ""));
        std::string file_path = target_path + "/" + language_name + "Factory.h";
        if (!ABnfFactory::WriteAllText(file_path, buffer))
            return file_path + " generate failed!";
    }

    return "";
}
