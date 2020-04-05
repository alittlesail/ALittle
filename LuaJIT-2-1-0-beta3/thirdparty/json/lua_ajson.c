/* Lua AJSON - JSON support for Lua
 *
 * Copyright (c) 2010-2012  Mark Pulford <mark@kyne.com.au>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/* Caveats:
 * - JSON "null" values are represented as lightuserdata since Lua
 *   tables cannot contain "nil". Compare with ajson.null.
 * - Invalid UTF-8 characters are not detected and will be passed
 *   untouched. If required, UTF-8 error checking should be done
 *   outside this library.
 * - Javascript comments are not part of the JSON spec, and are not
 *   currently supported.
 *
 * Note: Decoding is slower than encoding. Lua spends significant
 *       time (30%) managing tables when parsing JSON since it is
 *       difficult to know object/array sizes ahead of time.
 */

#include <assert.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <ctype.h>

#include "../../src/lua.h"
#include "../../src/lualib.h"
#include "../../src/lauxlib.h"

#include "strbuf.h"
#include "fpconv.h"

#ifdef _WIN32
#pragma warning(disable:4996)
#endif

#ifndef AJSON_MODNAME
#define AJSON_MODNAME   "ajson"
#endif

#ifndef AJSON_VERSION
#define AJSON_VERSION   "2.1.0"
#endif

#include <float.h>  

#ifdef _WIN32
#define isnan(x) ((x) != (x))  
#define isinf(x) (!_finite(x) && !_isnan(x))  
#define strncasecmp  _strnicmp   
#endif

/* Workaround for Solaris platforms missing isinf() */
#if !defined(isinf) && (defined(USE_INTERNAL_ISINF) || defined(MISSING_ISINF))
#define isinf(x) (!isnan(x) && isnan((x) - (x)))
#endif

#define DEFAULT_SPARSE_CONVERT 0
#define DEFAULT_SPARSE_RATIO 2
#define DEFAULT_SPARSE_SAFE 10
#define DEFAULT_ENCODE_MAX_DEPTH 1000
#define DEFAULT_DECODE_MAX_DEPTH 1000
#define DEFAULT_ENCODE_INVALID_NUMBERS 0
#define DEFAULT_DECODE_INVALID_NUMBERS 1
#define DEFAULT_ENCODE_KEEP_BUFFER 1
#define DEFAULT_ENCODE_NUMBER_PRECISION 14

#ifdef DISABLE_INVALID_NUMBERS
#undef DEFAULT_DECODE_INVALID_NUMBERS
#define DEFAULT_DECODE_INVALID_NUMBERS 0
#endif

typedef enum {
    T_OBJ_BEGIN,
    T_OBJ_END,
    T_ARR_BEGIN,
    T_ARR_END,
    T_STRING,
    T_NUMBER,
    T_BOOLEAN,
    T_NULL,
    T_COLON,
    T_COMMA,
    T_END,
    T_WHITESPACE,
    T_ERROR,
    T_UNKNOWN
} ajson_token_type_t;

static const char *ajson_token_type_name[] = {
    "T_OBJ_BEGIN",
    "T_OBJ_END",
    "T_ARR_BEGIN",
    "T_ARR_END",
    "T_STRING",
    "T_NUMBER",
    "T_BOOLEAN",
    "T_NULL",
    "T_COLON",
    "T_COMMA",
    "T_END",
    "T_WHITESPACE",
    "T_ERROR",
    "T_UNKNOWN",
    NULL
};

typedef struct {
    ajson_token_type_t ch2token[256];
    char escape2char[256];  /* Decoding */

    /* encode_buf is only allocated and used when
     * encode_keep_buffer is set */
    strbuf_t encode_buf;

    int encode_sparse_convert;
    int encode_sparse_ratio;
    int encode_sparse_safe;
    int encode_max_depth;
    int encode_invalid_numbers;     /* 2 => Encode as "null" */
    int encode_number_precision;
    int encode_keep_buffer;

    int decode_invalid_numbers;
    int decode_max_depth;
} ajson_config_t;

typedef struct {
    const char *data;
    const char *ptr;
    strbuf_t *tmp;    /* Temporary storage for strings */
    ajson_config_t *cfg;
    int current_depth;
} ajson_parse_t;

typedef struct {
    ajson_token_type_t type;
    int index;
    union {
        const char *string;
        double number;
        int boolean;
    } value;
    int string_len;
} ajson_token_t;

static const char *char2escape[256] = {
    "\\u0000", "\\u0001", "\\u0002", "\\u0003",
    "\\u0004", "\\u0005", "\\u0006", "\\u0007",
    "\\b", "\\t", "\\n", "\\u000b",
    "\\f", "\\r", "\\u000e", "\\u000f",
    "\\u0010", "\\u0011", "\\u0012", "\\u0013",
    "\\u0014", "\\u0015", "\\u0016", "\\u0017",
    "\\u0018", "\\u0019", "\\u001a", "\\u001b",
    "\\u001c", "\\u001d", "\\u001e", "\\u001f",
    NULL, NULL, "\\\"", NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, "\\/",
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, "\\\\", NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, "\\u007f",
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
};

/* ===== CONFIGURATION ===== */

static ajson_config_t *ajson_fetch_config(lua_State *l)
{
    ajson_config_t *cfg;

    cfg = (ajson_config_t *)lua_touserdata(l, lua_upvalueindex(1));
    if (!cfg)
        luaL_error(l, "BUG: Unable to fetch AJSON configuration");

    return cfg;
}

/* Ensure the correct number of arguments have been provided.
 * Pad with nil to allow other functions to simply check arg[i]
 * to find whether an argument was provided */
static ajson_config_t *ajson_arg_init(lua_State *l, int args)
{
    luaL_argcheck(l, lua_gettop(l) <= args, args + 1,
                  "found too many arguments");

    while (lua_gettop(l) < args)
        lua_pushnil(l);

    return ajson_fetch_config(l);
}

