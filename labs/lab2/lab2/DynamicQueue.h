#pragma once
#include "SafeQueue.h"
#include <queue>

using namespace std;

template<typename T>
class DynamicQueue : public ISafeQueue<T>
{
public:
	void push_back(T);
	bool pop(T&);

private:
	queue<T> q;
	mutex mtx;
};

template<typename T>
inline void DynamicQueue<T>::push_back(T arg)
{
	lock_guard<mutex> g(mtx);
	q.push(arg);
}

template<typename T>
inline bool DynamicQueue<T>::pop(T& value)
{
	unique_lock<mutex> g(mtx);
	if (q.empty()) {
		g.unlock();
		this_thread::sleep_for(chrono::milliseconds(1));
		if (q.empty()) {
			return false;
		}
		g.lock();
	}
	value = q.front();
	q.pop();
	return true;
	
}


