#ifndef ARDUINO
#include <gtest/gtest.h>
#include "./Headers.h"

TEST(HeadersTest, Headers) 
{
    HTTP::Header h;
    h.set("Content-Type", "application/json");
    char buf[256];
    h.to_string(buf, 256);

	EXPECT_STREQ("Content-Type: application/json", buf);
    h.set("key", "value");
    h.to_string(buf, 256);
    EXPECT_STREQ("key: value", buf);

    h.set("Content-Length", 500);
    h.to_string(buf, 256);
    EXPECT_STREQ("Content-Length: 500", buf);
}

TEST(HeadersTest, HeaderSet) 
{
    HTTP::HeaderSet headers;
    headers.set("Content-Type", "application/json");
    headers.set("Connection", "close");
    headers.set("Accept", "application/json");

    EXPECT_EQ(3, headers.length());
    char buf[256];
    headers.to_string(buf, 256);
    EXPECT_STREQ("Content-Type: application/json\nConnection: close\nAccept: application/json\n", buf);

    headers.reset();
    EXPECT_EQ(0, headers.length());
    headers.set("key1", "val1");
    headers.set("key2", "val2");
    EXPECT_EQ(2, headers.length());
    headers.to_string(buf, 256);
    EXPECT_STREQ("key1: val1\nkey2: val2\n", buf);
}

TEST(HeadersTest, Parsing) 
{
    HTTP::Header h;
    h.parse("Content-Type: application/json");
    EXPECT_STREQ("Content-Type", h.key);
    EXPECT_STREQ("application/json", h.val);
    
    h.reset();
    h.parse(" Accept: plain/text\r\n");
    EXPECT_STREQ("Accept", h.key);
    EXPECT_STREQ("plain/text", h.val);
}

TEST(HeadersTest, ParseLen)
{
    HTTP::HeaderSet hs;
    char line[] = "Content-Length: application/json \r\n";
    size_t offset = hs.parse(line);
    EXPECT_EQ(1, hs.length());
    EXPECT_EQ(33, offset);
    EXPECT_EQ('\r', line[offset]);
}

#endif