/* Process integer options for configuration functions */
static int ajson_integer_option(lua_State *l, int optindex, int *setting,
                               int min, int max)
{
    char errmsg[64];
    int value;

    if (!lua_isnil(l, optindex)) {
        value =(int)(luaL_checkinteger(l, optindex));
#ifdef _WIN32
        _snprintf(errmsg, sizeof(errmsg), "expected integer between %d and %d", min, max);
#else
		snprintf(errmsg, sizeof(errmsg), "expected integer between %d and %d", min, max);
#endif
		luaL_argcheck(l, min <= value && value <= max, 1, errmsg);
        *setting = value;
    }

    lua_pushinteger(l, *setting);

    return 1;
}

/* Process enumerated arguments for a configuration function */
static int ajson_enum_option(lua_State *l, int optindex, int *setting,
                            const char **options, int bool_true)
{
    static const char *bool_options[] = { "off", "on", NULL };

    if (!options) {
        options = bool_options;
        bool_true = 1;
    }

    if (!lua_isnil(l, optindex)) {
        if (bool_true && lua_isboolean(l, optindex))
            *setting = lua_toboolean(l, optindex) * bool_true;
        else
            *setting = luaL_checkoption(l, optindex, NULL, options);
    }

    if (bool_true && (*setting == 0 || *setting == bool_true))
        lua_pushboolean(l, *setting);
    else
        lua_pushstring(l, options[*setting]);

    return 1;
}

/* Configures handling of extremely sparse arrays:
 * convert: Convert extremely sparse arrays into objects? Otherwise error.
 * ratio: 0: always allow sparse; 1: never allow sparse; >1: use ratio
 * safe: Always use an array when the max index <= safe */
static int ajson_cfg_encode_sparse_array(lua_State *l)
{
    ajson_config_t *cfg = ajson_arg_init(l, 3);

    ajson_enum_option(l, 1, &cfg->encode_sparse_convert, NULL, 1);
    ajson_integer_option(l, 2, &cfg->encode_sparse_ratio, 0, INT_MAX);
    ajson_integer_option(l, 3, &cfg->encode_sparse_safe, 0, INT_MAX);

    return 3;
}

/* Configures the maximum number of nested arrays/objects allowed when
 * encoding */
static int ajson_cfg_encode_max_depth(lua_State *l)
{
    ajson_config_t *cfg = ajson_arg_init(l, 1);

    return ajson_integer_option(l, 1, &cfg->encode_max_depth, 1, INT_MAX);
}

/* Configures the maximum number of nested arrays/objects allowed when
 * encoding */
static int ajson_cfg_decode_max_depth(lua_State *l)
{
    ajson_config_t *cfg = ajson_arg_init(l, 1);

    return ajson_integer_option(l, 1, &cfg->decode_max_depth, 1, INT_MAX);
}

/* Configures number precision when converting doubles to text */
static int ajson_cfg_encode_number_precision(lua_State *l)
{
    ajson_config_t *cfg = ajson_arg_init(l, 1);

    return ajson_integer_option(l, 1, &cfg->encode_number_precision, 1, 14);
}

/* Configures JSON encoding buffer persistence */
static int ajson_cfg_encode_keep_buffer(lua_State *l)
{
    ajson_config_t *cfg = ajson_arg_init(l, 1);
    int old_value;

    old_value = cfg->encode_keep_buffer;

    ajson_enum_option(l, 1, &cfg->encode_keep_buffer, NULL, 1);

    /* Init / free the buffer if the setting has changed */
    if (old_value ^ cfg->encode_keep_buffer) {
        if (cfg->encode_keep_buffer)
            strbuf_init(&cfg->encode_buf, 0);
        else
            strbuf_free(&cfg->encode_buf);
    }

    return 1;
}

#if defined(DISABLE_INVALID_NUMBERS) && !defined(USE_INTERNAL_FPCONV)
void ajson_verify_invalid_number_setting(lua_State *l, int *setting)
{
    if (*setting == 1) {
        *setting = 0;
        luaL_error(l, "Infinity, NaN, and/or hexadecimal numbers are not supported.");
    }
}
#else
#define ajson_verify_invalid_number_setting(l, s)    do { } while(0)
#endif

static int ajson_cfg_encode_invalid_numbers(lua_State *l)
{
    static const char *options[] = { "off", "on", "null", NULL };
    ajson_config_t *cfg = ajson_arg_init(l, 1);

    ajson_enum_option(l, 1, &cfg->encode_invalid_numbers, options, 1);

    ajson_verify_invalid_number_setting(l, &cfg->encode_invalid_numbers);

    return 1;
}

static int ajson_cfg_decode_invalid_numbers(lua_State *l)
{
    ajson_config_t *cfg = ajson_arg_init(l, 1);

    ajson_enum_option(l, 1, &cfg->decode_invalid_numbers, NULL, 1);

    ajson_verify_invalid_number_setting(l, &cfg->encode_invalid_numbers);

    return 1;
}

static int ajson_destroy_config(lua_State *l)
{
    ajson_config_t *cfg;

    cfg = (ajson_config_t *)lua_touserdata(l, 1);
    if (cfg)
        strbuf_free(&cfg->encode_buf);
    cfg = NULL;

    return 0;
}

