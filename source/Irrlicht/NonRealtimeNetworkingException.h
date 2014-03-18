#include <iostream>

namespace irrlicht_nonrealtimenetworking {
	class __declspec(dllexport)NonRealtimeNetworkingException : public std::exception {

	  private:
		const char* errorMessage;

	  public:
		NonRealtimeNetworkingException(const char *message) : errorMessage(message) {};
		~NonRealtimeNetworkingException() throw() {};
		const char *what() const throw() { return this->errorMessage; };

	};
};