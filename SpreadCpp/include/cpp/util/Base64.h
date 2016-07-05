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
			static std::string encode(std::string inputStr);
			static std::string decode(std::string inputStr);
			static int32_t encode(const char * inputData, const uint32_t inputLen, char * outputBuf, uint32_t * outputLen, uint32_t maxOutputLen);
			static int32_t decode(const char * inputData, const uint32_t inputLen, char * outputBuf, uint32_t * outputLen, uint32_t maxOutputLen);
		private:
			static const char _base64EncodeTable[65];
			static const char _base64DecodeTable[256];
		};
	}
}
#endif