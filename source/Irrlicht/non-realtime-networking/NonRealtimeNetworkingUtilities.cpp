#include "NonRealtimeNetworkingUtilities.h"
#include "NonRealtimeNetworkingException.h"
#include "SOAP/GameWSSOap.nsmap"

namespace irrlicht_nonrealtimenetworking {

	// Constructor for the web service
	NonRealtimeNetworkingUtilities::NonRealtimeNetworkingUtilities(char* masterServerHostAddress) {
		initializeWS(masterServerHostAddress);
	}

	// Destructor, releasing memory
	NonRealtimeNetworkingUtilities::~NonRealtimeNetworkingUtilities() {
		delete webServiceAddress;
		delete soap;
		delete gameName;
	}

	void NonRealtimeNetworkingUtilities::setBuffer(char* buffer) {
		this->buffer = new char[strlen(buffer) + 1];
		strcpy(this->buffer, buffer);
	}

	/**
		Check if given string represents a valid IP address. Instead
		of localhost use 127.0.0.1 to pass validation test.
	*/
	void NonRealtimeNetworkingUtilities::validateIpAddress(char* ipAddress) {

		struct sockaddr_in sa;
		int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
		if (result == 0)
			throw new NonRealtimeNetworkingException("Provided string is not a valid IP address.");

	}

	/**
	set portnum to which socket will be bound
	default value defined by PORT_NUMBER constant
	*/
	void NonRealtimeNetworkingUtilities::setPortNumber(int portNumber) {
		if (portNumber < 0)
			throw NonRealtimeNetworkingException("Negative port number.");
		this->portNumber = portNumber;
	}

