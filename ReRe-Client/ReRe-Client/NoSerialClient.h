#ifdef _WIN32 
# define _WIN32_WINNT 0x0501 
#endif 

#ifndef NO_SERIAL_CLIENT
#define NO_SERIAL_CLIENT

#include "ImageQueue.h"
#include "MatrixQueue.h"

#include <string>
#include <vector>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>


class NoSerialClient
{
public:
	NoSerialClient(boost::asio::io_service &io_service, const std::string host, const std::string port);
	~NoSerialClient(void);

	/* 1. Handle resolved query. Seccess: connect to adress*/
	void resolveHandler(const boost::system::error_code &ec, 
		boost::asio::ip::tcp::resolver::iterator it);

	/* 2. Handle connection. Success: wait until a new matrix arrives in queue,
	write stream-length into header, and write to socket.*/
	void connectHandler(const boost::system::error_code &ec);

	/* 3. Handle write Data. Seccess: switch to read-mode.*/
	void writeHandler(const boost::system::error_code &ec, 
		std::size_t bytesTransferred,
		std::string *outHeader,
		std::string *outBuff);

	/* 4. Read header data (send image-data size). Success: read send image data in multiple passes.*/
	void readHeaderHandler(const boost::system::error_code &ec, 
		std::size_t bytesTransferred,
		std::vector<char> *inHeader);

	/* 5. Read image-data in multiple passes. Success: add new client to clients array and delete self.*/
	void readHandler(const boost::system::error_code &ec, 
		std::size_t bytesTransferred,
		std::vector<char> *inBuff,
		std::stringstream *data,
		std::size_t inbound_data_size);

private:
	boost::asio::ip::tcp::resolver resolver;
	boost::asio::ip::tcp::socket sock;
	boost::asio::ip::tcp::resolver::iterator endpointIterator;
	boost::asio::ip::tcp::resolver::query query;

	ImageQueue *imageQueue;
	MatrixQueue *matrixQueue;

	enum {header_length = 16};
};

/* global Shared pointer definition containing all active clients(=connections to server). 
	Clients delete themselves, if their job is done.*/
typedef boost::shared_ptr<NoSerialClient> clients;

#endif
