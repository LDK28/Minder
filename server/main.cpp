#include <iostream>
#include "NetworkController.hpp"
#include "BuisnessLogic.hpp"
#include "DatabaseSessionClient.h"

int main()
{
    NetworkController networkController;
    networkController.startServer();

    return 0;
}