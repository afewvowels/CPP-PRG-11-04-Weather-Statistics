//
//  main.cpp
//  CPP-PRG-11-04-Weather-Statistics
//
//  Created by Keith Smith on 11/6/17.
//  Copyright © 2017 Keith Smith. All rights reserved.
//
//  Write a program that uses a structure to store the following weather data for a
//  particular month:
//
//      Total Rainfall
//      High Temperature
//      Low Temperature
//      Average Temperature
//
//  The program should have an array of 12 structures to hold weather data for an entire
//  year. When the program runs, it should ask the user to enter data for each month.
//  (The average temperature should be calculated.) Once the data are entered for all the
//  months, the program should calculate and display the average monthly rainfall, the
//  total rainfall for the year, the highest and lowest temperatures for the year (and the
//  months they occurred in), and the average of all the monthly temperatures.
//
//  Input Validation: Only accept temperatures within the range between -100 and +140
//  degrees Fahrenheit.
//

#include <iostream>
#include <iomanip>

struct StructMonthWeather
{
    double dblRainfallTotal;
    double dblTempHigh;
    double dblTempLow;
    double dblTempAverage;
};

struct StructWeatherResults
{
    double dblAverageMonthlyRainfall;
    double dblTotalRainfallAnnual;
    double dblTempHighest;
    int intMonthHigh;
    double dblTempLowest;
    int intMonthLow;
    double dblAverageMonthlyTemp;
};

using namespace std;

StructMonthWeather *getMonthsData(int);
StructWeatherResults *calculateResults(StructMonthWeather *, const int);
void displayResults(StructWeatherResults *, const int);

int main()
{
    const int INT_ARR_SIZE = 12;
    
    StructMonthWeather *stcWeather = nullptr;
    stcWeather = new StructMonthWeather[INT_ARR_SIZE];
    
    StructWeatherResults *stcWeatherResults = nullptr;
    stcWeatherResults = new StructWeatherResults;
    
    for (int i = 0 ; i < INT_ARR_SIZE ; i++)
    {
        stcWeather[i] = *getMonthsData(i);
    }
    
    stcWeatherResults = calculateResults(stcWeather, INT_ARR_SIZE);
    
    displayResults(stcWeatherResults, INT_ARR_SIZE);
    
    return 0;
}

StructMonthWeather *getMonthsData(int intMonth)
{
    StructMonthWeather *stcWeatherMonth = nullptr;
    stcWeatherMonth = new StructMonthWeather;
    
    intMonth++;
    
    cout << "Please enter the total rainfall for month " << intMonth << ": ";
    cin >> stcWeatherMonth->dblRainfallTotal;
    while(!cin || stcWeatherMonth->dblRainfallTotal < 0 || stcWeatherMonth->dblRainfallTotal > 1000)
    {
        cout << "Please enter a number between 0 and 1,000: ";
        cin.clear();
        cin.ignore();
        cin >> stcWeatherMonth->dblRainfallTotal;
    }

    cout << "Please enter the highest temperature for month " << intMonth << ": ";
    cin >> stcWeatherMonth->dblTempHigh;
    while(!cin || stcWeatherMonth->dblTempHigh < -100 || stcWeatherMonth->dblTempHigh > 140)
    {
        cout << "Please enter a temperature between -100F and 140F: ";
        cin.clear();
        cin.ignore();
        cin >> stcWeatherMonth->dblTempHigh;
    }
    
    cout << "Please enter the lowest temperature for month " << intMonth << ": ";
    cin >> stcWeatherMonth->dblTempLow;
    while(!cin || stcWeatherMonth->dblTempLow < -100 || stcWeatherMonth->dblTempLow > 140)
    {
        cout << "Please enter a temperature between -100F and 140F: ";
        cin.clear();
        cin.ignore();
        cin >> stcWeatherMonth->dblTempLow;
    }
    
    stcWeatherMonth->dblTempAverage = (stcWeatherMonth->dblTempHigh + stcWeatherMonth->dblTempLow) / 2;
    
    return stcWeatherMonth;
}

StructWeatherResults *calculateResults(StructMonthWeather *stcArr, const int INT_SIZE)
{
    StructWeatherResults *stcResults = nullptr;
    stcResults = new StructWeatherResults;
    
    double *dblAverageRainfall = nullptr;
    dblAverageRainfall = new double;
    *dblAverageRainfall = 0;
    
    double *dblTotalRainfall = nullptr;
    dblTotalRainfall = new double;
    *dblTotalRainfall = 0;
    
    int *intHighestMonth = nullptr;
    intHighestMonth = new int;
    
    double *dblHighestTemp = nullptr;
    dblHighestTemp = new double;
    *dblHighestTemp = __DBL_MIN__;
    
    int *intLowestMonth = nullptr;
    intLowestMonth = new int;
    
    double *dblLowestTemp = nullptr;
    dblLowestTemp = new double;
    *dblLowestTemp = __DBL_MAX__;
    
    double *dblAverageTemp = nullptr;
    dblAverageTemp = new double;
    *dblAverageTemp = 0;
    
    for (int i = 0 ; i < INT_SIZE ; i++)
    {
        *dblTotalRainfall += stcArr[i].dblRainfallTotal;
    }
    stcResults->dblTotalRainfallAnnual = *dblTotalRainfall;
    
    *dblAverageRainfall = *dblTotalRainfall / INT_SIZE;
    stcResults->dblAverageMonthlyRainfall = *dblAverageRainfall;
    
    for (int i = 0 ; i < INT_SIZE ; i++)
    {
        *dblAverageTemp += stcArr[i].dblTempAverage;
        
        if (stcArr[i].dblTempHigh > *dblHighestTemp)
        {
            *dblHighestTemp = stcArr[i].dblTempHigh;
            *intHighestMonth = i + 1;
        }
        
        if (stcArr[i].dblTempLow < *dblLowestTemp)
        {
            *dblLowestTemp = stcArr[i].dblTempLow;
            *intLowestMonth = i + 1;
        }
    }
    
    stcResults->dblTempHighest = *dblHighestTemp;
    stcResults->intMonthHigh = *intHighestMonth;
    
    stcResults->dblTempLowest = *dblLowestTemp;
    stcResults->intMonthLow = *intLowestMonth;
    
    stcResults->dblAverageMonthlyTemp = *dblAverageTemp / INT_SIZE;
    
    return stcResults;
}

void displayResults(StructWeatherResults *stcResults, const int INT_SIZE)
{
    cout << fixed << showpoint << setprecision(1);
    
    cout << "The average monthly rainfall was: " << stcResults->dblAverageMonthlyRainfall << endl;
    
    cout << "The total annual rainfall was: " << stcResults->dblTotalRainfallAnnual << endl;
    
    cout << "The highest temperature of the year was in month ";
    cout << stcResults->intMonthHigh << ": " << stcResults->dblTempHighest << "F\n";
    
    cout << "The lowest temperature of the year was in month ";
    cout << stcResults->intMonthLow << ": " << stcResults->dblTempLowest << "F\n";
    
    cout << "The average monthly temperature was: ";
    cout << stcResults->dblAverageMonthlyTemp << "F\n";
}
