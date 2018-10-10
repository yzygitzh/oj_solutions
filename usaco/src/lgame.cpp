/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: lgame
LANG: C++
*/
/* LANG can be C++20 or C++14 for those more recent releases */
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

ifstream fin ("lgame.in");
ifstream din ("lgame.dict");
ofstream fout ("lgame.out");

class TrieNode {
public:
    // TrieNode* next[26];
    int next[26];
    unsigned char end[26];
    TrieNode() {
        memset(next, 0, sizeof(next));
        memset(end, 0, sizeof(end));
    }
};
// TrieNode rootNode;
// TrieNode* trieRoot = &rootNode;
TrieNode trie[80000];
int nextFree = 1;

int nodeCount = 0;
void insertWord(string word) {
    // TrieNode* currNode = trieRoot;
    TrieNode* currNode = trie;
    for (string::iterator itr = word.begin(); itr != word.end(); ++itr) {
        if (!currNode->next[*itr - 'a']) {
            // currNode->next[*itr - 'a'] = new TrieNode();
            currNode->next[*itr - 'a'] = nextFree++;
            nodeCount++;
        }
        if (itr + 1 == word.end()) currNode->end[*itr - 'a'] = 1;
        // currNode = currNode->next[*itr - 'a'];
        currNode = trie + currNode->next[*itr - 'a'];
    }
}

bool findWord(string word) {
    // TrieNode* currNode = trieRoot;
    TrieNode* currNode = trie;
    for (string::iterator itr = word.begin(); itr != word.end(); ++itr) {
        if (!currNode->next[*itr - 'a']) return false;
        if (itr + 1 == word.end()) return currNode->end[*itr - 'a'];
        // currNode = currNode->next[*itr - 'a'];
        currNode = trie + currNode->next[*itr - 'a'];
    }
    return false;
}

string inputStr;
int visited[10] = {0};
int letterScore[26] = {2, 5, 4, 4, 1, 6, 5,
                       5, 1, 7, 6, 3, 5, 2,
                       3, 5, 7, 2, 1, 2,
                       4, 6, 6, 7, 5, 7};
int maxScore = 0;
set<string> maxSet;

int getScore(string word) {
    int score = 0;
    for (string::iterator itr = word.begin();
         itr != word.end(); ++itr) {
        if (*itr != ' ') score += letterScore[*itr - 'a'];
    }
    return score;
}

void search(string word1, string word2) {
    if (word2.length() && (!word1.length() || word1 > word2)) return;
    // if (!word2.length()) cout << word1 << " " << word2 << endl;
    string currWord;
    currWord = word1;
    if (word2 != "") {
        currWord += " ";
        currWord += word2;
    }
    int score = getScore(currWord);
    if (findWord(word1) && (!word2.length() || findWord(word2))) {
        if (score > maxScore) {
            maxSet.clear();
            maxSet.insert(currWord);
            maxScore = score;
        } else if (score == maxScore) {
            maxSet.insert(currWord);
        }
    }
    // for each unused input, try word1 then word2
    for (int i = 0; i < inputStr.length(); i++) {
        if (!visited[i]) {
            visited[i] = 1;
            search(word1 + inputStr[i], word2);
            search(word1, word2 + inputStr[i]);
            visited[i] = 0;
        }
    }
}

int main() {
    fin >> inputStr;
    string dictWord;
    while (din >> dictWord) {
        if (dictWord == ".") break;
        insertWord(dictWord);
    }
    search("", "");

    fout << maxScore << endl;
    for (set<string>::iterator itr = maxSet.begin();
         itr != maxSet.end(); ++itr) {
        fout << *itr << endl;
    }
    // cout << nodeCount << endl;
    // while (true);

    return 0;
}

