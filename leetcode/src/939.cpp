class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        int minArea = 2000000000;
        int pointNum = points.size();
        sort(points.begin(), points.end());
        
        set<vector<int>> pointSet;
        pointSet.insert(points.begin(), points.end());
        
        for (int i = 0; i < pointNum; i++) {
            vector<int> p1 = points[i];
            for (int j = 0; j < i; j++) {
                vector<int> p4 = points[j];
                
                int area = (p4[0] - p1[0]) * (p4[1] - p1[1]);
                if (area > minArea) continue;
                
                vector<int> p2 = p1;
                p2[1] = p4[1];
                vector<int> p3 = p1;
                p3[0] = p4[0];
                
                if (pointSet.count(p2) && pointSet.count(p3)) {
                    if (area > 0 && area < minArea) minArea = area;
                }
            }
        }
        if (minArea == 2000000000) return 0;
        else return minArea;
    }
};