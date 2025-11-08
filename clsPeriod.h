#pragma once
#include "clsDate.h"
#include "Global.h"

class clsPeriod
{
public:

    clsDate StartDate;
    clsDate EndDate;

    clsPeriod(const clsDate& StartDate, const clsDate& DateTo)
    {
        this->StartDate = StartDate;
        this->EndDate = DateTo;
    }


    static bool IsOverlapPeriods(const clsPeriod& Period1, const clsPeriod& Period2)
    {

        if (
            clsDate::CompareDates(Period2.EndDate, Period1.StartDate) == clsDate::enDateCompare::Before
            ||
            clsDate::CompareDates(Period2.StartDate, Period1.EndDate) == clsDate::enDateCompare::After
            )
            return false;
        else
            return true;

    }

    bool IsOverLapWith(const clsPeriod& Period2)
    {
        return IsOverlapPeriods(*this, Period2);
    }


    static int PeriodLengthInDays(clsPeriod Period, bool IncludeEndDay = false)
    {
        return clsDate::GetDifferenceInDays(Period.StartDate, Period.EndDate, IncludeEndDay);
    }

    int PeriodLengthInDays(bool IncludeEndDay = false)
    {
        return PeriodLengthInDays(*this, IncludeEndDay);
    }


    static bool IsDateInPeriod(const clsPeriod& Period, const clsDate& Date)
    {
        return !(clsDate::CompareDates(Date, Period.StartDate) == clsDate::Before ||
            clsDate::CompareDates(Date, Period.EndDate) == clsDate::After);
    }

    bool IsDateInPeriod(const clsDate& Date)
    {
        return IsDateInPeriod(*this, Date);
    }


    static int CountOverlapedDays(clsPeriod& Period1, clsPeriod& Period2)
    {
        if (!clsPeriod::IsOverlapPeriods(Period1, Period2))
            return 0;

        int Period1Length = PeriodLengthInDays(Period1, true);
        int Period2Length = PeriodLengthInDays(Period2, true);
        int OverlapedDaysCounter = 0;


        if (Period1Length < Period2Length)
        {
            while (clsDate::IsDate1BeforeDate2(Period1.StartDate, Period1.EndDate))
            {
                if (IsDateInPeriod(Period2, Period1.StartDate))
                    OverlapedDaysCounter++;

                Period1.StartDate = clsDate::AddOneDay(Period1.StartDate);
            }
        }
        else
        {
            while (clsDate::IsDate1BeforeDate2(Period2.StartDate, Period2.EndDate))
            {
                if (IsDateInPeriod(Period1, Period2.StartDate))
                    OverlapedDaysCounter++;

                Period2.StartDate = clsDate::AddOneDay(Period2.StartDate);
            }
        }

        return OverlapedDaysCounter;
    }

    int CountOverlapedDays(clsPeriod& Period)
    {
        return CountOverlapedDays(*this, Period);
    }


    static void Print(clsPeriod& Period,
        const string& PeriodStartMessage = "PeriodStart: ",
        const string& PeriodEndMessage = "\nPeriodEnd: ",
        const string PrameterInDate = "/")
    {
        cout << PeriodStartMessage;
        clsDate::Print(Period.StartDate, PrameterInDate);

        cout << PeriodEndMessage;
        clsDate::Print(Period.EndDate, PrameterInDate);
    }


    void Print(const string& PeriodStartMessage = "PeriodStart: ",
        const string& PeriodEndMessage = "PeriodEnd: ",
        const string PrameterInDate = "/")
    {
        Print(*this, PeriodStartMessage, PeriodEndMessage, PrameterInDate);
    }



};
