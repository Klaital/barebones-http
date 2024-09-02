//
// Created by Kit on 8/28/2024.
//

#ifndef RESPONSE_H
#define RESPONSE_H

#ifndef MAX_BODY_SIZE
#define MAX_BODY_SIZE 512
#endif

#include "Headers.h"

namespace HTTP {

class Response {
public:
    int code = 0;
    char status[16];
    HeaderSet headers;
    char body[MAX_BODY_SIZE];

    Response() : body("") {}

    void to_string(char * buf, size_t len);
    void parse(char* raw);
    void reset();
};

}

#endif