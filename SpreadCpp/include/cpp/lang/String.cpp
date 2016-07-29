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


string String::substring(string& thisString, uint32_t beginIndex)
{
	if (thisString.length() <= beginIndex)
		return "";
	return thisString.substr(beginIndex);
}

string String::substring(string& thisString, uint32_t beginIndex, uint32_t endIndex)
{
	if (thisString.length() <= beginIndex)
		return thisString.substr(beginIndex);
	return thisString.substr(beginIndex, endIndex-beginIndex);
}

bool String::regionMatches(string& thisString, uint32_t toffset, string& otherString, uint32_t ooffset, uint32_t len)
{
	if (thisString.length() < (toffset + len) || otherString.length() < (ooffset + len))
		return false;

	if (thisString.substr(toffset, len).compare(otherString.substr(ooffset, len)) == 0)
		return true;
	else
		return false;

}

char String::charAt(string thisString, uint32_t index)
{
	return thisString.at(index);
}

int32_t String::indexOf(string thisString, const char c)
{
	return thisString.find(c);
}

int32_t String::indexOf(string thisString, const char c, int32_t fromIndex)
{
	return thisString.find(c,fromIndex);
}