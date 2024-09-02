//
// Created by Kit on 8/28/2024.
//

#include "Headers.h"
#include <string.h>
#include <stdio.h>
#include "util.h"
#include <iostream>

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
    std::cout << "Copying header key from " << raw[0] << " through " << raw[sep_idx];
    strcpy_trim(this->key, raw, 0, sep_idx);    
    std::cout << " => " << this->key << std::endl;
    std::cout << "Copying header value from " << raw[sep_idx+1] << " through " << raw[strlen(raw)-1];
    strcpy_trim(this->val, raw, sep_idx+1);
    std::cout << " => " << this->val << std::endl;
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

    this->headers[this->count].set(key, val);
    this->count++;
}
void HeaderSet::set(const char *key, size_t val)
{
    if (this->count >= MAX_HEADER_COUNT) {
        return;
    }

    this->headers[this->count].set(key, val);
    this->count++;
}
void HeaderSet::parse(const char* raw) 
{
    if (this->count >= MAX_HEADER_COUNT) {
        return;
    }
    this->headers[this->count].parse(raw);
    this->count++;
}
} // HTTP
