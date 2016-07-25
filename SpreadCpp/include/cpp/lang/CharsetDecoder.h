#ifndef _CPP_LANG_CHARSET_DECODER_H_
#define _CPP_LANG_CHARSET_DECODER_H_

#include <string>

using namespace std;

namespace cpp{
	namespace lang{
		class CharsetDecoder
		{
		public:
			CharsetDecoder(){};
			virtual ~CharsetDecoder(){};
			/* Decode To Unicode */
			virtual string decode(string from) = 0;
		};
	}
}

#endif