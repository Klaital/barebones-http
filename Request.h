//
// Created by Kit on 8/28/2024.
//

#ifndef REQUEST_H
#define REQUEST_H

#ifndef MAX_BODY_SIZE
#define MAX_BODY_SIZE 512
#endif

#include "Headers.h"

namespace HTTP {

class Request {
public:
    char method[12];
    char path[128];
    char query_string[128];
    HeaderSet headers;
    char body[MAX_BODY_SIZE];

    Request() : method(""), path(""), query_string("") {}

    void to_string(char *buf, size_t len);
    void reset();
};

} // HTTP

#endif //REQUEST_H
