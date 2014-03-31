#include "NonRealtimeNetworkingUtilities.h"
#include "NonRealtimeNetworkingException.h"
#include "SOAP/GameWSSOap.nsmap"

namespace irrlicht_nonrealtimenetworking {

	// Constructor for the web service
	NonRealtimeNetworkingUtilities::NonRealtimeNetworkingUtilities(std::string masterServerHostAddress) {
		initializeWS(masterServerHostAddress);
	}

	/**
		Initialize the library to use the web service. Set the address of the WSDL
		file and initialize SOAP structure.
	*/
	void NonRealtimeNetworkingUtilities::initializeWS(std::string masterServerHostAddress) {

		validateIpAddress(masterServerHostAddress);
		webServiceAddress = "http://" + masterServerHostAddress + ":8/MasterGameServer/GameWS.asmx?wsdl";
		soap = soap_new(); // Initialize SOAP

	}

	/**
		Check if given string represents a valid IP address. Instead
		of localhost use 127.0.0.1 to pass validation.
	*/
	void NonRealtimeNetworkingUtilities::validateIpAddress(std::string ipAddress) {

		struct sockaddr_in sa;
		int result = inet_pton(AF_INET, ipAddress.c_str(), &(sa.sin_addr));
		if (result == 0)
			throw new NonRealtimeNetworkingException("Provided string is not a valid IP address.");

	}

	/**
	Destructor
	*/
	NonRealtimeNetworkingUtilities::~NonRealtimeNetworkingUtilities() {
		delete soap;
	}

