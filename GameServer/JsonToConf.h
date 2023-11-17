#include <nlohmann/json.hpp>
#include <winsock2.h>
#include <iostream>

struct serverConf
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


class JsonToConf
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

	static void Init(const string& jsonFileName, serverConf& conf) {

		try {
			JsonToConf::Init_IPconfig(jsonFileName, conf);
			cout << "Success to get IP information" << endl;
		}
		catch (...)
		{
			cout << "IP: 127.0.0.1 is connected" << endl;
		}
	}
	static void Init_IPconfig(const string& jsonFileName, serverConf& conf)
	{
		try {
			std::ifstream inputfile(jsonFileName);
			if (!inputfile.is_open())
			{
				throw std::runtime_error("Failed to open the Json file");
			}

			nlohmann::json jconfig;

			try {inputfile >> jconfig;}
			catch (const std::exception& e){std::cerr<<"runtime error : " << e.what()<<std::endl;}

			conf.ip = stringToWString(jconfig["SERVER_IP"]);
			conf.port = (int32)jconfig["SERVER_PORT"];
			conf.maxSessionCount = (int32)jconfig["SERVER_MAXSESSIONCOUNT"];

			conf.dsn = jconfig["DB_DSN"];
			conf.username = jconfig["DB_USERNAME"];
			conf.password = jconfig["DB_PASSWORD"];

			inputfile.close();
		}
		catch (const std::exception& e) {
			std::cerr << "Runtime error: " << e.what() << std::endl;
			GetServerInfo(conf.ip);
		}
	}

	static void GetServerInfo(std::wstring& confIp)
	{
		hostInfo serverInfo;

		try {
			serverInfo.hostname = gethostname(serverInfo.host, sizeof(serverInfo.host));
			if (serverInfo.hostname == -1) {
				perror("gethostname");
				exit(1);
			}

			serverInfo.host_entry = gethostbyname(serverInfo.host);
			if (serverInfo.host_entry == nullptr) {
				perror("gethostbyname");
				exit(1);
			}

			serverInfo.ip = inet_ntoa(*((struct in_addr*)serverInfo.host_entry->h_addr_list[0]));

			std::wcout << "IPAddress :" << serverInfo.ip << endl;

			confIp = stringToWString(serverInfo.ip);
			WSACleanup();
		}
		catch (...)
		{
			cout << "failed to get server information" << endl;
		}
	}
};