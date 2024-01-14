#pragma once

#include <exception>

class DefaultConstructorCall:public std::exception {
public:
	DefaultConstructorCall():std::exception("Default constructor was called. Check if you didn't call it by accident") {}
};