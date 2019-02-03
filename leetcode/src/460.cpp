class LFUCache {
public:
    class DoubleListNode {
    public:
        DoubleListNode *prev, *next;
        DoubleListNode(): prev(nullptr), next(nullptr) {}
    };
    
    class DoubleList {
    public:
        DoubleListNode *head, *tail;
        DoubleList(): head(nullptr), tail(nullptr) {}
    
        bool empty() {
            return head == nullptr;
        }
        
        void push_front(DoubleListNode *p) {
            p->prev = p->next = nullptr;
            if (head == nullptr) {
                head = tail = p;
            } else {
                head->prev = p;
                p->next = head;
                head = head->prev;
            }
        }
        
        void erase(DoubleListNode *p) {
            if (p == head && p == tail) {
                head = tail = nullptr;
            } else if (p == head) {
                head = head->next;
                head->prev = nullptr;
            } else if (p == tail) {
                tail = tail->prev;
                tail->next = nullptr;
            } else {
                p->prev->next = p->next;
                p->next->prev = p->prev;
            }
            p->prev = p->next = nullptr;
        }
        
        void insert(DoubleListNode *p, DoubleListNode *q) {
            // q must be in the list
            p->prev = p->next = nullptr;
            if (q == nullptr) {
                head = tail = p;
            } else if (q == tail) {
                tail->next = p;
                p->prev = tail;
                tail = tail->next;
            } else {
                p->next = q->next;
                p->prev = q;
                q->next->prev = p;
                q->next = p;
            }
        }
    };
    
    class RListNode : public DoubleListNode {
    public:
        int key, value;
        RListNode(int _key, int _value): key(_key), value(_value) {}
    };
    
    class FListNode : public DoubleListNode {
    public:
        int freq;
        DoubleList RList;
        FListNode(int _freq): freq(_freq), RList() {}
    };
    
    DoubleList FList;
    unordered_map<int, RListNode*> keyToEntry;
    unordered_map<int, FListNode*> keyToFListPtr;
    int capacity, maxCapacity;
    
    LFUCache(int _capacity) {
        // F-list, R-list
        // key to cache entry
        // key to freq list node
        maxCapacity = _capacity;
        capacity = 0;
    }
    
    int get(int key) {
        if (maxCapacity == 0) return -1;
        if (!keyToEntry.count(key)) {
            return -1;
        } else {
            RListNode *entryP = keyToEntry[key];
            FListNode *freqP = keyToFListPtr[key];
            // remove entry from origin freq node
            freqP->RList.erase(entryP);
            // add new node for freq + 1 if not exist or not consecutive
            if (freqP->next == nullptr ||
                ((FListNode*)freqP->next)->freq != freqP->freq + 1) {
                FList.insert(new FListNode(freqP->freq + 1), freqP);
            }
            freqP = (FListNode*)freqP->next;
            // delete origin freqP if empty
            if (((FListNode*)freqP->prev)->RList.empty()) {
                FList.erase(freqP->prev);
            }
            // insert entry into new freq node
            freqP->RList.insert(entryP, freqP->RList.tail);
            // maintain keyToFListPtr
            keyToFListPtr[key] = freqP;
            return entryP->value;
        }
    }
    
    void put(int key, int value) {
        if (maxCapacity == 0) return;
        if (!keyToEntry.count(key)) {
            FListNode *FHead = (FListNode*)FList.head;
            if (capacity == maxCapacity) {
                // do evit
                RListNode *RHead = (RListNode*)FHead->RList.head;
                int evitKey = RHead->key;
                FHead->RList.erase(keyToEntry[evitKey]);
                keyToEntry.erase(evitKey);
                if (FHead->RList.empty()) {
                    FList.erase(FHead);
                }
                capacity--;
            }
            // do insert
            FHead = (FListNode*)FList.head;
            RListNode *entryP = new RListNode(key, value);
            if (FList.empty() || FHead->freq != 1) {
                FList.push_front(new FListNode(1));
                FHead = (FListNode*)FList.head;
            }
            FHead->RList.insert(entryP, FHead->RList.tail);
            // update keyTo*
            keyToEntry[key] = entryP;
            keyToFListPtr[key] = FHead;
            capacity++;
        } else {
            RListNode *entryP = keyToEntry[key];
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