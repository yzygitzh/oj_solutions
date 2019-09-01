class ExamRoom {
public:
    int size;
    static int maxSize;
    
    class SeatIntervalMaxDis {
    public:
        int left, right;
        SeatIntervalMaxDis(int left_, int right_) : left(left_), right(right_) {}
        
        int getSeat() {
            if (left == 0) {
                return 0;
            } else if (right == maxSize - 1) {
                return maxSize - 1;
            } else {
                return left + (right - left) / 2;
            }
        }
        
        int getDis() const {
            if (left == 0 || right == maxSize - 1) {
                return right - left + 1;
            } else {
                return (right - left) / 2 + 1;
            }
        }
        
        bool operator< (const SeatIntervalMaxDis& s) const {
            int dis = getDis();
            int sDis = s.getDis();
            if (dis != sDis) {
                return dis > sDis;
            }
            return left < s.left;
        }
    };
    
    class SeatIntervalMinLeft {
    public:
        int left, right;
        SeatIntervalMinLeft(int left_, int right_) : left(left_), right(right_) {}
        bool operator< (const SeatIntervalMinLeft& s) const {
            return left < s.left;
        }
    };
    
    set<SeatIntervalMaxDis> intervalsMaxDis;
    set<SeatIntervalMinLeft> intervalsMinLeft;
    
    ExamRoom(int N) {
        size = 0;
        maxSize = N;
        intervalsMaxDis.insert(SeatIntervalMaxDis(0, N - 1));
    }
    
    int seat() {
        size++;
        SeatIntervalMaxDis interval = *intervalsMaxDis.begin();
        intervalsMaxDis.erase(interval);
        intervalsMinLeft.erase(SeatIntervalMinLeft(interval.left, interval.right));
        if (size == 1) {
            if (1 <= interval.right) {
                intervalsMaxDis.insert(SeatIntervalMaxDis(1, interval.right));
                intervalsMinLeft.insert(SeatIntervalMinLeft(1, interval.right));
            }
            return 0;
        } else {
            int result = interval.getSeat();
            if (interval.left <= result - 1) {
                intervalsMaxDis.insert(SeatIntervalMaxDis(interval.left, result - 1));
                intervalsMinLeft.insert(SeatIntervalMinLeft(interval.left, result - 1));
            }
            if (result + 1 <= interval.right) {
                intervalsMaxDis.insert(SeatIntervalMaxDis(result + 1, interval.right));
                intervalsMinLeft.insert(SeatIntervalMinLeft(result + 1, interval.right));
            }
            return result;
        }
    }
    
    void leave(int p) {
        size--;
        SeatIntervalMinLeft seeker(p, p);
        auto itr1 = intervalsMinLeft.lower_bound(seeker);
        auto itr2 = itr1;
        
        if (itr1 != intervalsMinLeft.end()) {
            --itr1;
            if (itr1 != intervalsMinLeft.end() && itr1->right + 1 == p) {
                seeker.left = itr1->left;
            }
        } else if (intervalsMinLeft.rbegin() != intervalsMinLeft.rend() &&
                   intervalsMinLeft.rbegin()->right + 1 == p) {
            seeker.left = intervalsMinLeft.rbegin()->left;
        }
        
        if (itr2 != intervalsMinLeft.end() && p + 1 == itr2->left) {
            seeker.right = itr2->right;
        }
        
        // erase old intervals
        if (seeker.left != p) {
            intervalsMaxDis.erase(SeatIntervalMaxDis(seeker.left, p - 1));
            intervalsMinLeft.erase(SeatIntervalMinLeft(seeker.left, p - 1));
        }
        if (seeker.right != p) {
            intervalsMaxDis.erase(SeatIntervalMaxDis(p + 1, seeker.right));
            intervalsMinLeft.erase(SeatIntervalMinLeft(p + 1, seeker.right));
        }
        intervalsMaxDis.insert(SeatIntervalMaxDis(seeker.left, seeker.right));
        intervalsMinLeft.insert(seeker);
    }
};

int ExamRoom::maxSize;

/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom* obj = new ExamRoom(N);
 * int param_1 = obj->seat();
 * obj->leave(p);
 */