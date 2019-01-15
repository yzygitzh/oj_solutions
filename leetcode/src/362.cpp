class HitCounter {
public:
    queue<int> tsList;
    unordered_map<int, int> tsHitCnt;
    int deletedCnt = 0;
    int maxKey;
    
    /** Initialize your data structure here. */
    HitCounter() {
        
    }
    
    /** Record a hit.
        @param timestamp - The current timestamp (in seconds granularity). */
    void hit(int timestamp) {
        if (tsList.empty() || tsList.back() != timestamp) {
            if (tsList.empty()) tsHitCnt[timestamp] = deletedCnt;
            else tsHitCnt[timestamp] = tsHitCnt[tsList.back()];
            tsList.push(timestamp);
        }
        tsHitCnt[timestamp]++;
        clearHits(timestamp);
        maxKey = timestamp;
    }
    
    /** Return the number of hits in the past 5 minutes.
        @param timestamp - The current timestamp (in seconds granularity). */
    int getHits(int timestamp) {
        clearHits(timestamp);
        if (tsHitCnt.size() == 0) return 0;
        // timestamp is mono-increasing
        return tsHitCnt[maxKey] - deletedCnt;
    }
    
    void clearHits(int timestamp) {
        while (!tsList.empty() && timestamp - 300 >= tsList.front()) {
            deletedCnt = tsHitCnt[tsList.front()];
            tsHitCnt.erase(tsList.front());
            tsList.pop();
        }
    }
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter obj = new HitCounter();
 * obj.hit(timestamp);
 * int param_2 = obj.getHits(timestamp);
 */