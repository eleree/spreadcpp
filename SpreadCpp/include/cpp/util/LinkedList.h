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
				_head = new Node;
				_tail = _head;
				_end = new Node; 
				_tail->next = _end;
				_end->prev = _tail;
			}

			~LinkedList()
			{
				cout << "~Linked List" << endl;
			}
			
			class iterator
			{
			public:
				iterator(){};
				iterator & operator++()
				{

				}

				const T & operator*() const
				{

				}

				bool operator!=(iterator& rhs) const
				{
					return this->_node != rhs->_node;
				}

			protected:
				Node * _node;
				iterator(Node * n) :_node(n) {};
				friend class LinkedList<T>;
			};
				
			iterator begin()
			{
				iterator iter(_head->next);
				return iter;
			}

			iterator end()
			{
				iterator iter(_tail->next);
				return iter;
			}

			int32_t add(T t) {
				Node * newNode = new Node;				
				newNode->prev = _tail;
				newNode->next = _end;
				_tail->next = newNode;				
				_tail = newNode;
				_tail->t = t;
				_end->prev = _tail;
				_size++;
				return 0;
			}

			int32_t remove(T t) {
				Node * n = _head->next;
				if (size() == 0)
					return 0;

				while (n != _end)
				{
					if (n->t == t)
					{
						if (n == _tail)
							_tail = n->prev;
						n->prev->next = n->next;					
						n->next->prev = n->prev;
						delete n;
						break;
					}
					n = n->next;
				}
				_size--;
				return 0;
			}

			int32_t size(void) {
				return _size;
			};

			T front(void)
			{				
				return _head->next->t;
			}

			void clear()
			{

			}


		private:
			int32_t _size;
			Node * _head;
			Node * _tail;
			Node * _end;
		};
	}
}
#endif