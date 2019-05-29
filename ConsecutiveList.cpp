#include "ConsecutiveList.h"
#include <iostream>
using namespace std;
ConsecutiveList::ConsecutiveList(size_t _el_num, size_t _el_size):
	el_num(_el_num),
	el_size(_el_size),
	list()
{
	size_t total_size = el_num * el_size;
	ptr = malloc(total_size);
	upper_bound_address = (char*)ptr + total_size;

	int loop = el_num - 1;
	char* p = (char*)ptr;
	do {
		list.push_front(p);
		p += el_size;
	} while (loop--);
}

void* ConsecutiveList::get() {
	std::lock_guard<std::mutex> guard(mutex_);
	if (list.empty()) {
		return NULL;
	}
	void* temp = list.front();
	list.pop_front();
	return temp;
}

void ConsecutiveList::put(void* p) {
	if (p >= ((void*)ptr) && p < upper_bound_address) {
		std::lock_guard<std::mutex> guard(mutex_);
		list.push_front(p);
		return;
	}
	free(p);
}

ConsecutiveList::~ConsecutiveList() {
	free(ptr);
}