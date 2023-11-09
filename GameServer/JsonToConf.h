#include <nlohmann/json.hpp>

struct serverConf
{
	std::wstring ip;
	std::uint32_t port;
	std::uint32_t maxSessionCount;
	std::string dsn;
	std::string username;
	std::string password;
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

	static void Init(string jsonFileName, serverConf& conf)
	{
		std::ifstream inputfile(jsonFileName);
		if (!inputfile.is_open())
		{
			throw std::runtime_error("Failed to open the Json file");
		}

		nlohmann::json jconfig;

		try
		{
			inputfile >> jconfig;
		}
		catch (const std::exception& e)
		{
			std::cerr<<"runtime error : " << e.what()<<std::endl;
		}

		conf.ip = stringToWString(jconfig["SERVER_IP"]);
		conf.port = (int32)jconfig["SERVER_PORT"];
		conf.maxSessionCount = (int32)jconfig["SERVER_MAXSESSIONCOUNT"];

		conf.dsn = jconfig["DB_DSN"];
		conf.username = jconfig["DB_USERNAME"];
		conf.password = jconfig["DB_PASSWORD"];

		inputfile.close();
	}

	//static void jsonToPkt();
};