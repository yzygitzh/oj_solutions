class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        // mono stack of reaching time
        // scan from left to right
        vector<double> timeStack;
        vector<pair<int, int>> posSpeed;
        for (int i = 0; i < position.size(); i++) {
            posSpeed.push_back(make_pair(position[i], speed[i]));
        }
        sort(posSpeed.begin(), posSpeed.end(), [] (pair<int, int>& a, pair<int, int>& b) {
            return a.first < b.first;
        });
        for (auto& p : posSpeed) {
            double time = double(target - p.first) / p.second;
            while (!timeStack.empty() && time >= timeStack.back() - 1e-6) {
                timeStack.pop_back();
            }
            timeStack.push_back(time);
        }
        return timeStack.size();
    }
};