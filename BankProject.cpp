#include <iostream>
#include "D:\GitHub\Bank-Project\src\Screens\clsLoginScreen.h"

int main()
{
    while(true)
    {
        if (!clsLoginScreen::ShowLoginScreen())
        {
			break;
        }
    }

    return 0;
}