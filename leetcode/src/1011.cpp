class Solution {
public:
    bool validate(vector<int>& weights, int D, int vol) {
        int days = 1, currWeight = 0;
        for (auto w : weights) {
            if (w > vol) {
                return false;
            }
            if (currWeight + w <= vol) {
                currWeight += w;
            } else {
                days++;
                currWeight = w;
            }
            if (days > D) {
                return false;
            }
        }
        return true;
    }

    int shipWithinDays(vector<int>& weights, int D) {
        int left = 1, right = 50000 * 500;
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            if (validate(weights, D, mid)) {
                right = mid;
            } else {
                left = mid;
            }
        }
        if (validate(weights, D, left)) {
            return left;
        } else {
            return right;
        }
    }
};