#include <cpp/lang/String.h>

using namespace cpp::lang;

string String::convert(string s, Charset from, Charset to)
{
	GB2312CharsetDecoder gb2312Decoder;
	return gb2312Decoder.decode((const unsigned char *)s.c_str());
}