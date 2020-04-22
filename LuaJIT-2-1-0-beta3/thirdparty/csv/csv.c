    
#include "csv.h"
#include <stdio.h>
#include <stdlib.h>

csv* csv_create()
{
    csv* c = (csv*)malloc(sizeof(csv));
    csv_init(c);
    return c;
}

void csv_init(csv* c)
{
    c->path = 0;
    kv_init(c->data);
    c->col_count = 0;
}

void csv_destroy(csv* c)
{
    csv_clear(c);
    free(c);
}

void csv_clear(csv* c)
{
    if (c->path)
    {
        if (c->path->s) free(c->path->s);
        free(c->path);
        c->path = 0;
    }

    for (int row = 0; row < kv_size(c->data); ++row)
    {
        csvrow* rowdata = kv_A(c->data, row);
        for (int col = 0; col < kv_size(*rowdata); ++col)
        {
            kstring_t* data = kv_A(*rowdata, col);
            if (data)
            {
                if (data->s) free(data->s);
                free(data);
            }
        }
        kv_destroy(*rowdata);
        free(rowdata);
    }
    kv_destroy(c->data);
    kv_init(c->data);
    c->col_count = 0;
}

#define END_OF_FILE 0

int csv_addrow(csv* c, csvrow* rowdata, kstring_t* error)
{
    if (c->col_count == 0)
    {
        c->col_count = (int)kv_size(*rowdata);
        kv_push(csvrow*, c->data, rowdata);
        return 1;
    }

    if (kv_size(*rowdata) != c->col_count)
    {
        if (error) ksprintf(error, "row(%d) col(%d) != %d:%s", (int)kv_size(c->data) + 1, kv_size(*rowdata), c->col_count, c->path->s);
        return 0;
    }

    kv_push(csvrow*, c->data, rowdata);
    return 1;
}

size_t csv_std_fread(void* buffer, size_t element_size, size_t count, void* file)
{
    return fread(buffer, element_size, count, (FILE*)file);
}

int csv_std_load(csv* c, const char* path, kstring_t* error)
{
    FILE* file = 0;
#ifdef _WIN32
    fopen_s(&file, path, "rb");
#else
    file = fopen(path, "rb");
#endif
    if (file == 0)
    {
        if (error) ksprintf(error, "file open failed:%s", path);
        return 0;
    }

    int result = csv_load(c, path, csv_std_fread, file, error);

    fclose(file);
    return result;
}

