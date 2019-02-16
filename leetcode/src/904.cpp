class Solution {
public:
    int totalFruit(vector<int>& tree) {
        int treeNum = tree.size();
        int left = 0, right = 0;
        map<int, int> typeCnt;
        int result = 0;
        while (right < treeNum) {
            typeCnt[tree[right]]++;
            while (typeCnt.size() > 2) {
                typeCnt[tree[left]]--;
                if (typeCnt[tree[left]] == 0) {
                    typeCnt.erase(tree[left]);
                }
                left++;
            }
            result = max(result, right - left + 1);
            right++;
        }
        return result;
    }
};