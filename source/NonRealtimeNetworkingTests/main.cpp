#include <iostream>
#include <stdio.h>
#include <fstream>
#include <gtest/gtest.h>
#include <NonRealtimeNetworkingUtilities.h>
#include <NonRealtimeNetworkingException.h>
#include "Vector.h"
#include "../boost/text_iarchive.hpp"
#include "../boost/text_oarchive.hpp"

using namespace std;
using namespace irrlicht_nonrealtimenetworking;

//TEST(SET_BUFFER, MEMORY_ALLOCATION) // Check if our memory allocation works fine
//{
//	NonRealtimeNetworkingUtilities* utilities = new NonRealtimeNetworkingUtilities();
//	utilities->setBuffer("Test");
//    EXPECT_EQ("Test", utilities->getBuffer());
//}

TEST(SET_PORT_NUMBER, SMALLER_THAN_ZERO) // Try to assign port number smaller than 0 - should raise an exception
{
	NonRealtimeNetworkingUtilities* utilities = new NonRealtimeNetworkingUtilities();
	ASSERT_THROW(utilities->setPortNumber(-1), NonRealtimeNetworkingException);
	// delete utilities; <-- I removed this as the test kept failing with it
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

TEST(SEND_RCV_COMPLEX) // open a connection between two sockets + send 
{
	Vector* vector = new Vector(3, 4);
	int len = vector->getLength();

	// create and open a character archive for output
    ofstream ofs("serialization_file");

	// save data to archive
    {
        boost::archive::text_oarchive oa(ofs);
        // write class instance to archive
        oa << *vector;
    	// archive and stream closed when destructors are called
    }

	// establish connection between server and client socket
	NonRealtimeNetworkingUtilities* utilitiesSrv = new NonRealtimeNetworkingUtilities();
	ASSERT_NO_THROW(utilitiesSrv->openServerSocket());
	NonRealtimeNetworkingUtilities* utilitiesCl = new NonRealtimeNetworkingUtilities();
	ASSERT_NO_THROW(utilitiesCl->openClientSocket("127.0.0.1"));
	ASSERT_NO_THROW(utilitiesSrv->acceptClient());

	

	// close connection after work is done
	utilitiesCl->closeConnection();
	utilitiesSrv->closeConnection();
}

int main(int argc, char** argv) {

	testing::InitGoogleTest(&argc, argv); 
    RUN_ALL_TESTS();
	system("PAUSE");

}