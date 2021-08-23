#include "Server.h"
#include <iostream>

void main()
{
    setlocale(0, "");

    Server server(L"mypipe");
    server.run();

    system("pause");
}