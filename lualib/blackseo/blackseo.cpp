
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
#include <deque>

class BlackSeoInterface
{
public:
	virtual ~BlackSeoInterface() {}

public:
	virtual void PullUrl(std::vector<std::string>& out, size_t count) = 0;
};

class BlackSeoSchedule : public CarpSchedule
{
public:
	void Start(BlackSeoInterface* blackseo, const std::string& url_path
		, const std::string& match_text, bool complete_match, bool collect_error
		, bool output_use_src_url, bool debug_use_src_url)
	{
		m_blackseo = blackseo;
		m_url_path = url_path;
		m_match_text = match_text;
		m_collect_error = collect_error;
		m_output_use_src_url = output_use_src_url;
		m_debug_use_src_url = debug_use_src_url;

		// 启动
		Run(true, std::bind(&BlackSeoSchedule::Setup, this), std::bind(&BlackSeoSchedule::Shutdown, this));

		// 执行下一个
		for (int i = 0; i < 100; ++i)
			Execute(std::bind(&BlackSeoSchedule::NextOne, this));
	}

	void GetMatchSet(std::set<std::string>& result)
	{
		m_match_lock.lock();
		m_match_set.swap(result);
		m_match_lock.unlock();
	}

	void GetErrorSet(std::set<std::string>& result)
	{
		m_error_lock.lock();
		m_error_set.swap(result);
		m_error_lock.unlock();
	}

	void ClearTimeOut(int seconds)
	{
		Execute(std::bind(&BlackSeoSchedule::ClearTimeOutImpl, this, seconds));
	}

	bool IsCompleted()
	{
		return m_completed && m_stat_info_map.empty();
	}
	int GetFailedCount() const { return m_match_failed; }
	int GetSucceedCount() const { return m_match_succeed; }

	void ExitWhileCompleted()
	{
		if (!IsCompleted()) return;
		Exit();
	}

private:
	void ClearTimeOutImpl(int seconds)
	{
		std::list<CarpHttpClientTextPtr> client_list;
		auto cur_time = time(0);
		for (auto& pair : m_stat_info_map)
		{
			if (cur_time - pair.second.begin_time >= seconds)
			{
				// printf("Stop %s\n", pair.second.url.c_str());
				pair.second.stopped = true;
				client_list.push_back(pair.second.client);
			}
		}

		for (auto& client : client_list)
			client->Stop();
	}

	void NextOne()
	{
		if (m_url_list.empty())
			m_blackseo->PullUrl(m_url_list, 10);

		if (m_url_list.empty())
		{
			m_completed = true;
			return;
		}

		std::string url;
		{
			auto& back = m_url_list.back();
			if (back.find("http://") == 0)
				url = back + m_url_path;
			else
				url = "http://" + back + m_url_path;
			m_url_list.pop_back();
		}

		auto client = std::make_shared<CarpHttpClientText>();

		m_stat_id++;
		m_stat_info_map[m_stat_id].url = url;
		m_stat_info_map[m_stat_id].begin_time = time(0);
		m_stat_info_map[m_stat_id].client = client;

		client->SendRequest(url, true, "application/json", "", 0
			, std::bind(&BlackSeoSchedule::HandleHttpResult, this
				, std::placeholders::_1, std::placeholders::_2
				, std::placeholders::_3, std::placeholders::_4
				, 0, url, url, m_stat_id)
			, nullptr, &GetIOService(), "", 0, "");
	}

