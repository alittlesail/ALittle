#ifndef CARP_LOG_INCLUDED
#define CARP_LOG_INCLUDED

typedef struct
{
	
} _log_t;
static _log_t _log = {0};

void carp_log_setup()
{

}

void carp_log_info()
{

    HANDLE hfile = NULL;
    time_t tt;
    struct tm st = { 0 };
    char sztime[32] = { 0 };
    int ret = 0;
    DWORD dw_bytes_written = 0;

    time(&tt);
    ret = localtime_s(&st, &tt);
    if (ret != 0) return;

    ret = sprintf_s(sztime, sizeof(sztime), "%04d-%02d-%02d %02d:%02d:%02d ",
        st.tm_year + 1900, st.tm_mon + 1, st.tm_mday, st.tm_hour, st.tm_min, st.tm_sec);
    if (ret == -1) return;

    hfile = CreateFileA(file_path, FILE_APPEND_DATA, 0, NULL, OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (hfile == INVALID_HANDLE_VALUE) return;

    WriteFile(hfile, sztime, ret, &dw_bytes_written, NULL);
    WriteFile(hfile, log_content, (DWORD)(log_len), &dw_bytes_written, NULL);
    WriteFile(hfile, "\r\n", 2, &dw_bytes_written, NULL);
    CloseHandle(hfile);
}

void carp_log_shutdown()
{
	
}

#endif