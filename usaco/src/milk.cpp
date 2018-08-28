/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: milk
LANG: C++
*/
/* LANG can be C++20 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Farmer {
public:
    int price;
    int units;
    Farmer(int _price, int _units): price(_price), units(_units) {}
    bool operator<(const Farmer& f) {
        return this->price < f.price;
    }
};

int main() {
    ofstream fout ("milk.out");
    ifstream fin ("milk.in");

    int totalUnits, farmerN;
    int farmerUnits, farmerPrice;
    vector<Farmer> farmers;

    fin >> totalUnits >> farmerN;

    for (int i = 0; i < farmerN; i++) {
        fin >> farmerPrice >> farmerUnits;
        farmers.push_back(Farmer(farmerPrice, farmerUnits));
    }
    sort(farmers.begin(), farmers.end());

    int costSum = 0;
    for (int i = 0; i < farmerN; i++) {
        if (totalUnits > farmers[i].units) {
            costSum += farmers[i].units * farmers[i].price;
            totalUnits -= farmers[i].units;
        } else {
            costSum += totalUnits * farmers[i].price;
            break;
        }
    }
    fout << costSum << endl;

    return 0;
}

