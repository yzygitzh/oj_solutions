class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        queue<int> zeroPts;
        unordered_map<int, set<int> > src2tgt, tgt2src;
        
        for (int i = 0; i < numCourses; i++) {
            src2tgt[i] = set<int>();
            tgt2src[i] = set<int>();
        }
        
        int edgeNum = prerequisites.size();
        for (int i = 0; i < edgeNum; i++) {
            pair<int, int> edge = prerequisites[i];
            src2tgt[edge.first].insert(edge.second);
            tgt2src[edge.second].insert(edge.first);
        }
        
        // find init zero in points
        for (int i = 0; i < numCourses; i++) {
            if (tgt2src[i].size() == 0) zeroPts.push(i);
        }
        int nodeCount = 0;
        while (!zeroPts.empty()) {
            int currP = zeroPts.front();
            zeroPts.pop();
            nodeCount++;
            for (set<int>::iterator itr = src2tgt[currP].begin();
                 itr != src2tgt[currP].end(); ++itr) {
                tgt2src[*itr].erase(currP);
                if (tgt2src[*itr].size() == 0) zeroPts.push(*itr);
            }
            src2tgt[currP].clear();
        }
        
        return nodeCount == numCourses;
    }
};