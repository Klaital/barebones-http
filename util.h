//
// Created by Kit on 8/28/2024.
//

#ifndef HTTP_UTIL_H
#define HTTP_UTIL_H

#include <stddef.h>

constexpr char TRIMMED_CHARS[] = " \n\r\t";
bool is_trimmable_char(char c);
void strcpy_trim(char *dst, const char* src, size_t head_offset, size_t max_chars);
void strcpy_trim(char *dst, const char* src, size_t head_offset);
void strcpy_trim(char *dst, const char* src);

// Find the index of the first non-trimmable character in the string
size_t find_head(const char* src, size_t head_offset);
size_t find_tail(const char* src, size_t head_offset, size_t max_chars);
#endif
