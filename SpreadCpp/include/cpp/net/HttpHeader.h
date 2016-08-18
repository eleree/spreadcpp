#ifndef _CPP_NET_HTTP_HEADER_H_
#define _CPP_NET_HTTP_HEADER_H_

#include <mutex>
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdint.h>

#include <cpp/lang/String.h>

using namespace std;
using namespace cpp::lang;

namespace cpp{
	namespace net{
		class HttpHeader{
		public:
			HttpHeader(){};
			~HttpHeader(){};

			int32_t clear(void)
			{
				_nameValueVector.clear();
			}

			string get(string name)
			{
				if (_nameValueVector.size() <= 0)
					return "";

				for (uint32_t i = 0; i < _nameValueVector.size(); i += 2)
				{
					// Found it, the return
					if (String::equalsIgnoreCase(name, _nameValueVector[i]))
						return _nameValueVector[i+1];
				}

				return "";
			}

			HttpHeader& add(string name, string value)
			{
				if (name.empty() || value.empty())
					return *this;

				for (uint32_t i = 0; i < _nameValueVector.size(); i+=2)
				{
					// There is the header already
					if (String::equalsIgnoreCase(name,_nameValueVector[i]))
						return *this;
				}

				_nameValueVector.push_back(name);
				_nameValueVector.push_back(value);

				return *this;

			}

			HttpHeader& remove(string name)
			{				
				if (name.empty())
					return *this;

				for (uint32_t i = 0; i < _nameValueVector.size(); i += 2)
				{
					// There is the header already
					if (String::equalsIgnoreCase(name, _nameValueVector[i]))
					{
						// Remove name and value pair
						_nameValueVector.erase(_nameValueVector.begin() + i);
						_nameValueVector.erase(_nameValueVector.begin() + i);
					}
				}

				return *this;
			}			

			HttpHeader& set(string name, string value)
			{
				if (name.empty() || value.empty())
					return *this;

				for (uint32_t i = 0; i < _nameValueVector.size(); i += 2)
				{
					// Found, just update it
					if (String::equalsIgnoreCase(name, _nameValueVector[i]))
					{
						_nameValueVector[i + 1] = value;
						return *this;
					}
				}
				// Not found, just add it
				return add(name, value);
			}

			uint32_t size(void)
			{
				return _nameValueVector.size()/2;
			}

			string toString(void)
			{
				string result;

				for (uint32_t i = 0; i < _nameValueVector.size(); i += 2)
				{
					result.append(_nameValueVector[i]);
					result.append(":");
					result.append(_nameValueVector[i+1]);
					result.append("\r\n");
				}

				return result;
			}

		private:
			vector<string> _nameValueVector;
		};
	}
}
#endif