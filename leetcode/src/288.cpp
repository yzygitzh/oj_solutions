class ValidWordAbbr {
public:
    unordered_set<string> wordSet;
    unordered_map<string, int> abbrCnt;
    
    string wordToAbbr(string s) {
        if (s.length() <= 2) return s;
        return s.substr(0, 1) + to_string(s.length() - 2) +
               s.substr(s.length() - 1, 1);
    }
    
    ValidWordAbbr(vector<string> dictionary) {
        for (auto itr = dictionary.begin(); itr != dictionary.end(); ++itr) {
            if (wordSet.find(*itr) == wordSet.end()) {
                wordSet.insert(*itr);
                abbrCnt[wordToAbbr(*itr)] += 1;
            }
        }
    }
    
    bool isUnique(string word) {
        if (wordSet.find(word) == wordSet.end()) {
            return abbrCnt[wordToAbbr(word)] == 0;
        } else {
            return abbrCnt[wordToAbbr(word)] == 1;
        }
    }
};

/**
 * Your ValidWordAbbr object will be instantiated and called as such:
 * ValidWordAbbr obj = new ValidWordAbbr(dictionary);
 * bool param_1 = obj.isUnique(word);
 */