#ifndef _CPP_LANG_STRING_H_
#define _CPP_LANG_STRING_H_

#include <iostream>
#include <stdint.h>
#include <string>
#include <cpp/lang/GB2312CharsetDecoder.h>
#include <cpp/lang/UTF8CharsetEncoder.h>
using namespace std;

namespace cpp{
	namespace lang{
		class String{
		public:
			String(){};
			~String(){};
			enum Charset{
				GB2312,
				UTF8,
				UNICODE,
			};
			static string convert(string s, Charset from, Charset to);

		private:
		};
	}
}
#endif