#pragma once
#include <iostream>
#include <string>
#include "clsDate.h"
#include "clsPeriod.h"
using namespace std;

class clsInputValidate
{
public:

    // ----------------------Check Between---------------------
    static bool IsNumberBetween(short Number, short From,
        int To, bool CanBeFromOrTo = true)
    {
        if (CanBeFromOrTo)
            return (Number >= From && Number <= To);
        else
            return (Number > From && Number < To);
    }

    static bool IsNumberBetween(int Number, int From,
        int To, bool CanBeFromOrTo = true)
    {
        if (CanBeFromOrTo)
            return (Number >= From && Number <= To);
        else
            return (Number > From && Number < To);
    }

    static bool IsNumberBetween(double Number, double From,
        double To, bool CanBeFromOrTo = true)
    {
        if (CanBeFromOrTo)
            return (Number >= From && Number <= To);
        else
            return (Number > From && Number < To);
    }

    static bool IsDateBetween(const clsDate& Date, const clsDate& From,
        const clsDate& To, bool CanBeFromOrTo = true)
    {
        if (CanBeFromOrTo)
        {
            return clsDate::CompareDates(Date, From) == clsDate::Equal ||
                clsDate::CompareDates(Date, To) == clsDate::Equal ||
                (clsDate::CompareDates(Date, From) == clsDate::After &&
                    clsDate::CompareDates(Date, To) == clsDate::Before);

            // Date can be equal 'from' or 'to' or between 'from' and 'to'.
        }
        else
        {
            return (clsDate::CompareDates(Date, From) == clsDate::After &&
                clsDate::CompareDates(Date, To) == clsDate::Before);

            // Date can only be between 'from' and 'to'.
        }
    }


    // ----------------------ReadNumber---------------------
    static int ReadIntNumber(const string& EnterNumberMessage = "Enter number: ",
        const string& FailMessage = "Invalid number, please try again.\n")
    {
        string Input = "";
        int Number = 0;

        while (true)
        {
            cout << EnterNumberMessage;
            cin >> Input;

            try
            {
                Number = stoi(Input);
                return Number;
            }
            catch (...)
            {
                cout << FailMessage;
            }
        }
    }

    static int ReadPositiveInt(bool ZeroIsPositive = true,
        const string& EnterNumberMessage = "Enter positive number: ",
        const string& FailMessage = "Invalid number, please try again.\n")
    {
        int PositiveInt = -1;

        PositiveInt = ReadIntNumber(EnterNumberMessage, FailMessage);

        if (ZeroIsPositive)
        {
            while (PositiveInt < 0) // PositiveInt can equal [0]
            {
                cout << FailMessage;
                PositiveInt = ReadIntNumber(EnterNumberMessage, FailMessage);
            }
        }
        else
        {
            while (PositiveInt <= 0) // PositiveInt can NOT equal [0]
            {
                cout << FailMessage;
                PositiveInt = ReadIntNumber(EnterNumberMessage, FailMessage);
            }
        }


        return PositiveInt;
    }

    static int ReadNegativeInt(bool ZeroIsnegative = false, const string& EnterNumberMessage =
        "Enter negative number: ", const string& FailMessage =
        "Invalid number, please try again.\n")
    {
        int negativeInt = 1;

        negativeInt = ReadIntNumber(EnterNumberMessage, FailMessage);

        if (ZeroIsnegative)
        {
            while (negativeInt > 0) // NigaitiveInt can be [0]
            {
                cout << FailMessage;
                negativeInt = ReadIntNumber(EnterNumberMessage, FailMessage);
            }
        }
        else
        {
            while (negativeInt >= 0) // NigaitiveInt can NOT be [0]
            {
                cout << FailMessage;
                negativeInt = ReadIntNumber(EnterNumberMessage, FailMessage);
            }
        }

        return negativeInt;
    }

