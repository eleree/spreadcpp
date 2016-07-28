#ifndef _CPP_NET_DNS_H_
#define _CPP_NET_DNS_H_

#include <list>
#include <string>
#include <stdint.h>
#if defined(_WIN32) ||  defined(_WIN64)
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
// link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
#endif

using namespace std;
using namespace cpp::net;

namespace cpp{
	namespace net{
		class DNS{
		public:
			DNS(string host, uint16_t port) :_host(host), _port(port), _isResolved(false)
			{

			}

			int32_t resolve(uint32_t timeout)
			{
				int32_t rc = 0;
				INT iRetval;
				INT iResult;
				WSADATA wsaData;
				int i = 1;

				struct addrinfo hints;
				struct addrinfo *ptr = NULL;
				struct addrinfo *result = NULL;
				struct sockaddr_in  *sockaddr_ipv4;
				LPSOCKADDR sockaddr_ip;
				char ipstringbuffer[46];
				DWORD ipbufferlength = 46;
				DWORD dwRetval;

				ZeroMemory(&hints, sizeof(hints));
				hints.ai_family = AF_UNSPEC;
				hints.ai_socktype = SOCK_STREAM;
				hints.ai_protocol = IPPROTO_TCP;

				iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
				if (iResult != 0) {
					printf("WSAStartup failed: %d\n", iResult);
					return 1;
				}

				dwRetval = getaddrinfo(_host.c_str(), NULL, &hints, &result);
				if (dwRetval != 0) {
					printf("getaddrinfo failed with error: %d\n", dwRetval);
					WSACleanup();
					return 1;
				}
				// Retrieve each address and print out the hex bytes
				for (ptr = result; ptr != NULL; ptr = ptr->ai_next) 
				{

					printf("getaddrinfo response %d\n", i++);
					printf("\tFlags: 0x%x\n", ptr->ai_flags);
					printf("\tFamily: ");
					switch (ptr->ai_family) {
					case AF_UNSPEC:
						printf("Unspecified\n");
						break;
					case AF_INET:
						printf("AF_INET (IPv4)\n");
						sockaddr_ipv4 = (struct sockaddr_in *) ptr->ai_addr;
						printf("\tIPv4 address %s\n",
							inet_ntoa(sockaddr_ipv4->sin_addr));
						break;
					case AF_INET6:
						printf("AF_INET6 (IPv6)\n");
						// the InetNtop function is available on Windows Vista and later
						// sockaddr_ipv6 = (struct sockaddr_in6 *) ptr->ai_addr;
						// printf("\tIPv6 address %s\n",
						//    InetNtop(AF_INET6, &sockaddr_ipv6->sin6_addr, ipstringbuffer, 46) );

						// We use WSAAddressToString since it is supported on Windows XP and later
						sockaddr_ip = (LPSOCKADDR)ptr->ai_addr;
						// The buffer length is changed by each call to WSAAddresstoString
						// So we need to set it for each iteration through the loop for safety
						ipbufferlength = 46;
						iRetval = WSAAddressToString(sockaddr_ip, (DWORD)ptr->ai_addrlen, NULL,
							ipstringbuffer, &ipbufferlength);
						if (iRetval)
							printf("WSAAddressToString failed with %u\n", WSAGetLastError());
						else
							printf("\tIPv6 address %s\n", ipstringbuffer);
						break;
					case AF_NETBIOS:
						printf("AF_NETBIOS (NetBIOS)\n");
						break;
					default:
						printf("Other %ld\n", ptr->ai_family);
						break;
					}
					printf("\tSocket type: ");
					switch (ptr->ai_socktype) {
					case 0:
						printf("Unspecified\n");
						break;
					case SOCK_STREAM:
						printf("SOCK_STREAM (stream)\n");
						break;
					case SOCK_DGRAM:
						printf("SOCK_DGRAM (datagram) \n");
						break;
					case SOCK_RAW:
						printf("SOCK_RAW (raw) \n");
						break;
					case SOCK_RDM:
						printf("SOCK_RDM (reliable message datagram)\n");
						break;
					case SOCK_SEQPACKET:
						printf("SOCK_SEQPACKET (pseudo-stream packet)\n");
						break;
					default:
						printf("Other %ld\n", ptr->ai_socktype);
						break;
					}
					printf("\tProtocol: ");
					switch (ptr->ai_protocol) {
					case 0:
						printf("Unspecified\n");
						break;
					case IPPROTO_TCP:
						printf("IPPROTO_TCP (TCP)\n");
						break;
					case IPPROTO_UDP:
						printf("IPPROTO_UDP (UDP) \n");
						break;
					default:
						printf("Other %ld\n", ptr->ai_protocol);
						break;
					}
					printf("\tLength of this sockaddr: %d\n", ptr->ai_addrlen);
					printf("\tCanonical name: %s\n", ptr->ai_canonname);
				}
				return 0;
			}

			list<string> getIPv4Address(void)
			{
				return _ipv4Address;
			}

			list<string> getIPv6Address(void)
			{
				return _ipv6Address;
			}

		private:
			string _host;
			uint16_t _port;
			bool _isResolved;
			list<string> _ipv4Address;
			list<string> _ipv6Address;
		};
	}
}

#endif