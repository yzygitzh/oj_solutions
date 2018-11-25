class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int P) {
        sort(tokens.begin(), tokens.end());
        int tokensLen = tokens.size();
        if (tokensLen == 0) return 0;
        int left = 0, right = tokensLen - 1;
        int maxPoints = 0, currPoints = 0;
        while (left <= right) {
            if (tokens[left] <= P) {
                currPoints++;
                if (currPoints > maxPoints) maxPoints = currPoints;
                P -= tokens[left];
                left++;
            } else if (currPoints > 0) {
                currPoints--;
                P += tokens[right];
                right--;
            } else {
                return maxPoints;
            }
        }
        return maxPoints;
    }
};