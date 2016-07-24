#ifndef _CPP_NET_HTTP_HEADER_H_
#define _CPP_NET_HTTP_HEADER_H_

#include <map>
#include <memory>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdint.h>

using namespace std;

namespace cpp{
	namespace net{
		class HttpHeader{
		public:
			HttpHeader(){};
			~HttpHeader(){};

			string get(string name)
			{
				auto search = _nameValueMap.find(name);
				if (search != _nameValueMap.end()) {
					return search->second;
				}
				return "";
			}

			HttpHeader& set(string name, string value)
			{
				if (name.empty() || value.empty())
					return *this;

				std::pair<std::map<string, string>::iterator, bool> ret;
				ret = _nameValueMap.insert(std::pair<string, string>(name, value));
				if (ret.second == false)
				{
					_nameValueMap.erase(name);
					_nameValueMap.insert(std::pair<string, string>(name, value));
				}

				return *this;
			}

			uint32_t size(void)
			{
				return _nameValueMap.size();
			}

			string toString(void)
			{
				string result;
				for (auto &kv : _nameValueMap) {		
					result.append(kv.first).append(":").append(kv.second).append("\r\n");					
				}
				return result;
			}

		private:
			map<string, string> _nameValueMap;
		};
	}
}
#endif