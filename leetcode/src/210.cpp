class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<int> result;
        
        unordered_map<int, set<int> > src2tgt, tgt2src;
        for (int i = 0; i < numCourses; i++) {
            src2tgt[i] = set<int>();
            tgt2src[i] = set<int>();
        }
        
        int edgeNum = prerequisites.size();
        for (int i = 0; i < edgeNum; i++) {
            pair<int, int> edge = prerequisites[i];
            src2tgt[edge.second].insert(edge.first);
            tgt2src[edge.first].insert(edge.second);
        }
        
        queue<int> bfsQ;
        for (int i = 0; i < numCourses; i++) {
            if (tgt2src[i].size() == 0) bfsQ.push(i);
        }
        
        int nodeCount = 0;
        while (!bfsQ.empty()) {
            int currP = bfsQ.front();
            bfsQ.pop();
            nodeCount++;
            result.push_back(currP);
            for (set<int>::iterator itr = src2tgt[currP].begin();
                 itr != src2tgt[currP].end(); ++itr) {
                tgt2src[*itr].erase(currP);
                if (tgt2src[*itr].size() == 0) bfsQ.push(*itr);
            }
            src2tgt[currP].clear();
        }
        
        if (nodeCount == numCourses) return result;
        else return vector<int>();
    }
};