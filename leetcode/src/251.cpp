class Vector2D {
public:
    vector<vector<int>> v;
    
    vector<vector<int>>::iterator currRow;
    vector<int>::iterator currCol;
    
    void moveItr() {
        while (currRow != v.end() && currCol == currRow->end()) {
            ++currRow;
            if (currRow == v.end()) break;
            currCol = currRow->begin();
        }
    }
    
    Vector2D(vector<vector<int>> _v) {
        v = _v;
        currRow = v.begin();
        if (currRow == v.end()) return;
        currCol = currRow->begin();
        moveItr();
    }
    
    int next() {
        int result = *currCol;
        ++currCol;
        moveItr();
        return result;
    }
    
    bool hasNext() {
        return currRow != v.end() && currCol != currRow->end();
    }
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D* obj = new Vector2D(v);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */