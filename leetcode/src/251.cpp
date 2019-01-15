class Vector2D {
public:
    vector<vector<int>>* vec2d;
    vector<vector<int>>::iterator vec2dItr;
    vector<int>::iterator vecItr;
    
    // invariant: vec2dItr == vec2d->end() or vecItr is valid
    Vector2D(vector<vector<int>>& _vec2d) {
        vec2d = &_vec2d;
        
        // point to first element
        vec2dItr = vec2d->begin();
        move2d();
        if (vec2dItr != vec2d->end()) {
            vecItr = vec2dItr->begin();
        }
    }

    // called only when hasNext is true, i.e. vecItr is valid
    int next() {
        int result = *vecItr;
        move();
        return result;
    }
    
    void move() {
        // if vec2dItr == vec2d->end, vecItr must be some end.
        if (vec2dItr != vec2d->end()) {
            ++vecItr;
            if (vecItr == vec2dItr->end()) {
                ++vec2dItr;
                move2d();
                if (vec2dItr != vec2d->end()) vecItr = vec2dItr->begin();
            }
        }
    }

    // move to next non-zero-length vector
    void move2d() {
        while (vec2dItr != vec2d->end() &&
               vec2dItr->begin() == vec2dItr->end()) {
            ++vec2dItr;
        }
    }

    bool hasNext() {
        return vec2dItr != vec2d->end();
    }
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D i(vec2d);
 * while (i.hasNext()) cout << i.next();
 */