#include<iostream>
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#include <string>
#include<ctime> // used to work with date and time
#include<stdlib.h>
#include <Windows.h>
#include <iomanip>

using namespace std;

void ClearScreen() // clears console
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    SetConsoleCursorPosition(hStdOut, homeCoords);
}

int MilitaryTimeConv(int hrs) { //reverts time back to 0 after clock reach 24
    if (hrs >= 24) {
        hrs -= 24;
    }
    else {
        hrs = hrs;
    }
    return hrs;
}

int StandardTimeConv(int hrs) { //12 hour clock function
    if (hrs > 12) {
        hrs -= 12;
    }
    else if (hrs == 0) {
        hrs = 12;
    }
    
    else {
        hrs = hrs;
    }
    return hrs;
}

string AMPM(int hrs) { //Determines if standard time is am or pm
    string amPM = "";
    if (hrs > 12) {
        amPM = " PM";
    }
    else {
        amPM = " AM";
    }
    return amPM;
}

void AddHour(int& hours) { //Adds 1 hour to hours
    hours += 1;
}
void Addminute(int& minutes) { //Adds 1 minute to minutes
    minutes += 1;
}

void AddSecond(int& seconds) { //Adds 1 second to secodns
    seconds += 1;
}

string FillTimeSt(int currentNum) { //Fills time for stanard times hours to display two digits instead of 1
    string fillTimeSt = "";
    if (currentNum < 10 && currentNum != 0) {
        fillTimeSt = "0";
    }
    else if (currentNum > 12 && currentNum < 22){
        fillTimeSt = "0";
    }
    else {
        fillTimeSt = "";
    }
    return fillTimeSt;
}
string FillTime(int currentNum) { //Fills time to make time display as two digits instead of 1
    string fillTime = "";
    if (currentNum < 10) {
        fillTime = "0";
    }
    return fillTime;
}
int main() { 
    time_t t; // t passed as argument in function time()
    struct tm* tt; // declaring variable for localtime()
    time(&t); //passing argument to time()
    tt = localtime(&t);

    string time = asctime(tt); //creates modifiable string of current time
    string timeRevised = ""; // initalizes first revision of time
    timeRevised = time.substr(10, 10); //Takes hours minutes and seconds into string
    string timeRevised2 = ""; //initalizes final ititeration of time revised


    for (int i = 0; i < timeRevised.length(); i++) { //takes digits out of timeRevised
        if (isdigit(timeRevised.at(i))) {
            timeRevised2 += timeRevised.at(i);
        }
    }



    string userInput = "";
    int hours = stoi(timeRevised2.substr(0, 2)); //converts the hours section of timeRevised2 to int

    int minutes = stoi(timeRevised2.substr(2, 2)); //converts minutes section to int

    int seconds = stoi(timeRevised2.substr(4, 4)); // converts seconds section to int


    while (userInput != "4") {
        cout << "*****************************" << endl;
        cout << "*12-Hour Clock---" << FillTimeSt(hours) << StandardTimeConv(hours) << ":" << FillTime(minutes) << minutes << ":" << FillTime(seconds) << seconds << AMPM(hours) << "*" << endl;
        cout << "*24-Hour Clock---" << FillTime(hours) << MilitaryTimeConv(hours) << ":" << FillTime(minutes) << minutes << ":" << FillTime(seconds) << seconds << "   *" << endl;
        cout << "*****************************" << endl << endl;

        cout << "************************" << endl;
        cout << "*Option 1: Add 1 hour  *" << endl; 
        cout << "*Option 2: Add 1 minute*" << endl;
        cout << "*Option 3: Add 1 second*" << endl;
        cout << "*Option 4: Exit program*" << endl;
        cout << "************************" << endl;
        cin >> userInput;

        if (userInput == "1") { //Adds 1 hour if user enters 1
            AddHour(hours);
        }
        else if (userInput == "2") { //Adds 1 minute if user enters 2
            Addminute(minutes);
        }
        else if (userInput == "3") { //Adds 1 second if user enters 3
            AddSecond(seconds);
        }

        if (seconds > 59) { // reverts seconds to 0 if seconds goes over 60 and adds one minute
            seconds = 0;
            minutes += 1;
        }
        if (minutes > 59) { // reverts minutes to 0 if minutes goes over 60 and adds one hour
            minutes = 0;
            hours += 1;
        }
        if (hours > 23) { // reverts hours to 0 if hours reaches 24
            hours = 0;
        }
        ClearScreen();

    }


    return 0;
}



