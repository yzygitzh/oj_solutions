/*
 * POJ 3080 - Blue Jeans
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

int strNum;

string findPattern(vector<string>& strs, int patternLen) {
    string resultStr = "";
    for (int i = 0; i + patternLen <= 60; i++) {
        string pattern = strs[0].substr(i, patternLen);
        bool allFound = true;
        for (int j = 1; j < strNum; j++) {
            if (strs[j].find(pattern) == string::npos) {
                allFound = false;
                break;
            }
        }
        if (!allFound) continue;
        if (resultStr.length() == 0) {
            resultStr = pattern;
        } else {
            resultStr = min(resultStr, pattern);
        }
    }
    return resultStr;
}

int main() {
    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        string inputLine;
        vector<string> strs;
        cin >> strNum;
        for (int i = 0; i < strNum; i++) {
            cin >> inputLine;
            strs.push_back(inputLine);
        }
        int left = 3, right = 60;
        string pattern;
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            pattern = findPattern(strs, mid);
            if (pattern.length() > 0) {
                left = mid;
            } else {
                right = mid;
            }
        }
        pattern = findPattern(strs, right);
        if (pattern.length() > 0) {
            cout << pattern << endl;
            continue;
        }
        pattern = findPattern(strs, left);
        if (pattern.length() > 0) {
            cout << pattern << endl;
            continue;
        }
        cout << "no significant commonalities" << endl;
    }
    return 0;
}

