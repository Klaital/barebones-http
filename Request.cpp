//
// Created by Kit on 8/28/2024.
//

#include "Request.h"
#include <string.h>

namespace HTTP {

void Request::to_string(char *buf, size_t len) {
    buf[0] = '\0';
    strcpy(buf, this->method);
    strcat(buf, " ");
    strcat(buf, this->path);
    if (strlen(this->query_string) > 0)
    {
        strcat(buf, "?");
        strcat(buf, this->query_string);
    }
    strcat(buf, " HTTP/1.1\n");

    char headers_buf[512];
    size_t content_len = strlen(this->body);
    if (content_len > 0) {
        this->headers.set("Content-Length", content_len);
    }
    this->headers.to_string(headers_buf, 512);
    strcat(buf, headers_buf);
    strcat(buf, "\n");
    if (content_len > 0) {
        strcat(buf, this->body);
        strcat(buf, "\n");
    }
}

void Request::reset()
{
    this->body[0] = '\0';
    this->query_string[0] = '\0';
    this->method[0] = '\0';
    this->path[0] = '\0';
    this->headers.reset();
}

} // HTTP
