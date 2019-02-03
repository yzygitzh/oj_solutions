class Solution {
public:
    int crossProd(vector<int> a, vector<int> b) {
        return a[0] * b[1] - a[1] * b[0];
    }
    
    int getSign(int x) {
        if (x < 0) return -1;
        else if (x > 0) return 1;
        else return 0;
    }
    
    bool isConvex(vector<vector<int>>& points) {
        int pointsLen = points.size();
        if (points.size() < 3) return false;
        set<int> crossSignSet;
        for (int i = 0; i < pointsLen; i++) {
            vector<int> p1 = points[i],
                        p2 = points[(i + 1) % pointsLen],
                        p3 = points[(i + 2) % pointsLen];
            int crossSign = getSign(crossProd(vector<int>{p2[0] - p1[0], p2[1] - p1[1]},
                                              vector<int>{p3[0] - p2[0], p3[1] - p2[1]}));
            crossSignSet.insert(crossSign);
        }
        return !(crossSignSet.count(1) && crossSignSet.count(-1));
    }
};