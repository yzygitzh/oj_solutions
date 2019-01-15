class Solution {
public:
    class TrieNode {
    public:
        TrieNode *next[2];
        int count[2];
        TrieNode() {
            next[0] = next[1] = nullptr;
            count[0] = count[1] = 0;
        }
    };
    
    TrieNode *trieRoot;
    
    void insertNum(long long num) {
        num += (1LL << 50);
        unsigned long long uNum = (unsigned long long)num;
        
        if (trieRoot == nullptr) trieRoot = new TrieNode();
        TrieNode *p = trieRoot;
        for (int i = 0; i < 64; i++) {
            unsigned bit = ((uNum & (1ULL << (63 - i))) >> (63 - i));
            if (p->next[bit] == nullptr) p->next[bit] = new TrieNode();
            p->count[bit]++;
            p = p->next[bit];
        }
    }
    
    int countLessThan(long long num, bool inclusive) {
        num += (1LL << 50);
        unsigned long long uNum = (unsigned long long)num;
        
        if (trieRoot == nullptr) trieRoot = new TrieNode();
        TrieNode *p = trieRoot;
        int count = 0;
        for (int i = 0; i < 64 & p != nullptr; i++) {
            unsigned bit = ((uNum & (1ULL << (63 - i))) >> (63 - i));
            if (bit == 1) {
                count += p->count[0];
            }
            if (i == 63 && inclusive) {
                count += p->count[bit];
            }
            p = p->next[bit];
        }
        return count;
    }
    
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        // use BST with subtree count to manage prefixSums
        // do binary search in them
        if (lower > upper) return 0;
        
        int numsLen = nums.size();
        if (numsLen == 0) return 0;
        vector<long long> prefixSums(numsLen + 1, 0);
        insertNum(0);
        int count = 0;
        for (int i = 0; i < numsLen; i++) {
            prefixSums[i + 1] = prefixSums[i] + (long long)nums[i];
            int noLessThanLower = countLessThan(prefixSums[i + 1] - (long long)lower, true);
            int moreThanUpper = countLessThan(prefixSums[i + 1] - (long long)upper, false);
            count += noLessThanLower - moreThanUpper;
            insertNum(prefixSums[i + 1]);
        }
        
        return count;
    }
};