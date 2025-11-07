#pragma once
#include <iostream>
using namespace std;

class clsScreen
{
protected:

	static void _DrawScreenHeader(const string Title, const string SubTitle = "")
	{
		cout << "---------------------------------------------" << endl;
		cout << "\t\t" << Title << endl;
		if (SubTitle != "")
		{
			cout << "\t\t" << SubTitle << endl;
		}
		cout << "---------------------------------------------" << endl;
	}
};

