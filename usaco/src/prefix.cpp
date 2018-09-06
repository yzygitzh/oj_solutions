/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: prefix
LANG: C++
*/
/* LANG can be C++20 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <set>
#include <string>
#include <map>

using namespace std;

class TrieNode {
public:
    TrieNode *children[26];
    bool hasEnd[26];
    TrieNode() {
        for (int i = 0; i < 26; i++) {
            this->children[i] = NULL;
            this->hasEnd[i] = false;
        }
    }
};

class Trie {
public:
    TrieNode *root;
    Trie() {
        this->root = new TrieNode();
    }
    void insert(string word) {
        TrieNode *currPtr = this->root;
        for (int i = 0; i < word.length(); i++) {
            if (currPtr->children[word[i] - 'A'] == NULL) {
                currPtr->children[word[i] - 'A'] = new TrieNode();
            }
            currPtr = currPtr->children[word[i] - 'A'];
            if (i + 1 == word.length()) {
                currPtr->hasEnd[word[i] - 'A'] = true;
            }
        }
    }
    bool find(string word) {
        TrieNode *currPtr = this->root;
        for (int i = 0; i < word.length(); i++) {
            if (currPtr->children[word[i] - 'A'] == NULL) {
                return false;
            }
            currPtr = currPtr->children[word[i] - 'A'];
            if (i + 1 == word.length()) {
                return currPtr->hasEnd[word[i] - 'A'];
            }
        }
        return false;
    }
} trie;

int valid[200010] = {0};

int main() {
    ofstream fout ("prefix.out");
    ifstream fin ("prefix.in");

    string tmpStr, totalStr;
    while (true) {
        fin >> tmpStr;
        if (tmpStr == ".") break;
        trie.insert(tmpStr);
    }
    while (fin >> tmpStr) {
        totalStr += tmpStr;
    }

    // cout << totalStr << endl;
    
    for (int i = 0; i < totalStr.length(); i++) {
        // find whether length-j primitive will do
        for (int j = 1; j <= 10 && i - j + 1 >= 0; j++) {
            // cout << totalStr.substr(i - j + 1, j);
            // cout << trie.find(totalStr.substr(i - j + 1, j));
            // cout << endl;
            if (trie.find(totalStr.substr(i - j + 1, j))) {
                if (i - j + 1 == 0) valid[i] |= 1;
                else valid[i] |= valid[i - j];
            }
        }
    }

    int maxLen = 0;
    for (int i = 0; i < totalStr.length(); i++) {
        if (valid[i]) maxLen = i + 1;
    }
    fout << maxLen << endl;

    return 0;
}

