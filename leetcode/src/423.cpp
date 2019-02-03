class Solution {
public:
    string originalDigits(string s) {
        vector<pair<char, int>> features;
        vector<string> words;
        
        features.push_back(make_pair('x', 6));
        words.push_back("six");
        features.push_back(make_pair('z', 0));
        words.push_back("zero");
        features.push_back(make_pair('w', 2));
        words.push_back("two");
        features.push_back(make_pair('u', 4));
        words.push_back("four");
        features.push_back(make_pair('o', 1));
        words.push_back("one");
        features.push_back(make_pair('g', 8));
        words.push_back("eight");
        features.push_back(make_pair('t', 3));
        words.push_back("three");
        features.push_back(make_pair('f', 5));
        words.push_back("five");
        features.push_back(make_pair('s', 7));
        words.push_back("seven");
        features.push_back(make_pair('e', 9));
        words.push_back("nine");
        
        unordered_map<char, int> charCnt;
        for (auto itr = s.begin(); itr != s.end(); ++itr) {
            charCnt[*itr]++;
        }
        map<int, int> digitCnt;
        for (int i = 0; i < 10; i++) {
            while (charCnt[features[i].first] > 0) {
                for (auto itr = words[i].begin();
                     itr != words[i].end(); ++itr) {
                    charCnt[*itr]--;
                }
                digitCnt[features[i].second]++;
            }
        }
        
        string result;
        for (auto itr = digitCnt.begin();
             itr != digitCnt.end(); ++itr) {
            for (int i = 0; i < itr->second; i++) {
                result += to_string(itr->first);
            }
        }
        return result;
    }
};