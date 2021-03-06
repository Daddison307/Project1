// Project1.cpp
// Addison Dugal
// Project 1: Blood Sugar for COSC 2030


#include "stdafx.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <sstream> // stringstream used to convert input string into int, found on cppreference.com
using std::stringstream;

// Structs and count use to track day/week
// dayCount tracks day within main(), and other functions use that value to find the correct struct

struct day
{
	int data[100] = {};
	int count = 0;
	int min = 1000;
	int max = 0;
	int sum = 0;
};
struct week
{
	day days[7] = {};
} week1, week2;
int dayCount = 0;

// External functions used in main()

void addVal(int val)
{
	if (val <= 0) // Silently ignores 0 or negative values
	{
		return;
	}
	if (dayCount < 7) // Checks for first week
	{
		week1.days[dayCount].data[week1.days[dayCount].count] = val; // Adds value to array
		week1.days[dayCount].count++; // Keeps count of valid readings
		week1.days[dayCount].sum += val;
		if (val > week1.days[dayCount].max) //Adjusts max and min values
		{
			week1.days[dayCount].max = val;
		}
		if (val < week1.days[dayCount].min)
		{
			week1.days[dayCount].min = val;
		}
	}
	if (dayCount >= 7) // Same for week 2
	{
		week2.days[dayCount - 7].data[week2.days[dayCount - 7].count] = val;
		week2.days[dayCount - 7].count++;
		week2.days[dayCount - 7].sum += val;
		if (val > week2.days[dayCount - 7].max)
		{
			week2.days[dayCount - 7].max = val;
		}
		if (val < week2.days[dayCount - 7].min)
		{
			week2.days[dayCount - 7].min = val;
		}
	}
}

void printDay()
{
	cout << "Daily Summary:\n";
	if (dayCount < 7)
	{
		cout << "Sum of valid readings: " << week1.days[dayCount].sum << endl;
		cout << "Max of valid readings: " << week1.days[dayCount].max << endl;
		cout << "Min of valid readings: " << week1.days[dayCount].min << endl;
		cout << "Count of valid readings: " << week1.days[dayCount].count << endl;
	}
	if (dayCount >= 7)
	{
		cout << "Sum of valid readings: " << week2.days[dayCount - 7].sum << endl;
		cout << "Max of valid readings: " << week2.days[dayCount - 7].max << endl;
		cout << "Min of valid readings: " << week2.days[dayCount - 7].min << endl;
		cout << "Count of valid readings: " << week2.days[dayCount - 7].count << endl;
	}
}

void printWeek()
{
	cout << "Weekly Summary:\n";
	int weekMax = 0, weekMin = 1000, weekCount = 0, weekSum = 0, delta = 0, deltaDay = 0;
	if (dayCount < 7)
	{
		for (int i = 0; i < 7; i++)
		{
			if (week1.days[i].max > weekMax)
			{
				weekMax = week1.days[i].max;
			}
			if (week1.days[i].min < weekMin)
			{
				weekMin = week1.days[i].min;
			}
			weekCount += week1.days[i].count;
			weekSum += week1.days[i].sum;
			if (abs((week1.days[i].count - week1.days[i - 1].count)) > delta)
			{
				delta = abs((week1.days[i].count - week1.days[i - 1].count));
				deltaDay = i + 1;
			}
		}
	}
	if (dayCount >= 7)
	{
		for (int i = 0; i < 7; i++)
		{
			if (week2.days[i].max > weekMax)
			{
				weekMax = week2.days[i].max;
			}
			if (week2.days[i].min < weekMin)
			{
				weekMin = week2.days[i].min;
			}
			weekCount += week2.days[i].count;
			weekSum += week2.days[i].sum;
			if (abs((week2.days[i].count - week2.days[i - 1].count)) > delta)
			{
				delta = abs((week2.days[i].count - week2.days[i - 1].count));
				deltaDay = i + 1;
			}
		}
	}
	cout << "Sum of valid readings: " << weekSum << endl;
	cout << "Max of valid readings: " << weekMax << endl;
	cout << "Min of valid readings: " << weekMin << endl;
	cout << "Count of valid readings: " << weekCount << endl;
	cout << "Day with biggest Delta of readings: " << (deltaDay) << endl;
}

// Main function
int main()
{
	bool done = false; // Function will be 'done' when dayCount hits 14
	cout << "Please enter data. Enter 'N' or 'Next' to advance day.\nEnter 'D' or 'Day' for daily summary. Enter 'W' or 'Week' for weekly summary.\n";
	while (!done)
	{
		string buf;
		int value;
		string cmd;
		bool isInt = true; // Resets variable with each loop

		cin >> buf;
	
		string::const_iterator it = buf.begin();
		while (it != buf.end()) // Iterates through string to see if it is a number
		{
			if (!isdigit(*it))
			{
				isInt = false;
				it = buf.end(); // Exits loop faster once a non-numeric char is found
			}
			else
			{
				++it; // This must be put as an else, because an error will occur if the iterator moves past end
			}
		}

		if (isInt)
		{
			stringstream stream(buf); // from <sstream>
			stream >> value; // Allows string to be streamed into an integer
			addVal(value);
		}
		if (!isInt)
		{
			cmd = buf;
			if (cmd == "N" || cmd == "Next")
			{
				dayCount++;
				cout << "Next day:\n"; // Text output to confirm to user
			}
			if (cmd == "D" || cmd == "Day")
			{
				printDay();
			}
			if (cmd == "W" || cmd == "Week")
			{
				printWeek();
			}
		}
		if (dayCount == 14)
		{
			done = true;
		}
	}
	return 0;
}