    static int ReadIntNumberBetween(int From, int To,
        const string& EnterNumberMessage, bool CanBeFromOrTo = true,
        const string& FailMessage = "Invalid number please try again.\n")
    {
        int Number = ReadIntNumber(EnterNumberMessage, FailMessage);

        if (CanBeFromOrTo)
        {
            while (!IsNumberBetween(Number, From, To, true))
            {
                cout << FailMessage;
                Number = ReadIntNumber(EnterNumberMessage, FailMessage);
            }
        }
        else
        {
            while (!IsNumberBetween(Number, From, To, false))
            {
                cout << FailMessage;
                Number = ReadIntNumber(EnterNumberMessage, FailMessage);
            }
        }

        return Number;
    }

    //--------Float numbers--------
    static float ReadFloatNumber(const string& EnterNumberMessage =
        "Enter number: ", const string& FailMessage =
        "Invalid number, please try again.\n")
    {
        string Input = "";
        float Number = 0;

        while (true)
        {
            cout << EnterNumberMessage;
            cin >> Input;

            try
            {
                Number = stof(Input);
                return Number;
            }
            catch (...)
            {
                cout << FailMessage;
            }
        }
    }

    static float ReadPositiveFloat(bool ZeroIsPositive = true,
        const string& EnterNumberMessage = "Enter positive number: ",
        const string& FailMessage = "Invalid number, please try again.\n")
    {
        float PositiveFloat = -1;

        PositiveFloat = ReadFloatNumber(EnterNumberMessage, FailMessage);

        if (ZeroIsPositive)
        {
            while (PositiveFloat < 0) // negativeFloat can equal [0]
            {
                cout << FailMessage;
                PositiveFloat = ReadFloatNumber(EnterNumberMessage, FailMessage);
            }
        }
        else
        {
            while (PositiveFloat <= 0) // PositiveFloat can NOT equal [0]
            {
                cout << FailMessage;
                PositiveFloat = ReadFloatNumber(EnterNumberMessage, FailMessage);
            }
        }

        return PositiveFloat;
    }

    static float ReadNegativeFloat(bool ZeroIsnegative = false,
        const string& EnterNumberMessage = "Enter positive number: ",
        const string& FailMessage = "Invalid number, please try again.\n")
    {
        float negativeFloat = 1;

        negativeFloat = ReadFloatNumber(EnterNumberMessage, FailMessage);

        if (ZeroIsnegative)
        {
            while (negativeFloat > 0) // negativeFloat can equal [0]
            {
                cout << FailMessage;
                negativeFloat = ReadFloatNumber(EnterNumberMessage, FailMessage);
            }
        }
        else
        {
            while (negativeFloat >= 0) // PositiveFloat can NOT equal [0]
            {
                cout << FailMessage;
                negativeFloat = ReadFloatNumber(EnterNumberMessage, FailMessage);
            }
        }

        return negativeFloat;
    }

    static float ReadFloatNumberBetween(float From,
        float To, const string& EnterNumberMessage,
        bool CanBeFromOrTo = true,
        const string& FailMessage = "Invalid number, please try again.\n")
    {
        float Number = 0;

        Number = ReadFloatNumber(EnterNumberMessage, FailMessage);

        if (CanBeFromOrTo)
        {
            while (!IsNumberBetween(Number, From, To, true))
            {
                cout << FailMessage;
                Number = ReadFloatNumber(EnterNumberMessage, FailMessage);
            }
        }
        else
        {
            while (!IsNumberBetween(Number, From, To, false))
            {
                cout << FailMessage;
                Number = ReadFloatNumber(EnterNumberMessage, FailMessage);
            }
        }

        return Number;
    }


    //--------Double numbers--------
    static double ReadDblNumber(const string& EnterNumberMessage =
        "Enter number: ", const string& FailMessage =
        "Invalid number, please try again.\n")
    {
        string Input = "";
        double Number = 0;

        while (true)
        {
            cout << EnterNumberMessage;
            cin >> Input;

            try
            {
                Number = stod(Input);
                return Number;
            }
            catch (...)
            {
                cout << FailMessage;
            }
        }
    }

