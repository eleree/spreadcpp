#ifndef _CPP_UTIL_LINKED_LIST_H_
#define _CPP_UTIL_LINKED_LIST_H_

#include <iostream>
#include <stdint.h>
#include <cpp/util/List.h>

using namespace std;
namespace cpp{
	namespace util{

		template<typename T>
		class LinkedList : public List<T>
		{
			struct Node
			{
			public:
				T t;
				Node * next;
				Node * prev;
				Node() : next(NULL), prev(NULL){}
			};

		public:
			LinkedList() : _head(NULL), _tail(NULL), _size(0)
			{
				cout << "Linked List" << endl;
			}

			~LinkedList()
			{
				cout << "~Linked List" << endl;
			}

			int32_t add(T t) {
				if (_head == NULL)
				{
					_head = new Node;
					_tail = _head;
					_head->next = _head;
					_tail->next = _head;
					_head->t = t;
				}
				else{
					_tail->next = new Node;
					_tail->next->prev = _tail;
					_tail->next->next = _head;
					_tail->next->t = t;
					_tail = _tail->next;
				}
				_size++;
				return 0;
			}

			int32_t remove(T t) {
				return 0;
			}

			int32_t size(void) {
				return _size;
			};

			void clear()
			{

			}

		private:
			int32_t _size;
			Node * _head;
			Node * _tail;
		};
	}
}
#endif