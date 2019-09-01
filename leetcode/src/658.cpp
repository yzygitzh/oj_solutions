class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        sort(arr.begin(), arr.end(), [=] (int a, int b) {
            int deltaA = a < x ? x - a : a - x;
            int deltaB = b < x ? x - b : b - x;
            if (deltaA != deltaB) {
                return deltaA < deltaB;
            } else {
                return a < b;
            }
        });
        vector<int> result(k);
        for (int i = 0; i < k; i++) {
            result[i] = arr[i];
        }
        sort(result.begin(), result.end());
        return result;
    }
};