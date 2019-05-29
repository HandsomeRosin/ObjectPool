#pragma once
#include <atomic>

class ConsecutiveList {
private:
	void* ptr;   // 指向一块连续的内存
	void* upper_bound_address;   // ptr所指的连续内存的上界

	// 无锁栈（采用链表结构）
	class LockFreeList {
	private:
		struct Node {
			Node* next;
			void* ptr;
		};

		std::atomic<Node*> head;
	public:
		bool empty() {
			return head.load() == NULL;
		}

		void push(void*);
		void* pop();
	} list;   // 用于存放指针链表，链表中的指针指向连续内存中的每个对象起始地址

	// 为了保证无论什么情况下指向堆对象的指针最后都能调用delete
	template<class T>
	struct DeleteGuard {
		T* obj;
		DeleteGuard(T* ptr = NULL) : obj(ptr) { }
		~DeleteGuard() {
			if (obj != NULL) {
				delete obj;
			}
		}

		T* operator->() {
			return obj;
		}
		void operator=(T* ptr) {
			obj = ptr;
		}
		bool isNULL() {
			return obj == NULL;
		}
	};

	const size_t el_size;   // 对象大小
	const size_t el_num;    // 内存中可存的对象数
public:
	ConsecutiveList(size_t _el_num, size_t _el_size);
	void* get();
	void put(void*);
	~ConsecutiveList();
};
