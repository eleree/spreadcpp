#include <cpp/lang/UTF8CharsetEncoder.h>

#include <iostream>
using namespace cpp::lang;
string UTF8CharsetEncoder::encode(string s)
{
	return UTF8CharsetEncoder::encode(s.c_str());
}

string UTF8CharsetEncoder::encode(const char * s)
{
	uint8_t * us = (uint8_t*)s;
	string x;	
	if (strlen(s) % 2 != 0)
		return "";
	for (uint32_t i=0; i < strlen(s); i += 2);
	{
		uint32_t pointBytes = (uint32_t)((*us) * 256 + *(us + 1));
		x.append(encodeBytes(pointBytes));
	}
	return x;
}

string UTF8CharsetEncoder::encodeBytes(uint32_t cp)
{
	unsigned char encodeBuf[6];
	unsigned char * result = encodeBuf;
	if (cp < 0x80)                        // one octet
		*(result++) = static_cast<uint8_t>(cp);
	else if (cp < 0x800) {                // two octets
		*(result++) = static_cast<uint8_t>((cp >> 6) | 0xc0);
		*(result++) = static_cast<uint8_t>((cp & 0x3f) | 0x80);
	}
	else if (cp < 0x10000) {              // three octets
		*(result++) = static_cast<uint8_t>((cp >> 12) | 0xe0);
		*(result++) = static_cast<uint8_t>(((cp >> 6) & 0x3f) | 0x80);
		*(result++) = static_cast<uint8_t>((cp & 0x3f) | 0x80);
	}
	else {                                // four octets
		*(result++) = static_cast<uint8_t>((cp >> 18) | 0xf0);
		*(result++) = static_cast<uint8_t>(((cp >> 12) & 0x3f) | 0x80);
		*(result++) = static_cast<uint8_t>(((cp >> 6) & 0x3f) | 0x80);
		*(result++) = static_cast<uint8_t>((cp & 0x3f) | 0x80);
	}
	string x((char *)encodeBuf, (result - encodeBuf )/sizeof(char));
	return x;
}
