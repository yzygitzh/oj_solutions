/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (node == nullptr) return nullptr;
        
        unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> newPtr;
        
        // first build nodes
        queue<UndirectedGraphNode*> bfsQ;
        bfsQ.push(node);
        while (!bfsQ.empty()) {
            UndirectedGraphNode* currP = bfsQ.front();
            bfsQ.pop();
            if (currP == nullptr) continue;
            newPtr[currP] = new UndirectedGraphNode(currP->label);
            for (vector<UndirectedGraphNode*>::iterator itr = currP->neighbors.begin();
                 itr != currP->neighbors.end(); ++itr) {
                if (newPtr.find(*itr) == newPtr.end()) bfsQ.push(*itr);
            }
        }

        // then fillin edges
        for (unordered_map<UndirectedGraphNode*, UndirectedGraphNode*>::iterator
             itr1 = newPtr.begin(); itr1 != newPtr.end(); ++itr1) {
            for (vector<UndirectedGraphNode*>::iterator itr2 = itr1->first->neighbors.begin();
                 itr2 != itr1->first->neighbors.end(); ++itr2) {
                itr1->second->neighbors.push_back(newPtr[*itr2]);
            }
        }
        
        return newPtr[node];
    }
};