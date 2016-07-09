#ifndef _CPP_UTIL_QUEUE_H_
#define _CPP_UTIL_QUEUE_H_

#include <iostream>
#include <stdint.h>
using namespace std;

template<typename T>
class Queue{
public:
	Queue(){};
	virtual ~Queue(){ cout << "~Queue" << endl; };
	virtual int32_t push(T) { return 0; };
	virtual int32_t pop(T) { return 0; };
};

#endif