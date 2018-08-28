/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: namenum
LANG: C++
*/
/* LANG can be C++20 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

string dict[5010];

int char_map[26] = {2, 2, 2,
                    3, 3, 3,
                    4, 4, 4,
                    5, 5, 5,
                    6, 6, 6,
                    7, 7, 7, 7,
                    8, 8, 8,
                    9, 9, 9, 9};
char low_map[10] = {'\0', '\0', 'A', 'D', 'G', 'J', 'M', 'P', 'T', 'W'};
char high_map[10] = {'\0', '\0', 'C', 'F', 'I', 'L', 'O', 'S', 'V', 'Z'};

// [1,2]
int find_low(string low_str, int start, int end) {
    while (start + 1 < end) {
        int mid = (start + end) / 2;
        string seq = dict[mid];
        if (seq.compare(low_str) >= 0) {
            end = mid;
        } else {
            start = mid;
        }
    }
    return start;
}

int find_high(string high_str, int start, int end) {
    while (start + 1 < end) {
        int mid = (start + end) / 2;
        string seq = dict[mid];
        if (seq.compare(high_str) <= 0) {
            start = mid;
        } else {
            end = mid;
        }
    }
    return end;
}

int main() {
    ofstream fout ("namenum.out");
    ifstream fin ("namenum.in");
    ifstream fdict ("dict.txt");

    string N;
    fin >> N;

    int lineCount = 0;
    while (getline(fdict, dict[lineCount])) {
        int lineLen = dict[lineCount].length();
        lineCount += 1;
    }

    string low_str = "";
    string high_str = "";
    for (int i = 0; i < N.length(); i++) {
        low_str += low_map[N[i] - '0'];
        high_str += high_map[N[i] - '0'];
    }

    int low = find_low(low_str, 0, lineCount - 1);
    int high = find_high(high_str, 0, lineCount - 1);

    bool printed = false;
    for (int i = low; i <= high; i++) {
        bool goodToPrint = true;
        if (dict[i].length() != N.length()) {
            goodToPrint = false;
        }
        for (int j = 0; j < dict[i].length(); j++) {
            if (dict[i][j] == 'Q' || dict[i][j] == 'Z' || char_map[dict[i][j] - 'A'] != (N[j] - '0')) {
                goodToPrint = false;
                break;
            }
        }
        if (goodToPrint) {
            fout << dict[i] << endl;
            printed = true;
        }
    }
    if (!printed) {
        fout << "NONE" << endl;
    }

    return 0;
}

