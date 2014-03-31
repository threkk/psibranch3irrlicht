#ifndef nonrealtimenetworking
#define nonrealtimenetworking

#include "SOAP/soapH.h"

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <winsock.h>

#define BUFFER_LIMIT "!@#$%"
#define PORT_NUMBER 27015

namespace irrlicht_nonrealtimenetworking {
	class __declspec(dllexport)NonRealtimeNetworkingUtilities {
	
	private:
		SOCKET s;
		std::string buffer;
		int portNumber;
		WSADATA wsaData;

		// Web Service
		std::string webServiceAddress; // Address of the master server
		struct soap* soap; // Struct needed for SOAP
		std::string gameName; // Name of the game being played
		int sessionId; // Player's ID

		void checkVersion();

		// Web Service
		void checkSOAP();
		std::string getOpponentsIpAddress();
		void validateIpAddress(std::string ipAddress);

	public:
		NonRealtimeNetworkingUtilities() { portNumber = PORT_NUMBER; };
		NonRealtimeNetworkingUtilities(int portNumber) { this->portNumber = portNumber; };
		NonRealtimeNetworkingUtilities(std::string masterServerHostAddress);
		~NonRealtimeNetworkingUtilities();
		
		// server 
		void openServerSocket();
		void acceptClient();
		void hostGame(int portNo);

		// client
		void openClientSocket(std::string ipAddress);
		void joinGame(std::string ipAddress, int portNo);

		// send/receive
		void sendData();
		void receiveData();

		// terminate
		void closeConnection();

		// getters/setters
		void setBuffer(std::string buffer);
		std::string getBuffer() { return buffer; };
		void setPortNumber(int portNumber);
		int getPortNumber() { return portNumber; };

		// WinSock Errors
		int getWSALastError() { return WSAGetLastError(); };

		// Web Service
		int establishConnection(std::string gameName, int portNo);
		void registerOnTheServer();
		std::vector<std::string> getGamesList();
		void setGameName(std::string gameName);
		void initializeWS(std::string masterServerHostAddress);
	};

};
#endif