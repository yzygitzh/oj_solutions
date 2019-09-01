class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> result;
        vector<int> asteroidStack;
        for (auto asteroid : asteroids) {
            if (asteroid > 0) {
                asteroidStack.push_back(asteroid);
            } else {
                while (asteroid < 0 &&
                       !asteroidStack.empty()) {
                    if (asteroidStack.back() < -asteroid) {
                        asteroidStack.pop_back();
                    } else if (asteroidStack.back() == -asteroid) {
                        asteroidStack.pop_back();
                        asteroid = 0;
                    } else {
                        asteroid = 0;
                    }
                }
                if (asteroid < 0) {
                    result.push_back(asteroid);
                }
            }
        }
        for (auto asteroid : asteroidStack) {
            result.push_back(asteroid);
        }
        return result;
    }
};