/*
 * LeetCode 336 Palindrome Pairs
 * Trie
 */

class Solution {
public:
  class TrieNode {
  public:
    TrieNode *next[26];
    int idx;
    TrieNode () {
      for (int i = 0; i < 26; i++) next[i] = nullptr;
      idx = -1;
    }
  };

  void insertWord(string word, int idx, TrieNode* root) {
    for (auto c : word) {
      if (root->next[c - 'a'] == nullptr) {
        root->next[c - 'a'] = new TrieNode();
      }
      root = root->next[c - 'a'];
    }
    root->idx = idx;
  }

  TrieNode *normTrie, *revTrie;

  bool isPalindrome(string s) {
    int left = 0, right = s.length() - 1;
    while (left < right) {
      if (s[left] != s[right]) return false;
      left++, right--;
    }
    return true;
  }

  vector<vector<int>> palindromePairs(vector<string>& words) {
    int wordNum = words.size();
    normTrie = new TrieNode(),revTrie = new TrieNode();
    for (int i = 0; i < wordNum; i++) {
      insertWord(words[i], i, normTrie);
      string revWord = words[i];
      reverse(revWord.begin(), revWord.end());
      insertWord(revWord, i, revTrie);
    }
    set<vector<int>> resultSet;
    vector<TrieNode*> roots{normTrie, revTrie};
    // find reversed word in trie, and reverse them
    for (vector<TrieNode*>::iterator itr = roots.begin();
         itr != roots.end(); ++itr) {
      for (int i = 0; i < wordNum; i++) {
        string word = words[i];
        if (*itr == normTrie) reverse(word.begin(), word.end());
        TrieNode *p = *itr;
        int idx = 0, wordLen = word.length();
        if (isPalindrome(word) && p->idx >= 0 && p->idx != i) {
          resultSet.insert(vector<int>{i, p->idx});
          resultSet.insert(vector<int>{p->idx, i});
        }
        while (idx < wordLen) {
          p = p->next[word[idx] - 'a'];
          idx++;
          if (p == nullptr) break;
          if (p->idx >= 0 && p->idx != i && isPalindrome(word.substr(idx))) {
            if (*itr == normTrie) resultSet.insert(vector<int>{p->idx, i});
            else resultSet.insert(vector<int>{i, p->idx});
          }
        }
      }
    }
    return vector<vector<int>>(resultSet.begin(), resultSet.end());
  }
};


