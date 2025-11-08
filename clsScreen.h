#pragma once
#include <iostream>
#include "Global.h"
#include "clsDate.h"
class clsScreen
{
protected:

	static void _DrawScreenHeader(const string Title, const string SubTitle = "", bool InTheMid = false)
	{
		if (!InTheMid)
		{
			cout << "==============================================" << endl;
			cout << "\t\t[" << Title << "]" << endl;
			if (SubTitle != "")
			{
				cout << "\t\t[" << SubTitle << "]" << endl;
			}

			// Udate User Name and date display
			cout << endl;
			if (CurrentUser.UserName != "")
				cout << "User: " << CurrentUser.UserName << endl;

			cout << "Date: " << clsDate::DateToString(clsDate()) << endl;
			// End Udate User Name and date display

			cout << "==============================================" << endl;	
		}
		else
		{
			cout << "\t\t\t\t---------------------------------------------------" << endl;
			cout << "\t\t\t\t\t" << Title << endl;
			if (SubTitle != "")
			{
				cout << "\t\t\t\t\t" << SubTitle << endl;
			}

			// Udate User Name and date display
			cout << endl;
			if (CurrentUser.UserName != "")
				cout << "\t\t\t\t\tUser: " << CurrentUser.UserName << endl;

			cout << "\t\t\t\t\tDate: " << clsDate::DateToString(clsDate()) << endl;
			// End Udate User Name and date display

			cout << "\t\t\t\t---------------------------------------------------" << endl;
		}
	}
	
	static bool CheckAccessRights(clsUser::enPermissions Permission)
	{

		if (!CurrentUser.CheckAccessPermission(Permission))
		{
			_DrawScreenHeader("Access Denied Contact your admin");
			return false;
		}
		else
		{
			return true;
		}

	}


};

