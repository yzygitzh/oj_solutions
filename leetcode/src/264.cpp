class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> numbers;
        numbers.push_back(1);
        int idx2 = 0, idx3 = 0, idx5 = 0;
        while (--n) {
            int p2 = ~(1<<31), p3 = ~(1<<31), p5 = ~(1<<31);
            while (numbers[idx2] <= (~(1<<31))/2 &&
                   numbers[idx2] * 2 <= *numbers.rbegin()) {
                idx2++;
            }
            if (numbers[idx2] <= (~(1<<31))/2) p2 = numbers[idx2] * 2;
            while (numbers[idx3] <= (~(1<<31))/3 &&
                   numbers[idx3] * 3 <= *numbers.rbegin()) {
                idx3++;
            }
            if (numbers[idx3] <= (~(1<<31))/3) p3 = numbers[idx3] * 3;
            while (numbers[idx5] <= (~(1<<31))/5 &&
                   numbers[idx5] * 5 <= *numbers.rbegin()) {
                idx5++;
            }
            if (numbers[idx5] <= (~(1<<31))/5) p5 = numbers[idx5] * 5;

            if (p2 <= p3 && p2 <= p5) {
                numbers.push_back(p2);
                idx2++;
                continue;
            }
            if (p3 <= p2 && p3 <= p5) {
                numbers.push_back(p3);
                idx3++;
                continue;
            }
            if (p5 <= p2 && p5 <= p3) {
                numbers.push_back(p5);
                idx5++;
                continue;
            }
        }
        
        return *numbers.rbegin();
    }
};