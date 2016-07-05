#include <cpp/util/Base64.h>

using namespace cpp::util;

const char Base64::_base64EncodeTable[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const char Base64::_base64DecodeTable[256] =
{
	/* ASCII table */
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
	64, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
	64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
};


Base64::Base64()
{
}


Base64::~Base64()
{

}

std::string Base64::encode(std::string inputStr)
{
	int32_t outputLen = inputStr.size()/3*4 + ((inputStr.size() % 3 )!=0?4:0)+ 1;
	char * outputBuf = new char[outputLen];
	memset(outputBuf, 0, outputLen);
	Base64::encode(inputStr.c_str(), (uint32_t)inputStr.size(), outputBuf, NULL, outputLen);
	string outputStr = string(outputBuf);
	delete outputBuf;
	return outputStr;
}

std::string Base64::decode(std::string inputStr)
{
	string x = "YWJj";

	return x;
}

int32_t Base64::encode(const char * inputData, const uint32_t inputLen,
	char * outputBuf, uint32_t * outputLen, uint32_t maxOutputLen)
{

	uint32_t j = 0;
	int32_t tempInputLen = inputLen;
	if (inputData == NULL || inputLen == 0)
		return -1;
	if (outputBuf == NULL || maxOutputLen < (inputLen / 3 * 4))
		return -1;

	for (uint32_t i = 0; tempInputLen > 0; tempInputLen -= 3, i += 3, j += 4)
	{
		uint32_t bigNum = (inputData[i] << 16) +
			((i + 1>inputLen) ? 0 : (inputData[i + 1] << 8)) +
			((i + 2>inputLen) ? 0 : inputData[i + 2]);
		outputBuf[j] = _base64EncodeTable[(bigNum >> 18) & 0x00003F];
		outputBuf[j + 1] = _base64EncodeTable[(bigNum >> 12) & 0x00003F];
		outputBuf[j + 2] = _base64EncodeTable[(bigNum >> 6) & 0x00003F];
		outputBuf[j + 3] = _base64EncodeTable[bigNum & 0x00003F];
	}

	for (uint32_t i = 0; i < (3 - inputLen % 3) % 3; i++)
		outputBuf[j - i - 1] = '=';

	if (outputLen!=NULL)
		*outputLen = j;

	return 0;
}

int32_t Base64::decode(const char * inputData, const uint32_t inputLen,
	char * outputBuf, uint32_t * outputLen, uint32_t maxOutputLen)
{
	uint32_t j = 0;
	int32_t tempInputLen = inputLen;
	if (inputData == NULL || inputLen == 0)
		return -1;
	if (outputBuf == NULL || maxOutputLen == 0)
		return -1;

	for (uint32_t i = 0; tempInputLen > 0; tempInputLen -= 4, i += 4, j += 3)
	{
		uint32_t bigNum = (_base64DecodeTable[inputData[i]] << 18) +
			(_base64DecodeTable[inputData[i + 1]] << 12) +
			(inputData[i + 2] == '=' ? 0 : _base64DecodeTable[inputData[i + 2]] << 6) +
			(inputData[i + 3] == '=' ? 0 : _base64DecodeTable[inputData[i + 3]]);
		outputBuf[j] = (bigNum >> 16) & 0xFF;
		outputBuf[j + 1] = (bigNum >> 8) & 0xFF;
		outputBuf[j + 2] = (bigNum)& 0xFF;
	}
	if (inputData[inputLen - 1] == '=')
		j--;
	if (inputData[inputLen - 2] == '=')
		j--;
	if (outputLen != NULL)
		*outputLen = j;

	return 0;
}

