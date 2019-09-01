class Solution {
public:
    const string charMap = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456";
    const int shortUrlLen = 6;
    unsigned long long currId;
    unordered_map<unsigned long long, string> idToUrl;
    unordered_map<char, int> charToIdx;
    
    Solution(): currId(0) {
        for (int i = 0; i < charMap.length(); i++) {
            charToIdx[charMap[i]] = i;
        }
    }
    
    string idToShortUrl(unsigned long long urlId) {
        string result;
        unsigned long long base = charMap.length();
        for (int i = 0; i < shortUrlLen; i++) {
            result += charMap[urlId % base];
            urlId /= base;
        }
        return result;
    }
    
    unsigned long long shortUrlToId(const string& shortUrl) {
        unsigned long long base = charMap.length();
        unsigned long long result = 0;
        for (int i = shortUrlLen - 1; i >= 0; i--) {
            result += charToIdx[shortUrl[i]];
            result *= base;
        }
        return result;
    }
    
    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        string result = idToShortUrl(currId);
        idToUrl[currId] = longUrl;
        currId++;
        return result;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        return idToUrl[shortUrlToId(shortUrl)];
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));