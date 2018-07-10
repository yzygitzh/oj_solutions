/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: gift1
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main() {
    ofstream fout ("gift1.out");
    ifstream fin ("gift1.in");

    int NP;
    fin >> NP;
    string name;
    map<string, int> personMoney;
    vector<string> nameList;

    for (int i = 0; i < NP; i++) {
        fin >> name;
        personMoney[name] = 0;
        nameList.push_back(name);
    }

    int totalMoney, divider;
    string hostName;
    for (int i = 0; i < NP; i++) {
        fin >> hostName;
        fin >> totalMoney >> divider;
        if (divider == 0) {
            continue;
        }
        personMoney[hostName] -= totalMoney;
        int rest = totalMoney % divider;
        personMoney[hostName] += rest;
        int part = (totalMoney - rest) / divider;
        for (int j = 0; j < divider; j++) {
            fin >> name;
            personMoney[name] += part;
        }
    }

    for (int i = 0; i < nameList.size(); i++) {
        fout << nameList[i] << " " << personMoney[nameList[i]] << endl;
    }

    return 0;
}