static void ajson_create_config(lua_State *l)
{
    ajson_config_t *cfg;
    int i;

    cfg = (ajson_config_t *)lua_newuserdata(l, sizeof(*cfg));

    /* Create GC method to clean up strbuf */
    lua_newtable(l);
    lua_pushcfunction(l, ajson_destroy_config);
    lua_setfield(l, -2, "__gc");
    lua_setmetatable(l, -2);

    cfg->encode_sparse_convert = DEFAULT_SPARSE_CONVERT;
    cfg->encode_sparse_ratio = DEFAULT_SPARSE_RATIO;
    cfg->encode_sparse_safe = DEFAULT_SPARSE_SAFE;
    cfg->encode_max_depth = DEFAULT_ENCODE_MAX_DEPTH;
    cfg->decode_max_depth = DEFAULT_DECODE_MAX_DEPTH;
    cfg->encode_invalid_numbers = DEFAULT_ENCODE_INVALID_NUMBERS;
    cfg->decode_invalid_numbers = DEFAULT_DECODE_INVALID_NUMBERS;
    cfg->encode_keep_buffer = DEFAULT_ENCODE_KEEP_BUFFER;
    cfg->encode_number_precision = DEFAULT_ENCODE_NUMBER_PRECISION;

#if DEFAULT_ENCODE_KEEP_BUFFER > 0
    strbuf_init(&cfg->encode_buf, 0);
#endif

    /* Decoding init */

    /* Tag all characters as an error */
    for (i = 0; i < 256; i++)
        cfg->ch2token[i] = T_ERROR;

    /* Set tokens that require no further processing */
    cfg->ch2token['{'] = T_OBJ_BEGIN;
    cfg->ch2token['}'] = T_OBJ_END;
    cfg->ch2token['['] = T_ARR_BEGIN;
    cfg->ch2token[']'] = T_ARR_END;
    cfg->ch2token[','] = T_COMMA;
    cfg->ch2token[':'] = T_COLON;
    cfg->ch2token['\0'] = T_END;
    cfg->ch2token[' '] = T_WHITESPACE;
    cfg->ch2token['\t'] = T_WHITESPACE;
    cfg->ch2token['\n'] = T_WHITESPACE;
    cfg->ch2token['\r'] = T_WHITESPACE;

    /* Update characters that require further processing */
    cfg->ch2token['f'] = T_UNKNOWN;     /* false? */
    cfg->ch2token['i'] = T_UNKNOWN;     /* inf, ininity? */
    cfg->ch2token['I'] = T_UNKNOWN;
    cfg->ch2token['n'] = T_UNKNOWN;     /* null, nan? */
    cfg->ch2token['N'] = T_UNKNOWN;
    cfg->ch2token['t'] = T_UNKNOWN;     /* true? */
    cfg->ch2token['"'] = T_UNKNOWN;     /* string? */
    cfg->ch2token['+'] = T_UNKNOWN;     /* number? */
    cfg->ch2token['-'] = T_UNKNOWN;
    for (i = 0; i < 10; i++)
        cfg->ch2token['0' + i] = T_UNKNOWN;

    /* Lookup table for parsing escape characters */
    for (i = 0; i < 256; i++)
        cfg->escape2char[i] = 0;          /* String error */
    cfg->escape2char['"'] = '"';
    cfg->escape2char['\\'] = '\\';
    cfg->escape2char['/'] = '/';
    cfg->escape2char['b'] = '\b';
    cfg->escape2char['t'] = '\t';
    cfg->escape2char['n'] = '\n';
    cfg->escape2char['f'] = '\f';
    cfg->escape2char['r'] = '\r';
    cfg->escape2char['u'] = 'u';          /* Unicode parsing required */
}

/* ===== ENCODING ===== */

static void ajson_encode_exception(lua_State *l, ajson_config_t *cfg, strbuf_t *ajson, int lindex,
                                  const char *reason)
{
    if (!cfg->encode_keep_buffer)
        strbuf_free(ajson);
    luaL_error(l, "Cannot serialise %s: %s",
                  lua_typename(l, lua_type(l, lindex)), reason);
}

/* ajson_append_string args:
 * - lua_State
 * - JSON strbuf
 * - String (Lua stack index)
 *
 * Returns nothing. Doesn't remove string from Lua stack */
static void ajson_append_string(lua_State *l, strbuf_t *ajson, int lindex)
{
    const char *escstr;
    int i;
    const char *str;
    size_t len;

    str = lua_tolstring(l, lindex, &len);

    /* Worst case is len * 6 (all unicode escapes).
     * This buffer is reused constantly for small strings
     * If there are any excess pages, they won't be hit anyway.
     * This gains ~5% speedup. */
    strbuf_ensure_empty_length(ajson, (int)(len) * 6 + 2);

    strbuf_append_char_unsafe(ajson, '\"');
    for (i = 0; i < (int)len; i++) {
        escstr = char2escape[(unsigned char)str[i]];
        if (escstr)
            strbuf_append_string(ajson, escstr);
        else
            strbuf_append_char_unsafe(ajson, str[i]);
    }
    strbuf_append_char_unsafe(ajson, '\"');
}

/* Find the size of the array on the top of the Lua stack
 * -1   object (not a pure array)
 * >=0  elements in array
 */
static int lua_array_length(lua_State *l, ajson_config_t *cfg, strbuf_t *ajson)
{
    double k;
    int max;
    int items;

    max = 0;
    items = 0;

    lua_pushnil(l);
    /* table, startkey */
    while (lua_next(l, -2) != 0) {
        /* table, key, value */
        if (lua_type(l, -2) == LUA_TNUMBER &&
            (k = lua_tonumber(l, -2))) {
            /* Integer >= 1 ? */
            if (floor(k) == k && k >= 1) {
                if (k > max)
                    max = (int)k;
                items++;
                lua_pop(l, 1);
                continue;
            }
        }

        /* Must not be an array (non integer key) */
        lua_pop(l, 2);
        return -1;
    }

    /* Encode excessively sparse arrays as objects (if enabled) */
    if (cfg->encode_sparse_ratio > 0 &&
        max > items * cfg->encode_sparse_ratio &&
        max > cfg->encode_sparse_safe) {
        if (!cfg->encode_sparse_convert)
            ajson_encode_exception(l, cfg, ajson, -1, "excessively sparse array");

        return -1;
    }

    return max;
}

