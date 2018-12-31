class Solution {
public:
    int calculate(string s) {
        vector<int> operands;
        vector<char> operators;
        
        int sLen = s.length();
        for (int i = 0; i < sLen; i++) {
            if (s[i] == ' ') {
                continue;
            } else if ('0' <= s[i] && s[i] <= '9') {
                int num = 0;
                while ('0' <= s[i] && s[i] <= '9') {
                    num *= 10;
                    num += s[i] - '0';
                    i++;
                }
                operands.push_back(num);
                i--;
                
                // try calc * and /
                if (operands.size() >= 2) {
                    if (*operators.rbegin() == '*') {
                        operators.pop_back();
                        int num2 = *operands.rbegin();
                        operands.pop_back();
                        int num1 = *operands.rbegin();
                        operands.pop_back();
                        operands.push_back(num1 * num2);
                    } else if (*operators.rbegin() == '/') {
                        operators.pop_back();
                        int num2 = *operands.rbegin();
                        operands.pop_back();
                        int num1 = *operands.rbegin();
                        operands.pop_back();
                        operands.push_back(num1 / num2);
                    }
                }
            } else {
                operators.push_back(s[i]);
            }
        }
        
        int operatorsLen = operators.size();
        int result = operands[0];
        for (int i = 0; i < operatorsLen; i++) {
            if (operators[i] == '+') result += operands[i + 1];
            else result -= operands[i + 1];
        }
        return result;
    }
};