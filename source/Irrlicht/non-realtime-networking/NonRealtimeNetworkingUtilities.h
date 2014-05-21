#ifndef NON_REALTIME_NETWORKING_UTILITIES_H
#define NON_REALTIME_NETWORKING_UTILITIES_H

#include "../../../include/IrrCompileConfig.h" // DLL export/import definition
#include "SOAP/soapH.h"


#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <tchar.h>
#include <winsock.h>

#define BUFFER_LIMIT "!@#$%"
#define PORT_NUMBER 6

namespace irrlicht_nonrealtimenetworking {
	class IRRLICHT_API NonRealtimeNetworkingUtilities {
	
	private:
		// WinSock attributes
		SOCKET s;
		WSADATA wsaData;

		// Web Service attributes
		char* webServiceAddress; // Address of the master server
		struct soap* soap; // Struct needed for SOAP
		char* gameName; // Name of the game being played
		int sessionId; // Player's ID

		// Common attributes
		char* buffer;
		int portNumber;

		// WinSock methods
		void checkVersion();

		// Web Service methods
		void checkSOAP();		

		// Common methods
		void validateIpAddress(char* ipAddress);

	public:
		// Constructors
		NonRealtimeNetworkingUtilities() { this->portNumber = PORT_NUMBER; };
		NonRealtimeNetworkingUtilities(int portNumber) { this->portNumber = portNumber; };
		NonRealtimeNetworkingUtilities(char* masterServerHostAddress);
		~NonRealtimeNetworkingUtilities();
		
		// WinSock server 
		void openServerSocket();
		void acceptClient();
		void hostGame(int portNo);

		// WinSock client
		void openClientSocket(char* ipAddress);
		void joinGame(char* ipAddress, int portNo);

		// WinSock send/receive
		void sendData();
		void receiveData();
		void receiveDataThread();
        static DWORD WINAPI networkingThread(LPVOID lpParam);


		// WinSock terminate
		void closeConnection();

		// Common getters/setters
		void setBuffer(char* buffer);
		char* getBuffer() { return buffer; };
		void setPortNumber(int portNumber);
		int getPortNumber() { return portNumber; };

		// WinSock Errors
		int getWSALastError() { return WSAGetLastError(); };

		// Web Service methods
		int establishConnection(char* gameName, int portNo);
		void registerOnTheServer();
		char* getOpponentsIpAddress();
		char** getGamesList();
		void setGameName(char* gameName);
		int getSessionId() { return sessionId; };
		void initializeWS(char* masterServerHostAddress);
	};

};
#endif