static void ajson_check_encode_depth(lua_State *l, ajson_config_t *cfg,
                                    int current_depth, strbuf_t *ajson)
{
    /* Ensure there are enough slots free to traverse a table (key,
     * value) and push a string for a potential error message.
     *
     * Unlike "decode", the key and value are still on the stack when
     * lua_checkstack() is called.  Hence an extra slot for luaL_error()
     * below is required just in case the next check to lua_checkstack()
     * fails.
     *
     * While this won't cause a crash due to the EXTRA_STACK reserve
     * slots, it would still be an improper use of the API. */
    if (current_depth <= cfg->encode_max_depth && lua_checkstack(l, 3))
        return;

    if (!cfg->encode_keep_buffer)
        strbuf_free(ajson);

    luaL_error(l, "Cannot serialise, excessive nesting (%d)",
               current_depth);
}

static void ajson_append_data(lua_State *l, ajson_config_t *cfg,
                             int current_depth, strbuf_t *ajson);

/* ajson_append_array args:
 * - lua_State
 * - JSON strbuf
 * - Size of passwd Lua array (top of stack) */
// ALITTLE 改动：array的序列化不需要了
// static void ajson_append_array(lua_State *l, ajson_config_t *cfg, int current_depth,
//                               strbuf_t *ajson, int array_length)
// {
//     int comma, i;
// 
//     strbuf_append_char(ajson, '[');
// 
//     comma = 0;
//     for (i = 1; i <= array_length; i++) {
//         if (comma)
//             strbuf_append_char(ajson, ',');
//         else
//             comma = 1;
// 
//         lua_rawgeti(l, -1, i);
//         ajson_append_data(l, cfg, current_depth, ajson);
//         lua_pop(l, 1);
//     }
// 
//     strbuf_append_char(ajson, ']');
// }

static void ajson_append_number(lua_State *l, ajson_config_t *cfg,
                               strbuf_t *ajson, int lindex)
{
    double num = lua_tonumber(l, lindex);
    int len;

    if (cfg->encode_invalid_numbers == 0) {
        /* Prevent encoding invalid numbers */
        if (isinf(num) || isnan(num))
            ajson_encode_exception(l, cfg, ajson, lindex, "must not be NaN or Inf");
    } else if (cfg->encode_invalid_numbers == 1) {
        /* Encode invalid numbers, but handle "nan" separately
         * since some platforms may encode as "-nan". */
        if (isnan(num)) {
            strbuf_append_mem(ajson, "nan", 3);
            return;
        }
    } else {
        /* Encode invalid numbers as "null" */
        if (isinf(num) || isnan(num)) {
            strbuf_append_mem(ajson, "null", 4);
            return;
        }
    }

    strbuf_ensure_empty_length(ajson, FPCONV_G_FMT_BUFSIZE);
    len = fpconv_g_fmt(strbuf_empty_ptr(ajson), num, cfg->encode_number_precision);
    strbuf_extend_length(ajson, len);
}

static void ajson_append_object(lua_State *l, ajson_config_t *cfg,
                               int current_depth, strbuf_t *ajson)
{
    int comma, keytype;

    /* Object */
    strbuf_append_char(ajson, '{');

    lua_pushnil(l);
    /* table, startkey */
    comma = 0;
    while (lua_next(l, -2) != 0) {
        if (comma)
            strbuf_append_char(ajson, ',');
        else
            comma = 1;

        /* table, key, value */
        keytype = lua_type(l, -2);
        if (keytype == LUA_TNUMBER) {
            // ALITTLE 改动：对于number不需要使用引号括起来
            // strbuf_append_char(ajson, '"');
			ajson_append_number(l, cfg, ajson, -2);
			// ALITTLE 改动：对于number不需要使用引号括起来
			// strbuf_append_mem(ajson, "\":", 2);
			strbuf_append_char(ajson, ':');
        } else if (keytype == LUA_TSTRING) {
            ajson_append_string(l, ajson, -2);
            strbuf_append_char(ajson, ':');
        } else {
            ajson_encode_exception(l, cfg, ajson, -2,
                                  "table key must be a number or string");
            /* never returns */
        }

        /* table, key, value */
        ajson_append_data(l, cfg, current_depth, ajson);
        lua_pop(l, 1);
        /* table, key */
    }

    strbuf_append_char(ajson, '}');
}

/* Serialise Lua data into JSON string. */
static void ajson_append_data(lua_State *l, ajson_config_t *cfg,
                             int current_depth, strbuf_t *ajson)
{
    // int len;

    switch (lua_type(l, -1)) {
    case LUA_TSTRING:
        ajson_append_string(l, ajson, -1);
        break;
    case LUA_TNUMBER:
        ajson_append_number(l, cfg, ajson, -1);
        break;
    case LUA_TBOOLEAN:
        if (lua_toboolean(l, -1))
            strbuf_append_mem(ajson, "true", 4);
        else
            strbuf_append_mem(ajson, "false", 5);
        break;
    case LUA_TTABLE:
        current_depth++;
        ajson_check_encode_depth(l, cfg, current_depth, ajson);
        // ALITTLE 改动，取消使用array，全部使用object
        // len = lua_array_length(l, cfg, ajson);
        // if (len > 0)
        //     ajson_append_array(l, cfg, current_depth, ajson, len);
        // else
            ajson_append_object(l, cfg, current_depth, ajson);
        break;
    case LUA_TNIL:
        strbuf_append_mem(ajson, "null", 4);
        break;
    case LUA_TLIGHTUSERDATA:
        if (lua_touserdata(l, -1) == NULL) {
            strbuf_append_mem(ajson, "null", 4);
            break;
        }
    default:
        /* Remaining types (LUA_TFUNCTION, LUA_TUSERDATA, LUA_TTHREAD,
         * and LUA_TLIGHTUSERDATA) cannot be serialised */
        ajson_encode_exception(l, cfg, ajson, -1, "type not supported");
        /* never returns */
    }
}