	/**
	set buffer to be sent later
	*/
	void NonRealtimeNetworkingUtilities::setBuffer(std::string buffer) {
		this->buffer = buffer;
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
	void NonRealtimeNetworkingUtilities::openClientSocket(std::string ipAddress) {

		checkVersion();

		SOCKADDR_IN target; // Socket address information

		target.sin_family = AF_INET; // address family Internet
		target.sin_port = htons (portNumber); // Port to connect on
		target.sin_addr.s_addr = inet_addr (ipAddress.c_str()); // Target IP

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
	void NonRealtimeNetworkingUtilities::joinGame(std::string ipAddress, int portNo) {
		setPortNumber(portNo);
		openClientSocket(ipAddress);
	}

	/**
	Send the content of the buffer to the other side of the pipe.
	The buffer must be set beforehand.
	*/
	void NonRealtimeNetworkingUtilities::sendData() {

		if (buffer == "" || buffer.length() == 0)
			throw NonRealtimeNetworkingException("Buffer empty. Set buffer before sending!");

		int iResult;

		char* sendBuffer = new char[buffer.length() + strlen(BUFFER_LIMIT) + 1];
		strcpy(sendBuffer, buffer.c_str());
		strcat(sendBuffer, BUFFER_LIMIT);

		// Send an initial buffer
		iResult = send(s, sendBuffer, (int) strlen(sendBuffer), 0);
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
		buffer = std::string(tmpBuffer);
		size_t length = buffer.find(BUFFER_LIMIT);
		buffer = buffer.substr(0, length);

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

	// Web Service functions

	/**
		Check if the library was properly initialized to work with the web service.
	*/
	void NonRealtimeNetworkingUtilities::checkSOAP() {

		/// Check if the address of WS's WSDL file was specified.
		if (webServiceAddress.length() == 0 || webServiceAddress == "")
			throw new NonRealtimeNetworkingException("The address of the web service was not specified.");
		/// Check if SOAP structure was initialized
		if (soap == NULL)
			throw new NonRealtimeNetworkingException("SOAP was not initialized.");

	}

	/**
		Get the list of games registered on the server. 
	*/
	std::vector<std::string> NonRealtimeNetworkingUtilities::getGamesList() {

		checkSOAP();

		_GameWS__getGamesPlayed* getGamesListCall = new _GameWS__getGamesPlayed();
		_GameWS__getGamesPlayedResponse* getGamesListResult = new _GameWS__getGamesPlayedResponse();

		if (!(soap_call___GameWS__getGamesPlayed(soap, webServiceAddress.c_str(), NULL, getGamesListCall, getGamesListResult) == SOAP_OK))
			throw new NonRealtimeNetworkingException("SOAP error occured: " + soap->errnum);

		return getGamesListResult->getGamesPlayedResult->string;

	}

	/**
		When a player registers on the server his IP address is saved
		and a unique ID for a given game is generated for him. That way
		when another player registers to play the same game he can easily
		obtain opponent's IP address and establish connection with him.
	*/
	void NonRealtimeNetworkingUtilities::registerOnTheServer() {

		checkSOAP(); // Check if SOAP was initialized

		_GameWS__register* registerCall = new _GameWS__register(); 
		_GameWS__registerResponse* registerResult = new _GameWS__registerResponse();

		if (gameName.length() == 0 || gameName == "")
			throw new NonRealtimeNetworkingException("gameName not specified!");

		registerCall->gameName = new std::string(this->gameName);

		if (!(soap_call___GameWS__register(soap, webServiceAddress.c_str(), NULL, registerCall, registerResult) == SOAP_OK))
			throw new NonRealtimeNetworkingException("SOAP error occured: " + soap->errnum);

		int sessionId = registerResult->registerResult;

		// if (sessionId < 0) --> ERROR ?

		this->sessionId = sessionId;

	}

	/**
		Get IP address of your opponent from the server 
		to be able to open a client socket and play.
	*/
	std::string NonRealtimeNetworkingUtilities::getOpponentsIpAddress() {

		checkSOAP(); // Check if SOAP was initialized

		/// This structure is needed to set request's parameters (name of the game and session ID)
		_GameWS__getOpponentsIpAddress* getOpponentsIpAddressCall = new _GameWS__getOpponentsIpAddress();
		/// This structure will hold the response
		_GameWS__getOpponentsIpAddressResponse* getOpponentsIpAddressResult = new _GameWS__getOpponentsIpAddressResponse();

		/// Make sure that we registered on the WS
		if (gameName.length() == 0 || gameName == "" || sessionId == 0)
			throw new NonRealtimeNetworkingException("gameName or sessionId not specified.");

		/// Set request parameters
		getOpponentsIpAddressCall->gameName = new std::string(gameName);
		getOpponentsIpAddressCall->sessionId = sessionId;

		/// Call the WS
		if (!(soap_call___GameWS__getOpponentsIpAddress(soap, webServiceAddress.c_str(), NULL, getOpponentsIpAddressCall, getOpponentsIpAddressResult) == SOAP_OK))
			throw new NonRealtimeNetworkingException("SOAP error occured: " + soap->errnum);

		return *getOpponentsIpAddressResult->getOpponentsIpAddressResult;

	}

	/**
		Register on the web service to obtain unique session ID
		for a given game. Depending on that ID a player either hosts a game
		or joins an already hosted game to start playing.
	*/
	int NonRealtimeNetworkingUtilities::establishConnection(std::string gameName, int portNo = 0) {

		checkSOAP(); // Check if SOAP was initialized

		if (portNo != 0) // Port number specified as an actual parameter
			setPortNumber(portNo);

		setGameName(gameName);

		/// Register player on the server to obtain session's ID
		registerOnTheServer();

		/// Open socket
		if ((sessionId % 2) == 1) // Odd ID - hosting the game (server socket)
			hostGame(portNumber);
		else // Even ID - joining the game (client socket)
			joinGame(getOpponentsIpAddress(), portNumber);

		return sessionId;

	}

	/**
		Allocate memory and set gameName for further
		use by other web service related functions.
	*/
	void NonRealtimeNetworkingUtilities::setGameName(std::string gameName) {
		this->gameName = gameName;
	}

};