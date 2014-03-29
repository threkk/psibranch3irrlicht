#ifndef nonrealtimenetworking
#define nonrealtimenetworking

#include "SOAP/soapH.h"

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <winsock.h>

#define PORT_NUMBER 27015

namespace irrlicht_nonrealtimenetworking {
	class __declspec(dllexport)NonRealtimeNetworkingUtilities {

	private:
		SOCKET s;
		char* buffer;
		int portNumber;
		WSADATA wsaData;

		// Web Service
		char* webServiceAddress; // Address of the master server
		struct soap* soap; // Struct needed for SOAP
		char* gameName; // Name of the game being played
		int sessionId; // Player's ID

		void checkVersion();

		// Web Service
		void checkSOAP();
		char* getOpponentsIpAddress();
		void validateIpAddress(const char* ipAddress);

	public:
		NonRealtimeNetworkingUtilities() { portNumber = PORT_NUMBER; };
		NonRealtimeNetworkingUtilities(int portNumber) { this->portNumber = portNumber; };
		NonRealtimeNetworkingUtilities(const char* masterServerHostAddress);
		~NonRealtimeNetworkingUtilities();
		
		// server 
		void openServerSocket();
		void acceptClient();
		void hostGame(int portNo);

		// client
		void openClientSocket(char* ipAddress);
		void joinGame(char* ipAddress, int portNo);

		// send/receive
		void sendData();
		void receiveData();

		// terminate
		void closeConnection();

		// getters/setters
		void setBuffer(char* buffer);
		char* getBuffer() { return buffer; };
		void setPortNumber(int portNumber);
		int getPortNumber() { return portNumber; };

		// WinSock Errors
		int getWSALastError() { return WSAGetLastError(); };

		// Web Service
		int establishConnection(char* gameName, int portNo);
		void registerOnTheServer();
		std::vector<std::string> getGamesList();
		void setGameName(char* gameName);
		void initializeWS(const char* masterServerHostAddress);
	};

};
#endif