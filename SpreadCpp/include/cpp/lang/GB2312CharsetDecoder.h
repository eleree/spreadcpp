#ifndef _CPP_LANG_GB2312_CHARSET_DECODER_H_
#define _CPP_LANG_GB2312_CHARSET_DECODER_H_

#include <stdint.h>
#include <cpp/lang/CharsetDecoder.h>

namespace cpp{
	namespace lang{
		class GB2312CharsetDecoder:public CharsetDecoder
		{
		public:
			GB2312CharsetDecoder(){};
			~GB2312CharsetDecoder(){};
			/* Decode To Unicode */
			string decode(string fromString);
			string decode(const unsigned char * fromBytes);
		private:
			uint16_t decodeBytes(uint16_t gb2312Bytes);
			static uint16_t _tableGB2312ToUnicode[][2];
		};
	}
}

#endif