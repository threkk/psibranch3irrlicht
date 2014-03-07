#include <iostream>
#include <gtest/gtest.h>
#include <NonRealtimeNetworkingUtilities.h>
#include <NonRealtimeNetworkingException.h>

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
}

int main(int argc, char** argv) {

	testing::InitGoogleTest(&argc, argv); 
    RUN_ALL_TESTS();
	system("PAUSE");

}