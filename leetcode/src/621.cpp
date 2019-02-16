class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char, int> taskCnt;
        for (auto c: tasks) {
            taskCnt[c]++;
        }
        unordered_map<char, int> taskLastIdx;
        for (auto ci: taskCnt) {
            taskLastIdx[ci.first] = -(n + 1);
        }
        int idx = 0, result = 0;
        while (taskCnt.size() > 0) {
            // find tasks with most remaining valid to do
            int mostRemaining = 0;
            char mostTask = '#';
            for (auto ci: taskCnt) {
                if (idx - taskLastIdx[ci.first] - 1 >= n &&
                    taskCnt[ci.first] > mostRemaining) {
                    mostTask = ci.first;
                    mostRemaining = taskCnt[ci.first];
                }
            }
            if (mostTask != '#') {
                taskCnt[mostTask]--;
                if (taskCnt[mostTask] == 0) taskCnt.erase(mostTask);
                taskLastIdx[mostTask] = idx;
            }
            result++;
            idx++;
        }
        return result;
    }
};