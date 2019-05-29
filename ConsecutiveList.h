#pragma once
#include <forward_list>
#include <mutex>

class ConsecutiveList {
private:
	void* ptr;   // 指向一块连续的内存
	void* upper_bound_address;   // ptr所指的连续内存的上界
	std::forward_list<void*> list;   // 用于存放指针链表，链表中的指针指向连续内存中的每个对象起始地址
	const size_t el_size;   // 对象大小
	const size_t el_num;    // 内存中可存的对象数
	std::mutex mutex_;
public:
	ConsecutiveList(size_t _el_num, size_t _el_size);
	void* get();
	void put(void*);
	~ConsecutiveList();
};