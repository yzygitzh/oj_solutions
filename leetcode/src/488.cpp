class Solution {
public:
    map<pair<string, string>, int> memo;
    
    string eraseBalls(string s) {
        bool changed = true;
        while (changed) {
            changed = false;
            int sLen = s.length();
            for (int i = 0; i < sLen; i++) {
                if (i - 1 >= 0 && i + 1 < sLen &&
                    s[i - 1] == s[i] && s[i] == s[i + 1]) {
                    changed = true;
                    int sameIdx = i + 2;
                    while (sameIdx < sLen && s[i - 1] == s[sameIdx]) sameIdx++;
                    s.erase(i - 1, sameIdx - i + 1);
                    break;
                }
            }
        }
        return s;
    }
    
    int findMinStep(string board, string hand) {
        if (board.length() == 0) return 0;
        sort(hand.begin(), hand.end());
        if (!memo.count(make_pair(board, hand))) {
            int minStep = 10;
            int boardLen = board.length();
            int handLen = hand.length();
            for (int i = 0; i < handLen; i++) {
                if (i > 0 && hand[i - 1] == hand[i]) continue;
                for (int j = 0; j < boardLen; j++) {
                    if (board[j] == hand[i]) {
                        string inserted = board;
                        inserted.insert(j, string() + board[j]);
                        string erased = eraseBalls(inserted);
                        string newHand = hand;
                        newHand.erase(i, 1);
                        int currMinStep = findMinStep(erased, newHand);
                        if (currMinStep != -1) {
                            minStep = min(minStep, currMinStep + 1);
                        }
                    }
                }
            }
            memo[make_pair(board, hand)] = minStep == 10 ? -1 : minStep;
        }
        return memo[make_pair(board, hand)];
    }
};