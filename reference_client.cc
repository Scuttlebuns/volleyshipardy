//
// daytime_client.cpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
using namespace std;
using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
	try
	{
		tcp::iostream stream("localhost", "2101"); //[1] == host, [2] == port
		if (!stream) //Connection failed
		{
			cout << "Unable to connect: " << stream.error().message() << endl;
			return EXIT_FAILURE;
		}

		while (true) {
			string s;
			stream >> s;
			if (!stream) break;
			cout << "Read: " << s << endl;
			stream << "PONG!" << endl;
		}
	}
	catch (exception& e)
	{
		cout << "Exception: " << e.what() << endl;
	}
}
