class Solution {
public:
    class TrieNode {
    public:
        TrieNode *next[2];
        TrieNode () {
            next[0] = next[1] = nullptr;
        }
    };
    
    TrieNode *trieRoot = nullptr;
    
    void insertNum(int num) {
        unsigned uNum = (unsigned)num;
        if (trieRoot == nullptr) {
            trieRoot = new TrieNode();
        }
        TrieNode *p = trieRoot;
        for (int i = 0; i < 32; i++) {
            int bit = ((uNum & (1U << (31 - i))) >> (31 - i));
            if (p->next[bit] == nullptr) {
                p->next[bit] = new TrieNode();
            }
            p = p->next[bit];
        }
    }
    
    unsigned findMax(int pos, TrieNode *p1, TrieNode *p2) {
        if (p1 == nullptr || p2 == nullptr) {
            return 0;
        } else {
            unsigned maxNum = 0;
            if (p1->next[0] != nullptr && p2->next[1] != nullptr ||
                p1->next[1] != nullptr && p2->next[0] != nullptr) {
                maxNum += (1U << pos);
                maxNum += max(findMax(pos - 1, p1->next[0], p2->next[1]),
                              findMax(pos - 1, p1->next[1], p2->next[0]));
            } else {
                maxNum += max(findMax(pos - 1, p1->next[0], p2->next[0]),
                              findMax(pos - 1, p1->next[1], p2->next[1]));
            }
            return maxNum;
        }
    }
    
    int findMaximumXOR(vector<int>& nums) {
        for (auto itr = nums.begin(); itr != nums.end(); ++itr) {
            insertNum(*itr);
        }
        return (int)findMax(31, trieRoot, trieRoot);
    }
};