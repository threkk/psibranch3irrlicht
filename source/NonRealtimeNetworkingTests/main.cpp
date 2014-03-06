#include <iostream>
#include <gtest/gtest.h>
#include <NonRealtimeNetworkingUtilities.h>
#include <NonRealtimeNetworkingException.h>

using namespace std;

TEST(SET_BUFFER, MEMORY_ALLOCATION) // Check if our memory allocation works fine
{
	NonRealtimeNetworkingUtilities* utilities = new NonRealtimeNetworkingUtilities();
	utilities->setBuffer("Test");
    EXPECT_EQ("Test", utilities->getBuffer());
}

TEST(SET_PORT_NUMBER, SMALLER_THAN_ZERO) // Try to assign port number smaller than 0 - should raise an exception
{
	NonRealtimeNetworkingUtilities* utilities = new NonRealtimeNetworkingUtilities();
	ASSERT_THROW(utilities->setPortNumber(-1), NonRealtimeNetworkingException);
}

int main(int argc, char** argv) {

	testing::InitGoogleTest(&argc, argv); 
    RUN_ALL_TESTS();
	system("PAUSE");

}