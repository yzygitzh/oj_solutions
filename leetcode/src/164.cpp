class Solution {
public:
    class TrieNode {
    public:
        TrieNode *next[2];
        TrieNode () {
            next[0] = next[1] = nullptr;
        }
    };
    
    TrieNode *trieRoot;
    
    void insertNum(int num) {
        if (trieRoot == nullptr) trieRoot = new TrieNode();
        TrieNode *p = trieRoot;
        for (int i = 1; i < 32; i++) {
            int digit = ((num & (1 << (31 - i))) >> (31 - i));
            if (p->next[digit] == nullptr) p->next[digit] = new TrieNode();
            p = p->next[digit];
        }
    }
    
    int findMaxGap() {
        int maxGap = 0;
        vector<int> numbers;
        walkTrie(trieRoot, 0, 0, numbers);
        int numbersLen = numbers.size();
        for (int i = 1; i < numbersLen; i++) {
            if (numbers[i] - numbers[i - 1] > maxGap) {
                maxGap = numbers[i] - numbers[i - 1];
            }
        }
        return maxGap;
    }
    
    void walkTrie(TrieNode *p, int idx, int number, vector<int> &numbers) {
        if (idx == 31) {
            numbers.push_back(number);
        } else {
            if (p->next[0] != nullptr) {
                walkTrie(p->next[0], idx + 1, number, numbers);
            }
            if (p->next[1] != nullptr) {
                walkTrie(p->next[1], idx + 1, number + (1 << (30 - idx)), numbers);
            }
        }
    }
    
    int maximumGap(vector<int>& nums) {
        int numsLen = nums.size();
        if (numsLen <= 1) return 0;
        
        for (int i = 0; i < numsLen; i++) insertNum(nums[i]);
        return findMaxGap();
    }
};