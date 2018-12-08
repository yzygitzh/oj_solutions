class Solution {
public:
    int getMax(int a, int b) {
        return a > b ? a : b;
    }
    
    int getMin(int a, int b) {
        return a < b ? a : b;
    }
    
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        // if two rectangles doesn't intersect
        if (C < E || G < A || D < F || H < B) {
            return (C - A) * (D - B) + (G - E) * (H - F);
        }
        // cut ABCD
        int area = (G - E) * (H - F);
        int newB = B, newD = D;
        // up
        if (H < D) {
            area += (C - A) * (D - getMax(B, H));
            newD = getMax(B, H);
        }
        // down
        if (B < F) {
            area += (C - A) * (getMin(D, F) - B);
            newB = getMin(D, F);
        }
        if (newD > newB) {
            // left
            if (A < E) {
                area += (newD - newB) * (E - A);
            }
            // right
            if (G < C) {
                area += (newD - newB) * (C - G);
            }
        }
        return area;
    }
};