    static double ReadPositiveDbl(bool ZeroIsPositive = true,
        const string& EnterNumberMessage = "Enter positive number: ",
        const string& FailMessage = "Invalid number, please try again.\n")
    {
        double PositiveDbl = -1;

        PositiveDbl = ReadDblNumber(EnterNumberMessage, FailMessage);

        if (ZeroIsPositive)
        {
            while (PositiveDbl < 0) // negativeInt can equal [0]
            {
                cout << FailMessage;
                PositiveDbl = ReadDblNumber(EnterNumberMessage, FailMessage);
            }
        }
        else
        {
            while (PositiveDbl <= 0) // PositiveInt can NOT equal [0]
            {
                cout << FailMessage;
                PositiveDbl = ReadDblNumber(EnterNumberMessage, FailMessage);
            }
        }

        return PositiveDbl;
    }

    static double ReadNegativeDbl(bool ZeroIsnegative = false,
        const string& EnterNumberMessage = "Enter positive number: ",
        const string& FailMessage = "Invalid number, please try again.\n")
    {
        double negativeDbl = 1;

        negativeDbl = ReadDblNumber(EnterNumberMessage, FailMessage);

        if (ZeroIsnegative)
        {
            while (negativeDbl > 0) // negativeInt can equal [0]
            {
                cout << FailMessage;
                negativeDbl = ReadDblNumber(EnterNumberMessage, FailMessage);
            }
        }
        else
        {
            while (negativeDbl >= 0) // PositiveInt can NOT equal [0]
            {
                cout << FailMessage;
                negativeDbl = ReadDblNumber(EnterNumberMessage, FailMessage);
            }
        }

        return negativeDbl;
    }


    static double ReadDblNumberBetween(double From,
        double To, const string& EnterNumberMessage,
        bool CanBeFromOrTo = true,
        const string& FailMessage = "Invalid number, please try again.\n")
    {
        double Number = 0;

        Number = ReadDblNumber(EnterNumberMessage, FailMessage);

        if (CanBeFromOrTo)
        {
            while (!IsNumberBetween(Number, From, To, true))
            {
                cout << FailMessage;
                Number = ReadDblNumber(EnterNumberMessage, FailMessage);
            }
        }
        else
        {
            while (!IsNumberBetween(Number, From, To, false))
            {
                cout << FailMessage;
                Number = ReadDblNumber(EnterNumberMessage, FailMessage);
            }
        }

        return Number;
    }


    // ----------------------ReadDate---------------------
    static clsDate ReadDate(
        const string& EnterDayMessage = "Enter day: ",
        const string& EnterMonthMessage = "Enter month: ",
        const string& EnterYearMessage = "Enter year: ",
        const string& DayFail = "Invalid day, please try again.\n",
        const string& MonthFail = "Invalid month, please try again.\n",
        const string& YearFail = "Invalid year, please try again.\n",
        const string& DateFail = "Invalid date, please try again.\n")
    {
        clsDate Date(0, 0, 0);

        Date.Day = ReadIntNumberBetween(1, 31, EnterDayMessage, true, DayFail);
        Date.Month = ReadIntNumberBetween(1, 12, EnterMonthMessage, true, MonthFail);
        Date.Year = ReadPositiveInt(false, EnterYearMessage, YearFail);

        while (!clsDate::IsValidDate(Date))
        {
            cout << DateFail;
            Date.Day = ReadIntNumberBetween(1, 31, EnterDayMessage, true, DayFail);
            Date.Month = ReadIntNumberBetween(1, 12, EnterMonthMessage, true, MonthFail);
            Date.Year = ReadPositiveInt(false, EnterYearMessage, YearFail);
        }

        return Date;
    }

    static clsDate ReadDateAfter(
        clsDate Date,
        const string& EnterDayMessage = "Enter day: ",
        const string& EnterMonthMessage = "Enter month: ",
        const string& EnterYearMessage = "Enter year: ",
        const string& DayFail = "Invalid day, please try again.\n",
        const string& MonthFail = "Invalid month, please try again.\n",
        const string& YearFail = "Invalid year, please try again.\n",
        const string& DateFail = "Invalid date, please try again.\n")
    {
        clsDate UserInput;

        UserInput = ReadDate(EnterDayMessage, EnterMonthMessage,
            EnterYearMessage, DayFail, MonthFail, YearFail, DateFail);

        while (clsDate::CompareDates(UserInput, Date) != clsDate::After)
        {
            cout << DateFail;
            UserInput = ReadDate(EnterDayMessage, EnterMonthMessage,
                EnterYearMessage, DayFail, MonthFail, YearFail, DateFail);
        }

        return UserInput;
    }

