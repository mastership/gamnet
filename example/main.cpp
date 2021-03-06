/*
 * main.cpp
 *
 *  Created on: Jun 11, 2014
 *      Author: kukuta
 */
#include "ClientSession.h"

int main()
{

	Gamnet::Log::ReadXml("config.xml");
	Gamnet::Network::Listen<ClientSession>(20000, 1024, 60);
	Gamnet::Http::Listen(8000, 1024, 600);
	/*
	Gamnet::Router::Listen("HELLOWORLD", 20001);
	Gamnet::Router::Connect("localhost", 20001);
	*/
	Gamnet::Test::ReadXml<TestSession>("config.xml");
	Gamnet::Test::Run<TestSession>();
	Gamnet::Run(20);
	return 0;
}