static int ajson_encode(lua_State *l)
{
    ajson_config_t *cfg = ajson_fetch_config(l);
    strbuf_t local_encode_buf;
    strbuf_t *encode_buf;
    char *ajson;
    int len;

    luaL_argcheck(l, lua_gettop(l) == 1, 1, "expected 1 argument");

    if (!cfg->encode_keep_buffer) {
        /* Use private buffer */
        encode_buf = &local_encode_buf;
        strbuf_init(encode_buf, 0);
    } else {
        /* Reuse existing buffer */
        encode_buf = &cfg->encode_buf;
        strbuf_reset(encode_buf);
    }

    ajson_append_data(l, cfg, 0, encode_buf);
    ajson = strbuf_string(encode_buf, &len);

    lua_pushlstring(l, ajson, len);

    if (!cfg->encode_keep_buffer)
        strbuf_free(encode_buf);

    return 1;
}

/* ===== DECODING ===== */

static void ajson_process_value(lua_State *l, ajson_parse_t *ajson,
                               ajson_token_t *token);

static int hexdigit2int(char hex)
{
    if ('0' <= hex  && hex <= '9')
        return hex - '0';

    /* Force lowercase */
    hex |= 0x20;
    if ('a' <= hex && hex <= 'f')
        return 10 + hex - 'a';

    return -1;
}

static int decode_hex4(const char *hex)
{
    int digit[4];
    int i;

    /* Convert ASCII hex digit to numeric digit
     * Note: this returns an error for invalid hex digits, including
     *       NULL */
    for (i = 0; i < 4; i++) {
        digit[i] = hexdigit2int(hex[i]);
        if (digit[i] < 0) {
            return -1;
        }
    }

    return (digit[0] << 12) +
           (digit[1] << 8) +
           (digit[2] << 4) +
            digit[3];
}

/* Converts a Unicode codepoint to UTF-8.
 * Returns UTF-8 string length, and up to 4 bytes in *utf8 */
static int codepoint_to_utf8(char *utf8, int codepoint)
{
    /* 0xxxxxxx */
    if (codepoint <= 0x7F) {
        utf8[0] = codepoint;
        return 1;
    }

    /* 110xxxxx 10xxxxxx */
    if (codepoint <= 0x7FF) {
        utf8[0] = (codepoint >> 6) | 0xC0;
        utf8[1] = (codepoint & 0x3F) | 0x80;
        return 2;
    }

    /* 1110xxxx 10xxxxxx 10xxxxxx */
    if (codepoint <= 0xFFFF) {
        utf8[0] = (codepoint >> 12) | 0xE0;
        utf8[1] = ((codepoint >> 6) & 0x3F) | 0x80;
        utf8[2] = (codepoint & 0x3F) | 0x80;
        return 3;
    }

    /* 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx */
    if (codepoint <= 0x1FFFFF) {
        utf8[0] = (codepoint >> 18) | 0xF0;
        utf8[1] = ((codepoint >> 12) & 0x3F) | 0x80;
        utf8[2] = ((codepoint >> 6) & 0x3F) | 0x80;
        utf8[3] = (codepoint & 0x3F) | 0x80;
        return 4;
    }

    return 0;
}


/* Called when index pointing to beginning of UTF-16 code escape: \uXXXX
 * \u is guaranteed to exist, but the remaining hex characters may be
 * missing.
 * Translate to UTF-8 and append to temporary token string.
 * Must advance index to the next character to be processed.
 * Returns: 0   success
 *          -1  error
 */
static int ajson_append_unicode_escape(ajson_parse_t *ajson)
{
    char utf8[4];       /* Surrogate pairs require 4 UTF-8 bytes */
    int codepoint;
    int surrogate_low;
    int len;
    int escape_len = 6;

    /* Fetch UTF-16 code unit */
    codepoint = decode_hex4(ajson->ptr + 2);
    if (codepoint < 0)
        return -1;

    /* UTF-16 surrogate pairs take the following 2 byte form:
     *      11011 x yyyyyyyyyy
     * When x = 0: y is the high 10 bits of the codepoint
     *      x = 1: y is the low 10 bits of the codepoint
     *
     * Check for a surrogate pair (high or low) */
    if ((codepoint & 0xF800) == 0xD800) {
        /* Error if the 1st surrogate is not high */
        if (codepoint & 0x400)
            return -1;

        /* Ensure the next code is a unicode escape */
        if (*(ajson->ptr + escape_len) != '\\' ||
            *(ajson->ptr + escape_len + 1) != 'u') {
            return -1;
        }

        /* Fetch the next codepoint */
        surrogate_low = decode_hex4(ajson->ptr + 2 + escape_len);
        if (surrogate_low < 0)
            return -1;

        /* Error if the 2nd code is not a low surrogate */
        if ((surrogate_low & 0xFC00) != 0xDC00)
            return -1;

        /* Calculate Unicode codepoint */
        codepoint = (codepoint & 0x3FF) << 10;
        surrogate_low &= 0x3FF;
        codepoint = (codepoint | surrogate_low) + 0x10000;
        escape_len = 12;
    }

    /* Convert codepoint to UTF-8 */
    len = codepoint_to_utf8(utf8, codepoint);
    if (!len)
        return -1;

    /* Append bytes and advance parse index */
    strbuf_append_mem_unsafe(ajson->tmp, utf8, len);
    ajson->ptr += escape_len;

    return 0;
}

static void ajson_set_token_error(ajson_token_t *token, ajson_parse_t *ajson,
                                 const char *errtype)
{
    token->type = T_ERROR;
    token->index = (int)(ajson->ptr - ajson->data);
    token->value.string = errtype;
}

