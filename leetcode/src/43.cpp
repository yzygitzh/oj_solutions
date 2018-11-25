class Solution {
public:
    string add(string num1, string num2) {
        if (num1 == "0") return num2;
        if (num2 == "0") return num1;

        int num1Len = num1.length();
        int num2Len = num2.length();
        int maxLen = num1Len > num2Len ? num1Len : num2Len;
        string answer;
        
        int idx = 0, carry = 0;
        while (idx < maxLen) {
            int sum = carry;
            if (idx < num1Len) sum += num1[idx] - '0';
            if (idx < num2Len) sum += num2[idx] - '0';
            carry = sum / 10;
            sum = sum - carry * 10;
            answer.push_back('0' + sum);
            idx++;
        }
        if (carry > 0) {
            answer.push_back('0' + carry);
        }
        
        return answer;
    }
    
    string multiDigit(string num, char digit) {
        if (num == "0" || digit == '0') return "0";
        
        int numLen = num.length();
        string answer;
        
        int idx = 0, carry = 0;
        while (idx < numLen) {
            int multi = carry;
            if (idx < numLen) multi += (num[idx] - '0') * (digit - '0');
            carry = multi / 10;
            multi = multi - carry * 10;
            answer.push_back('0' + multi);
            idx++;
        }
        if (carry > 0) {
            answer.push_back('0' + carry);
        }
        
        return answer;
    }
    
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";
        
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        
        int num1Len = num1.length();
        int num2Len = num2.length();
        
        string answer = "0";
        for (int i = 0; i < num2Len; i++) {
            string newNum1;
            for (int j = 0; j < i; j++) newNum1 += '0';
            newNum1 += num1;
            string multi = multiDigit(newNum1, num2[i]);
            answer = add(answer, multi);
        }
        
        reverse(answer.begin(), answer.end());
        return answer;
    }
};