class Solution {
public:
    int bitArray[2100];
    
    int lowbit(int x) {
        return (x & (-x));
    }
    
    void bitDelta(int idx, int delta) {
        while (idx <= 2048) {
            bitArray[idx] += delta;
            idx += lowbit(idx);
        }
    }
    
    int getBitVal(int idx) {
        int result = 0;
        while (idx) {
            result += bitArray[idx];
            idx -= lowbit(idx);
        }
        return result;
    }
    
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
        // sort people indices according to their heights
        // greedy take the lowest person if mulitple person satisfies
        
        // swap-invariant!
        memset(bitArray, 0, sizeof(bitArray));
        
        map<int, set<int>> heightToIdx;
        map<int, int> heightToId;
        for (auto itr = people.begin(); itr != people.end(); ++itr) {
            heightToIdx[itr->first].insert(itr->second);
            heightToId[itr->first] = 0;
        }
        
        int heightId = 1;
        for (auto itr = heightToId.rbegin(); itr != heightToId.rend(); ++itr) {
            heightToId[itr->first] = heightId;
            heightId++;
        }
        
        vector<pair<int, int>> result;
        while (heightToIdx.size() > 0) {
            for (auto itr = heightToIdx.begin(); itr != heightToIdx.end(); ++itr) {
                if (getBitVal(heightToId[itr->first]) == *itr->second.begin()) {
                    result.push_back(make_pair(itr->first, *itr->second.begin()));
                    itr->second.erase(itr->second.begin());
                    bitDelta(heightToId[itr->first], 1);
                    if (itr->second.size() == 0) {
                        heightToIdx.erase(itr->first);
                    }
                    break;
                }
            }
        }
        return result;
    }
};