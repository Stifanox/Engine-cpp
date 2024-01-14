#pragma once


class Binder {
public:
	unsigned int bufferId = 0;
	virtual void bind() = 0;
	virtual void unbind() = 0;
	virtual ~Binder() {};
};