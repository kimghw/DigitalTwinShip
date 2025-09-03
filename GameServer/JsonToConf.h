#include <nlohmann/json.hpp>
#include <winsock2.h>
#include <iostream>
#include <iphlpapi.h>
#include <iptypes.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

struct ServerIpInfo
{
	std::wstring ip;
	std::uint32_t port;
	std::uint32_t maxSessionCount;
	std::string dsn;
	std::string username;
	std::string password;

};

struct hostInfo
{
	char host[256];
	char* ip;
	struct hostent* host_entry;
	int hostname;
};


class ServerConf
{
public:
	static std::wstring stringToWString(const std::string& str)
	{
		int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
		if (len == 0) return L""; 

		std::wstring ws(len - 1, 0);
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &ws[0], len);

		return ws;
	}

	// both external file including ip address 
	// and port and initial ip address and port go into the function as arguments.

	static void Init(const string& jsonFileName, ServerIpInfo& conf) {

		try {
			ServerConf::Init_IPconfig(jsonFileName, conf);
			
		}
		catch (...)
		{
			cout << "IP: 127.0.0.1 is connected" << endl;
		}
		std::wcout << "IPAddress :" << conf.ip << ", Port :" << conf.port << endl;

	}
	static void Init_IPconfig(const string& jsonFileName, ServerIpInfo& conf)
	{
			nlohmann::json jconfig;

		try {
			std::ifstream inputfile(jsonFileName);
			if (!inputfile.is_open())
				throw std::runtime_error("Failed to open the Json file");

			try {
				inputfile >> jconfig;
				inputfile.close();
			}
			catch (const std::exception& e){std::cerr<<"runtime error : " << e.what()<<std::endl;}

			if (jconfig["USE"] == 0)
			{
				wcout << "Using the loopback IP Address : 127.0.0.1 "<< endl;
				return;
			}
			conf.ip = stringToWString(jconfig["SERVER_IP"]);
			conf.port = (int32)jconfig["SERVER_PORT"];
			conf.maxSessionCount = (int32)jconfig["SERVER_MAXSESSIONCOUNT"];

			conf.dsn = jconfig["DB_DSN"];
			conf.username = jconfig["DB_USERNAME"];
			conf.password = jconfig["DB_PASSWORD"];
			wcout << "Success to get IP from JsonFile : " << conf.ip << endl;

		}
		catch (const std::exception& e) {
			std::cerr << "Runtime error: " << e.what() << std::endl;
			std::cout << "Automatically getting the IP address from the network" << endl;
			GetServerInfo(conf.ip);
		}
	}

	static void GetServerInfo(std::wstring& confip)
	{
		//hostInfo serverInfo;

		try {
			WSADATA wsaData;
			WSAStartup(MAKEWORD(2, 2), &wsaData);

			DWORD dwSize = sizeof(IP_ADAPTER_INFO);
			IP_ADAPTER_INFO* pAdapterInfo = (IP_ADAPTER_INFO*)malloc(dwSize);

			if (GetAdaptersInfo(pAdapterInfo, &dwSize) == ERROR_BUFFER_OVERFLOW) {
				free(pAdapterInfo);
				pAdapterInfo = (IP_ADAPTER_INFO*)malloc(dwSize);
			}

			if (GetAdaptersInfo(pAdapterInfo, &dwSize) == NO_ERROR) {
				for (IP_ADAPTER_INFO* pAdapter = pAdapterInfo; pAdapter != NULL; pAdapter = pAdapter->Next) {
					// 첫 번째 IP 주소만 출력
					if (pAdapter->IpAddressList.IpAddress.String != NULL) {
						std::string ipAddr = pAdapter->IpAddressList.IpAddress.String;
						confip = stringToWString(ipAddr);
						std::cout << "Success to get the IP Address: " << pAdapter->IpAddressList.IpAddress.String << std::endl;
					}
				}
			}

			if (pAdapterInfo) {
				free(pAdapterInfo);
			}

		}
		catch (...)
		{
			cout << "failed to get server information" << endl;
		}
	}
};