class Solution {
public:
    void matMul22(long long a[], long long b[], long long c[]) {
        c[0] = b[0] * a[0] + b[2] * a[1];
        c[1] = b[1] * a[0] + b[3] * a[1];
        c[2] = b[0] * a[2] + b[2] * a[3];
        c[3] = b[1] * a[2] + b[3] * a[3];
    }
    
    int climbStairs(int n) {
        // a(n) = a(n - 1) + a(n - 2)
        // 1 1 2 3 ...
        // use fast power
        long long mat[4] = {0};
        mat[1] = mat[2] = mat[3] = 1;
        long long finalMat[4] = {0};
        finalMat[0] = finalMat[3] = 1;
        while (n) {
            long long newMat[4];
            if (n & 1) {
                matMul22(mat, finalMat, newMat);
                memcpy(finalMat, newMat, sizeof(finalMat));
            }
            matMul22(mat, mat, newMat);
            memcpy(mat, newMat, sizeof(mat));
            n >>= 1;
        }
        return int(finalMat[0] + finalMat[1]);
    }
};