	/**
	Check installed winsock2 version
	*/
	void NonRealtimeNetworkingUtilities::checkVersion() {

		WORD wVersionRequested;
		int wsaerr;

		// Using MAKEWORD macro, Winsock version request 2.2
		wVersionRequested = MAKEWORD(2, 2);

		wsaerr = WSAStartup(wVersionRequested, &wsaData);
		if (wsaerr != 0)
		{
			throw NonRealtimeNetworkingException("Server: The Winsock dll not found!\n");
		}

		// TO DO how to concatenate char* ?
		if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2 )
		{
			// Tell the user that we could not find a usable WinSock DLL.
			WSACleanup();
			throw NonRealtimeNetworkingException("WinSock version not supported: " + LOBYTE(wsaData.wVersion) + HIBYTE(wsaData.wVersion));
		}

	}

	/**
	Open a server socket, listen to port number that's currently set
	*/
	void NonRealtimeNetworkingUtilities::openServerSocket() {

		checkVersion();		

		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		// Check for errors to ensure that the socket is a valid socket.
		if (s == INVALID_SOCKET)
		{
			WSACleanup();
			throw NonRealtimeNetworkingException("Invalid socket: " + WSAGetLastError());
		}

		// Create a sockaddr_in object and set its values.
		sockaddr_in service;

		// AF_INET is the Internet address family.
		service.sin_family = AF_INET;
		// Listen for a connection from any IP address
		service.sin_addr.s_addr = inet_addr("0.0.0.0");
		// The socket will be bound to the port number set by setPortNumber() method
		service.sin_port = htons(portNumber);

		// Call the bind function, passing the created socket and the sockaddr_in structure as parameters.
		// Check for general errors.
		if (bind(s, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
		{
			closesocket(s);
			throw new NonRealtimeNetworkingException("Bind failed: " + WSAGetLastError());
		}

		// Call the listen function, passing the created socket and the maximum number of allowed
		// connections to accept as parameters. Check for general errors.
		if (listen(s, 10) == SOCKET_ERROR)
			throw NonRealtimeNetworkingException("Listen failed: " + WSAGetLastError());

	}

	/**
	Accept the TCP connection request from client.
	*/
	void NonRealtimeNetworkingUtilities::acceptClient() {
		SOCKET AcceptSocket;

		while (1)
		{
			AcceptSocket = SOCKET_ERROR;
			while (AcceptSocket == SOCKET_ERROR)
			{
				AcceptSocket = accept(s, NULL, NULL);
			}
			// else, accept the connection...
			// When the client connection has been accepted, transfer control from the
			// temporary socket to the original socket and stop checking for new connections.
			s = AcceptSocket;
			break;
		}
	}

	/**
	host a game by opening a server socket and waiting for clients
	*/
	void NonRealtimeNetworkingUtilities::hostGame(int portNo) {
		setPortNumber(portNo);
		openServerSocket();
		acceptClient();
	}

	/**
	Open a client socket and connect to the server.
	@param ipAddress IP address of the server
	*/
	void NonRealtimeNetworkingUtilities::openClientSocket(char* ipAddress) {

		checkVersion();

		SOCKADDR_IN target; // Socket address information

		target.sin_family = AF_INET; // address family Internet
		target.sin_port = htons(portNumber); // Port to connect on
		target.sin_addr.s_addr = inet_addr(ipAddress); // Target IP

		s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); // Create socket
		if (s == INVALID_SOCKET)
		{
			throw NonRealtimeNetworkingException("Socket creation failed.");
		}  

		// connect, throw exception if fails
		if (connect(s, (SOCKADDR *)&target, sizeof(target)) == SOCKET_ERROR)
		{
			throw NonRealtimeNetworkingException("Connection failed.");
		}

	}

	/**
	Open a client socket and connect to the server.
	@param ipAddress IP address of the server
	*/
	void NonRealtimeNetworkingUtilities::joinGame(char* ipAddress, int portNo) {
		setPortNumber(portNo);
		openClientSocket(ipAddress);
	}
	
	void NonRealtimeNetworkingUtilities::receiveDataThread(){
        DWORD threadId[1];
        NonRealtimeNetworkingUtilities *pp = this;
        HANDLE threadHandle = CreateThread(NULL, 0, networkingThread, pp, 0, NULL);
        WaitForSingleObject(threadHandle, INFINITE);
        CloseHandle(threadHandle);
    }

    DWORD WINAPI NonRealtimeNetworkingUtilities::networkingThread(LPVOID lpParam){
        NonRealtimeNetworkingUtilities* utility = (NonRealtimeNetworkingUtilities*)lpParam;
        
        if(utility != NULL){
            std::cout<< "the new thread utility is ok";
            utility->receiveData();
        }
        return 0;
    }

	/**
	Send the content of the buffer to the other side of the pipe.
	The buffer must be set beforehand.
	*/
	void NonRealtimeNetworkingUtilities::sendData() {

		if (strlen(buffer) == 0 || strcmp(buffer, "") == 0)
			throw NonRealtimeNetworkingException("Buffer empty. Set buffer before sending!");

		int iResult;

		char* sendBuffer = new char[strlen(buffer) + strlen(BUFFER_LIMIT) + 1];
		strcpy(sendBuffer, buffer);
		strcat(sendBuffer, BUFFER_LIMIT);

		// Send an initial buffer
		iResult = send(s, sendBuffer, (int)strlen(sendBuffer), 0);
		if (iResult == SOCKET_ERROR) {
			closesocket(s);
			WSACleanup();
			throw NonRealtimeNetworkingException("Send failed: " + WSAGetLastError());
		}

	}

	/**
	Receive the data, will be written to buffer
	*/
	void NonRealtimeNetworkingUtilities::receiveData() {

		int bytesRecv = SOCKET_ERROR;
		char* tmpBuffer = new char[256];
		bytesRecv = recv(s, tmpBuffer, 256, 0);

		if (bytesRecv == SOCKET_ERROR)
			throw NonRealtimeNetworkingException("Receive failed: " + WSAGetLastError());
		
		// remove random characters from the end of received string:
		std::string tmp = std::string(tmpBuffer);
		size_t length = tmp.find(BUFFER_LIMIT);
		delete tmpBuffer;
		// delete buffer;
		buffer = new char[length + 1];
		strcpy(buffer, tmp.substr(0, length).c_str());

	}

	/**
	Close the connection and clean up.
	*/
	void NonRealtimeNetworkingUtilities::closeConnection ()
	{
		//Close the socket if it exists
		if (s)
			closesocket(s);

		WSACleanup(); //Clean up Winsock
	}

	/**
		Initialize the library to use the web service. Set the address of the WSDL
		file and initialize SOAP structure.
		@param masterServerHostAddress IP address of the web service
	*/
	void NonRealtimeNetworkingUtilities::initializeWS(char* masterServerHostAddress) {

		/// Check if given string is a potentially correct IP address
		validateIpAddress(masterServerHostAddress);
		/// Allocate memory for the string
		webServiceAddress = new char[59];
		/// Create the string
		strcpy(webServiceAddress, "http://");
		strcat(webServiceAddress, masterServerHostAddress);
		strcat(webServiceAddress, ":8/MasterGameServer/GameWS.asmx?wsdl");
		/// Initialize SOAP structure
		soap = soap_new();

	}

	/// Set gameName to register for on the server
	void NonRealtimeNetworkingUtilities::setGameName(char* gameName) {
		/// Allocate memory
		this->gameName = new char[strlen(gameName) + 1];
		/// Copy the string
		strcpy(this->gameName, gameName);
	}

	/**
		Check if the library was properly initialized to work with the web service.
		There are two conditions that need to hold here: the address of the web service
		has to be specified and SOAP structure has to be initialized before
		calling any WebMethod.
	*/
	void NonRealtimeNetworkingUtilities::checkSOAP() {

		/// Check if the address of WS's WSDL file was specified.
		if (strlen(webServiceAddress) == 0 || strcmp(webServiceAddress, "") == 0)
			throw new NonRealtimeNetworkingException("The address of the web service was not specified.");
		/// Check if SOAP structure was initialized
		if (soap == NULL)
			throw new NonRealtimeNetworkingException("SOAP was not initialized.");

	}

	/**
		Get the list of games registered on the server. 
	*/
	char** NonRealtimeNetworkingUtilities::getGamesList() {

		/// Check if SOAP structure was initialized
		checkSOAP();

		/// Create structures needed for request and response
		_GameWS__getGamesPlayed* getGamesListCall = new _GameWS__getGamesPlayed();
		_GameWS__getGamesPlayedResponse* getGamesListResult = new _GameWS__getGamesPlayedResponse();

		/// Call the web service to retrieve the list of games registered
		if (!(soap_call___GameWS__getGamesPlayed(soap, webServiceAddress, NULL, getGamesListCall, getGamesListResult) == SOAP_OK))
			throw new NonRealtimeNetworkingException("SOAP error occured: " + soap->errnum);

		/// Convert std::vector<std::string> to char**

		/// Create a temporary copy for code clarity
		std::vector<std::string> gamesList = getGamesListResult->getGamesPlayedResult->string;
		/// Allocate memory for char*
		char** games = new char*[gamesList.size()];

		for (int i=0; i<gamesList.size(); i++) {
			/// Allocate memory for each string separately
			games[i] = new char[gamesList[i].size() + 1];
			/// Copy the string
			strcpy(games[i], gamesList[i].c_str());
		}

		/// Return the list of games
		return games;

	}

	/**
		When a player registers on the server his IP address is saved
		and a unique ID for a given game is generated for him. That way
		when another player registers to play the same game he can easily
		obtain opponent's IP address and establish a connection with him.
	*/
	void NonRealtimeNetworkingUtilities::registerOnTheServer() {

		/// Check if SOAP was initialized
		checkSOAP();

		/// Create structures needed for request and response
		_GameWS__register* registerCall = new _GameWS__register(); 
		_GameWS__registerResponse* registerResult = new _GameWS__registerResponse();

		/// Check if the name of the game to register for was set
		if (strlen(gameName) == 0 || strcmp(gameName, "") == 0)
			throw new NonRealtimeNetworkingException("gameName not specified!");

		/// Set gameName in the request structure
		registerCall->gameName = new std::string(this->gameName);

		/**
			Call the web service. Pointers to request and response structures
			are passed here. That way, if the call succeeds, response structure 
			will contain data of interest. If something goes wrong, we throw
			an exception together with an error message. 
		*/
		if (!(soap_call___GameWS__register(soap, webServiceAddress, NULL, registerCall, registerResult) == SOAP_OK))
			throw new NonRealtimeNetworkingException("SOAP error occured: " + soap->errnum);

		int sessionId = registerResult->registerResult;

		/// If returned sessionID is <= 0 then something went wrong!
		if (sessionId < 1)
			throw new NonRealtimeNetworkingException("Could not obtain session's ID from the server!");

		/// Set sessionId
		this->sessionId = sessionId;

	}

	/**
		Get IP address of your opponent from the server 
		to be able to open a client socket and play.
	*/
	char* NonRealtimeNetworkingUtilities::getOpponentsIpAddress() {
		
		/// Check if SOAP was initialized
		checkSOAP();

		/// This structure is needed to set request's parameters (name of the game and session ID)
		_GameWS__getOpponentsIpAddress* getOpponentsIpAddressCall = new _GameWS__getOpponentsIpAddress();
		/// This structure will hold the response
		_GameWS__getOpponentsIpAddressResponse* getOpponentsIpAddressResult = new _GameWS__getOpponentsIpAddressResponse();

		/// Make sure that we registered on the WS
		if (strlen(gameName) == 0 || strcmp(gameName, "") == 0 || sessionId == 0)
			throw new NonRealtimeNetworkingException("gameName or sessionId not specified.");

		/// Set request parameters
		getOpponentsIpAddressCall->gameName = new std::string(gameName);
		getOpponentsIpAddressCall->sessionId = sessionId;

		/// Call the WS
		if (!(soap_call___GameWS__getOpponentsIpAddress(soap, webServiceAddress, NULL, getOpponentsIpAddressCall, getOpponentsIpAddressResult) == SOAP_OK))
			throw new NonRealtimeNetworkingException("SOAP error occured: " + soap->errnum);

		/// Need to return char*, converting from std::string:
		char* ipAddress = new char[getOpponentsIpAddressResult->getOpponentsIpAddressResult->size() + 1];
		std::copy(getOpponentsIpAddressResult->getOpponentsIpAddressResult->begin(), getOpponentsIpAddressResult->getOpponentsIpAddressResult->end(), ipAddress);
		ipAddress[getOpponentsIpAddressResult->getOpponentsIpAddressResult->size()] = '\0';

		// return the IP address
		return ipAddress;

	}

	/**
		Register on the web service to obtain unique session ID
		for a given game. Depending on that ID a player either hosts a game
		or joins an already hosted game to start playing.
		@param gameName name of the game to be played
		@param portNo port number to open a server/client socket on
	*/
	int NonRealtimeNetworkingUtilities::establishConnection(char* gameName, int portNo = 0) {
		
		// Check if gameName is not empty
		if (strlen(gameName) == 0 || strcmp(gameName, "") == 0)
			throw new NonRealtimeNetworkingException("Establish connection: gameName cannot be empty!");

		/// Check if SOAP was initialized
		checkSOAP();

		/// Set port number if it was specified
		if (portNo != 0)
			setPortNumber(portNo);

		// Set gameName 
		setGameName(gameName);

		/// Register player on the server to obtain session's ID
		registerOnTheServer();

		/**
			Open server/client socket depending on
			session's ID which was generated by the web service.
		*/
		if ((sessionId % 2) == 1) // Odd ID - hosting the game (server socket)
			hostGame(portNumber);
		else // Even ID - joining the game (client socket)
			joinGame(getOpponentsIpAddress(), portNumber);

		/// Return session's ID
		return sessionId;

	}

};