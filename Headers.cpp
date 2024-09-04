//
// Created by Kit on 8/28/2024.
//

#include "Headers.h"
#include <string.h>
#include <stdio.h>
#include "util.h"

namespace HTTP {

Header::Header() 
{
    this->key[0] = '\0';
    this->val[0] = '\0';
}

void Header::set(const char *key, const char *val) 
{
    strcpy(this->key, key);
    strcpy(this->val, val);
}

void Header::set(const char *key, size_t val) 
{
    char buf[16];
    buf[0] = '\0';
    sprintf(buf, "%lu", val);
    strcpy(this->key, key);
    strcpy(this->val, buf);
}


void Header::to_string(char *buf, size_t len) const
{
    if (strlen(this->key) + strlen(this->val) + 3 > len) 
    {
        // early-out if there's not enough room in the buffer
        return;
    }
    strcpy(buf, this->key);
    strcat(buf, ": ");
    strcat(buf, this->val);
}

void Header::reset()
{
    this->key[0] = '\0';
    this->val[0] = '\0';
}

void Header::parse(const char* raw) 
{
    size_t sep_idx = 0;
    for (size_t i=0; i<strlen(raw); i++) 
    {
        if (raw[i] == ':') 
        {
            sep_idx = i;
            break;
        }
    }
    if (sep_idx == 0) 
    {
        // either the separator wasn't found, or the key was empty. 
        // Either way, this is an invalid header
        return;
    }
    strcpy_trim(this->key, raw, 0, sep_idx);    
    strcpy_trim(this->val, raw, sep_idx+1);
}

size_t HeaderSet::length() const 
{
    return this->count;
}
void HeaderSet::reset() 
{
    for (size_t i=0; i < this->count; i++) {
        this->headers[i].reset();
    }
    this->count = 0;
}
void HeaderSet::to_string(char *buf, size_t len) const 
{
    size_t bytes = 0;
    buf[0] = '\0';
    char header_buf[256];
    for (size_t i=0; i < this->count; i++) {
        header_buf[0] = '\0';
        this->headers[i].to_string(header_buf, 256-bytes);
        int new_bytes = strlen(header_buf);
        if (bytes + new_bytes > len) {
            break;
        }
        strcat(buf, header_buf);
        strcat(buf, "\n");
        bytes += new_bytes+1;
    }
}
void HeaderSet::set(const char *key, const char *val) 
{
    if (this->count >= MAX_HEADER_COUNT) {
        return;
    }
    // update an existing header value if found
    bool found = false;
    size_t idx = 0;
    for (idx=0; idx < this->count; idx++) 
    {
        if (strcmp(this->headers[idx].key, key) == 0) 
        {
            found = true;
            break;
        }
    }

    if (found) {
        this->headers[idx].set(key, val);
    } else {
        this->headers[this->count].set(key, val);
        this->count++;
    }
}
void HeaderSet::set(const char *key, size_t val)
{
    if (this->count >= MAX_HEADER_COUNT) {
        return;
    }
    // update an existing header value if found
    bool found = false;
    size_t idx = 0;
    for (idx=0; idx < this->count; idx++) 
    {
        if (strcmp(this->headers[idx].key, key) == 0) 
        {
            found = true;
            break;
        }
    }

    if (found) {
        this->headers[idx].set(key, val);
    } else {
        this->headers[this->count].set(key, val);
        this->count++;
    }
}
size_t HeaderSet::parse(const char* raw) 
{
    if (this->count >= MAX_HEADER_COUNT) {
        return 0;
    }
    // find the end of the line
    size_t line_chars = 0;
    for (line_chars=0; line_chars < strlen(raw); line_chars++) 
    {
        if (raw[line_chars] == '\n' || raw[line_chars] == '\r') 
        {
            break;
        }
    }
    if (line_chars > 1)
    {
        this->headers[this->count].parse(raw);
        this->count++;
        return line_chars;
    }

    // Empty line
    return 0;
}
} // HTTP
