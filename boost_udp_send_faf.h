#pragma once

//   Copyright 2018 Kevin Godden
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#include <boost/asio.hpp>
#include <string>

//
// Fire-and-Forget (FAF) transmission for UDP
// using the boost::asio lib. Very simple wrapper
// around the boost libs.
//
// Can throw the following exception:
//	boost::system::system_error
//
// Synopsis --->
//
// For a single Fire-and-Forget send:
//
// #include "boost_udp_send_faf.h"
//
// boost_udp_send_faf("192.168.1.44", 8861).send("The message!");
//
//
// To send multiple datagrams while keeping the socket open and
// reusing end-point:
//
// #include "boost_udp_send_faf.h"
//
// boost_udp_send_faf sender("192.168.1.44", 8861);
//		
// for (auto i = 0; i != 10; i++) {
//     sender.send("Lots of messages! :-/");
// }
//
// The socket will remain open while the boost_udp_send_faf object is in scope
// so to control when the socket is closed, control the scope of the object.
//
// If you want to do anything fancy like using scatter-gather buffers etc. then
// just use the boost libs!  This is for real simple stuff!
//


class boost_udp_send_faf {
	boost::asio::io_service io_service;
	boost::asio::ip::udp::socket socket;
	boost::asio::ip::udp::endpoint remote_endpoint;

public:

	boost_udp_send_faf(const std::string& ip_address, const int port, const bool broadcast = false) : socket(io_service) {
		
		// Open socket
		socket.open(boost::asio::ip::udp::v4());

		// I wouldn't recommend broadcasting unless you are
		// in complete control of your subnet and know
		// what's on it and how it will react
		if (broadcast) {
			boost::asio::socket_base::broadcast option(true);
			socket.set_option(option);
		}

		// make endpoint
		remote_endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(ip_address.c_str()), port);
	}

	// Send a string to the preconfigured endpoint
	// via the open socket.
	void send(const std::string& message) {
		boost::system::error_code ignored_error;
		socket.send_to(boost::asio::buffer(message), remote_endpoint, 0, ignored_error);
	}

	// Send some binary data to the preconfigured endpoint
	// via the open socket.
	void send(const unsigned char* data, const int len) {
		boost::system::error_code ignored_error;
		socket.send_to(boost::asio::buffer(data, len), remote_endpoint, 0, ignored_error);
	}
};
