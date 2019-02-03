class Solution {
public:
    double radius, x_center, y_center;
    
    Solution(double _radius, double _x_center, double _y_center) 
        : radius(_radius), x_center(_x_center), y_center(_y_center) {}
    
    vector<double> randPoint() {
        double x = ((double)rand() / RAND_MAX - 0.5) * radius * 2;
        double y = ((double)rand() / RAND_MAX - 0.5) * radius * 2;
        if (x * x + y * y <= radius * radius) {
            return vector<double>{x + x_center, y + y_center};
        } else {
            return randPoint();
        }
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(radius, x_center, y_center);
 * vector<double> param_1 = obj.randPoint();
 */