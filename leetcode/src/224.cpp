class Solution {
public:
    vector<int> operands;
    vector<char> operators;
    
    void parseExp(string &s) {
        int sLen = s.length();
        for (int i = 0; i < sLen; i++) {
            if (s[i] == ' ') {
                continue;
            } else if ('0' <= s[i] && s[i] <= '9') {
                int operand = 0;
                while (i < sLen && '0' <= s[i] && s[i] <= '9') {
                    operand *= 10;
                    operand += s[i] - '0';
                    i++;
                }
                operands.push_back(operand);
                i--;
            } else {
                operators.push_back(s[i]);
            }
        }
    }
    
    int evalExp() {
        vector<int> operandStack{operands[0]};
        vector<char> operatorStack;
        int operandIdx = 1, operatorIdx = 0;
        int operatorLen = operators.size();
        
        while (operatorIdx < operatorLen) {
            if (operators[operatorIdx] == '(') {
                operatorStack.push_back(operators[operatorIdx]);
            } else if (operators[operatorIdx] == ')') {
                int result = 0;
                while (*operatorStack.rbegin() != '(') {
                    if (*operatorStack.rbegin() == '+') {
                        result += *operandStack.rbegin();
                    } else {
                        result -= *operandStack.rbegin();
                    }
                    operandStack.pop_back();
                    operatorStack.pop_back();
                }
                operatorStack.pop_back();
                result += *operandStack.rbegin();
                operandStack.pop_back();
                operandStack.push_back(result);
            } else {
                operatorStack.push_back(operators[operatorIdx]);
                operandStack.push_back(operands[operandIdx++]);
            }
            operatorIdx++;
        }
        
        return operandStack[0];
    }
    
    int calculate(string s) {
        string wrappedS = "(";
        wrappedS += s;
        wrappedS += ")";
        parseExp(wrappedS);
        return evalExp();
    }
};