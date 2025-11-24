#pragma once
#include <iostream>
#include "clsDate.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "Global.h"

class clsUtil
{
public:

    enum enCharType { SmallLetter = 1, CapitalLetter = 2, SpecialCharacter = 3, Digit = 4, Mix = 5 };

    static void Srand()
    {
        srand((unsigned)time(NULL));
    }

    static int RandomNumber(int From, int To)
    {
        int randNum = rand() % (To - From + 1) + From;
        return randNum;
    }

    static char GetRandomCharacter(const enCharType& CharType)
    {
        switch (CharType)
        {
        case enCharType::SmallLetter:
        {
            return char(RandomNumber(97, 122));
            break;
        }
        case enCharType::CapitalLetter:
        {
            return char(RandomNumber(65, 90));
            break;
        }
        case enCharType::SpecialCharacter:
        {
            return char(RandomNumber(33, 47));
            break;
        }
        case enCharType::Digit:
        {
            return char(RandomNumber(48, 57));
            break;
        }
        case enCharType::Mix:
        {
            short RandomType = RandomNumber(1, 4);

            switch (RandomType)
            {
            case 1:
                return GetRandomCharacter(enCharType::SmallLetter);
            case 2:
                return GetRandomCharacter(enCharType::CapitalLetter);
            case 3:
                return GetRandomCharacter(enCharType::SpecialCharacter);
            case 4:
                return GetRandomCharacter(enCharType::Digit);
            }
            break;
        }
        }

        return '\0';
    }

    static string GenerateWord(const enCharType& CharType, short WordLength)
    {
        string Word;

        for (int i = 1; i <= WordLength; i++)
        {
            Word = Word + GetRandomCharacter(CharType);
        }
        return Word;
    }

    static string GenerateKey(const enCharType& CharType)
    {
        string Key = "";

        Key = GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4);

