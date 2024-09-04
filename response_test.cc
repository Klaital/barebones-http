#ifndef ARDUINO
#include <gtest/gtest.h>
#include "Response.h"

TEST(ResponseWriteTest, Response) 
{
	HTTP::Response resp;
    strcpy(resp.status, "Not Found");
    resp.code = 404;
    strcpy(resp.body, "0.5");

    char buf[1024];
    resp.to_string(buf, 1024);
    EXPECT_STREQ("HTTP/1.1 404 Not Found\nContent-Length: 3\n\n0.5\n", buf);

    resp.reset();
}

TEST(ResponseParsing, Response) 
{
    HTTP::Response resp;
    char raw[] = "HTTP/1.1 200 OK\nContent-Length: 3\n\n0.5\n";
    resp.parse(raw);
    EXPECT_EQ(200, resp.code);
    EXPECT_STREQ("OK", resp.status);
    EXPECT_STREQ("0.5", resp.body);
    EXPECT_EQ(1, resp.headers.length());
}
#endif
