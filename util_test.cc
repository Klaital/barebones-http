#ifndef ARDUINO
#include <gtest/gtest.h>
#include "util.h"

TEST(UtilsTest, Trim) 
{
	char buf[32];

    strcpy_trim(buf, " hello, world!\n");
    EXPECT_STREQ("hello, world!", buf);

    strcpy_trim(buf, "a");
    EXPECT_STREQ("a", buf);

    strcpy_trim(buf, " a");
    EXPECT_STREQ("a", buf);

    strcpy_trim(buf, "a ");
    EXPECT_STREQ("a", buf);
}

TEST(UtilsTest, FindHead)
{
    EXPECT_EQ(0, find_head("asdf", 0));
    EXPECT_EQ(0, find_head("", 0));
    EXPECT_EQ(1, find_head(" ", 0));
    EXPECT_EQ(1, find_head(" a", 0));
    EXPECT_EQ(1, find_head(" a ", 0));
}

TEST(UtilsTest, FindTail)
{
    EXPECT_EQ(3, find_tail("asdf", 0, 4));
    EXPECT_EQ(0, find_tail("", 0, 0));
    EXPECT_EQ(0, find_tail(" ", 0, 1));
    EXPECT_EQ(1, find_tail(" a", 0, 2));
    EXPECT_EQ(1, find_tail(" a ", 0, 3));
    EXPECT_EQ(13, find_tail(" hello, world!\n", 0, 15));
}

TEST(UtilsTest, Trimmable) 
{
    EXPECT_EQ(true, is_trimmable_char(' '));
    EXPECT_EQ(true, is_trimmable_char('\t'));
    EXPECT_EQ(true, is_trimmable_char('\n'));
    EXPECT_EQ(true, is_trimmable_char('\r'));
    EXPECT_EQ(false, is_trimmable_char('a'));
}

TEST(UtilsTest, TrimSubstring) 
{
    char buf[32];
    strcpy_trim(buf, "Content-Type: application/json", 13);
    EXPECT_STREQ("application/json", buf);
}

TEST(UtilsTest, ParseHttpDecl) 
{
    char http_buf[16];
    char code_buf[8];
    char status_buf[16];

    parse_http_line("HTTP/1.1 500 Internal Server Error", http_buf, code_buf, status_buf);
    EXPECT_STREQ("HTTP/1.1", http_buf);
    EXPECT_STREQ("500", code_buf);
    EXPECT_STREQ("Internal Server Error", status_buf);
}

TEST(UtilsTest, Strlen)
{
    EXPECT_EQ(30, strlen_trimmed(" Content-Type: application/json\n"));
}
#endif