        return Key;
    }

    static void GenerateKeys(short NumberOfKeys, const enCharType& CharType)
    {
        for (int i = 1; i <= NumberOfKeys; i++)
        {
            cout << "Key [" << i << "] : ";
            cout << GenerateKey(CharType) << endl;
        }
    }


    // --------------------------Arrays---------------------------
    static void FillArrayWithRandomNumbers(int arr[], short Size, int From, int To)
    {
        for (short i = 0; i < Size; i++)
        {
            arr[i] = RandomNumber(From, To);
        }
    }

    static void FillArrayWithRandomWords(string arr[], short Size, const enCharType& CharType, short WordLength)
    {
        for (short i = 0; i < Size; i++)
        {
            arr[i] = GenerateWord(CharType, WordLength);
        }
    }

    static void FillArrayWithRandomKeys(string arr[], short Size, const enCharType& CharType)
    {
        for (short i = 0; i < Size; i++)
        {
            arr[i] = GenerateKey(CharType);
        }
    }

    static int CountPosNumsInArr(int arr[], int Size)
    {
        int Counter = 0;

        for (int i = 0; i < Size; i++)
        {
            if (arr[i] > 0)
                Counter++;
        }

        return Counter;
    }

    int CountNigNumsInArr(int arr[], int Size)
    {
        int Counter = 0;

        for (int i = 0; i < Size; i++)
        {
            if (arr[i] < 0)
                Counter++;
        }
        return Counter;
    }

    static int CountOddInArr(int arr1[], int Size)
    {
        int Counter = 0;

        for (int i = 0; i < Size; i++)
        {
            if (arr1[i] % 2 != 0)
                Counter++;
        }
        return Counter;
    }

    static int CountEvenInArr(int arr1[], int Size)
    {
        int Counter = 0;

        for (int i = 0; i < Size; i++)
        {
            if (arr1[i] % 2 == 0)
                Counter++;
        }
        return Counter;
    }

    static void PrintArrayElements(int arr[], short Size)
    {
        for (int i = 0; i < Size; i++)
        {
            cout << "Element[" << i + 1 << "]: " << arr[i] << endl;
        }
    }

    static int MaxNumberInArray(int arr[], short Size)
    {
        int Max = arr[0];

        for (int i = 1; i < Size; i++)
        {
            if (arr[i] > Max)
            {
                Max = arr[i];
            }
        }

        return Max;
    }

    static int MinNumberInArray(int arr[], short Size)
    {
        int Min = arr[0];

        for (int i = 1; i < Size; i++)
        {
            if (arr[i] < Min)
            {
                Min = arr[i];
            }
        }

        return Min;
    }

    static float SumOfNumbersInArray(int arr[], short Size)
    {
        float Sum = 0;

        for (int i = 0; i < Size; i++)
        {
            Sum += arr[i];
        }
        return Sum;
    }

    static float AverageOfNumbersInArray(int arr[], short Size)
    {
        return SumOfNumbersInArray(arr, Size) / Size;
    }

    static void CopyArray(int MainArr[], int ArrToCopyIn[], short Size)
    {
        for (int i = 0; i < Size; i++)
        {
            ArrToCopyIn[i] = MainArr[i];
        }
    }

    static bool CheckPrime(int Number)
    {
        if (Number <= 1) return false;
        if (Number == 2) return true;
        if (Number % 2 == 0) return false;

        int limit = (int)std::sqrt(Number);

        for (int i = 3; i <= limit; i += 2)
        {
            if (Number % i == 0) return false;
        }

        return true;
    }

    // Copies prime numbers from MainArr to arr2 and returns the count of copied elements
    static short PrimToArray2(int MainArr[], int arr2[], short Size)
    {
        short Counter = 0;

        for (short i = 0; i < Size; i++)
        {
            if (CheckPrime(MainArr[i]) == true)
            {
                arr2[Counter] = MainArr[i];
                Counter++;
            }

        }

        return Counter;
    }

    static void SumTwoArrays(int arr1[], int arr2[], int result[], short Size)
    {
        for (short i = 0; i < Size; i++)
        {
            result[i] = arr1[i] + arr2[i];
        }
    }

    // -----------Swap----------
    static void Swap(int& Num1, int& Num2)
    {
        int Temp;

        Temp = Num1;
        Num1 = Num2;
        Num2 = Temp;
    }

    static void Swap(double& Num1, double& Num2)
    {
        double Temp;

        Temp = Num1;
        Num1 = Num2;
        Num2 = Temp;
    }

    static void Swap(string& Num1, string& Num2)
    {
        string Temp;

        Temp = Num1;
        Num1 = Num2;
        Num2 = Temp;
    }

    static  void Swap(clsDate& A, clsDate& B)
    {
        clsDate::SwapDates(A, B);
    }

    // -----------Shuffle---------- 
    static void ShuffleArray(int arr[], short Size)
    {
        if (Size <= 1)
            return;

        for (short i = 0; i < Size; i++)
        {
            int ArrayIndex1 = RandomNumber(0, Size - 1);
            int ArrayIndex2 = RandomNumber(0, Size - 1);

            Swap(arr[ArrayIndex1], arr[ArrayIndex2]);
        }
    }

    static void ShuffleArray(double arr[], short Size)
    {
        for (short i = 0; i < Size; i++)
        {
            int ArrayIndex1 = RandomNumber(0, Size - 1);
            int ArrayIndex2 = RandomNumber(0, Size - 1);

            Swap(arr[ArrayIndex1], arr[ArrayIndex2]);
        }
    }

    static void ShuffleArray(string arr[], short Size)
    {
        for (short i = 0; i < Size; i++)
        {
            int ArrayIndex1 = RandomNumber(0, Size - 1);
            int ArrayIndex2 = RandomNumber(0, Size - 1);

            Swap(arr[ArrayIndex1], arr[ArrayIndex2]);
        }
    }


    static void CopyArrayInReverseOrder(int arr1[], int arr2[], short Size)
    {
        for (short i = 0; i < Size; i++)
        {
            arr2[Size - 1 - i] = arr1[i];
        }
    }

    // This function count how meny occurrence time for number
    static short CountOccurrences(int arr[], short Size, int NumberToFind)
    {
        short Counter = 0;

        for (short i = 0; i < Size; i++)
        {
            if (arr[i] == NumberToFind)
                Counter++;

        }

        return Counter;
    }

    // return (-1) means the number doesn't existed
    static short FindFirstPositionForNumberInArray(int arr[], short Size, int RequiredNumber)
    {
        for (short i = 0; i < Size; i++)
        {
            if (arr[i] == RequiredNumber)
                return i;
        }

        return -1;
    }

    static bool IsNumberInArray(int arr[], int Size, int ReqNumber)
    {
        return FindFirstPositionForNumberInArray(arr, Size, ReqNumber) != -1;
    }

    enum enNumberType { Odd, Even };

    static enNumberType GetNumberType(int Number)
    {
        if (Number % 2 != 0)
            return enNumberType::Odd;
        else
            return enNumberType::Even;
    }

    static void CopyOddNumbers(int MainArr[], int CopyTo[], short MainArr_Size, short& CopyTo_Size)
    {
        short Counter = 0;
        for (short i = 0; i < MainArr_Size; i++)
        {
            if (GetNumberType(MainArr[i]) == enNumberType::Odd)
            {
                CopyTo[Counter] = MainArr[i];
                Counter++;

                if (Counter >= CopyTo_Size)
                    break;
            }
        }
        CopyTo_Size = Counter;
    }

    static bool IsPalindromeArray(int arr[], short arrLength)
    {
        for (int i = 0; i < arrLength / 2; i++)
        {
            if (arr[i] != arr[arrLength - 1 - i])
                return false;
        }
        return true;
    }

    static short CountEvenInArray(int arr[], short Size)
    {
        short Counter = 0;

        for (short i = 0; i < Size; i++)
        {
            if (arr[i] % 2 == 0)
                Counter++;
        }

        return Counter;
    }

    static short CountOddInArray(int arr[], short Size)
    {
        short Counter = 0;

        for (short i = 0; i < Size; i++)
        {
            if (arr[i] % 2 != 0)
                Counter++;
        }

        return Counter;
    }

    static short CountPositiveNumbersInArray(int arr[], short Size)
    {
        short Counter = 0;

        for (short i = 0; i < Size; i++)
        {
            if (arr[i] > 0)
                Counter++;
        }

        return Counter;
    }

    static int CountNegativeNumbersInArray(int arr[], short Size)
    {
        short Counter = 0;

        for (short i = 0; i < Size; i++)
        {
            if (arr[i] < 0)
                Counter++;
        }

        return Counter;
    }

    static string Tabs(short HowManyTabs)
    {
        string Tabs = "";

        for (short i = 0; i < HowManyTabs; i++)
        {
            Tabs += "\t";
        }

        return Tabs;
    }

    static string EncryptText(string Text, short EncryptionKey = 2)
    {
        for (int i = 0; i < (int)Text.length(); i++)
        {
            Text[i] = char((int)Text[i] + EncryptionKey);
        }

        return Text;
    }

    static string DecryptText(string Text, short EncryptionKey = 2)
    {
        for (int i = 0; i < (int)Text.length(); i++)
        {
            Text[i] = char((int)Text[i] - EncryptionKey);
        }

        return Text;
    }

    static string NumberToText(int Number)
    {
        if (Number == 0)
        {
            return "";
        }

        if (Number >= 1 && Number <= 19)
        {
            string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
        "Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
          "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

            return  arr[Number] + " ";

        }

        if (Number >= 20 && Number <= 99)
        {
            string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
            return  arr[Number / 10] + " " + NumberToText(Number % 10);
        }

        if (Number >= 100 && Number <= 199)
        {
            return  "One Hundred " + NumberToText(Number % 100);
        }

        if (Number >= 200 && Number <= 999)
        {
            return   NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
        }

        if (Number >= 1000 && Number <= 1999)
        {
            return  "One Thousand " + NumberToText(Number % 1000);
        }

        if (Number >= 2000 && Number <= 999999)
        {
            return   NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
        }

        if (Number >= 1000000 && Number <= 1999999)
        {
            return  "One Million " + NumberToText(Number % 1000000);
        }

        if (Number >= 2000000 && Number <= 999999999)
        {
            return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
        }

        if (Number >= 1000000000 && Number <= 1999999999)
        {
            return  "One Billion " + NumberToText(Number % 1000000000);
        }
        else
        {
            return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
        }
    }
};

