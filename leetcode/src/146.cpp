class LRUCache {
public:
    int capacity, maxCapacity;
    list<pair<int, int>> values;
    unordered_map<int, list<pair<int, int>>::iterator> keyToValues;
    
    LRUCache(int _capacity) {
        capacity = 0;
        maxCapacity = _capacity;
    }
    
    int get(int key) {
        if (maxCapacity == 0) return -1;
        if (keyToValues.count(key)) {
            auto itr = keyToValues[key];
            int value = itr->second;
            values.erase(itr);
            values.push_back(make_pair(key, value));
            keyToValues[key] = prev(values.end(), 1);
            return value;
        } else {
            return -1;
        }
    }
    
    void put(int key, int value) {
        if (maxCapacity == 0) return;
        if (keyToValues.count(key)) {
            auto itr = keyToValues[key];
            itr->second = value;
            get(key);
        } else {
            if (capacity == maxCapacity) {
                int evictKey = values.front().first;
                values.pop_front();
                keyToValues.erase(evictKey);
                capacity--;
            }
            values.push_back(make_pair(key, value));
            keyToValues[key] = prev(values.end(), 1);
            capacity++;
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */