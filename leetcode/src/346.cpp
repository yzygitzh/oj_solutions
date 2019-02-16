class MovingAverage {
public:
    int size, sum = 0;
    deque<int> numQ;
    
    /** Initialize your data structure here. */
    MovingAverage(int _size): size(_size) {}
    
    double next(int val) {
        numQ.push_back(val);
        sum += val;
        if (numQ.size() > size) {
            sum -= numQ.front();
            numQ.pop_front();
        }
        return (double)sum / min(size, (int)numQ.size());
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage obj = new MovingAverage(size);
 * double param_1 = obj.next(val);
 */