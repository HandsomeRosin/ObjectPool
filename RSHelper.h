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

		// �õ�һ��ָ������ڳ�ʼ��������ڴ��ָ��
		void* get(size_t size) {
			void* temp = list.get();
			if (temp == NULL) {
				return malloc(size);
			}
			return temp;

		}
		// ����һ����get�õ���ָ�룬�п��ܷŻ������п���free
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