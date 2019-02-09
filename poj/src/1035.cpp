/*
 * POJ 1035 - Spell checker
 *
 */

#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <set>
#include <string>
#include <map>
#include <cmath>

using namespace std;

vector<string> dict;
vector<string> wordsToCheck;

bool checkWord(string s1, string s2) {
    int len1 = s1.length(), len2 = s2.length();
    int idx = 0;
    while (idx < len1 && idx < len2) {
        if (s1[idx] != s2[idx]) break;
        idx++;
    }
    if (len1 < len2) return s1.substr(idx) == s2.substr(idx + 1);
    else if (len1 > len2) return s1.substr(idx + 1) == s2.substr(idx);
    else return s1 == s2 || s1.substr(idx + 1) == s2.substr(idx + 1);
}

int main() {
    string inputLine;
    while (true) {
        cin >> inputLine;
        if (inputLine == "#") break;
        dict.push_back(inputLine);
    }
    while (true) {
        cin >> inputLine;
        if (inputLine == "#") break;
        wordsToCheck.push_back(inputLine);
    }
    for (vector<string>::iterator itr = wordsToCheck.begin();
         itr != wordsToCheck.end(); ++itr) {
        vector<string> result;
        bool correct = false;
        for (vector<string>::iterator itr2 = dict.begin();
             itr2 != dict.end(); ++itr2) {
            if (*itr == *itr2) {
                correct = true;
                break;
            } else if (checkWord(*itr, *itr2)) {
                result.push_back(*itr2);
            }
        }
        cout << *itr;
        if (correct) {
            cout << " is correct" << endl;
        } else {
            cout << ":";
            for (vector<string>::iterator itr2 = result.begin();
                 itr2 != result.end(); ++itr2) {
                cout << " " << *itr2;
            }
            cout << endl;
        }
    }
    return 0;
}

