class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        vector<int> result;
        int inputLen = input.length();
        if (inputLen == 0) return result;
        
        // first tokenize input
        vector<int> numbers;
        vector<char> operators;

        int idx = 0, currNum = 0;
        while (idx < inputLen) {
            if ('0' <= input[idx] && '9' >= input[idx]) {
                currNum *= 10;
                currNum += input[idx++] - '0';
            } else {
                numbers.push_back(currNum);
                currNum = 0;
                operators.push_back(input[idx++]);
            }
        }
        numbers.push_back(currNum);
        int numbersLen = numbers.size();
     
        vector<vector<vector<int> > >
            memo(numbersLen,
                 vector<vector<int> >(numbersLen, vector<int>()));
        calc(numbers, operators, 0, numbersLen - 1, memo);
        result = memo[0][numbersLen - 1];
        sort(result.begin(), result.end());
        return result;
    }
    vector<int> calc(vector<int>& numbers, vector<char>& operators,
                     int left, int right,
                     vector<vector<vector<int> > >& memo) {
        if (memo[left][right].size() > 0) return memo[left][right];
        if (left == right) {
            memo[left][right].push_back(numbers[left]);
            return memo[left][right];
        }
        vector<int> result;
        for (int i = left; i < right; i++) {
            vector<int> set1 = calc(numbers, operators, left, i, memo);
            vector<int> set2 = calc(numbers, operators, i + 1, right, memo);
            for (vector<int>::iterator itr1 = set1.begin();
                 itr1 != set1.end(); ++itr1) {
                for (vector<int>::iterator itr2 = set2.begin();
                     itr2 != set2.end(); ++itr2) {
                    if (operators[i] == '+') {
                        result.push_back((*itr1) + (*itr2));
                    } else if (operators[i] == '-') {
                        result.push_back((*itr1) - (*itr2));
                    } else if (operators[i] == '*') {
                        result.push_back((*itr1) * (*itr2));
                    }
                }
            }
        }
        memo[left][right] = result;
        return memo[left][right];
    }
};