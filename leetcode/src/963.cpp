class Solution {
public:
    double crossProd(double x1, double y1, double x2, double y2) {
        return x1 * y2 - x2 * y1;
    }
    
    double dotProd(double x1, double y1, double x2, double y2) {
        return x1 * x2 + y1 * y2;
    }
    
    double getAbs(double x) {
        return x < 0.0 ? -x : x;
    }
    
    double minAreaFreeRect(vector<vector<int>>& points) {
        int pointsLen = points.size();
        if (pointsLen < 4) return 0.0;
        
        set<vector<int> > pointsSet;
        for (int i = 0; i < pointsLen; i++) {
            pointsSet.insert(points[i]);
        }
        
        double minArea = 2000000000;
        for (int i = 0; i < pointsLen; i++) {
            for (int j = i + 1; j < pointsLen; j++) {
                for (int k = 0; k < pointsLen; k++) {
                    if (i == k || j == k) continue;
                    
                    double x1 = points[i][0], y1 = points[i][1];
                    double x2 = points[j][0], y2 = points[j][1];
                    double x3 = points[k][0], y3 = points[k][1];
                    
                    // get the 4-th point if 90 degree
                    if (getAbs(dotProd(x2 - x1, y2 - y1, x3 - x1, y3 - y1)) < 1e-6) {
                        int iX4 = (int)(x3 + x2 - x1);
                        int iY4 = (int)(y3 + y2 - y1);
                        if (pointsSet.count(vector<int>{iX4, iY4})) {
                            double area = getAbs(crossProd(x2 - x1, y2 - y1, x3 - x1, y3 - y1));
                            if (area < minArea) minArea = area;
                        }
                    }
                }
            }
        }
        
        if (getAbs(minArea - 2000000000) < 1e-6) minArea = 0.0;
        
        return minArea;
    }
};