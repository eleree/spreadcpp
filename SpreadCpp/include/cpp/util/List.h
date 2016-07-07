#ifndef _CPP_UTIL_LIST_H_
#define _CPP_UTIL_LIST_H_

#include <iostream>
using namespace std;

template<typename T>
class List{
public:
	List(){ cout << "List" << endl; };
	virtual ~List(){ cout << "~List" << endl; };
	virtual void add(T) {};
	virtual void remove(T) {};
};

#endif