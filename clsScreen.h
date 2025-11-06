#pragma once
#include <iostream>
using namespace std;

class clsScreen
{
protected:

	void _DrawScreenHeader(const string Title, const string SubTitle = "")
	{
		cout << "______________________________________";
		cout << "\t\t\t" << Title << endl;
		if (SubTitle != "")
		{
			cout << "\t\t\t" << SubTitle << endl;
		}
		cout << "______________________________________";
	}
};

