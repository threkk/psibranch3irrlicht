#ifndef NON_REALTIME_NETWORKING_EXCEPTION_H
#define NON_REALTIME_NETWORKING_EXCEPTION_H

#include <iostream>

/**
	A custom exception class used by the non-real time networking library
	to handle all kinds of errors that may occur in it.
*/
namespace irrlicht_nonrealtimenetworking {
	/// Inherit from standard library's exception class
	class IRRLICHT_API NonRealtimeNetworkingException : public std::exception {

	  private:
		const char* errorMessage;

	  public:
		NonRealtimeNetworkingException(const char *message) : errorMessage(message) {};
		~NonRealtimeNetworkingException() throw() {};
		/// Returns message indicating the error
		const char *what() const throw() { return this->errorMessage; };

	};
};
#endif