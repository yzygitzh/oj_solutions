class Solution {
public:
    vector<long long> numStack;
    vector<char> opStack;
    
    void calcOp() {
        char op = opStack.back();
        opStack.pop_back();
        if (op == '#') {
            return;
        } else if (op == '=') {
            numStack.back() = -numStack.back();
            return;
        }
        long long num2 = numStack.back();
        numStack.pop_back();
        long long num1 = numStack.back();
        numStack.pop_back();
        if (op == '+') {
            numStack.push_back(num1 + num2);
        } else if (op == '-') {
            numStack.push_back(num1 - num2);
        } else if (op == '*') {
            numStack.push_back(num1 * num2);
        } else if (op == '/') {
            numStack.push_back(num1 / num2);
        } else {
            numStack.push_back(0);
        }
    }
    
    int calculate(string s) {
        bool lastIsDigit = false;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == ' ') {
                continue;
            } else if ('0' <= s[i] && s[i] <= '9') {
                long long num = 0;
                while (i < s.length() && '0' <= s[i] && s[i] <= '9') {
                    num *= 10;
                    num += s[i] - '0';
                    i++;
                }
                i--;
                numStack.push_back(num);
                lastIsDigit = true;
            } else if (s[i] == '(') {
                opStack.push_back('(');
                lastIsDigit = false;
            } else if (s[i] == ')') {
                while (opStack.back() != '(') {
                    calcOp();
                }
                opStack.pop_back();
                lastIsDigit = true;
            } else if (s[i] == '+' || s[i] == '-') {
                if (!lastIsDigit) {
                    if (s[i] == '+') {
                        opStack.push_back('#');
                    } else {
                        opStack.push_back('=');
                    }
                } else {
                    while (!opStack.empty() && opStack.back() != '(') {
                        calcOp();
                    }
                    opStack.push_back(s[i]);
                }
                lastIsDigit = false;
            } else if (s[i] == '*' || s[i] == '/') {
                while (!opStack.empty() &&
                       (opStack.back() == '*' || opStack.back() == '/')) {
                    calcOp();
                }
                opStack.push_back(s[i]);
                lastIsDigit = false;
            }
        }
        while (!opStack.empty()) {
            calcOp();
        }
        return int(numStack[0]);
    }
};