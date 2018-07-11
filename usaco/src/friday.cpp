/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: friday
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool isLeapYear(int year) {
    return (!(year % 4)) && ((year % 100) || (!(year % 400)));
}

int main() {
    ofstream fout ("friday.out");
    ifstream fin ("friday.in");

    int N;
    fin >> N;

    int dayCount[7] = {0};
    dayCount[5] = 1; // Jan 13, 1990 was Sat.
    int normalYear[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int leapYear[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int endYear = 1900 + N - 1;
    int day = 5;

    for (int i = 1900; i <= endYear; i++) {
        for (int j = 0; j < 12; j++) {
            if (isLeapYear(i)) {
                day = (day + leapYear[j]) % 7;
            } else {
                day = (day + normalYear[j]) % 7;
            }
            dayCount[day] += 1;
        }
    }
    // last day is Jan. 13th
    dayCount[day] -= 1;

    for (int i = 0; i < 7; i++) {
        fout << dayCount[(i + 5) % 7];
        if (i == 6) {
            fout << endl;
        } else {
            fout << " ";
        }
    }

    return 0;
}
