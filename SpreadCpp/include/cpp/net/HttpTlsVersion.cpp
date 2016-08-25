#include "cpp/net/HttpTlsVersion.h"

using namespace cpp::net;

std::mutex HttpTlsVersion::_mutex;
map<string, const SSL_METHOD *> HttpTlsVersion::_methodMap = map<string, const SSL_METHOD *>();
