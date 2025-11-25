#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "clsString.h"
#include <fstream>

static const string _fileName = "Currencies.txt";

class clsCurrency
{
private:


	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _StringToCurrencyObject(const string& line)
	{
		vector <string> _vSplitedLine = clsString::Split(line, "#//#");

		if (_vSplitedLine.size() == 4)
		{
			return clsCurrency(clsCurrency::enMode::UpdateMode,
				_vSplitedLine[0], _vSplitedLine[1], _vSplitedLine[2], stof(_vSplitedLine[3]));
		}
		else
		{
			return clsCurrency(clsCurrency::enMode::EmptyMode,
				"", "", "", 0);
		}
	}

	static vector <clsCurrency> _LoadCurrenciesDataFromFile()
	{
		vector <clsCurrency> _vAllCurrenciesInFile;

		fstream _myFile;
		_myFile.open(_fileName, ios::in); // read only mode

		if (_myFile.is_open())
		{
			string _oneLineInFile = "";

			while (getline(_myFile, _oneLineInFile))
			{
				_vAllCurrenciesInFile.push_back(_StringToCurrencyObject(_oneLineInFile));
			}

			_myFile.close();
		}

		return _vAllCurrenciesInFile;
	}

	string _CurrencyObjectToString(clsCurrency& object, const string Seprator = "#//#")
	{
		return object.Country() + Seprator + object.CurrencyCode() +
			Seprator + object.CurrencyName() + Seprator +
			to_string(object.Rate());
	}

	void _SaveCurrencyDataToFile(vector <clsCurrency>& _vCurrencies)
	{
		fstream _myFile;
		_myFile.open(_fileName, ios::out); // overwrite

		string DataLine = "";

		if (_myFile.is_open())
		{
			for (clsCurrency& _Currency : _vCurrencies)
			{
				DataLine = _CurrencyObjectToString(_Currency);
				_myFile << DataLine << endl;
			}

			_myFile.close();
		}

	}

	void _Update()
	{
		vector <clsCurrency> _vAllCurrenciesInFile = _LoadCurrenciesDataFromFile();

		for (clsCurrency& Currency : _vAllCurrenciesInFile)
		{
			if (Currency.CurrencyCode() == _CurrencyCode)
			{
				Currency = *this;
				break;
			}
		}

		_SaveCurrencyDataToFile(_vAllCurrenciesInFile);
	}

	static clsCurrency _getEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode,
		string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	bool isEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	string Country()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	float Rate()
	{
		return _Rate;
	}

	static clsCurrency findByCode(string code)
	{
		code = clsString::UpperAllString(code);

		fstream myFile;
		myFile.open(_fileName, ios::in); // read only mode

		if (myFile.is_open())
		{
			string line = "";

			while (getline(myFile, line))
			{
				clsCurrency Currency = _StringToCurrencyObject(line);

				if (Currency.CurrencyCode() == code)
				{
					myFile.close();
					return Currency;
				}
			}

			myFile.close();
		}

		return _getEmptyCurrencyObject();
	}

	static clsCurrency findByCountry(string Country)
	{

		fstream myFile;
		myFile.open(_fileName, ios::in); //read only mode

		if (myFile.is_open())
		{
			string line = "";

			while (getline(myFile, line))
			{
				clsCurrency Currency = _StringToCurrencyObject(line);

				if (Currency.Country() == Country)
				{
					myFile.close();
					return Currency;
				}
			}

			myFile.close();
		}

		return _getEmptyCurrencyObject();
	}

	static bool isCurrencyExist(string& CurrencyCode)
	{
		clsCurrency Test = findByCode(CurrencyCode);
		return !Test.isEmpty();
	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesDataFromFile();
	}

	float ConvertToUSD(float Amount)
	{
		return Amount / _Rate;
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency OtherCurrency)
	{
		float AmountInUSD = ConvertToUSD(Amount);
		return AmountInUSD * OtherCurrency.Rate();
	}


};

