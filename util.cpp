
#include "util.h"
#include <stdlib.h>
#include <string.h>

bool is_trimmable_char(char c) 
{
    for (size_t i=0; i<strlen(TRIMMED_CHARS); i++) 
    {
        if (c == TRIMMED_CHARS[i]) 
        {
            return true;
        }
    }
    return false;
}


size_t find_head(const char* src, size_t head_offset) 
{
    size_t len = strlen(src);
    if (len == 0) 
    {
        return 0;
    }

    size_t idx;
    for (idx = head_offset; idx < len; idx++) 
    {
        if (!is_trimmable_char(src[idx])) 
        {
            return idx;
        } 
    }
    return idx; 
}

size_t find_tail(const char* src, size_t head_offset, size_t max_chars) 
{
    size_t len = strlen(src);
    if (len == 0) 
    {
        return 0;
    }
    if (head_offset > len) 
    {
        return 0;
    }
    if (max_chars + head_offset > len) 
    {
        return 0;
    }

    size_t idx;
    for(idx = head_offset + max_chars-1; idx > head_offset; idx--) 
    {
        if (!is_trimmable_char(src[idx]))
        {
            return idx;
        }
    }
    return idx;
}
void strcpy_trim(char *dst, const char* src) 
{
    return strcpy_trim(dst, src, 0, strlen(src));
}
void strcpy_trim(char *dst, const char* src, size_t head_offset)
{
    return strcpy_trim(dst, src, head_offset, strlen(src+head_offset));
}
void strcpy_trim(char *dst, const char* src, size_t head_offset, size_t max_chars) 
{
    // Find the index of the first non-whitespace character
    size_t head = find_head(src, head_offset);
    size_t tail = find_tail(src, head_offset, max_chars);

    if (head > tail) 
    {
        // all whitespace
        dst[0] = '\0';
        return;
    }

    if (tail == head) 
    {
        // Single character
        dst[0] = src[head];
        dst[1] = '\0';
        return;
    }
    strncpy(dst, src+head, tail-head+1);
    dst[tail-head+1] = '\0';
}

size_t parse_http_line(const char* src, char* http_buf, char *code_buf, char *status_buf) {
    // find the end of the http declaration
    size_t http_sep = 0;
    for (http_sep = 0; src[http_sep] != ' '; http_sep++) {}
    if (http_buf != nullptr)
    {
        strcpy_trim(http_buf, src, 0, http_sep);
    }
    
    // find the end of the status code
    size_t code_sep;
    for (code_sep = http_sep+1; src[code_sep] != ' '; code_sep++) {}
    strcpy_trim(code_buf, src, http_sep+1, code_sep-http_sep);

    // find the end of the line
    size_t status_sep;
    for (status_sep = code_sep+1; status_sep < strlen(src); status_sep++) 
    {
        if (src[status_sep] == '\n' || src[status_sep] == '\r') 
        {
            break;
        }
    }
    strcpy_trim(status_buf, src, code_sep+1, status_sep-code_sep-1);
    return status_sep+1;
}

size_t strlen_trimmed(const char *str)
{
    size_t head = find_head(str, 0);
    size_t tail = find_tail(str, 0, strlen(str));
    return tail-head+1;
}
