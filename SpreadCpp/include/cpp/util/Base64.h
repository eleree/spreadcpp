#ifndef _CPP_UTIL_BASE64_H_
#define _CPP_UTIL_BASE64_H_

#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <cstdio>
#include <string>


using namespace std;
namespace cpp{
	namespace util{		
		class Base64{
		public:
			Base64();
			~Base64();
			std::string encode(std::string inputStr);
			std::string decode(std::string inputStr);
			int32_t encode(const char * inputData, const uint32_t inputLen, char * outputBuf, uint32_t * outputLen, uint32_t maxOutputLen);
			int32_t decode(const char * inputData, const uint32_t inputLen, char * outputBuf, uint32_t * outputLen, uint32_t maxOutputLen);
		private:
			static const char _base64EncodeTable[65];
			static const char _base64DecodeTable[256];
		};
	}
}
#endif