#ifndef ARDUINO
#include <gtest/gtest.h>
#include "Request.h"


TEST(RequestWriteTest, Request) 
{
	HTTP::Request req;

	strcpy(req.method, "GET");
	strcpy(req.path, "/cfg");
	strcpy(req.query_string, "");
	strcpy(req.body, "");
	req.headers.set("Accept", "application/text");

	char buf[1024];
	req.to_string(buf, 1024);
	EXPECT_STREQ("GET /cfg HTTP/1.1\nAccept: application/text\n\n", buf);

	req.reset();
	strcpy(req.method, "PUT");
	strcpy(req.path, "/lights/dimmer");
	strcpy(req.query_string, "state=on");
	strcpy(req.body, "0.5");
	req.headers.set("Accept", "application/text");
	req.headers.set("Content-Type", "plain/text");

	req.to_string(buf, 1024);
	EXPECT_STREQ("PUT /lights/dimmer?state=on HTTP/1.1\nAccept: application/text\nContent-Type: plain/text\nContent-Length: 3\n\n0.5\n", buf);
}
#endif