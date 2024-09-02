//
// Created by Kit on 8/28/2024.
//

#include "Response.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void HTTP::Response::to_string(char *buf, size_t len) 
{
    char tmp[512];
    sprintf(tmp, "HTTP/1.1 %d %s\n", this->code, this->status);
    strcpy(buf, tmp);
    tmp[0] = '\0';
    size_t content_len = strlen(this->body);
    if (content_len > 0)
    {
        this->headers.set("Content-Length", content_len);
    }
    this->headers.to_string(tmp, 512);
    strcat(buf, tmp);
    strcat(buf, "\n");
    if (content_len > 0) 
    {
        strcat(buf, this->body);
    }
    strcat(buf, "\n");
}

void HTTP::Response::reset() 
{
    this->code = 0;
    this->status[0] = '\0';
    this->headers.reset();
    this->body[0] = '\0';
}


void HTTP::Response::parse(char* raw) 
{
    // line 1 has form of 'HTTP/1.1 404 Not Found'
    char* tok = strtok(raw, " "); // throw away "HTTP/1.1"
    tok = strtok(nullptr, " ");
    this->code = atoi(tok);
    tok = strtok(nullptr, "\n");
    strcpy_trim(this->status, tok);
    // next N lines are headers
    tok = strtok(nullptr, "\n");
    while (tok != nullptr && strlen(tok) > 2) 
    {
        this->headers.parse(tok);
    }
    // we get here once we hit an empty line
    // any further data past here is the body
    tok = strtok(nullptr, "\n");
    if (tok != nullptr) 
    {
        strcpy_trim(this->body, raw);
    }
}
