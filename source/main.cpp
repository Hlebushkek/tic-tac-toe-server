#include <iostream>
#include "TicTacToeServer.hpp"


int main()
{
    TicTacToeServer server(60000); 
	server.start();

    while (true)
	{
		server.update(-1, true);
	}

    return 0;
}