    static clsDate ReadDateBefore(
        clsDate Date,
        const string& EnterDayMessage = "Enter day: ",
        const string& EnterMonthMessage = "Enter month: ",
        const string& EnterYearMessage = "Enter year: ",
        const string& DayFail = "Invalid day, please try again.\n",
        const string& MonthFail = "Invalid month, please try again.\n",
        const string& YearFail = "Invalid year, please try again.\n",
        const string& DateFail = "Invalid date, please try again.\n")
    {
        clsDate UserInput;

        UserInput = ReadDate(EnterDayMessage, EnterMonthMessage,
            EnterYearMessage, DayFail, MonthFail, YearFail, DateFail);

        while (clsDate::CompareDates(UserInput, Date) != clsDate::Before)
        {
            cout << DateFail;
            UserInput = ReadDate(EnterDayMessage, EnterMonthMessage,
                EnterYearMessage, DayFail, MonthFail, YearFail, DateFail);
        }

        return UserInput;
    }

    static clsDate ReadDateBetween(
        const clsDate& DateFrom, const clsDate& DateTo,
        const string& EnterDayMessage = "Enter day: ",
        const string& EnterMonthMessage = "Enter month: ",
        const string& EnterYearMessage = "Enter year: ",
        const string& DayFail = "Invalid day, please try again.\n",
        const string& MonthFail = "Invalid month, please try again.\n",
        const string& YearFail = "Invalid year, please try again.\n",
        const string& DateFail = "Invalid date, please try again.\n")
    {
        clsDate UserInput;

        UserInput = ReadDate(EnterDayMessage, EnterMonthMessage, EnterYearMessage, DayFail, MonthFail, YearFail, DateFail);


        while (clsDate::CompareDates(UserInput, DateFrom) == clsDate::Before ||
            clsDate::CompareDates(UserInput, DateTo) == clsDate::After)
        {
            cout << DateFail;
            UserInput = ReadDate(EnterDayMessage, EnterMonthMessage, EnterYearMessage, DayFail, MonthFail, YearFail, DateFail);
        }


        return UserInput;
    }

    static bool IsValidDate(clsDate& Date)
    {
        return clsDate::IsValidDate(Date);
    }


    // ----------------------ReadPeriod---------------------
    static clsPeriod ReadPeriod(
        const string& StartingDateMessage = "Starting date:\n",
        const string& EndingDateMessage = "\nEnding date:\n",
        const string& EnterDayMessage = "Enter day: ",
        const string& EnterMonthMessage = "Enter month: ",
        const string& EnterYearMessage = "Enter year: ",
        const string& DayFail = "Invalid day, please try again.\n",
        const string& MonthFail = "Invalid month, please try again.\n",
        const string& YearFail = "Invalid year, please try again.\n",
        const string& DateFail = "Invalid date, please try again.\n")
    {
        cout << StartingDateMessage;
        clsDate StartDate = ReadDate(EnterDayMessage, EnterMonthMessage,
            EnterYearMessage, DayFail, MonthFail, YearFail, DateFail);

        cout << EndingDateMessage;
        clsDate EndDate = ReadDateAfter(StartDate, EnterDayMessage, EnterMonthMessage, EnterYearMessage, DayFail, MonthFail, YearFail, DateFail);

        clsPeriod Period(StartDate, EndDate);
        return Period;
    }


