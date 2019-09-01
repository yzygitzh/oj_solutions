class Solution {
public:
    double getDis(vector<int>& p1, vector<int>& p2) {
        return sqrt(pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2));
    }
    
    int crossProd(vector<int>& p1, vector<int>& p2, vector<int>& p3) {
        vector<int> v1{p1[0] - p2[0], p1[1] - p2[1]};
        vector<int> v2{p2[0] - p3[0], p2[1] - p3[1]};
        return v1[0] * v2[1] - v1[1] * v2[0];
    }
    
    bool isSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        return abs(getDis(p1, p2)) > 1e-6 &&
               abs(getDis(p1, p2) - getDis(p2, p3)) < 1e-6 &&
               abs(getDis(p2, p3) - getDis(p3, p4)) < 1e-6 &&
               abs(getDis(p3, p4) - getDis(p4, p1)) < 1e-6 &&
               abs(getDis(p4, p1) - getDis(p1, p2)) < 1e-6 &&
               abs(crossProd(p1, p2, p3) - getDis(p1, p2) * getDis(p2, p3)) < 1e-6 &&
               abs(crossProd(p2, p3, p4) - getDis(p2, p3) * getDis(p3, p4)) < 1e-6 &&
               abs(crossProd(p3, p4, p1) - getDis(p3, p4) * getDis(p4, p1)) < 1e-6 &&
               abs(crossProd(p4, p1, p2) - getDis(p4, p1) * getDis(p1, p2)) < 1e-6;
    }
    
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        return isSquare(p1, p2, p3, p4) ||
               isSquare(p1, p2, p4, p3) ||
               isSquare(p1, p3, p2, p4) ||
               isSquare(p1, p3, p4, p2) ||
               isSquare(p1, p4, p2, p3) ||
               isSquare(p1, p4, p3, p2);
    }
};