
#ifdef _WIN32

// øÿ÷∆Ã®√¸¡Ó

#ifndef _ALITTLE_CONSOLESYSTEM_H_
#define _ALITTLE_CONSOLESYSTEM_H_

#include <thread>
#include <map>
#include <string>
#include <functional>

namespace ALittle
{

class ConsoleSystem
{
public:
    static ConsoleSystem& Instance();

private:
    ConsoleSystem();
    ~ConsoleSystem();

public:
    void Setup(const std::string& title, std::function<void(const std::string&, const std::string&)> func
        , std::function<void()> exit, std::function<void()> list);
    void Shutdown();

private:
    static int Run(ConsoleSystem* self);
    void HandleCmd(std::string& cmd);

private:
    std::thread* m_thread;
    volatile bool m_run;

private:
    std::string m_title;
    std::function<void()> m_exit;
    std::function<void()> m_list;
    std::function<void(const std::string&, const std::string&)> m_handle;
};

} // ALittle

#define g_ConsoleSystem ALittle::ConsoleSystem::Instance()

#endif // _ALITTLE_CONSOLESYSTEM_H_

#endif