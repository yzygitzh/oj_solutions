class Solution {
public:
    int mergeStones(vector<int>& stones, int K) {
        int stonesNum = stones.size();
        vector<vector<vector<int>>> minCost(
            stonesNum,
            vector<vector<int>>(
                stonesNum, vector<int>(K + 1, -2)));
        // minCost[i][j][k] = min(minCost[i][m][k - 1] + minCost[m + 1][j][1])
        // minCost[i][j][1] = min(minCost[i][j][K]) + sum(i to j)
        // minCost[i][i][1] = 0
        // -2: not calculated, -1: not valid
        return findMinCost(0, stonesNum - 1, 1, K, stones, minCost);
    }
    
    int findMinCost(int left, int right, int pileNum, int K,
                    vector<int>& stones,
                    vector<vector<vector<int>>>& minCost) {
        int stonesNum = right - left + 1;
        // 5 stones, K = 3 -> 5,3,1
        if (minCost[left][right][pileNum] == -2) {
            if (stonesNum >= pileNum &&
                !((stonesNum - pileNum) % (K - 1))) {
                // there might be valid answer
                if (pileNum == 1) {
                    if (left == right) {
                        // no need to merge
                        minCost[left][right][pileNum] = 0;
                    } else {
                        // last step must be K piles
                        int result = findMinCost(left, right, K, K, stones, minCost);
                        if (result != -1) {
                            for (int i = left; i <= right; i++) {
                                result += stones[i];
                            }
                            minCost[left][right][pileNum] = result;
                        } else {
                            minCost[left][right][pileNum] = -1;
                        }
                    }
                } else {
                    int currMinCost = ~(1 << 31), sum = stones[right];
                    for (int i = right - 1; i >= left; i--) {
                        // pileNum - 1 piles at left, 1 pile at right
                        int result1 = findMinCost(left, i, pileNum - 1, K, stones, minCost);
                        int result2 = findMinCost(i + 1, right, 1, K, stones, minCost);
                        if (result1 != -1 && result2 != -1) {
                            currMinCost = min(currMinCost, result1 + result2);
                        }
                    }
                    if (currMinCost != ~(1 << 31)) {
                        minCost[left][right][pileNum] = currMinCost;
                    } else {
                        minCost[left][right][pileNum] = -1;
                    }
                }
            } else {
                minCost[left][right][pileNum] = -1;
            }
        }
        return minCost[left][right][pileNum];
    }
};