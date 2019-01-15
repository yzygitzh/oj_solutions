class Codec {
public:

    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        string encoded;
        for (auto itr = strs.begin(); itr != strs.end(); ++itr) {
            for (auto itr2 = itr->begin(); itr2 != itr->end(); ++itr2) {
                encoded += '\\';
                encoded += *itr2;
            }
            encoded += '#';
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        vector<string> decoded;
        int sLen = s.length(), sIdx = 0;
        while (sIdx < sLen) {
            string tmpStr;
            while (s[sIdx] != '#') {
                tmpStr += s[sIdx + 1];
                sIdx += 2;
            }
            decoded.push_back(tmpStr);
            sIdx++;
        }
        return decoded;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));