    static clsPeriod ReadPeriodBefore(
        clsPeriod Period,
        const string& UserInputNotBeforePeriodMessage = "Invalid Period, please try again.\n",
        const string& StartingDateMessage = "Period beginning:\n",
        const string& EndingDateMessage = "\nPeriod end:\n",
        const string& EnterDayMessage = "Enter day: ",
        const string& EnterMonthMessage = "Enter month: ",
        const string& EnterYearMessage = "Enter year: ",
        const string& DayFail = "Invalid day, please try again.\n",
        const string& MonthFail = "Invalid month, please try again.\n",
        const string& YearFail = "Invalid year, please try again.\n",
        const string& DateFail = "Invalid date, please try again.\n")
    {
        clsPeriod UserInput = ReadPeriod(StartingDateMessage, EndingDateMessage,
            EnterDayMessage, EnterMonthMessage, EnterYearMessage,
            DayFail, MonthFail, YearFail, DateFail);

        while (clsDate::CompareDates(UserInput.EndDate, Period.StartDate) != clsDate::Before)
        {
            cout << UserInputNotBeforePeriodMessage;

            // Read period again
            UserInput = ReadPeriod(StartingDateMessage, EndingDateMessage,
                EnterDayMessage, EnterMonthMessage, EnterYearMessage,
                DayFail, MonthFail, YearFail, DateFail);
        }

        return UserInput;
    }


    static clsPeriod ReadPeriodAfter(
        clsPeriod Period,
        const string& UserInputNotAfterPeriodMessage = "Invalid Period, please try again.\n",
        const string& PeriodStartMessage = "Period beginning:\n",
        const string& PeriodEndMessage = "\nPeriod end:\n",
        const string& EnterDayMessage = "Enter day: ",
        const string& EnterMonthMessage = "Enter month: ",
        const string& EnterYearMessage = "Enter year: ",
        const string& DayFail = "Invalid day, please try again.\n",
        const string& MonthFail = "Invalid month, please try again.\n",
        const string& YearFail = "Invalid year, please try again.\n",
        const string& DateFail = "Invalid date, please try again.\n")
    {
        clsPeriod UserInput = ReadPeriod(PeriodStartMessage, PeriodEndMessage,
            EnterDayMessage, EnterMonthMessage, EnterYearMessage,
            DayFail, MonthFail, YearFail, DateFail);

        while (clsDate::CompareDates(UserInput.StartDate, Period.EndDate) != clsDate::After)
        {
            cout << UserInputNotAfterPeriodMessage;
            UserInput = ReadPeriod(PeriodStartMessage, PeriodEndMessage,
                EnterDayMessage, EnterMonthMessage, EnterYearMessage,
                DayFail, MonthFail, YearFail, DateFail);
        }

        return UserInput;
    }

    static clsPeriod ReadPeriodInPeriod(
        clsPeriod Period,
        const string& UserInputNotAfterPeriodMessage = "Invalid Period, please try again.\n",
        const string& PeriodStartMessage = "Period beginning:\n",
        const string& PeriodEndMessage = "\nPeriod end:\n",
        const string& EnterDayMessage = "Enter day: ",
        const string& EnterMonthMessage = "Enter month: ",
        const string& EnterYearMessage = "Enter year: ",
        const string& DayFail = "Invalid day, please try again.\n",
        const string& MonthFail = "Invalid month, please try again.\n",
        const string& YearFail = "Invalid year, please try again.\n",
        const string& DateFail = "Invalid date, please try again.\n")
    {
        clsPeriod UserInput = ReadPeriod(PeriodStartMessage, PeriodEndMessage,
            EnterDayMessage, EnterMonthMessage, EnterYearMessage,
            DayFail, MonthFail, YearFail, DateFail);

        while (clsDate::CompareDates(UserInput.StartDate, Period.StartDate) == clsDate::Before ||
            clsDate::CompareDates(UserInput.EndDate, Period.EndDate) == clsDate::After)
        {
            cout << UserInputNotAfterPeriodMessage;
            UserInput = ReadPeriod(PeriodStartMessage, PeriodEndMessage,
                EnterDayMessage, EnterMonthMessage, EnterYearMessage,
                DayFail, MonthFail, YearFail, DateFail);
        }


        return UserInput;
    }


    static bool IsValidPeriod(clsPeriod& Period)
    {
        if (IsValidDate(Period.StartDate) && IsValidDate(Period.EndDate))
        {
            if (clsDate::CompareDates(Period.StartDate, Period.EndDate) == clsDate::Before)
                return true;
            else
                return false;
        }
        return false;
    }

    static string ReadString(const string& EnterStringMessage = "Enter a string: ")
    {
        string UserInput = "";

        cout << EnterStringMessage;
        getline(cin >> ws, UserInput);

        return UserInput;
    }
};

