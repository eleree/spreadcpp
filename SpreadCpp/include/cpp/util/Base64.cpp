#include <cpp/util/Base64.h>

using namespace cpp::util;

Base64::Base64()
{
}


Base64::~Base64()
{

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
	*outputLen = j;

	return 0;
}

