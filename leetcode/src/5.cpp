class Solution {
public:
    vector<int> posHash[2], negHash[2], modPow[2];
    int primes[2] = {12289, 13331};
    string answer = "";

    bool findPalin(int len, string &s) {
        if (len <= 1) {
            return true;
        }        
        int halfLen = len / 2;
        int pivotLen = len % 2;
        for (int i = halfLen - 1; i + pivotLen + halfLen < posHash[0].size() - 1; i++) {
            bool valid = true;
            for (int j = 0; j < 2; j++) {
                int leftHash = (((posHash[j][i + 1] - 
                                  posHash[j][i - halfLen + 1] * 
                                  modPow[j][halfLen]) % primes[j]) + primes[j]) % primes[j];
                int rightHash = (((negHash[j][i + pivotLen + 1] - 
                                   negHash[j][i + pivotLen + halfLen + 1] * 
                                   modPow[j][halfLen]) % primes[j]) + primes[j]) % primes[j];
                if (leftHash != rightHash) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                if (len > answer.length()) {
                    answer = s.substr(i - halfLen + 1, len);
                }
                return true;
            }
        }
        return false;
    }

    string longestPalindrome(string s) {
        if (s.length() == 0) {
            return answer;
        }
        answer = s.substr(0, 1);
        
        for (int j = 0; j < 2; j++) {
            posHash[j].resize(s.length() + 1, 0);
            posHash[j][0] = 0;
            for (int i = 1; i <= s.length(); i++) {
                posHash[j][i] = (posHash[j][i - 1] * 256 + int(s[i - 1])) % primes[j];
            }

            negHash[j].resize(s.length() + 1, 0);
            negHash[j][s.length()] = 0;
            for (int i = s.length() - 1; i >= 0; i--) {
                negHash[j][i] = (negHash[j][i + 1] * 256 + int(s[i])) % primes[j];
            }

            modPow[j].resize(s.length() + 1, 0);
            modPow[j][0] = 1;
            for (int i = 1; i <= s.length(); i++) {
                modPow[j][i] = (modPow[j][i - 1] * 256) % primes[j];
            }
        }

        int maxLen = 1;
        // try odd palin
        int left = 0, right = (s.length() - 1) / 2;
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            if (findPalin(2 * mid + 1, s)) {
                left = mid;
            } else {
                right = mid;
            }
        }
        if (findPalin(2 * right + 1, s)) {
            maxLen = max(maxLen, 2 * right + 1);
        } else if (findPalin(2 * left + 1, s)) {
            maxLen = max(maxLen, 2 * left + 1);
        }

        // try even palin
        left = 1, right = s.length() / 2;
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            if (findPalin(2 * mid, s)) {
                left = mid;
            } else {
                right = mid;
            }
        }
        if (findPalin(2 * right, s)) {
            maxLen = max(maxLen, 2 * right);
        } else if (findPalin(2 * left, s)) {
            maxLen = max(maxLen, 2 * left);
        }

        return answer;
    }
};