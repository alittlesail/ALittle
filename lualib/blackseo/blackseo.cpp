
extern "C" {
#include "blackseolib.h"
}

#include "carp_lua.hpp"
#include "carp_rwops.hpp"
#include "carp_string.hpp"
#include "carp_schedule.hpp"
#include "carp_http_client.hpp"

#include <thread>
#include <set>
#include <string>

class BlackSeoSchedule : public CarpSchedule
{
public:
	void Start(size_t start, size_t end, const std::vector<std::string>* url_list
		, const std::string& url_path, const std::string& match_text)
	{
		m_url_path = url_path;
		m_match_text = match_text;

		// 启动
		Run(true, std::bind(&BlackSeoSchedule::Setup, this), std::bind(&BlackSeoSchedule::Shutdown, this));

		// 执行下一个
		Execute(std::bind(&BlackSeoSchedule::NextOne, this, start, end, url_list));
	}

	void GetMatchSet(std::set<std::string>& result)
	{
		m_match_lock.lock();
		m_match_set.swap(result);
		m_match_lock.unlock();
	}

	bool IsCompleted() const { return m_completed; }
	int GetFailedCount() const { return m_match_failed; }
	int GetSucceedCount() const { return m_match_succeed; }

private:
	void NextOne(size_t start, size_t end, const std::vector<std::string>* url_list)
	{
		if (start >= end)
		{
			m_completed = true;
			return;
		}

		auto url = (*url_list)[start] + m_url_path;
		auto client = std::make_shared<CarpHttpClientText>();

		client->SendRequest(url, true, "application/json", nullptr, 0
			, std::bind(&BlackSeoSchedule::HandleHttpResult, this
				, std::placeholders::_1, std::placeholders::_2
				, std::placeholders::_3, std::placeholders::_4
				, 0, url, start, end, url_list)
			, nullptr, &GetIOService(), "", 0, "");
	}

	void HandleHttpResult(bool result, const std::string& body, const std::string& head, const std::string& error
		, int location, const std::string& url, size_t start, size_t end, const std::vector<std::string>* url_list)
	{
		if (head.find("301 Moved Permanently") != std::string::npos)
		{
			// 已经重复location了5次，那么就算失败
			if (location >= 5)
			{
				m_match_failed += 1;
				return;
			}

			std::vector<std::string> head_list;
			CarpString::Split(head, "\r\n", true, head_list);
			for (auto& value : head_list)
			{
				auto pos = value.find("Location:");
				if (pos != std::string::npos)
				{
					auto new_url = value.substr(pos + strlen("Location:"));

					auto client = std::make_shared<CarpHttpClientText>();
					client->SendRequest(new_url, true, "application/json", nullptr, 0
						, std::bind(&BlackSeoSchedule::HandleHttpResult, this
							, std::placeholders::_1, std::placeholders::_2
							, std::placeholders::_3, std::placeholders::_4
							, location + 1, new_url, start, end, url_list)
						, nullptr, &GetIOService(), "", 0, "");
					return;
				}
			}
		}

		auto pos = body.find(m_match_text);
		if (pos == std::string::npos)
			m_match_failed += 1;
		else
		{
			m_match_succeed += 1;

			m_match_lock.lock();
			m_match_set.insert(url);
			m_match_lock.unlock();
		}

		start += 1;
		NextOne(start, end, url_list);
	};

private:
	void Setup()
	{
	}

	void Shutdown()
	{
	}

private:
	int m_match_succeed = 0;
	int m_match_failed = 0;

	std::mutex m_match_lock;
	std::set<std::string> m_match_set;

private:
	bool m_completed = false;
	std::string m_url_path;
	std::string m_match_text;
};

