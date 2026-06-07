#include<iostream>
#include<vector>
#include<ctime>
#include<string>
#include<iomanip>

using namespace std;

class Country
{

public:
    string name;
    int utcHour;
    int utcMinute;
    Country(string n, int h , int m){
        name = n;
        utcHour = h;
        utcMinute = m;
    }
};



vector<Country> countries = {
    {"India", 5,30}, 
    {"UK",0,00}, 
    {"USA",-5,0}, 
    {"Japan",9,0}, 
    {"Nepal", 5, 45},
    {"Germany", 1,0}, 
    {"Australia", 10,0 },
    {"China",8,0},
    {"Singapore",8,0},
    {"UAE",4,0}
};

int findCountry(string name){
    for (int i = 0; i < countries.size(); i++)
    {
        if (countries[i].name == name)
        {
            return i;
        }
    }
    return -1;
}

void getLocalTime(const Country&c, int &hour , int &minute){
    time_t now = time(0);;
    tm *utc = gmtime(&now);

    hour = utc->tm_hour + c.utcHour;
    minute = utc -> tm_min + c.utcMinute;

    while (minute >= 60){
        minute = minute-60;
        hour ++;
    }

    while (minute < 0)
    {
        minute = minute+60;
        hour--;
    }

    hour = (hour+24) % 24;
}

void print12Hour(int hour , int minute ){
    string period = (hour>=12) ? "PM" : "AM";
    hour %= 12;
    if (hour  == 0)
    {
       hour = 12;
    }

    cout << setw(2) << setfill('0') << hour << ":" << setw(2) << minute << " " << period;
    
    cout << setfill(' ');
}

void displayWorldTime()
{
    cout << "\n=====================================================\n";
    cout << "                    WORLD CLOCK\n";
    cout << "=====================================================\n";

    cout << left
         << setw(15) << "Country"
         << setw(15) << "24-Hour"
         << "12-Hour\n";

    cout << "-----------------------------------------------------\n";

    for(auto country : countries)
    {
        int h,m;

        getLocalTime(country,h,m);

        cout << left
             << setw(15)
             << country.name;

        cout << right
             << setw(2)
             << setfill('0')
             << h << ":"
             << setw(2)
             << m
             << setfill(' ');

        cout << "        ";

        print12Hour(h,m);

        cout << endl;
    }
}
void searchCountry()
{
    string name;

    cout << "\nEnter Country Name: ";
    cin >> name;

    int idx = findCountry(name);

    if(idx == -1)
    {
        cout << "Country not found.\n";
        return;
    }

    int h,m;

    getLocalTime(countries[idx],h,m);

    cout << "\nCountry: "
         << countries[idx].name
         << endl;

    cout << "24-Hour Format: ";

    cout << setw(2)
         << setfill('0')
         << h << ":"
         << setw(2)
         << m
         << endl;

    cout << "12-Hour Format: ";
    print12Hour(h,m);
    cout << endl;
}

void compareTimeZones()
{
    string c1,c2;

    cout << "\nEnter First Country: ";
    cin >> c1;

    cout << "Enter Second Country: ";
    cin >> c2;

    int i1 = findCountry(c1);
    int i2 = findCountry(c2);

    if(i1 == -1 || i2 == -1)
    {
        cout << "Invalid Country Name.\n";
        return;
    }

    int hDiff =
        countries[i1].utcHour - countries[i2].utcHour;

    int mDiff =
        countries[i1].utcMinute - countries[i2].utcMinute;

    if(mDiff < 0)
    {
        mDiff += 60;
        hDiff--;
    }

    if(hDiff < 0)
        hDiff *= -1;

    cout << "\nTime Difference Between "
         << c1 << " and "
         << c2 << " = "
         << hDiff << " hour(s) "
         << mDiff << " minute(s)\n";
}

void suggestMeetingTime()
{
    string c1,c2;

    cout << "\nEnter First Country: ";
    cin >> c1;

    cout << "Enter Second Country: ";
    cin >> c2;

    int i1 = findCountry(c1);
    int i2 = findCountry(c2);

    if(i1 == -1 || i2 == -1)
    {
        cout << "Invalid Country Name.\n";
        return;
    }

    int offsetHour =
        countries[i2].utcHour -
        countries[i1].utcHour;

    int offsetMin =
        countries[i2].utcMinute -
        countries[i1].utcMinute;

    bool found = false;

    cout << "\nSuggested Meeting Slots\n";
    cout << "(Working Hours: 9AM - 5PM)\n\n";

    for(int h = 9; h <= 17; h++)
    {
        int otherHour = h + offsetHour;
        int otherMin = offsetMin;

        while(otherMin >= 60)
        {
            otherMin -= 60;
            otherHour++;
        }

        while(otherMin < 0)
        {
            otherMin += 60;
            otherHour--;
        }

        otherHour = (otherHour + 24) % 24;

        if(otherHour >= 9 &&
           otherHour <= 17)
        {
            found = true;

            cout << setw(2)
                 << setfill('0')
                 << h
                 << ":00 "
                 << c1
                 << " <--> ";

            cout << setw(2)
                 << otherHour
                 << ":"
                 << setw(2)
                 << otherMin
                 << " "
                 << c2
                 << endl;
        }
    }

    if(!found)
    {
        cout << "No common meeting slot found.\n";
    }

    cout << setfill(' ');
}

void showCountries()
{
    cout << "\nAvailable Countries:\n";

    for(auto c : countries)
    {
        cout << "- "
             << c.name
             << endl;
    }
}
int main()
{
    int choice;

    do
    {
        cout << "\n========================================\n";
        cout << "     SMART WORLD CLOCK SYSTEM\n";
        cout << "========================================\n";

        cout << "1. Display World Time\n";
        cout << "2. Search Country Time\n";
        cout << "3. Compare Time Zones\n";
        cout << "4. Suggest Meeting Time\n";
        cout << "5. Show Countries\n";
        cout << "6. Exit\n";

        cout << "\nEnter Choice: ";

        while(!(cin >> choice))
        {
            cin.clear();
            cout << "Invalid Input. Enter Again: ";
        }

        switch(choice)
        {
            case 1:
                displayWorldTime();
                break;

            case 2:
                searchCountry();
                break;

            case 3:
                compareTimeZones();
                break;

            case 4:
                suggestMeetingTime();
                break;

            case 5:
                showCountries();
                break;

            case 6:
                cout << "\nThank You For Using Smart World Clock!\n";
                break;

            default:
                cout << "\nInvalid Choice.\n";
        }

    }while(choice != 6);

    return 0;
}