static void ajson_next_string_token(ajson_parse_t *ajson, ajson_token_t *token)
{
    char *escape2char = ajson->cfg->escape2char;
    char ch;

    /* Caller must ensure a string is next */
    assert(*ajson->ptr == '"');

    /* Skip " */
    ajson->ptr++;

    /* ajson->tmp is the temporary strbuf used to accumulate the
     * decoded string value.
     * ajson->tmp is sized to handle JSON containing only a string value.
     */
    strbuf_reset(ajson->tmp);

    while ((ch = *ajson->ptr) != '"') {
        if (!ch) {
            /* Premature end of the string */
            ajson_set_token_error(token, ajson, "unexpected end of string");
            return;
        }

        /* Handle escapes */
        if (ch == '\\') {
            /* Fetch escape character */
            ch = *(ajson->ptr + 1);

            /* Translate escape code and append to tmp string */
            ch = escape2char[(unsigned char)ch];
            if (ch == 'u') {
                if (ajson_append_unicode_escape(ajson) == 0)
                    continue;

                ajson_set_token_error(token, ajson,
                                     "invalid unicode escape code");
                return;
            }
            if (!ch) {
                ajson_set_token_error(token, ajson, "invalid escape code");
                return;
            }

            /* Skip '\' */
            ajson->ptr++;
        }
        /* Append normal character or translated single character
         * Unicode escapes are handled above */
        strbuf_append_char_unsafe(ajson->tmp, ch);
        ajson->ptr++;
    }
    ajson->ptr++;    /* Eat final quote (") */

    strbuf_ensure_null(ajson->tmp);

    token->type = T_STRING;
    token->value.string = strbuf_string(ajson->tmp, &token->string_len);
}

/* JSON numbers should take the following form:
 *      -?(0|[1-9]|[1-9][0-9]+)(.[0-9]+)?([eE][-+]?[0-9]+)?
 *
 * ajson_next_number_token() uses strtod() which allows other forms:
 * - numbers starting with '+'
 * - NaN, -NaN, infinity, -infinity
 * - hexadecimal numbers
 * - numbers with leading zeros
 *
 * ajson_is_invalid_number() detects "numbers" which may pass strtod()'s
 * error checking, but should not be allowed with strict JSON.
 *
 * ajson_is_invalid_number() may pass numbers which cause strtod()
 * to generate an error.
 */
static int ajson_is_invalid_number(ajson_parse_t *ajson)
{
    const char *p = ajson->ptr;

    /* Reject numbers starting with + */
    if (*p == '+')
        return 1;

    /* Skip minus sign if it exists */
    if (*p == '-')
        p++;

    /* Reject numbers starting with 0x, or leading zeros */
    if (*p == '0') {
        int ch2 = *(p + 1);

        if ((ch2 | 0x20) == 'x' ||          /* Hex */
            ('0' <= ch2 && ch2 <= '9'))     /* Leading zero */
            return 1;

        return 0;
    } else if (*p <= '9') {
        return 0;                           /* Ordinary number */
    }

    /* Reject inf/nan */
    if (!strncasecmp(p, "inf", 3))
        return 1;
    if (!strncasecmp(p, "nan", 3))
        return 1;

    /* Pass all other numbers which may still be invalid, but
     * strtod() will catch them. */
    return 0;
}

static void ajson_next_number_token(ajson_parse_t *ajson, ajson_token_t *token)
{
    char *endptr;

    token->type = T_NUMBER;
    token->value.number = fpconv_strtod(ajson->ptr, &endptr);
    if (ajson->ptr == endptr)
        ajson_set_token_error(token, ajson, "invalid number");
    else
        ajson->ptr = endptr;     /* Skip the processed number */

    return;
}

/* Fills in the token struct.
 * T_STRING will return a pointer to the ajson_parse_t temporary string
 * T_ERROR will leave the ajson->ptr pointer at the error.
 */
static void ajson_next_token(ajson_parse_t *ajson, ajson_token_t *token)
{
    const ajson_token_type_t *ch2token = ajson->cfg->ch2token;
    int ch;

    /* Eat whitespace. */
    while (1) {
        ch = (unsigned char)*(ajson->ptr);
        token->type = ch2token[ch];
        if (token->type != T_WHITESPACE)
            break;
        ajson->ptr++;
    }

    /* Store location of new token. Required when throwing errors
     * for unexpected tokens (syntax errors). */
    token->index = (int)(ajson->ptr - ajson->data);

    /* Don't advance the pointer for an error or the end */
    if (token->type == T_ERROR) {
        ajson_set_token_error(token, ajson, "invalid token");
        return;
    }

    if (token->type == T_END) {
        return;
    }

    /* Found a known single character token, advance index and return */
    if (token->type != T_UNKNOWN) {
        ajson->ptr++;
        return;
    }

    /* Process characters which triggered T_UNKNOWN
     *
     * Must use strncmp() to match the front of the JSON string.
     * JSON identifier must be lowercase.
     * When strict_numbers if disabled, either case is allowed for
     * Infinity/NaN (since we are no longer following the spec..) */
    if (ch == '"') {
        ajson_next_string_token(ajson, token);
        return;
    } else if (ch == '-' || ('0' <= ch && ch <= '9')) {
        if (!ajson->cfg->decode_invalid_numbers && ajson_is_invalid_number(ajson)) {
            ajson_set_token_error(token, ajson, "invalid number");
            return;
        }
        ajson_next_number_token(ajson, token);
        return;
    } else if (!strncmp(ajson->ptr, "true", 4)) {
        token->type = T_BOOLEAN;
        token->value.boolean = 1;
        ajson->ptr += 4;
        return;
    } else if (!strncmp(ajson->ptr, "false", 5)) {
        token->type = T_BOOLEAN;
        token->value.boolean = 0;
        ajson->ptr += 5;
        return;
    } else if (!strncmp(ajson->ptr, "null", 4)) {
        token->type = T_NULL;
        ajson->ptr += 4;
        return;
    } else if (ajson->cfg->decode_invalid_numbers &&
               ajson_is_invalid_number(ajson)) {
        /* When decode_invalid_numbers is enabled, only attempt to process
         * numbers we know are invalid JSON (Inf, NaN, hex)
         * This is required to generate an appropriate token error,
         * otherwise all bad tokens will register as "invalid number"
         */
        ajson_next_number_token(ajson, token);
        return;
    }

    /* Token starts with t/f/n but isn't recognised above. */
    ajson_set_token_error(token, ajson, "invalid token");
}

