class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> charToNum;
        charToNum['I'] = 1;
        charToNum['V'] = 5;
        charToNum['X'] = 10;
        charToNum['L'] = 50;
        charToNum['C'] = 100;
        charToNum['D'] = 500;
        charToNum['M'] = 1000;
        int maxAccessed = 0, result = 0;
        for (auto itr = s.rbegin(); itr != s.rend(); ++itr) {
            if (charToNum[*itr] >= maxAccessed) {
                result += charToNum[*itr];
                maxAccessed = charToNum[*itr];
            } else {
                result -= charToNum[*itr];
            }
        }
        return result;
    }
};