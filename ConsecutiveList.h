#pragma once
#include <forward_list>
#include <mutex>

class ConsecutiveList {
private:
	void* ptr;   // ָ��һ���������ڴ�
	void* upper_bound_address;   // ptr��ָ�������ڴ���Ͻ�
	std::forward_list<void*> list;   // ���ڴ��ָ�����������е�ָ��ָ�������ڴ��е�ÿ��������ʼ��ַ
	const size_t el_size;   // �����С
	const size_t el_num;    // �ڴ��пɴ�Ķ�����
	std::mutex mutex_;
public:
	ConsecutiveList(size_t _el_num, size_t _el_size);
	void* get();
	void put(void*);
	~ConsecutiveList();
};