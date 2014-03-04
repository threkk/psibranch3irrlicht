#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <winsock.h>

#define PORT_NUMBER 27015

class NonRealtimeNetworkingUtilities {

private:
	SOCKET s;
	char* buffer;
	int portNumber;
	WSADATA wsaData;

	bool checkVersion(); 

public:
	NonRealtimeNetworkingUtilities() { portNumber = PORT_NUMBER; };
	NonRealtimeNetworkingUtilities(int portNumber) { this->portNumber = portNumber; };
	~NonRealtimeNetworkingUtilities();
	void openServerSocket();
	void acceptClient();
	void openClientSocket(char* ipAddress);
	void sendData();
	void receiveData();
	void closeConnection();
	void setBuffer(char* buffer);
	char* getBuffer() { return buffer; }
	void setPortNumber(int portNumber) { this->portNumber = portNumber; }
	int getPortNumber() { return portNumber; }

};
