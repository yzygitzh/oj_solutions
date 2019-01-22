class Solution {
public:
    int candy(vector<int>& ratings) {
        // find all peaks
        int ratingsLen = ratings.size();
        int candySum = 0;
        
        for (int i = 0; i < ratingsLen; i++) {
            // invariant: need to find a peak
            int upLen = 0, downLen = 0;
            
            if (i > 0 && ratings[i] > ratings[i - 1]) {
                candySum -= 1;
                upLen++;
            }

            // find going up
            while (i + 1 < ratingsLen &&
                   ratings[i] < ratings[i + 1]) {
                upLen++;
                i++;
            }
            
            // find going down
            while (i + 1 < ratingsLen &&
                   ratings[i] > ratings[i + 1]) {
                downLen++;
                i++;
            }
            
            candySum += (upLen + 1) * upLen / 2 + (downLen + 1) * downLen / 2;
            candySum += max(upLen + 1, downLen + 1);
        }
        
        return candySum;
    }
};