class Solution {
public:
    int minX, minY, maxX, maxY;
    
    int minArea(vector<vector<char>>& image, int x, int y) {
        int m = image.size();
        if (m == 0) return 0;
        int n = image[0].size();
        if (n == 0) return 0;
        
        minX = maxX = x;
        minY = maxY = y;
        dfs(image, x, y);
        return (maxX - minX + 1) * (maxY - minY + 1);
    }
    
    void dfs(vector<vector<char>>& image, int x, int y) {
        image[x][y] = '2';
        minX = min(minX, x);
        maxX = max(maxX, x);
        minY = min(minY, y);
        maxY = max(maxY, y);
        int m = image.size();
        int n = image[0].size();
        if (x - 1 >= 0 && image[x - 1][y] == '1') dfs(image, x - 1, y);
        if (x + 1 < m && image[x + 1][y] == '1') dfs(image, x + 1, y);
        if (y - 1 >= 0 && image[x][y - 1] == '1') dfs(image, x, y - 1);
        if (y + 1 < n && image[x][y + 1] == '1') dfs(image, x, y + 1);
    }
};