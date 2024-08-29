test:
	bazel test --cxxopt=-std=c++14 --test_output=all //:http_test

build:
	bazel build //:barebones-http
