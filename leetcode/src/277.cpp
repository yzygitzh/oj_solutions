// Forward declaration of the knows API.
bool knows(int a, int b);

class Solution {
public:
    int findCelebrity(int n) {
        if (n <= 0) return -1;
        if (n == 1) return 0;

        set<int> candidates;
        for (int i = 0; i < n; i++) candidates.insert(i);
        while (candidates.size() > 1) {
            int c1 = *candidates.begin();
            int c2 = *candidates.rbegin();
            if (knows(c1, c2)) candidates.erase(c1);
            else candidates.erase(c2);
        }
        int finalC = *candidates.begin();
        for (int i = 0; i < n; i++) {
            if (i == finalC) continue;
            if (knows(finalC, i) || !knows(i, finalC)) return -1;
        }
        return finalC;
    }
};