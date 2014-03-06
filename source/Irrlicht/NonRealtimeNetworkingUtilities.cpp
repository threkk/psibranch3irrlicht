#include "NonRealtimeNetworkingUtilities.h"
#include "NonRealtimeNetworkingException.h"
#include "winsock.h"

// Destructor
NonRealtimeNetworkingUtilities::~NonRealtimeNetworkingUtilities() {

	delete[] buffer;

}

// Buffer setter
void NonRealtimeNetworkingUtilities::setBuffer(char* buffer) {
	
	this->buffer = new char[sizeof(buffer)/sizeof(char)]; // Calculate the length of the string and allocate memory for it
	this->buffer = buffer;

}

// Setting port number
void NonRealtimeNetworkingUtilities::setPortNumber(int portNumber) {
	if (portNumber < 0) // What really is the smallest we can assign here? 1024?
		throw NonRealtimeNetworkingException("Negative port number.");
	this->portNumber = portNumber;
}

bool NonRealtimeNetworkingUtilities::checkVersion() {

	WORD wVersionRequested;
	int wsaerr;

	// Using MAKEWORD macro, Winsock version request 2.2
	wVersionRequested = MAKEWORD(2, 2);

	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0)
	{
		throw NonRealtimeNetworkingException("Server: The Winsock dll not found!\n");
	}

	// Check how to make string concatenation later so that the version looks nicer
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2 )
	{
		/* Tell the user that we could not find a usable WinSock DLL.*/
		WSACleanup();
		throw NonRealtimeNetworkingException("WinSock version not supported: " + LOBYTE(wsaData.wVersion) + HIBYTE(wsaData.wVersion));
	}

}

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
	// "127.0.0.1" is the local IP address to which the socket will be bound.
	service.sin_addr.s_addr = inet_addr("0.0.0.0");
	// 55555 is the port number to which the socket will be bound.
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

void NonRealtimeNetworkingUtilities::openClientSocket(char* ipAddress) {

	if (!checkVersion())
		throw NonRealtimeNetworkingException("Socket version check failed.");

	// Fill out the information needed to initialize a socket…
    SOCKADDR_IN target; //Socket address information

    target.sin_family = AF_INET; // address family Internet
    target.sin_port = htons (portNumber); // Port to connect on
    target.sin_addr.s_addr = inet_addr (ipAddress); // Target IP

    s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
    if (s == INVALID_SOCKET)
    {
		throw NonRealtimeNetworkingException("Socket creation failed.");
    }  

    //Try connecting...

    if (connect(s, (SOCKADDR *)&target, sizeof(target)) == SOCKET_ERROR)
    {
		throw NonRealtimeNetworkingException("Connection failed.");
    }

}

void NonRealtimeNetworkingUtilities::sendData() {

	if (buffer == NULL || buffer == "")
		throw NonRealtimeNetworkingException("Buffer empty. Set buffer before sending!");

	int iResult;

	// Send an initial buffer
	iResult = send(s, buffer, (int) strlen(buffer), 0);
	if (iResult == SOCKET_ERROR) {
		closesocket(s);
		WSACleanup();
		throw NonRealtimeNetworkingException("Send failed: " + WSAGetLastError());
	}

}

void NonRealtimeNetworkingUtilities::receiveData() {

	int bytesRecv = SOCKET_ERROR;
	bytesRecv = recv(s, buffer, 200, 0);

	if (bytesRecv == SOCKET_ERROR)
		throw NonRealtimeNetworkingException("Receive failed: " + WSAGetLastError());

}

void NonRealtimeNetworkingUtilities::closeConnection ()
{
    //Close the socket if it exists
    if (s)
        closesocket(s);

    WSACleanup(); //Clean up Winsock
}