class BlackSeo
{
public:
	~BlackSeo()
	{
		Release();
	}

public:
	bool Init(const char* file_path, const char* target_path, const char* url_path, const char* match_text, int thread_count)
	{
		if (file_path == nullptr || url_path == nullptr || match_text == nullptr) return false;

		// open src file
		auto* file = CarpRWops::OpenFile(file_path, "rb", false);
		if (file == nullptr) return false;

		Release();

		// define buffer, read and write
		char buff[1024];
		std::string content;
		m_url_list.reserve(1000000);
		do
		{
			size_t read_size = SDL_RWread(file, buff, 1, sizeof(buff));
			if (read_size == 0) break;
			content.append(buff, read_size);

			do
			{
				auto pos_1 = content.find("\r\n");
				if (pos_1 != std::string::npos)
				{
					m_url_list.emplace_back(content.substr(0, pos_1));
					content = content.substr(pos_1 + 2);
				}
				else
				{
					auto pos_2 = content.find("\n");
					if (pos_2 != std::string::npos)
					{
						m_url_list.emplace_back(content.substr(0, pos_2));
						content = content.substr(pos_2 + 1);
					}
					else
					{
						break;
					}
				}
			} while (true);

		} while (true);

		if (!content.empty())
			m_url_list.emplace_back(content);

		// close file
		SDL_RWclose(file);

		if (m_url_list.empty()) return false;

		if (thread_count <= 0) thread_count = 1;

		m_target_file = CarpRWops::OpenFile(target_path, "wb", false);

		if (m_url_list.size() < thread_count)
			thread_count = static_cast<int>(m_url_list.size());

		size_t split_count = m_url_list.size() / thread_count;

		for (int i = 0; i < thread_count; ++i)
		{
			size_t start = i * split_count;
			size_t end = start + split_count;
			if (end > m_url_list.size()) end = m_url_list.size();
			auto* schedule = new BlackSeoSchedule;
			schedule->Start(start, end, &m_url_list, url_path, match_text);
			m_schedule_list.push_back(schedule);
		}

		return true;
	}

	void Release()
	{
		m_url_list.resize(0);
		for (auto& schedule : m_schedule_list)
		{
			schedule->Exit();
			delete schedule;
		}	
		m_schedule_list.resize(0);

		WriteToFile();

		if (m_target_file)
		{
			SDL_RWclose(m_target_file);
			m_target_file = nullptr;
		}
	}

	bool IsComplete()
	{
		for (auto schedule : m_schedule_list)
		{
			if (!schedule->IsCompleted()) return false;
		}

		return true;
	}

	int GetFailedCount()
	{
		int count = 0;

		for (auto schedule : m_schedule_list)
			count += schedule->GetFailedCount();

		return count;
	}

	int GetSucceedCount()
	{
		int count = 0;

		for (auto schedule : m_schedule_list)
			count += schedule->GetSucceedCount();

		return count;
	}

	size_t GetTotalCount()
	{
		return m_url_list.size();
	}

	void WriteToFile()
	{
		if (m_target_file == nullptr) return;

		std::set<std::string> out;
		bool has_content = false;
		for (auto schedule : m_schedule_list)
		{
			schedule->GetMatchSet(out);
			for (auto& value : out)
			{
				SDL_RWwrite(m_target_file, value.c_str(), 1, value.size());
				SDL_RWwrite(m_target_file, "\n", 1, 1);
				has_content = true;
			}
			out.clear();
		}
		if (has_content)
			std::fflush(m_target_file);
	}

private:
	std::vector<std::string> m_url_list;
	FILE* m_target_file = nullptr;

private:
	std::vector<BlackSeoSchedule*> m_schedule_list;
};

class BlackSeoBind
{
public:
	static void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.beginNamespace("blackseo")
			.beginClass<BlackSeo>("BlackSeo")
			.addConstructor<void(*)()>()
			.addFunction("Init", &BlackSeo::Init)
			.addFunction("Release", &BlackSeo::Release)
			.addFunction("IsComplete", &BlackSeo::IsComplete)
			.addFunction("GetTotalCount", &BlackSeo::GetTotalCount)
			.addFunction("GetFailedCount", &BlackSeo::GetFailedCount)
			.addFunction("GetSucceedCount", &BlackSeo::GetSucceedCount)
			.addFunction("WriteToFile", &BlackSeo::WriteToFile)
			.endClass()
			.endNamespace();
	}
};

int luaopen_blackseo(lua_State* l_state) {
	BlackSeoBind::Bind(l_state);
    lua_getglobal(l_state, "blackseo");
    return 1;
}
