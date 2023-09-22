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



std::wstring stringToWString(const std::string& str);

class JsonToConf
{
public:

	static void Init(string jsonFileName, serverConf& conf)
	{
		std::ifstream inputfile(jsonFileName);
		nlohmann::json jconfig;

		inputfile >> jconfig;
		conf.ip = stringToWString(jconfig["SERVER_IP"]);
		conf.port = (int32)jconfig["SERVER_PORT"];
		conf.maxSessionCount = (int32)jconfig["SERVER_MAXSESSIONCOUNT"];

		conf.dsn = jconfig["DB_DSN"];
		conf.username = jconfig["DB_USERNAME"];
		conf.password = jconfig["DB_PASSWORD"];


		inputfile.close();
	}
};