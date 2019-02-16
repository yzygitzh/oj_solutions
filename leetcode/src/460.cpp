class LFUCache {
public:
    class RListNode {
    public:
        int key, value;
        RListNode(int _key, int _value): key(_key), value(_value) {}
    };
    
    class FListNode {
    public:
        int freq;
        list<RListNode> RList;
        FListNode(int _freq): freq(_freq), RList() {}
    };
    
    list<FListNode> FList;
    unordered_map<int, list<RListNode>::iterator> keyToEntry;
    unordered_map<int, list<FListNode>::iterator> keyToFListPtr;
    int capacity, maxCapacity;
    
    LFUCache(int _capacity) {
        maxCapacity = _capacity;
        capacity = 0;
    }
    
    int get(int key) {
        if (maxCapacity == 0 || !keyToEntry.count(key)) {
            return -1;
        } else {
            auto entryP = keyToEntry[key];
            auto freqP = keyToFListPtr[key];
            // remove entry from origin freq node
            RListNode entry = *entryP;
            freqP->RList.erase(entryP);
            // add new node for freq + 1 if not exist or not consecutive
            if (next(freqP, 1) == FList.end() ||
                next(freqP, 1)->freq != freqP->freq + 1) {
                FList.insert(next(freqP, 1), FListNode(freqP->freq + 1));
            }
            ++freqP;
            // delete origin freqP if empty
            if (prev(freqP, 1)->RList.empty()) {
                FList.erase(prev(freqP, 1));
            }
            // insert entry into new freq node
            freqP->RList.push_back(entry);
            // update keyTo*
            keyToEntry[key] = prev(freqP->RList.end(), 1);
            keyToFListPtr[key] = freqP;
            return entry.value;
        }
    }
    
    void put(int key, int value) {
        if (maxCapacity == 0) return;
        if (!keyToEntry.count(key)) {
            if (capacity == maxCapacity) {
                // do evit
                auto RHead = FList.begin()->RList.begin();
                int evitKey = RHead->key;
                FList.begin()->RList.erase(keyToEntry[evitKey]);
                keyToEntry.erase(evitKey);
                if (FList.begin()->RList.empty()) {
                    FList.erase(FList.begin());
                }
                capacity--;
            }
            // do insert
            RListNode entry(key, value);
            if (FList.empty() || FList.begin()->freq != 1) {
                FList.push_front(FListNode(1));
            }
            FList.begin()->RList.push_back(entry);
            // update keyTo*
            keyToEntry[key] = prev(FList.begin()->RList.end(), 1);
            keyToFListPtr[key] = FList.begin();
            capacity++;
        } else {
            auto entryP = keyToEntry[key];
            entryP->value = value;
            get(key);
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache obj = new LFUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */