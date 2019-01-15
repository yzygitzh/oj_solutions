class Solution {
public:
    static bool cmpPoints(const vector<int>& a, const vector<int>& b) {
        double disA = (double)a[0] * (double)a[0] + (double)a[1] * (double)a[1];
        double disB = (double)b[0] * (double)b[0] + (double)b[1] * (double)b[1];
        return disA < disB;
    }
    
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        sort(points.begin(), points.end(), cmpPoints);
        return vector<vector<int>>(points.begin(), points.begin() + K);
    }
};