#pragma once
class ServerPacketHandler
{
private : 
	ServerPacketHandler();
	~ServerPacketHandler();


public : 
	static ServerPacketHandler& GetInstance()
	{
		static ServerPacketHandler instance;
		return instance;
	}

	ServerPacketHandler(const ServerPacketHandler&) = delete;
	ServerPacketHandler operator =(const ServerPacketHandler&) = delete;





public :
	

};

