#include <iostream>
#include <stdio.h>
#include <fstream>
#include <gtest/gtest.h>
#include <NonRealtimeNetworkingUtilities.h>
#include <NonRealtimeNetworkingException.h>
#include "Vector.h"
#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"

using namespace irrlicht_nonrealtimenetworking;

namespace boost {
	namespace serialization {

		template<class Archive>
		void serialize(Archive & ar, Vector & v, const unsigned int version)
		{
			ar & v.x;
			ar & v.y;	
		}

	}
}


TEST(SET_BUFFER, MEMORY_ALLOCATION) // Check if our memory allocation works fine
{
	NonRealtimeNetworkingUtilities* utilities = new NonRealtimeNetworkingUtilities();
	utilities->setBuffer("Test");
	ASSERT_STREQ("Test", utilities->getBuffer());
}

TEST(SET_PORT_NUMBER, SMALLER_THAN_ZERO) // Try to assign port number smaller than 0 - should raise an exception
{
	NonRealtimeNetworkingUtilities* utilities = new NonRealtimeNetworkingUtilities();
	ASSERT_THROW(utilities->setPortNumber(-1), NonRealtimeNetworkingException);
}

TEST(OPEN_SERVER_CONN, NO_EXCEPTION) // Try to open a server socket
{
	NonRealtimeNetworkingUtilities* utilities = new NonRealtimeNetworkingUtilities();
	ASSERT_NO_THROW(utilities->openServerSocket());
	utilities->closeConnection();
}

TEST(OPEN_CLIENT_CONN, NO_EXCEPTIONS) // Try to open a client socket
{
	NonRealtimeNetworkingUtilities* utilitiesSrv = new NonRealtimeNetworkingUtilities();
	ASSERT_NO_THROW(utilitiesSrv->openServerSocket());
	NonRealtimeNetworkingUtilities* utilities = new NonRealtimeNetworkingUtilities();
	ASSERT_NO_THROW(utilities->openClientSocket("127.0.0.1"));
	ASSERT_NO_THROW(utilitiesSrv->acceptClient());
	utilities->closeConnection();
	utilitiesSrv->closeConnection();
}

TEST(SEND_STRING, RECEIVED_PROPERLY) // Try sending/receiving of an example string
{
	// Establish a connection between server and client:
	NonRealtimeNetworkingUtilities* utilitiesSrv = new NonRealtimeNetworkingUtilities();
	ASSERT_NO_THROW(utilitiesSrv->openServerSocket());
	NonRealtimeNetworkingUtilities* utilitiesClient = new NonRealtimeNetworkingUtilities();
	ASSERT_NO_THROW(utilitiesClient->openClientSocket("127.0.0.1"));
	ASSERT_NO_THROW(utilitiesSrv->acceptClient());
	
	// Set the buffer on the server side:
	ASSERT_NO_THROW(utilitiesClient->setBuffer("Test buffer"));
	// Send the buffer to the client
	ASSERT_NO_THROW(utilitiesClient->sendData());

	// Receive the buffer from the server:
	ASSERT_NO_THROW(utilitiesSrv->receiveData());

	printf(utilitiesSrv->getBuffer());

	// Close connections once we're done:
	utilitiesClient->closeConnection();
	utilitiesSrv->closeConnection();
}

TEST(SEND_RCV_COMPLEX) // serialize a complex object, send via sockets, deserialize received char* 
{
	// create complex vector object
	Vector* vector = new Vector(3, 4);
	int len = vector->getLength();


	// file that serialized object will be saved to on server side
	char* filenameSrv = "serialization_file_srv";

	// create and open a character archive for serialized vector instance
    std::ofstream ofs(filenameSrv);

	// save data to archive
    {
        boost::archive::text_oarchive oa(ofs);
        // write class instance to archive
        oa << *vector;
    	// archive and stream closed when destructors are called

		ofs.close();
    }

	NonRealtimeNetworkingUtilities* utilitiesSrv = new NonRealtimeNetworkingUtilities();
	ASSERT_NO_THROW(utilitiesSrv->openServerSocket());
	NonRealtimeNetworkingUtilities* utilitiesClient = new NonRealtimeNetworkingUtilities();
	ASSERT_NO_THROW(utilitiesClient->openClientSocket("127.0.0.1"));
	ASSERT_NO_THROW(utilitiesSrv->acceptClient());

	std::ifstream ifs(filenameSrv);

	std::filebuf* pbuf = ifs.rdbuf();

	// get file size using buffer's members
	size_t size = pbuf->pubseekoff (0, ifs.end, ifs.in);
	pbuf->pubseekpos (0, ifs.in);

	// allocate memory to contain file data
	char* buffer = new char[size];

	// get file data
	pbuf->sgetn(buffer, size);
	// std::cout << "Buffer to be send: " << buffer << std::endl;
	ifs.close();

	// Set the buffer on the server side:
	ASSERT_NO_THROW(utilitiesClient->setBuffer(buffer));
	// Send the buffer to the client
	ASSERT_NO_THROW(utilitiesClient->sendData());

	// Receive the buffer from the server:
	ASSERT_NO_THROW(utilitiesSrv->receiveData());

	//delete buffer;
	//buffer = new char[size];
	//buffer = utilitiesSrv->getBuffer();

	char* filenameCl = "serialization_file_client";

	//std::ofstream outfile ("serialization_file_client", std::ofstream::binary);
	//outfile.write(utilitiesSrv->getBuffer(), size);
	// std::cout << "Client's buffer after receiving the string: " << utilitiesClient->getBuffer() << std::endl;

	std::ofstream ofs2(filenameCl);
	ofs2 << utilitiesClient->getBuffer();
	ofs2.close();

	Vector newVector;
	{
        // create and open an archive for input
        std::ifstream ifs(filenameCl);
		// printf("hello1");
		// HEEERE is where the shit happens
        boost::archive::text_iarchive ia(ifs);
		// printf("hello!");
        // read class state from archive
        ia >> newVector;
        // archive and stream closed when destructors are called
    }

	ASSERT_TRUE(newVector.getLength() == len);

	// Close connections once we're done:
	utilitiesClient->closeConnection();
	utilitiesSrv->closeConnection();
		
}

int main(int argc, char** argv) {

	testing::InitGoogleTest(&argc, argv); 
    RUN_ALL_TESTS();
	system("PAUSE");

}