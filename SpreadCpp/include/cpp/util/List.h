#ifndef _CPP_UTIL_LIST_H_
#define _CPP_UTIL_LIST_H_

#include <iostream>
#include <stdint.h>
using namespace std;

template<typename T>
class List{
public:
	List(){};
	virtual ~List(){ cout << "~List" << endl; };
	virtual int32_t add(T) { return 0; };
	virtual int32_t remove(T) { return 0; };
};

#endif