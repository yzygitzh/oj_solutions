class LRUCache {
public:
    class Entry {
    public:
        Entry *prev, *next;
        int key, val;
        Entry(int _key, int _val): prev(nullptr), next(nullptr), key(_key), val(_val) {}
    };
    
    // tail is the latest
    Entry *head, *tail;
    unordered_map<int, Entry*> key2Entry;
    int capacity;
    int currSize;
    
    LRUCache(int _capacity) {
        head = tail = nullptr;
        capacity = _capacity;
        currSize = 0;
    }
    
    void insertEntry(int key, int val) {
        if (head == nullptr && tail == nullptr) {
            tail = head = new Entry(key, val);
            tail = head;
        } else {
            tail->next = new Entry(key, val);
            tail->next->prev = tail;
            tail = tail->next;
        }
        key2Entry[key] = tail;
        currSize++;
    }

    void deleteEntry(int key) {
        Entry *target = key2Entry[key];
        if (target->prev != nullptr) {
            target->prev->next = target->next;
        }
        if (target->next != nullptr) {
            target->next->prev = target->prev;
        }
        if (tail == target) tail = target->prev;
        if (head == target) head = target->next;
        key2Entry.erase(key);
        delete target;
        currSize--;
    }
    
    void move2Tail(int key) {
        Entry *target = key2Entry[key];
        int targetVal = target->val;
        deleteEntry(key);
        insertEntry(key, targetVal);
    }
    
    int get(int key) {
        if (key2Entry.find(key) == key2Entry.end()) {
            return -1;
        } else {
            move2Tail(key);
            return tail->val;
        }
    }
    
    void put(int key, int value) {
        if (capacity == 0) return;
        if (key2Entry.find(key) != key2Entry.end()) {
            move2Tail(key);
            tail->val = value;
        } else {
            if (capacity == currSize) {
                deleteEntry(head->key);
            }
            insertEntry(key, value);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */