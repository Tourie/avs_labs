#pragma once

template<typename T>
__interface ISafeQueue
{
	void push_back(T);
	bool pop(T&);
};