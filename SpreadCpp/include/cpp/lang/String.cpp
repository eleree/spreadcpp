#include <cpp/lang/String.h>

using namespace cpp::lang;

string String::convert(string s, Charset from, Charset to)
{
	GB2312CharsetDecoder gb2312Decoder;
	UTF8CharsetEncoder utf8Encoder;
	if (from == Charset::GB2312 && to == Charset::UTF8)
		return utf8Encoder.encode(gb2312Decoder.decode((const unsigned char *)s.c_str()));
	if (from == Charset::UNICODE && to == Charset::UTF8)
		return utf8Encoder.encode(s);
	return "";
}