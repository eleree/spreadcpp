#ifndef _CPP_LANG_UTF8_CHARSET_ENCODER_H_
#define _CPP_LANG_UTF8_CHARSET_ENCODER_H_

#include <stdint.h>
#include <string>

using namespace std;

namespace cpp
{
	namespace lang
	{
		class UTF8CharsetEncoder
		{
		public:
			UTF8CharsetEncoder(){};
			~UTF8CharsetEncoder(){};
			string encode(string s);
			string encode(const char * s);
		private:
			string encodeBytes(uint32_t s);
		};
	}
}
#endif