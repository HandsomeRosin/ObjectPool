#include "ConsecutiveList.h"

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
		list.push(p);
		p += el_size;
	} while (loop--);
}

void* ConsecutiveList::get() {
	if (list.empty()) {
		return NULL;
	}
	void* temp = list.pop();
	return temp;
}

void ConsecutiveList::put(void* p) {
	if (p >= ((void*)ptr) && p < upper_bound_address) {
		list.push(p);
		return;
	}
	free(p);
}

ConsecutiveList::~ConsecutiveList() {
	free(ptr);
}

void ConsecutiveList::LockFreeList::push(void* p) {
	DeleteGuard<Node> node(new Node);
	node->ptr = p;

	do {
		node->next = head.load();
	} while (!head.compare_exchange_weak(node->next, node.obj));

	node.obj = NULL;
}

void* ConsecutiveList::LockFreeList::pop() {
	DeleteGuard<Node> node;
	do {
		node = head.load();
		if (node.isNULL()) {
			return NULL;
		}
	} while (!head.compare_exchange_weak(node.obj, node->next)); 

	return node->ptr;
}
