/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: ride
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ofstream fout ("ride.out");
    ifstream fin ("ride.in");
    string comet, group;
    int cometProduct = 1;
    int groupProduct = 1;
    fin >> comet >> group;
    for (size_t i = 0; i < comet.length(); i++)
        cometProduct = (cometProduct * (int(comet[i]) - int('A') + 1)) % 47;
    for (size_t i = 0; i < group.length(); i++)
        groupProduct = (groupProduct * (int(group[i]) - int('A') + 1)) % 47;
    if (cometProduct == groupProduct)
        fout << "GO" << endl;
    else
        fout << "STAY" << endl;
    return 0;
}
