//
// Created by Kit on 8/28/2024.
//

#ifndef HEADERS_H
#define HEADERS_H

#ifndef MAX_HEADER_COUNT
    #define MAX_HEADER_COUNT 10
#endif

#include <stddef.h>


namespace HTTP {

class Header {
public:
    char key[24];
    char val[32];

    Header();

    void set(const char* key, const char* val);
    void set(const char* key, size_t val);
    void to_string(char *buf, size_t len) const;
    void reset();
    void parse(const char* raw);

};

class HeaderSet {
    Header headers[MAX_HEADER_COUNT];
    size_t count=0;

public:
    HeaderSet() {}
    void to_string(char *buf, size_t len) const;
    void set(const char *key, const char* val);
    void set(const char *key, size_t val);
    void reset();
    size_t parse(const char *raw);
    size_t length() const;
};

} // HTTP

#endif //HEADERS_H