/* This function does not return.
 * DO NOT CALL WITH DYNAMIC MEMORY ALLOCATED.
 * The only supported exception is the temporary parser string
 * ajson->tmp struct.
 * ajson and token should exist on the stack somewhere.
 * luaL_error() will long_jmp and release the stack */
static void ajson_throw_parse_error(lua_State *l, ajson_parse_t *ajson,
                                   const char *exp, ajson_token_t *token)
{
    const char *found;

    strbuf_free(ajson->tmp);

    if (token->type == T_ERROR)
        found = token->value.string;
    else
        found = ajson_token_type_name[token->type];

    /* Note: token->index is 0 based, display starting from 1 */
    luaL_error(l, "Expected %s but found %s at character %d",
               exp, found, token->index + 1);
}

static inline void ajson_decode_ascend(ajson_parse_t *ajson)
{
    ajson->current_depth--;
}

static void ajson_decode_descend(lua_State *l, ajson_parse_t *ajson, int slots)
{
    ajson->current_depth++;

    if (ajson->current_depth <= ajson->cfg->decode_max_depth &&
        lua_checkstack(l, slots)) {
        return;
    }

    strbuf_free(ajson->tmp);
    luaL_error(l, "Found too many nested data structures (%d) at character %d",
        ajson->current_depth, ajson->ptr - ajson->data);
}

static void ajson_parse_object_context(lua_State *l, ajson_parse_t *ajson)
{
    ajson_token_t token;

    /* 3 slots required:
     * .., table, key, value */
    ajson_decode_descend(l, ajson, 3);

    lua_newtable(l);

    ajson_next_token(ajson, &token);

    /* Handle empty objects */
    if (token.type == T_OBJ_END) {
        ajson_decode_ascend(ajson);
        return;
    }

    while (1) {
        // ALITTLE 改动：这里本来只对字符串做处理，这里加上number
//         if (token.type != T_STRING)
//             ajson_throw_parse_error(l, ajson, "object key string", &token);
// 
//         /* Push key */
//         lua_pushlstring(l, token.value.string, token.string_len);
        if (token.type == T_STRING)
            lua_pushlstring(l, token.value.string, token.string_len);
        else if (token.type == T_NUMBER)
            lua_pushnumber(l, token.value.number);
        else
            ajson_throw_parse_error(l, ajson, "object key string or number", &token);

        ajson_next_token(ajson, &token);
        if (token.type != T_COLON)
            ajson_throw_parse_error(l, ajson, "colon", &token);

        /* Fetch value */
        ajson_next_token(ajson, &token);
        ajson_process_value(l, ajson, &token);

        /* Set key = value */
        lua_rawset(l, -3);

        ajson_next_token(ajson, &token);

        if (token.type == T_OBJ_END) {
            ajson_decode_ascend(ajson);
            return;
        }

        if (token.type != T_COMMA)
            ajson_throw_parse_error(l, ajson, "comma or object end", &token);

        ajson_next_token(ajson, &token);
    }
}

/* Handle the array context */
static void ajson_parse_array_context(lua_State *l, ajson_parse_t *ajson)
{
    ajson_token_t token;
    int i;

    /* 2 slots required:
     * .., table, value */
    ajson_decode_descend(l, ajson, 2);

    lua_newtable(l);

    ajson_next_token(ajson, &token);

    /* Handle empty arrays */
    if (token.type == T_ARR_END) {
        ajson_decode_ascend(ajson);
        return;
    }

    for (i = 1; ; i++) {
        ajson_process_value(l, ajson, &token);
        lua_rawseti(l, -2, i);            /* arr[i] = value */

        ajson_next_token(ajson, &token);

        if (token.type == T_ARR_END) {
            ajson_decode_ascend(ajson);
            return;
        }

        if (token.type != T_COMMA)
            ajson_throw_parse_error(l, ajson, "comma or array end", &token);

        ajson_next_token(ajson, &token);
    }
}

/* Handle the "value" context */
static void ajson_process_value(lua_State *l, ajson_parse_t *ajson,
                               ajson_token_t *token)
{
    switch (token->type) {
    case T_STRING:
        lua_pushlstring(l, token->value.string, token->string_len);
        break;;
    case T_NUMBER:
        lua_pushnumber(l, token->value.number);
        break;;
    case T_BOOLEAN:
        lua_pushboolean(l, token->value.boolean);
        break;;
    case T_OBJ_BEGIN:
        ajson_parse_object_context(l, ajson);
        break;;
    case T_ARR_BEGIN:
        ajson_parse_array_context(l, ajson);
        break;;
    case T_NULL:
        /* In Lua, setting "t[k] = nil" will delete k from the table.
         * Hence a NULL pointer lightuserdata object is used instead */
        lua_pushlightuserdata(l, NULL);
        break;;
    default:
        ajson_throw_parse_error(l, ajson, "value", token);
    }
}

