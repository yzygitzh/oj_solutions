class MedianFinder {
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
    
    TrieNode *trieRoot = nullptr;

    void insertNum(int num) {
        if (trieRoot == nullptr) trieRoot = new TrieNode();
        
        long long lNum = (1LL << 31);
        lNum += (long long)num;
        unsigned uNum = (unsigned)lNum;

        TrieNode *p = trieRoot;
        for (int i = 0; i < 32; i++) {
            int bit = ((uNum & (1U << (31 - i))) >> (31 - i));
            if (p->next[bit] == nullptr) p->next[bit] = new TrieNode();
            p->count[bit]++;
            p = p->next[bit];
        }
    }
    
    double getMid() {
        TrieNode *p = trieRoot;
        int numLen = p->count[0] + p->count[1];
        int indices[2] = {(numLen - 1) / 2, numLen / 2};
        long long midTotal = 0;
        for (int i = 0; i < 2; i++) {
            int idx = indices[i];
            p = trieRoot;
            unsigned uNum = 0;
            for (int i = 0; i < 32; i++) {
                if (idx + 1 <= p->count[0]) {
                    p = p->next[0];
                } else {
                    idx -= p->count[0];
                    uNum |= (1U << (31 - i));
                    p = p->next[1];
                }
            }
            long long lNum = -(1LL << 31);
            lNum += (long long)uNum;
            midTotal += lNum;
        }
        return (double)midTotal / 2;
    }
    
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        insertNum(num);
    }
    
    double findMedian() {
        return getMid();
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder obj = new MedianFinder();
 * obj.addNum(num);
 * double param_2 = obj.findMedian();
 */