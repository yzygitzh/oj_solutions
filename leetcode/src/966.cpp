class Solution {
public:
    unordered_map<string, vector<int> > caseLookup;
    unordered_map<string, vector<int> > vowelLookup;
    unordered_set<string> directLookup;
    
    string toCaseKey(string word) {
        string lowerWord;
        int wordLen = word.length();
        for (int i = 0; i < wordLen; i++) {
            char currChar = word[i];
            if ('A' <= currChar && currChar <= 'Z') {
                currChar += 'a' - 'A';
            }
            lowerWord += currChar;
        }
        return lowerWord;
    }
    
    string toVowelKey(string word) {
        word = toCaseKey(word);
        string vowelWord;
        int wordLen = word.length();
        for (int i = 0; i < wordLen; i++) {
            char currChar = word[i];
            if (currChar == 'a' || currChar == 'e' || currChar == 'i' ||
                currChar == 'o' || currChar == 'u') {
                vowelWord += '*';
            } else {
                vowelWord += currChar;
            }
        }
        return vowelWord;
    }
    
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        int wordListLen = wordlist.size();
        for (int i = 0; i < wordListLen; i++) {
            caseLookup[toCaseKey(wordlist[i])].push_back(i);
            vowelLookup[toVowelKey(wordlist[i])].push_back(i);
            directLookup.insert(wordlist[i]);
        }
        
        vector<string> result;
        int queriesLen = queries.size();
        for (int i = 0; i < queriesLen; i++) {
            if (directLookup.find(queries[i]) != directLookup.end()) {
                result.push_back(queries[i]);
            } else if (caseLookup.find(toCaseKey(queries[i])) != caseLookup.end()) {
                result.push_back(wordlist[caseLookup[toCaseKey(queries[i])][0]]);
            } else if (vowelLookup.find(toVowelKey(queries[i])) != vowelLookup.end()) {
                result.push_back(wordlist[vowelLookup[toVowelKey(queries[i])][0]]);
            } else {
                result.push_back("");
            }
        }
        return result;
    }
};