static int ajson_decode(lua_State *l)
{
    ajson_parse_t ajson;
    ajson_token_t token;
    size_t ajson_len;

    luaL_argcheck(l, lua_gettop(l) == 1, 1, "expected 1 argument");

    ajson.cfg = ajson_fetch_config(l);
    ajson.data = luaL_checklstring(l, 1, &ajson_len);
    ajson.current_depth = 0;
    ajson.ptr = ajson.data;

    /* Detect Unicode other than UTF-8 (see RFC 4627, Sec 3)
     *
     * AJSON can support any simple data type, hence only the first
     * character is guaranteed to be ASCII (at worst: '"'). This is
     * still enough to detect whether the wrong encoding is in use. */
    if (ajson_len >= 2 && (!ajson.data[0] || !ajson.data[1]))
        luaL_error(l, "JSON parser does not support UTF-16 or UTF-32");

    /* Ensure the temporary buffer can hold the entire string.
     * This means we no longer need to do length checks since the decoded
     * string must be smaller than the entire ajson string */
    ajson.tmp = strbuf_new((int)(ajson_len));

    ajson_next_token(&ajson, &token);
    ajson_process_value(l, &ajson, &token);

    /* Ensure there is no more input left */
    ajson_next_token(&ajson, &token);

    if (token.type != T_END)
        ajson_throw_parse_error(l, &ajson, "the end", &token);

    strbuf_free(ajson.tmp);

    return 1;
}

/* ===== INITIALISATION ===== */

// #if !defined(LUA_VERSION_NUM) || LUA_VERSION_NUM < 502
/* Compatibility for Lua 5.1.
 *
 * luaL_setfuncs() is used to create a module table where the functions have
 * ajson_config_t as their first upvalue. Code borrowed from Lua 5.2 source. */
// static void luaL_setfuncs (lua_State *l, const luaL_Reg *reg, int nup)
// {
//     int i;

//	   luaL_checkstack(l, nup, "too many upvalues");
//     for (; reg->name != NULL; reg++) {  /* fill the table with given functions */
//         for (i = 0; i < nup; i++)  /* copy upvalues to the top */
//             lua_pushvalue(l, -nup);
//         lua_pushcclosure(l, reg->func, nup);  /* closure with those upvalues */
//         lua_setfield(l, -(nup + 2), reg->name);
//     }
//     lua_pop(l, nup);  /* remove upvalues */
// }
// #endif


/* Call target function in protected mode with all supplied args.
 * Assumes target function only returns a single non-nil value.
 * Convert and return thrown errors as: nil, "error message" */
static int ajson_protect_conversion(lua_State *l)
{
    int err;

    /* Deliberately throw an error for invalid arguments */
    luaL_argcheck(l, lua_gettop(l) == 1, 1, "expected 1 argument");

    /* pcall() the function stored as upvalue(1) */
    lua_pushvalue(l, lua_upvalueindex(1));
    lua_insert(l, 1);
    err = lua_pcall(l, 1, 1, 0);
    if (!err)
        return 1;

    if (err == LUA_ERRRUN) {
        lua_pushnil(l);
        lua_insert(l, -2);
        return 2;
    }

    /* Since we are not using a custom error handler, the only remaining
     * errors are memory related */
    return luaL_error(l, "Memory allocation error in AJSON protected call");
}

/* Return ajson module table */
static int lua_ajson_new(lua_State *l)
{
    luaL_Reg reg[] = {
        { "encode", ajson_encode },
        { "decode", ajson_decode },
        { "encode_sparse_array", ajson_cfg_encode_sparse_array },
        { "encode_max_depth", ajson_cfg_encode_max_depth },
        { "decode_max_depth", ajson_cfg_decode_max_depth },
        { "encode_number_precision", ajson_cfg_encode_number_precision },
        { "encode_keep_buffer", ajson_cfg_encode_keep_buffer },
        { "encode_invalid_numbers", ajson_cfg_encode_invalid_numbers },
        { "decode_invalid_numbers", ajson_cfg_decode_invalid_numbers },
        { "new", lua_ajson_new },
        { NULL, NULL }
    };

    /* Initialise number conversions */
    fpconv_init();

    /* ajson module table */
    lua_newtable(l);

    /* Register functions with config data as upvalue */
    ajson_create_config(l);
    luaL_setfuncs(l, reg, 1);

    /* Set ajson.null */
    lua_pushlightuserdata(l, NULL);
    lua_setfield(l, -2, "null");

    /* Set module name / version fields */
    lua_pushliteral(l, AJSON_MODNAME);
    lua_setfield(l, -2, "_NAME");
    lua_pushliteral(l, AJSON_VERSION);
    lua_setfield(l, -2, "_VERSION");

    return 1;
}

/* Return ajson.safe module table */
static int lua_ajson_safe_new(lua_State *l)
{
    const char *func[] = { "decode", "encode", NULL };
    int i;

    lua_ajson_new(l);

    /* Fix new() method */
    lua_pushcfunction(l, lua_ajson_safe_new);
    lua_setfield(l, -2, "new");

    for (i = 0; func[i]; i++) {
        lua_getfield(l, -1, func[i]);
        lua_pushcclosure(l, ajson_protect_conversion, 1);
        lua_setfield(l, -2, func[i]);
    }

    return 1;
}
#define ENABLE_AJSON_GLOBAL

int luaopen_ajson(lua_State *l)
{
    lua_ajson_new(l);
#ifdef ENABLE_AJSON_GLOBAL
    /* Register a global "ajson" table. */
    lua_pushvalue(l, -1);
    lua_setglobal(l, AJSON_MODNAME);
#endif

    /* Return ajson table */
    return 1;
}

int luaopen_ajson_safe(lua_State *l)
{
    lua_ajson_safe_new(l);
#ifdef ENABLE_AJSON_GLOBAL
	/* Register a global "ajson" table. */
	lua_pushvalue(l, -1);
	lua_setglobal(l, AJSON_MODNAME);
#endif
    /* Return ajson.safe table */
    return 1;
}

/* vi:ai et sw=4 ts=4:
 */
