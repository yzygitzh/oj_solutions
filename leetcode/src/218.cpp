class Solution {
public:
    map<int, int> heightCnt;
    
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        int buildingsLen = buildings.size();
        heightCnt[0]++;
        
        // <pos, height, begin/end>
        vector<vector<int> > platforms(2 * buildingsLen);
        for (int i = 0; i < buildingsLen; i++) {
            platforms[2 * i] = vector<int>{buildings[i][0], buildings[i][2], 0};
            platforms[2 * i + 1] = vector<int>{buildings[i][1], buildings[i][2], 1};
        }
        
        sort(platforms.begin(), platforms.end());
        
        map<int, int> heightCnt;
        heightCnt[0] = 1;
        int platformsLen =  platforms.size();
        int idx = 0;
        int maxH = 0;
        vector<pair<int, int> > result;
                
        while (idx < platformsLen) {
            int currPos = platforms[idx][0];
            vector<int> starts;
            vector<int> ends;
            while (idx < platformsLen && currPos == platforms[idx][0]) {
                if (platforms[idx][2] == 0) {
                    starts.push_back(platforms[idx][1]);
                } else {
                    ends.push_back(platforms[idx][1]);
                }
                idx++;
            }
            // erase ends
            for (vector<int>::iterator itr = ends.begin();
                 itr != ends.end(); ++itr) {
                heightCnt[*itr]--;
                if (heightCnt[*itr] == 0) heightCnt.erase(*itr);
            }
            // add starts
            for (vector<int>::iterator itr = starts.begin();
                 itr != starts.end(); ++itr) {
                heightCnt[*itr]++;
            }
            int currMaxH = heightCnt.rbegin()->first;
            if (currMaxH != maxH) {
                maxH = currMaxH;
                result.push_back(make_pair(currPos, maxH));
            }
        }
        return result;
    }
};