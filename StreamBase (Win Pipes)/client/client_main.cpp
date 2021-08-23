#include "Client.h"
#include <iostream>

void main()
{
    setlocale(0, "");

    Client client(L"mypipe");
    client.run();

    system("pause");
}