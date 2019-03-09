class AllOne {
public:
    list<pair<int, list<string>>> freqList;
    unordered_map<string,
                  list<pair<int, list<string>>>::iterator> keyToFreqList;
    unordered_map<string,
                  list<string>::iterator> keyToElem;
    
    /** Initialize your data structure here. */
    AllOne() {
        
    }
    
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        if (!keyToFreqList.count(key)) {
            if (freqList.size() == 0 || freqList.begin()->first != 1) {
                freqList.push_front(make_pair(1, list<string>()));
            }
            freqList.begin()->second.push_back(key);
            keyToFreqList[key] = freqList.begin();
            keyToElem[key] = prev(freqList.begin()->second.end(), 1);
            return;
        }
        auto itrFreqList = keyToFreqList[key];
        auto itrElem = keyToElem[key];
        itrFreqList->second.erase(itrElem);
        if (next(itrFreqList, 1) == freqList.end() ||
            next(itrFreqList, 1)->first != itrFreqList->first + 1) {
            freqList.insert(
                next(itrFreqList, 1),
                make_pair(itrFreqList->first + 1, list<string>())
            );
        }
        ++itrFreqList;
        keyToFreqList[key] = itrFreqList;
        itrFreqList->second.push_back(key);
        keyToElem[key] = prev(itrFreqList->second.end(), 1);
        if (prev(itrFreqList, 1)->second.size() == 0) {
            freqList.erase(prev(itrFreqList, 1));
        }
    }
    
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        if (!keyToFreqList.count(key)) return;
        auto itrFreqList = keyToFreqList[key];
        auto itrElem = keyToElem[key];
        string elem = *itrElem;
        itrFreqList->second.erase(itrElem);
        if (itrFreqList->first == 1) {
            keyToFreqList.erase(key);
            keyToElem.erase(key);
            if (itrFreqList->second.size() == 0) {
                freqList.erase(itrFreqList);
            }
            return;
        }
        if (prev(itrFreqList, 1) == freqList.end() ||
            prev(itrFreqList, 1)->first != itrFreqList->first - 1) {
            freqList.insert(
                itrFreqList,
                make_pair(itrFreqList->first - 1, list<string>())
            );
        }
        --itrFreqList;
        keyToFreqList[key] = itrFreqList;
        itrFreqList->second.push_back(key);
        keyToElem[key] = prev(itrFreqList->second.end(), 1);
        if (next(itrFreqList, 1)->second.size() == 0) {
            freqList.erase(next(itrFreqList, 1));
        }
    }
    
    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        if (freqList.size() == 0) return "";
        return *(freqList.rbegin()->second.begin());
    }
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        if (freqList.size() == 0) return "";
        return *(freqList.begin()->second.begin());
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne obj = new AllOne();
 * obj.inc(key);
 * obj.dec(key);
 * string param_3 = obj.getMaxKey();
 * string param_4 = obj.getMinKey();
 */