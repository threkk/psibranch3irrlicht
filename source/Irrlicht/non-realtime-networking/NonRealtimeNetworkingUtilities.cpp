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

	void NonRealtimeNetworkingUtilities::setLogin(char* login) {
		this->login = new char[strlen(login) + 1];
		strcpy(this->login, login);
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

	/**
	Send the content of the buffer to the other side of the pipe.
	The buffer must be set beforehand.
	*/
	void NonRealtimeNetworkingUtilities::sendData() {

		if (stringEmpty(buffer))
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
		char* tmpBuffer = new char[1000];
		bytesRecv = recv(s, tmpBuffer, 1000, 0);

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

		login = NULL;

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
		if (stringEmpty(webServiceAddress))
			throw new NonRealtimeNetworkingException("The address of the web service was not specified.");
		/// Check if SOAP structure was initialized
		if (soap == NULL)
			throw new NonRealtimeNetworkingException("SOAP was not initialized.");

	}

	/**
		When a player registers on the server his IP address is saved
		and a unique ID for a given game is generated for him. That way
		when another player registers to play the same game he can easily
		obtain opponent's IP address and establish a connection with him.
	*/
	int NonRealtimeNetworkingUtilities::registerOnTheServer() {

		/// Check if SOAP was initialized
		checkSOAP();

		/// Create structures needed for request and response
		_GameWS__register* registerCall = new _GameWS__register(); 
		_GameWS__registerResponse* registerResult = new _GameWS__registerResponse();

		/// Check if the name of the game to register for was set
		if (stringEmpty(gameName))
			throw new NonRealtimeNetworkingException("gameName not specified!");

		/// Set gameName in the request structure
		registerCall->gameName = new std::string(this->gameName);

		if (login == NULL)
			setLogin("");

		/// Set player login in request structure if such was specified
		registerCall->login = new std::string(this->login);

		/**
			Call the web service. Pointers to request and response structures
			are passed here. That way, if the call succeeds, response structure 
			will contain data of interest. If something goes wrong, we throw
			an exception together with an error message. 
		*/
		if (!(soap_call___GameWS__register(soap, webServiceAddress, NULL, registerCall, registerResult) == SOAP_OK))
			throw new NonRealtimeNetworkingException("SOAP error occured: " + soap->errnum);

		GameWS__PlayRequestResult* result = registerResult->registerResult;

		if (result->errorCode != 0) // Error occured
			return result->errorCode;

		assignPlayerAttributes(result);

		return 0;

	}

	/**
		Sends a request to remove player with given session ID
		from the server.
	*/
	int NonRealtimeNetworkingUtilities::removePlayer() {

		// Player has to exist on the server in order to remove him
		if (sessionId < 1)
			throw new NonRealtimeNetworkingException("Session ID was not assigned. Register on the server to obtain one.");

		_GameWS__removePlayer* removePlayerRequest = new _GameWS__removePlayer();
		_GameWS__removePlayerResponse* removePlayerResponse = new _GameWS__removePlayerResponse();

		// Set session ID in the request structure
		removePlayerRequest->sessionId = this->sessionId;

		// Call the WS
		if (!(soap_call___GameWS__removePlayer(soap, webServiceAddress, NULL, removePlayerRequest, removePlayerResponse) == SOAP_OK))
			throw new NonRealtimeNetworkingException("SOAP error occured: " + soap->errnum);

		// ZERO all player attributes inside the class
		sessionId = 0;
		login = opponentsIP = gameName = NULL;
		hosting = false;
		
		return removePlayerResponse->removePlayerResult;

	}

	/**
		Obtains a list of best scores for a given game.
		@param limit list size limit (optional)
	*/
	char** NonRealtimeNetworkingUtilities::getHighScores(int limit) {

		if (limit < 0)
			throw new NonRealtimeNetworkingException("Invalid limit provided!");

		// Check if gameName is not empty
		if (stringEmpty(gameName))
			throw new NonRealtimeNetworkingException("Game name was not set.");

		_GameWS__getScoreList* getScoreListRequest = new _GameWS__getScoreList();
		_GameWS__getScoreListResponse* getScoreListResponse = new _GameWS__getScoreListResponse();

		getScoreListRequest->gameName = new std::string(this->gameName);
		getScoreListRequest->limit = limit;

		if (!(soap_call___GameWS__getScoreList(soap, webServiceAddress, NULL, getScoreListRequest, getScoreListResponse) == SOAP_OK))
			throw new NonRealtimeNetworkingException("SOAP error occured: " + soap->errnum);

		if (getScoreListResponse->getScoreListResult == NULL)
			return NULL;

		/// Create a temporary copy for code clarity
		std::vector<GameWS__Score*> scoreList = getScoreListResponse->getScoreListResult->Score;

		/// Convert to char**:

		/// Allocate memory for char*
		char** scores = new char*[scoreList.size()];

		for (int i=0; i<scoreList.size(); i++) {
			/// Allocate memory for each string separately
			std::ostringstream ss;
			ss << scoreList[i]->score;
			std::string stringScore(ss.str());
			std::string result = std::string(stringScore + *(scoreList[i]->playerLogin));
			scores[i] = new char[result.size() + 1];
			/// Copy the string
			strcpy(scores[i], result.c_str());
		}

		/// Return the list of scores
		return scores;

	}

	/**
		Checks in on the server.
	*/
	int NonRealtimeNetworkingUtilities::checkIn() {

		if (sessionId < 1)
			throw new NonRealtimeNetworkingException("Session ID was not assigned. Register on the server to obtain one.");

		_GameWS__checkIn* checkInRequest = new _GameWS__checkIn();
		_GameWS__checkInResponse* checkInResponse = new _GameWS__checkInResponse();

		checkInRequest->sessionId = this->sessionId;

		if (!(soap_call___GameWS__checkIn(soap, webServiceAddress, NULL, checkInRequest, checkInResponse) == SOAP_OK))
			throw new NonRealtimeNetworkingException("SOAP error occured: " + soap->errnum);

		return checkInResponse->checkInResult;

	}

	/**
		Calls the web service to add player's score to the
		list of best scores for the game he's playing.
		Returns error code on failure or 0 if everytinh
		went well.
	*/
	int NonRealtimeNetworkingUtilities::addPlayerScore(float score) {

		// Score cannot be negative
		if (score < 0)
			throw new NonRealtimeNetworkingException("Invalid score provided!");

		if (sessionId < 1)
			throw new NonRealtimeNetworkingException("Session ID was not assigned. Register on the server to obtain one.");

		_GameWS__addScore* addScoreRequest = new _GameWS__addScore();
		_GameWS__addScoreResponse* addScoreResponse = new _GameWS__addScoreResponse();

		addScoreRequest->sessionId = this->sessionId;
		addScoreRequest->score = score;

		if (!(soap_call___GameWS__addScore(soap, webServiceAddress, NULL, addScoreRequest, addScoreResponse) == SOAP_OK))
			throw new NonRealtimeNetworkingException("SOAP error occured: " + soap->errnum);

		return addScoreResponse->addScoreResult;

	}

	/**
		Converts std::string into char*
	*/
	char* NonRealtimeNetworkingUtilities::convertStringToCharPointer(std::string* string) {

		if (string == NULL || string->size() == 0)
			return NULL;

		char* returnBuffer = new char[string->size() + 1];
		std::copy(string->begin(), string->end(), returnBuffer);
		returnBuffer[string->size()] = '\0';

		return returnBuffer;

	}

	/**
		Check if given char* points to a real string
	*/
	bool NonRealtimeNetworkingUtilities::stringEmpty(char* string) {

		if (string == NULL || strlen(string) == 0 || strcmp(string, "") == 0)
			return true;
		else
			return false;

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

		if (getGamesListResult->getGamesPlayedResult == NULL)
			return NULL;

		/// Create a temporary copy for code clarity
		std::vector<GameWS__Game*> gamesList = getGamesListResult->getGamesPlayedResult->Game;
		/// Allocate memory for char*
		char** games = new char*[gamesList.size()];
		gamesList[0]->name;

		for (int i=0; i<gamesList.size(); i++) {
			/// Allocate memory for each string separately
			games[i] = new char[gamesList[i]->name->size() + 1];
			/// Copy the string
			strcpy(games[i], gamesList[i]->name->c_str());
		}

		/// Return the list of games
		return games;

	}

	/**
		Register on the web service to obtain data necessary
		to start playing.
		@param gameName name of the game to be played
		@param portNo port number to open a server/client socket on
	*/
	int NonRealtimeNetworkingUtilities::establishConnection(char* gameName, int portNo = 0) {
		
		// Check if gameName is not empty
		if (stringEmpty(gameName))
			throw new NonRealtimeNetworkingException("Establish connection: gameName cannot be empty!");

		/// Check if SOAP was initialized
		checkSOAP();

		/// Set port number if it was specified
		if (portNo != 0)
			setPortNumber(portNo);

		// Set gameName 
		setGameName(gameName);

		/// Register player on the server to obtain session's ID
		int error = registerOnTheServer();

		if (error < 0)
			return error;

		playGame();

		return 0;

	}

	/**
		Opens a socket using data obtained from the server.
	*/
	void NonRealtimeNetworkingUtilities::playGame() {

		// Session ID needs to be assigned before calling this function
		if (sessionId < 1)
			throw new NonRealtimeNetworkingException("Session ID was not assigned. Register on the server to obtain one.");

		if (hosting == true) // Host game
			hostGame(portNumber);
		else // Join the opponent
			joinGame(opponentsIP, portNumber);

	}

	/**
		Called when a player wants to play again. Session
		ID needs to be assigned before calling this function.
	*/
	int NonRealtimeNetworkingUtilities::playAgain() {

		// Session ID not assigned, need to register first
		if (sessionId < 1)
			throw new NonRealtimeNetworkingException("Session ID was not assigned. Register on the server to obtain one.");

		// Request structure
		_GameWS__play* playAgainCall = new _GameWS__play(); 
		// Response structure
		_GameWS__playResponse* playAgainResult = new _GameWS__playResponse();

		// Put session ID in the request structure
		playAgainCall->sessionId = this->sessionId;

		// Call the web service
		if (!(soap_call___GameWS__play(soap, webServiceAddress, NULL, playAgainCall, playAgainResult) == SOAP_OK))
			throw new NonRealtimeNetworkingException("SOAP error occured: " + soap->errnum);

		GameWS__PlayRequestResult* playRequestResult = playAgainResult->playResult;

		// Error occured, terminate function
		if (playRequestResult->errorCode != 0)
			return playRequestResult->errorCode;

		// Process the response
		assignPlayerAttributes(playRequestResult);

		// Return no error
		return 0;
	}

	
	/**
		Process data obtained from the web service.
	*/
	void NonRealtimeNetworkingUtilities::assignPlayerAttributes(GameWS__PlayRequestResult* requestResult) {

		hosting = requestResult->hosting;
		sessionId = requestResult->sessionId;
		opponentsIP = convertStringToCharPointer(requestResult->opponentsIP);
		login = convertStringToCharPointer(requestResult->login);
		checkInInterval = requestResult->checkInInterval;

	}

	/**
		Returns error message in a form understandable by humans.
	*/
	char* NonRealtimeNetworkingUtilities::getErrorMessage(int errorCode) {

		switch(errorCode) {
			case NO_SUCH_PLAYER:
				return "Player with given session ID was not registered on the server.";
				break;
			case NO_SUCH_GAME:
				return "No such game was registered on the server.";
				break;
			case GAME_NAME_EMPTY:
				return "Name of the game was not provided.";
				break;
			case LOGIN_TAKEN:
				return "Player with such login already exists. Please choose a different login.";
				break;
			case SCORE_TOO_SMALL:
				return "The list of high scores for this game is full and your score is too small. Try harder the next time.";
				break;
			default:
				return "ERROR_CODE_NOT_KNOWN!";
				break;
		}

	}

};