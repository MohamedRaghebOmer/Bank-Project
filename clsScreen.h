#pragma once
#include <iostream>
using namespace std;

class clsScreen
{
protected:

	static void _DrawScreenHeader(const string Title, const string SubTitle = "", bool InTheMid = false)
	{
		if (!InTheMid)
		{
			cout << "==============================================" << endl;
			cout << "\t\t" << Title << endl;
			if (SubTitle != "")
			{
				cout << "\t\t" << SubTitle << endl;
			}
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
			cout << "\t\t\t\t---------------------------------------------------" << endl;

		}
	}
};