int csv_load(csv* c, const char* path, csv_fread func_read, void* file, kstring_t* error)
{
    // 读取第一个字符
    char cur_char = END_OF_FILE;
    size_t size = func_read(&cur_char, 1, 1, file);
    if (size == 0)
    {
        if (error) ksprintf(error, "file is empty:%s", path);
        return 0;
    }
    if (cur_char == 0)
    {
        if (error) ksprintf(error, "row(1) has char is 0:%s", path);
        return 0;
    }

    // 设置路径
    if (c->path == 0) c->path = (kstring_t*)calloc(1, sizeof(kstring_t));
    kputs(path, c->path);

    // 读取下一个字符
    char next_char = 0;
    size = func_read(&next_char, 1, 1, file);
    if (size == 0)
    {
        // 构建字符串
        kstring_t* data = (kstring_t*)calloc(1, sizeof(kstring_t));
        kputc(cur_char, data);
        
        // 构建行数据
        csvrow* rowdata = (csvrow*)malloc(sizeof(csvrow));
        kv_init(*rowdata);
        kv_push(kstring_t*, *rowdata, data);

        // 添加到总数据
        kv_push(csvrow*, c->data, rowdata);

        return 1;
    }

    if (next_char == 0)
    {
        if (error) ksprintf(error, "row(1) has char is 0:%s", path);
        return 0;
    }

    // 结果
    int result = 1;

    // 标记当前是否在引号中
    int in_quote = 0;

    // 当前行数据
    csvrow* row = (csvrow*)malloc(sizeof(csvrow));
    kv_init(*row);
    // 当前列数据
    kstring_t* cell = (kstring_t*)calloc(1, sizeof(kstring_t));

    while (1) {
        // 如果是分隔符
        if (cur_char == ',')
        {
            // 如果在引号中，那么就要添加到当前的字符
            if (in_quote)
            {
                // 添加到列
                kputc(cur_char, cell);

                // 如果后面没有数据了，说明没有关闭引号，报错
                if (next_char == END_OF_FILE)
                {
                    if (error) ksprintf(error, "row(%d) have no close quote:%s", (int)kv_size(c->data), path);
                    result = 0;
                    break;
                }
            }
            // 如果没有在引号中，那么就要做切割
            else
            {
                // 添加到行
                kv_push(kstring_t*, *row, cell);
                cell = (kstring_t*)calloc(1, sizeof(kstring_t));

                // 如果后面没有数据了
                if (next_char == END_OF_FILE)
                {
                    // 再塞一个空列
                    kv_push(kstring_t*, *row, (kstring_t*)calloc(1, sizeof(kstring_t)));
                    // 添加到表
                    if (!csv_addrow(c, row, error))
                    {
                        result = 0;
                        break;
                    }
                    // 构建一个新的
                    row = (csvrow*)malloc(sizeof(csvrow));
                    kv_init(*row);
                }
            }
        }
        // 如果是换行
        else if (cur_char == '\n')
        {
            // 如果在引号中，那么就要添加到当前的字符
            if (in_quote)
            {
                // 添加到列
                kputc(cur_char, cell);

                // 如果后面没有数据了，说明没有关闭引号，报错
                if (next_char == END_OF_FILE)
                {
                    if (error) ksprintf(error, "row(%d) have no close quote:%s", (int)kv_size(c->data), path);
                    result = 0;
                    break;
                }
            }
            // 如果没有在引号中，那么就要做切割
            else
            {
                // 添加到行
                kv_push(kstring_t*, *row, cell);
                cell = (kstring_t*)calloc(1, sizeof(kstring_t));

                // 添加到表
                if (!csv_addrow(c, row, error))
                {
                    result = 0;
                    break;
                }
                // 构建一个新的
                row = (csvrow*)malloc(sizeof(csvrow));
                kv_init(*row);
            }
        }
        // 如果是引号
        else if (cur_char == '"')
        {
            // 如果在引号中
            if (in_quote)
            {
                // 如果下一个也是引号，那么当前直接转义为引号
                if (next_char == '"')
                {
                    // 添加到列
                    kputc('"', cell);
                    // 直接读取下一个字符
                    next_char = END_OF_FILE;
                    func_read(&next_char, 1, 1, file);
                    // 如果后面没有数据了，说明没有关闭引号，报错
                    if (next_char == END_OF_FILE)
                    {
                        if (error) ksprintf(error, "row(%d) have no close quote:%s", (int)kv_size(c->data), path);
                        result = 0;
                        break;
                    }
                }
                // 如果下一个不是引号，那么就关闭引号
                else
                {
                    in_quote = 0;

                    if (next_char == END_OF_FILE)
                    {
                        // 添加到行
                        kv_push(kstring_t*, *row, cell);
                        cell = (kstring_t*)calloc(1, sizeof(kstring_t));

                        // 添加到表
                        if (!csv_addrow(c, row, error))
                        {
                            result = 0;
                            break;
                        }
                        // 构建一个新的
                        row = (csvrow*)malloc(sizeof(csvrow));
                        kv_init(*row);
                    }
                }
            }
            // 不在引号中，直接标记为在引号中
            else
            {
                // 如果当前列是空的，那么就标记引号开始
                if (ks_len(cell) == 0)
                {
                    in_quote = 1;
                }
                // 如果当前已经有数据了，那么直接当做普通字符
                else
                {
                    kputc(cur_char, cell);
                }

                // 如果后面没有数据了，说明没有关闭引号，报错
                if (next_char == END_OF_FILE)
                {
                    if (error) ksprintf(error, "row(%d) have no close quote:%s", (int)kv_size(c->data), path);
                    result = 0;
                    break;
                }
            }
        }
        // 其他字符直接添加
        else
        {
            if (in_quote)
            {
                // 无条件添加字符
                kputc(cur_char, cell);

                // 如果后面没有数据了，说明没有关闭引号，报错
                if (next_char == END_OF_FILE)
                {
                    if (error) ksprintf(error, "row(%d) have no close quote:%s", (int)kv_size(c->data), path);
                    result = 0;
                    break;
                }
            }
            else
            {
                // 添加到列
                if (!(cur_char == '\r' && next_char == '\n')) {
                    kputc(cur_char, cell);
                }

                // 如果后面没有数据了
                if (next_char == END_OF_FILE) {
                    // 添加到行
                    kv_push(kstring_t*, *row, cell);
                    cell = (kstring_t*)calloc(1, sizeof(kstring_t));

                    // 添加到表
                    if (!csv_addrow(c, row, error))
                    {
                        result = 0;
                        break;
                    }
                    // 构建一个新的
                    row = (csvrow*)malloc(sizeof(csvrow));
                    kv_init(*row);
                }
            }

        }

        // 如果没有下个字符了，说明结束了
        if (next_char == END_OF_FILE) {
            break;
        }

        // 读取下一个字符
        cur_char = next_char;
        next_char = END_OF_FILE;
        func_read(&next_char, 1, 1, file);
    }

    if (cell)
    {
        if (cell->s) free(cell->s);
        free(cell);
    }

    if (row)
    {
        for (int col = 0; col < kv_size(*row); ++col)
        {
            kstring_t* data = kv_A(*row, col);
            if (data)
            {
                if (data->s) free(data->s);
                free(data);
            }
        }
        kv_destroy(*row);
        free(row);
    }

    return result;
}

const char* csv_getpath(csv* c)
{
    if (c->path == 0) return 0;
    return ks_str(c->path);
}

const char* csv_readcell(csv* c, int row, int col)
{
    if (row >= kv_size(c->data)) return 0;
    csvrow* rowdata = kv_A(c->data, row);
    if (rowdata == 0) return 0;
    if (col >= kv_size(*rowdata)) return 0;
    kstring_t* cell = kv_A(*rowdata, col);
    if (cell == 0) return 0;
    return ks_str(cell);
}

int csv_rowcount(csv* c)
{
    return (int)kv_size(c->data);
}

int csv_colcount(csv* c)
{
    return c->col_count;
}
