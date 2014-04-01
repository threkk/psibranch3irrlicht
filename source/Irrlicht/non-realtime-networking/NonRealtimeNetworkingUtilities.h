#ifndef NON_REALTIME_NETWORKING_UTILITIES_H
#define NON_REALTIME_NETWORKING_UTILITIES_H

#include "../../../include/IrrCompileConfig.h" // DLL export/import definition
#include "SOAP/soapH.h"


#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <winsock.h>

#define BUFFER_LIMIT "!@#$%"
#define PORT_NUMBER 6

namespace irrlicht_nonrealtimenetworking {
	class IRRLICHT_API NonRealtimeNetworkingUtilities {
	
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
		void validateIpAddress(char* ipAddress);

	public:
		NonRealtimeNetworkingUtilities() { this->portNumber = PORT_NUMBER; };
		NonRealtimeNetworkingUtilities(int portNumber) { this->portNumber = portNumber; };
		NonRealtimeNetworkingUtilities(char* masterServerHostAddress);
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
		char* getOpponentsIpAddress();
		std::vector<std::string> getGamesList();
		void setGameName(char* gameName);
		int getSessionId() { return sessionId; };
		void initializeWS(char* masterServerHostAddress);
	};

};
#endif