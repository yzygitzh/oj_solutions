class Solution {
public:
    vector<string> units{"One", "Two", "Three", "Four", "Five",
                         "Six", "Seven", "Eight", "Nine"};
    vector<string> tens{"Eleven", "Twelve", "Thirteen",
                        "Fourteen", "Fifteen", "Sixteen", "Seventeen",
                        "Eighteen", "Nineteen"};
    vector<string> xties{"", "Twenty", "Thirty", "Forty", "Fifty",
                         "Sixty", "Seventy", "Eighty", "Ninety"};

    string getPrefix(vector<int> digits) {
        int digitsLen = digits.size();
        string result;
        bool isTens = false;
        for (int i = 0; i < digitsLen; i++) {
            if (!isTens && digits[i] == 0) continue;
            if (digitsLen - i == 3) {
                result += " ";
                result += units[digits[i] - 1];
                result += " Hundred";
            } else if (digitsLen - i == 2) {
                if (digits[i] == 1) {
                    isTens = true;
                } else {
                    result += " ";
                    result += xties[digits[i] - 1];
                }
            } else {
                result += " ";
                if (isTens) {
                    if (digits[i] == 0) result += "Ten";
                    else result += tens[digits[i] - 1];
                } else {
                    result += units[digits[i] - 1];
                }
            }
        }
        return result.substr(1);
    }

    string numberToWords(int num) {
        if (num == 0) return "Zero";
        vector<vector<int>> digits(4);
        for (int i = 3; i >= 0; i--) {
            for (int j = 0; j < 3; j++) {
                digits[i].push_back(num % 10);
                num /= 10;
            }
            while (!digits[i].empty() && *digits[i].rbegin() == 0) {
                digits[i].pop_back();
            }
            reverse(digits[i].begin(), digits[i].end());
        }
        string result;
        // billions
        if (digits[0].size()) {
            result += " ";
            result += getPrefix(digits[0]);
            result += " Billion";
        }
        // millions
        if (digits[1].size()) {
            result += " ";
            result += getPrefix(digits[1]);
            result += " Million";
        }
        // thousands
        if (digits[2].size()) {
            result += " ";
            result += getPrefix(digits[2]);
            result += " Thousand";
        }
        // units
        if (digits[3].size()) {
            result += " ";
            result += getPrefix(digits[3]);
        }
        return result.substr(1);
    }
};