#pragma once

#include <exception>

class DefaultFigureCall : public std::exception {
public:
	DefaultFigureCall(const char* msg):std::exception(msg) {}
};