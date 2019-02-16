class Solution {
public:
    double largestTriangleArea(vector<vector<int>>& points) {
        int pointsNum = points.size();
        double maxArea = 0;
        for (int i = 0; i < pointsNum; i++) {
            for (int j = i + 1; j < pointsNum; j++) {
                for (int k = j + 1; k < pointsNum; k++) {
                    double ab = sqrt(pow(points[i][0] - points[j][0], 2) +
                                     pow(points[i][1] - points[j][1], 2));
                    double bc = sqrt(pow(points[j][0] - points[k][0], 2) +
                                     pow(points[j][1] - points[k][1], 2));
                    double ac = sqrt(pow(points[i][0] - points[k][0], 2) +
                                     pow(points[i][1] - points[k][1], 2));
                    double p = (ab + bc + ac) / 2;
                    maxArea = max(maxArea, sqrt(p * (p - ab) * (p - bc) * (p - ac)));
                }
            }
        }
        return maxArea;
    }
};