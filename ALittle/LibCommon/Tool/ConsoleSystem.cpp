
#ifdef _WIN32

#include "ConsoleSystem.h"
#include "ALittle/LibCommon/Helper/LogHelper.h"
#include "ALittle/LibCommon/Helper/StringHelper.h"

#include <Windows.h>

namespace ALittle
{

ConsoleSystem& ConsoleSystem::Instance()
{
    static ConsoleSystem instance;
    return instance;
}

ConsoleSystem::ConsoleSystem()
    : m_thread(nullptr), m_run(false)
{
}

ConsoleSystem::~ConsoleSystem()
{
    Shutdown();
}

void ConsoleSystem::Setup(const std::string& title, std::function<void(const std::string&, const std::string&)> func
    , std::function<void()> exit, std::function<void()> list)
{
    if (m_thread != nullptr) return;

    m_run = true;
    m_thread = new std::thread(ConsoleSystem::Run, this);
    m_title = title;
    m_handle = func;
    m_exit = exit;
    m_list = list;
}

void ConsoleSystem::Shutdown()
{
    if (m_thread == nullptr) return;

    m_run = false;
    HANDLE std_in = GetStdHandle(STD_INPUT_HANDLE);
    if (std_in != INVALID_HANDLE_VALUE && std_in != NULL) {
        INPUT_RECORD record;
        record.EventType = KEY_EVENT;
        record.Event.KeyEvent.bKeyDown = true;
        record.Event.KeyEvent.uChar.AsciiChar = 0;
        DWORD count;
        WriteConsoleInput(std_in, &record, 1, &count);
    }

    m_thread->join();
    delete m_thread;
    m_thread = 0;
}

int ConsoleSystem::Run(ConsoleSystem* self)
{
    // Get the standard input handle. 
    HANDLE std_in = GetStdHandle(STD_INPUT_HANDLE);
    if (std_in == INVALID_HANDLE_VALUE)
    {
        ALITTLE_ERROR("GetStdHandle(STD_INPUT_HANDLE) failed!");
        return 0;
    }

    if (std_in == NULL) return 0;

    INPUT_RECORD irInBuf[128];
    DWORD cNumRead;
    std::string cmd;

    while (self->m_run)
    {
        if (!ReadConsoleInput(
            std_in,      // input buffer handle 
            irInBuf,     // buffer to read into 
            128,         // size of read buffer 
            &cNumRead)) // number of records read
        {
            ALITTLE_ERROR("ReadConsoleInput failed!");
            return 0;
        }

        for (DWORD i = 0; i < cNumRead; ++i)
        {
            if (irInBuf[i].EventType != KEY_EVENT) continue;

            KEY_EVENT_RECORD& ker = irInBuf[i].Event.KeyEvent;
            if (!ker.bKeyDown) continue;
            if (ker.uChar.AsciiChar == 0) continue;

            if (ker.uChar.AsciiChar == 8)
            {
                if (cmd.empty()) continue;
                if (cmd.back() > 0)
                    cmd.pop_back();
                else
                {
                    cmd.pop_back();
                    if (!cmd.empty()) cmd.pop_back();
                }
            }
            else if (ker.uChar.AsciiChar == '\r'
                || ker.uChar.AsciiChar == '\n')
            {
                if (cmd.empty()) continue;

                std::string cmd_utf8 = StringHelper::ANSI2UTF8(cmd.c_str());
                self->HandleCmd(cmd);
                cmd.clear();
            }
            else
            {
                cmd.push_back(ker.uChar.AsciiChar);
            }

            if (cmd.size())
            {
                std::string cmd_utf8 = StringHelper::ANSI2UTF8(cmd.c_str());
                cmd_utf8 = self->m_title + ":" + cmd_utf8;
                std::string cmd_gbk = StringHelper::UTF82ANSI(cmd_utf8.c_str());
                ::SetConsoleTitle(cmd_gbk.c_str());
            }
            else
                ::SetConsoleTitle(self->m_title.c_str());
        }
    }

    return 0;
}

void ConsoleSystem::HandleCmd(std::string& cmd)
{
    StringHelper::TrimLeft(cmd);
    StringHelper::TrimRight(cmd);
    if (cmd.empty()) return;

    std::string upper_cmd = cmd;
    StringHelper::UpperString(upper_cmd);
    if (m_exit && upper_cmd == "EXIT")
    {
        m_exit();
        return;
    }

    if (m_list && upper_cmd == "HELP")
    {
        m_list();
        return;
    }

    std::string::size_type module_pos = cmd.find(' ');
    if (module_pos == 0)
    {
        ALITTLE_WARN(u8"没有输入模块名");
        return;
    }
    if (module_pos == std::string::npos)
    {
        ALITTLE_WARN(u8"没有输入任何指令，指令格式为: 模块名 指令名 指令参数");
        return;
    }
    std::string module_name = cmd.substr(0, module_pos);
    std::string cmd_content = cmd.substr(module_pos + 1);
    StringHelper::TrimLeft(cmd_content);
    StringHelper::TrimRight(cmd_content);

    if (m_handle)
        m_handle(module_name, cmd_content);
}

} // ALittle

#endif