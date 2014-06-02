#ifndef NON_REALTIME_NETWORKING_UTILITIES_H
#define NON_REALTIME_NETWORKING_UTILITIES_H

#include "../../../include/IrrCompileConfig.h" // DLL export/import definition
#include "SOAP/soapH.h"

#include <iostream>
#include <fstream>
#include <sstream>
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
		char* login; // Player's login
		char* opponentsIP; // Opponent's IP address
		int sessionId; // Player's ID
		bool hosting; // Determines whether current player is a hosting player
		int checkInInterval; // Check in interval required by the server

		// Common attributes
		char* buffer;
		int portNumber;

		// WinSock methods
		void checkVersion();

		// Web Service methods
		void checkSOAP();		

		// Common methods
		void validateIpAddress(char* ipAddress);

		void assignPlayerAttributes(GameWS__PlayRequestResult* requestResult);

		char* convertStringToCharPointer(std::string* string);

		bool stringEmpty(char* string);

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

		// WinSock terminate
		void closeConnection();

		// Common getters/setters
		void setBuffer(char* buffer);
		char* getBuffer() { return buffer; };
		void setPortNumber(int portNumber);
		int getPortNumber() { return portNumber; };
		void setLogin(char* login);
		char* getLogin() { return login; };

		// WinSock Errors
		int getWSALastError() { return WSAGetLastError(); };

		// Web Service methods
		int establishConnection(char* gameName, int portNo);
		int registerOnTheServer();
		char** getGamesList();
		void setGameName(char* gameName);
		int getSessionId() { return sessionId; };
		void initializeWS(char* masterServerHostAddress);
		int addPlayerScore(float score);
		char** getHighScores(int limit = 0);
		int playAgain();
		int checkIn();
		void playGame();
		char* getOpponentsIP() { return opponentsIP; };
		int removePlayer();
		char* getErrorMessage(int errorCode);

		// ERROR CODES:

		// Score errors:
		static const int SCORE_TOO_SMALL = -5;

		// Register errors:
		static const int NO_SUCH_PLAYER = -4;
		static const int GAME_NAME_EMPTY = -3;
		static const int LOGIN_TAKEN = -2;
		static const int NO_SUCH_GAME = -1;
	};

};
#endif