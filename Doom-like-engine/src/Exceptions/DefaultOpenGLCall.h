#pragma once

#include <exception>

class DefaultOpenGLCall : public std::exception {
public:
	DefaultOpenGLCall(const char* msg) :std::exception(msg) {}
};