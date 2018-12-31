class Solution {
public:
    int getMax(int a, int b) {
        return a > b ? a : b;
    }
    
    int candy(vector<int>& ratings) {
        int ratingsLen = ratings.size();
        if (ratingsLen <= 1) return ratingsLen;

        priority_queue<pair<int, int>, vector<pair<int, int> >,
                       greater<pair<int, int> > > ratingHeap;
        for (int i = 0; i < ratingsLen; i++) {
            ratingHeap.push(make_pair(ratings[i], i));
        }
        
        vector<int> candies(ratingsLen, 0);
        vector<int> given(ratingsLen, 0);
        
        while (ratingHeap.size() > 0) {
            pair<int, int> top = ratingHeap.top();
            ratingHeap.pop();
            if (given[top.second]) continue;
            given[top.second] = 1;
            candies[top.second] = 1;
            // expand to left
            int leftOffset = 1;
            while (top.second - leftOffset >= 0 &&
                   ratings[top.second - leftOffset] >
                   ratings[top.second - leftOffset + 1]) {
                candies[top.second - leftOffset] = getMax(
                    candies[top.second - leftOffset],
                    candies[top.second - leftOffset + 1] + 1
                );
                given[top.second - leftOffset] = 1;
                leftOffset++;
            }
            // expand to right
            int rightOffset = 1;
            while (top.second + rightOffset < ratingsLen &&
                   ratings[top.second + rightOffset] >
                   ratings[top.second + rightOffset - 1]) {
                candies[top.second + rightOffset] = getMax(
                    candies[top.second + rightOffset],
                    candies[top.second + rightOffset - 1] + 1
                );
                given[top.second + rightOffset] = 1;
                rightOffset++;
            }
        }
        
        int candySum = 0;
        for (int i = 0; i < ratingsLen; i++) candySum += candies[i];
        return candySum;
    }
};