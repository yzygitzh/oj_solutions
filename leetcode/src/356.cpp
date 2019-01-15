class Solution {
public:
    unordered_map<int, unordered_set<int>> yToXs;
    
    double getAbs(double a) {
        return a < 0 ? -a : a;
    }
    
    bool isReflected(vector<pair<int, int>>& points) {
        for (auto itr = points.begin(); itr != points.end(); ++itr) {
            yToXs[itr->second].insert(itr->first);
        }
        
        vector<double> mids;
        for (auto itr = yToXs.begin(); itr != yToXs.end(); ++itr) {
            double avg = 0;
            for (auto itr2 = itr->second.begin(); itr2 != itr->second.end(); ++itr2) {
                avg += *itr2;
            }
            avg /= itr->second.size();
            if (mids.size() > 0 && getAbs(*mids.rbegin() - avg) > 1e-6) return false;
            
            unordered_map<double, int> leftCnt, rightCnt;
            for (auto itr2 = itr->second.begin(); itr2 != itr->second.end(); ++itr2) {
                if (*itr2 - avg < -1e-6) leftCnt[getAbs(*itr2 - avg)]++;
                if (*itr2 - avg > 1e-6) rightCnt[getAbs(*itr2 - avg)]++;
            }
            if (leftCnt != rightCnt) return false;
            
            mids.push_back(avg);
        }
        return true;        
    }
};