#pragma once
#include <mutex>
#include <iostream>

#include "ConsecutiveList.h"

template<typename T, int S = 1024>
class RSHelper {
private:
	class RSManager {
	private:
		ConsecutiveList list;
	public:
		RSManager(): list(S, sizeof(T)) { }

		// 得到一个指向可用于初始化对象的内存的指针
		void* get(size_t size) {
			void* temp = list.get();
			if (temp == NULL) {
				return malloc(size);
			}
			return temp;

		}
		// 回收一个由get得到的指针，有可能放回链表，有可能free
		void put(void* t) {
			list.put(t);
		}
	};

	static RSManager manager_;

public:

	void* operator new(size_t sz) {
		return manager_.get(sz);
	}

	void operator delete(void* m) {
		if (!m)
			return;
		manager_.put(m);
	}
};

template<typename T, int S>
typename RSHelper<T, S>::RSManager RSHelper<T, S>::manager_;