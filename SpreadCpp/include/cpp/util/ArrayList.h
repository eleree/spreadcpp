#ifndef _CPP_UTIL_ARRAY_LIST_H_
#define _CPP_UTIL_ARRAY_LIST_H_

#include <iostream>
#include <cpp/util/List.h>

using namespace std;


template<typename T>
class ArrayList : public List<T>
{
public:
	ArrayList(){ cout << "Arrary List" << endl; }
	ArrayList(T t){ cout << "Arrary List" << endl; }
	~ArrayList(){ cout << "~Arrary List" << endl; }
	void add(T){}
	void remove(T){}
};

#endif