class Solution {
public:    
    int evalRPN(vector<string>& tokens) {
        vector<int> stack;
        int tokensLen = tokens.size();
        for (int i = 0; i < tokensLen; i++) {
            int stackLen = stack.size();
            if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/") {
                int n1 = stack[stackLen - 1];
                int n2 = stack[stackLen - 2];
                stack.pop_back();
                stack.pop_back();
                if (tokens[i] == "+") stack.push_back(n2 + n1);
                if (tokens[i] == "-") stack.push_back(n2 - n1);
                if (tokens[i] == "*") stack.push_back(n2 * n1);
                if (tokens[i] == "/") stack.push_back(n2 / n1);
            } else {
                stack.push_back(stoi(tokens[i]));
            } 
        }
        return stack[0];
    }
};