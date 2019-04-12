/*
 * POJ 2503 - Babelfish
 *
 */

#include <cstdio>
#include <cstdlib>
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
#include <unordered_map>
#include <cmath>

using namespace std;

int main() {
    unordered_map<string, string> dict;
    char buf[50] = {0}, word1[20] = {0}, word2[20] = {0};
    int cnt = 0;
    while (true) {
        char *ret = fgets(buf, sizeof(buf), stdin);
        if (buf[0] == '\n') break;
        sscanf(buf, "%s %s\n", word1, word2);
        dict[string(word2)] = string(word1);
        cnt++;
    }

    while (scanf("%s", word1) > 0) {
        string key(word1);
        if (dict.find(word1) != dict.end()) {
            printf("%s\n", dict[string(word1)].c_str());
        } else {
            printf("eh\n");
        }
    }

    return 0;
}

