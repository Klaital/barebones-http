#include <gtest/gtest.h>
#include "Response.h"

TEST(ResponseWriteTest, Request) 
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

