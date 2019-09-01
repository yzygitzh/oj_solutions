class LFUCache {
public:
    class Entry {
    public:
        int key, value;
        Entry(int _key, int _value): key(_key), value(_value) {}
    };
    
    class FreqToEntries {
    public:
        int freq;
        list<Entry> entries;
        FreqToEntries(int _freq): freq(_freq) {}
    };
    
    unordered_map<int, list<Entry>::iterator> keyToEntryItr;
    unordered_map<int, list<FreqToEntries>::iterator> keyToFreqToEntriesItr;
    list<FreqToEntries> freqList;
    int capacity, size;
    
    LFUCache(int _capacity) {
        capacity = _capacity;
        size = 0;
    }
    
    int get(int key) {
        if (capacity == 0 || keyToEntryItr.find(key) == keyToEntryItr.end()) {
            return -1;
        } else {
            auto entryItr = keyToEntryItr[key];
            auto freqToEntriesItr = keyToFreqToEntriesItr[key];
            if (next(freqToEntriesItr, 1) == freqList.end() ||
                next(freqToEntriesItr, 1)->freq > freqToEntriesItr->freq + 1) {
                freqList.insert(next(freqToEntriesItr, 1),
                                FreqToEntries(freqToEntriesItr->freq + 1));
            }
            auto newFreqToEntriesItr = next(freqToEntriesItr, 1);
            newFreqToEntriesItr->entries.push_back(*entryItr);
            keyToEntryItr[key] = prev(newFreqToEntriesItr->entries.end(), 1);
            keyToFreqToEntriesItr[key] = newFreqToEntriesItr;
            freqToEntriesItr->entries.erase(entryItr);
            if (freqToEntriesItr->entries.empty()) {
                freqList.erase(freqToEntriesItr);
            }
            return newFreqToEntriesItr->entries.back().value;
        }
    }
    
    void put(int key, int value) {
        if (capacity == 0) {
            return;
        } else if (keyToEntryItr.find(key) == keyToEntryItr.end()) {
            if (size == capacity) {
                int keyToEvict = freqList.front().entries.front().key;
                freqList.front().entries.erase(keyToEntryItr[keyToEvict]);
                if (freqList.front().entries.empty()) {
                    freqList.erase(freqList.begin());
                }
                keyToEntryItr.erase(keyToEvict);
                keyToFreqToEntriesItr.erase(keyToEvict);
                size--;
            }
            if (freqList.empty() || freqList.front().freq != 1) {
                freqList.push_front(FreqToEntries(1));
            }
            freqList.front().entries.push_back(Entry(key, value));
            keyToEntryItr[key] = prev(freqList.front().entries.end(), 1);
            keyToFreqToEntriesItr[key] = freqList.begin();
            size++;
        } else {
            auto entryItr = keyToEntryItr[key];
            entryItr->value = value;
            get(key);
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */