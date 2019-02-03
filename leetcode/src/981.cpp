class TimeMap {
public:
    unordered_map<string, map<int, string>> keyToVals;
    
    /** Initialize your data structure here. */
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        keyToVals[key][timestamp] = value;
    }
    
    string get(string key, int timestamp) {
        if (!keyToVals.count(key)) return "";
        
        if (timestamp < keyToVals[key].begin()->first) return "";
        // timestamp >= keyToVals[key].begin()->first, there must be answer
        auto itr = keyToVals[key].lower_bound(timestamp);
        if (itr == keyToVals[key].end()) return keyToVals[key].rbegin()->second;
        if (itr->first == timestamp) return itr->second;
        --itr;
        return itr->second;
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */