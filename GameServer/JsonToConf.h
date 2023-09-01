#include <nlohmann/json.hpp>

struct serverConf
{
	std::wstring ip;
	std::uint32_t port;
	std::uint32_t maxSessionCount;
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
	}
};