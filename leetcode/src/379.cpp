class PhoneDirectory {
public:
    unsigned char *numberPool;
    int maxNumbers;
    int poolIdx;
    queue<int> releasedNumbers;
    
    /** Initialize your data structure here
        @param maxNumbers - The maximum numbers that can be stored in the phone directory. */
    PhoneDirectory(int _maxNumbers) {
        maxNumbers = _maxNumbers;
        numberPool = new unsigned char[maxNumbers];
        memset(numberPool, 0, maxNumbers);
        poolIdx = 0;
    }
    
    /** Provide a number which is not assigned to anyone.
        @return - Return an available number. Return -1 if none is available. */
    int get() {
        int result;
        if (!releasedNumbers.empty()) {
            result = releasedNumbers.front();
            numberPool[result] = 1;
            releasedNumbers.pop();
        } else if (poolIdx < maxNumbers) {
            result = poolIdx;
            numberPool[result] = 1;
            poolIdx++;
        } else {
            result = -1;
        }
        return result;
    }
    
    /** Check if a number is available or not. */
    bool check(int number) {
        return !numberPool[number];
    }
    
    /** Recycle or release a number. */
    void release(int number) {
        if (numberPool[number]) {
            numberPool[number] = 0;
            releasedNumbers.push(number);
        }
    }
};

/**
 * Your PhoneDirectory object will be instantiated and called as such:
 * PhoneDirectory obj = new PhoneDirectory(maxNumbers);
 * int param_1 = obj.get();
 * bool param_2 = obj.check(number);
 * obj.release(number);
 */