	void HandleHttpResult(bool result, const std::string& body, const std::string& head, const std::string& error
		, int location, const std::string& cur_url, const std::string& src_url, int id)
	{
		/*auto it = m_stat_info_map.find(id);
		if (it != m_stat_info_map.end())
		{
			if (it->second.stopped)
				printf("HandleHttpResult %s\n", it->second.url.c_str());
			m_stat_info_map.erase(it);
		}*/
		m_stat_info_map.erase(id);

		auto copy_head = head;
		CarpString::UpperString(copy_head);
		auto location_pos = copy_head.find("LOCATION:");
		if (location_pos != std::string::npos && location < 10)
		{
			location_pos += strlen("LOCATION:");

			auto location_end = copy_head.find("\r\n", location_pos);
			if (location_end != std::string::npos)
			{
				auto new_url = head.substr(location_pos, location_end - location_pos);
				CarpString::TrimLeft(new_url);
				CarpString::TrimRight(new_url);

				if (new_url.find("https") == 0)
				{
					auto pos_443 = new_url.find(":443");
					if (pos_443 != std::string::npos)
						new_url = new_url.substr(0, pos_443) + new_url.substr(pos_443 + strlen(":443"));
				}
				else if (new_url.find("http") == 0)
				{
					auto pos_80 = new_url.find(":80");
					if (pos_80 != std::string::npos)
						new_url = new_url.substr(0, pos_80) + new_url.substr(pos_80 + strlen(":80"));
				}

				auto client = std::make_shared<CarpHttpClientText>();

				m_stat_id++;
				m_stat_info_map[m_stat_id].url = new_url;
				m_stat_info_map[m_stat_id].begin_time = time(0);
				m_stat_info_map[m_stat_id].client = client;

				client->SendRequest(new_url, true, "application/json", "", 0
					, std::bind(&BlackSeoSchedule::HandleHttpResult, this
						, std::placeholders::_1, std::placeholders::_2
						, std::placeholders::_3, std::placeholders::_4
						, location + 1, new_url, src_url, m_stat_id)
					, nullptr, &GetIOService(), "", 0, "");
				return;
			}
		}

		if (head.empty())
		{
			m_match_failed += 1;
			if (m_collect_error)
			{
				m_error_lock.lock();
				if (m_debug_use_src_url)
					m_error_set.insert(src_url + ", error:" + error);
				else
					m_error_set.insert(cur_url + ", error:" + error);
				m_error_lock.unlock();
			}
		}
		else
		{
			if (m_complete_match)
			{
				if (body != m_match_text)
				{
					m_match_failed += 1;
				}
				else
				{
					m_match_succeed += 1;

					m_match_lock.lock();
					if (m_output_use_src_url)
						m_match_set.insert(src_url);
					else
						m_match_set.insert(cur_url);
					m_match_lock.unlock();
				}
			}
			else
			{
				auto pos = body.find(m_match_text);
				if (pos == std::string::npos)
				{
					m_match_failed += 1;
				}
				else
				{
					m_match_succeed += 1;

					m_match_lock.lock();
					if (m_output_use_src_url)
						m_match_set.insert(src_url);
					else
						m_match_set.insert(cur_url);
					m_match_lock.unlock();
				}
			}
		}

		NextOne();
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
	std::mutex m_error_lock;
	std::set<std::string> m_error_set;

private:
	bool m_completed = false;
	std::string m_url_path;
	std::string m_match_text;
	bool m_complete_match = false;
	bool m_collect_error = false;

private:
	bool m_output_use_src_url = false;
	bool m_debug_use_src_url = true;

private:
	std::vector<std::string> m_url_list;
	BlackSeoInterface* m_blackseo = nullptr;

private:
	struct StatInfo
	{
		CarpHttpClientTextPtr client;
		std::string url;
		time_t begin_time = 0;
		bool stopped = false;
	};
	std::map<int, StatInfo> m_stat_info_map;
	int m_stat_id = 0;
};

class BlackSeo : public BlackSeoInterface
{
public:
	~BlackSeo()
	{
		Release();
	}

public:
	void UseSrcUrl(bool output_use_src_url, bool debug_use_src_url)
	{
		m_output_use_src_url = output_use_src_url;
		m_debug_use_src_url = debug_use_src_url;
	}

public:
	bool Init(const char* file_path, int start_line, const char* target_path
		, const char* url_path, const char* match_text, int thread_count
		, bool complete_match, const char* error_path)
	{
		if (file_path == nullptr || url_path == nullptr || match_text == nullptr) return false;

		// open src file
		auto* file = CarpRWops::OpenFile(file_path, "rb", false);
		if (file == nullptr) return false;

		Release();

		// define buffer, read and write
		char buff[1024];
		std::string content;
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
					if (start_line <= 0)
						m_url_list.emplace_back(content.substr(0, pos_1));
					else
						start_line -= 1;
					content = content.substr(pos_1 + 2);
				}
				else
				{
					auto pos_2 = content.find("\n");
					if (pos_2 != std::string::npos)
					{
						if (start_line <= 0)
							m_url_list.emplace_back(content.substr(0, pos_2));
						else
							start_line -= 1;
						content = content.substr(pos_2 + 1);
					}
					else
					{
						break;
					}
				}
			} while (true);

		} while (true);

		if (!content.empty() && start_line <= 0) m_url_list.emplace_back(content);

		// close file
		SDL_RWclose(file);

		if (m_url_list.empty()) return false;

		m_total_count = m_url_list.size();
		if (thread_count <= 0) thread_count = 1;

		m_target_file = CarpRWops::OpenFile(target_path, "wb", false);
		if (error_path != nullptr)
			m_error_file = CarpRWops::OpenFile(error_path, "wb", false);

		if (m_url_list.size() < thread_count)
			thread_count = static_cast<int>(m_url_list.size());

		size_t split_count = m_url_list.size() / thread_count;

		for (int i = 0; i < thread_count; ++i)
		{
			auto* schedule = new BlackSeoSchedule;
			schedule->Start(this, url_path, match_text, complete_match, m_error_file != nullptr
				, m_output_use_src_url, m_debug_use_src_url);
			m_schedule_list.push_back(schedule);
		}

		return true;
	}

	void Release()
	{
		m_url_list.resize(0);
		m_total_count = 0;
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

		if (m_error_file)
		{
			SDL_RWclose(m_error_file);
			m_error_file = nullptr;
		}
	}

	bool IsComplete()
	{
		for (auto schedule : m_schedule_list)
		{
			if (!schedule->IsCompleted())
				return false;
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
		return m_total_count;
	}

	void WriteToFile()
	{
		if (m_target_file != nullptr)
		{
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

		if (m_error_file != nullptr)
		{
			std::set<std::string> out;
			bool has_content = false;
			for (auto schedule : m_schedule_list)
			{
				schedule->GetErrorSet(out);
				for (auto& value : out)
				{
					SDL_RWwrite(m_error_file, value.c_str(), 1, value.size());
					SDL_RWwrite(m_error_file, "\n", 1, 1);
					has_content = true;
				}
				out.clear();
			}
			if (has_content)
				std::fflush(m_error_file);
		}

		for (auto schedule : m_schedule_list)
		{
			schedule->ClearTimeOut(10 * 60);
			schedule->ExitWhileCompleted();
		}
	}

	void PullUrl(std::vector<std::string>& out, size_t count) override
	{
		m_url_lock.lock();
		while (count > 0 && !m_url_list.empty())
		{
			out.emplace_back(std::move(m_url_list.front()));
			m_url_list.pop_front();
			--count;
		}
		m_url_lock.unlock();
	}

private:
	std::mutex m_url_lock;
	std::deque<std::string> m_url_list;
	size_t m_total_count = 0;
	FILE* m_target_file = nullptr;
	FILE* m_error_file = nullptr;

private:
	bool m_output_use_src_url = false;
	bool m_debug_use_src_url = true;

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
			.addFunction("UseSrcUrl", &BlackSeo::UseSrcUrl)
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
