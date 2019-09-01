class MyCircularQueue {
public:
    vector<int> buf;
    int head, tail, size, maxSize;
    
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) {
        head = tail = size = 0;
        maxSize = k;
        buf.resize(maxSize);
    }
    
    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        if (isFull()) {
            return false;
        } else {
            buf[head++] = value;
            head %= maxSize;
            size++;
            return true;
        }
    }
    
    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        if (isEmpty()) {
            return false;
        } else {
            tail++;
            tail %= maxSize;
            size--;
            return true;
        }
    }
    
    /** Get the front item from the queue. */
    int Front() {
        return isEmpty() ? -1 : buf[tail];
    }
    
    /** Get the last item from the queue. */
    int Rear() {
        return isEmpty() ? -1 : buf[(head + maxSize - 1) % maxSize];
    }
    
    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() {
        return size == 0;
    }
    
    /** Checks whether the circular queue is full or not. */
    bool isFull() {
        return size == maxSize;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */