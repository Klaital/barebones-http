cc_library(
	name = "barebones-http",
	hdrs=glob(["**/*.h"]),
    srcs=glob(["**/*.cpp"]),
)
cc_test(
	name = "http_test",
	size = "small",
	srcs = [
		"Headers.cpp",
		"Request.cpp",
		"request_test.cc",
		"headers_test.cc",
	],
	deps = [
		"@googletest//:gtest",
		"@googletest//:gtest_main",
		"//:barebones-http",
	],
)
