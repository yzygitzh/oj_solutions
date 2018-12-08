class Solution {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        // use floyd
        int equationsLen = equations.size();
        unordered_set<string> nodes;
        unordered_map<string,
                      unordered_map<string, double> > adjMat;
        unordered_map<string,
                      unordered_map<string, double> > dis;
        for (int i = 0; i < equationsLen; i++) {
            nodes.insert(equations[i].first);
            nodes.insert(equations[i].second);
            adjMat[equations[i].first][equations[i].second] = values[i];
            dis[equations[i].first][equations[i].second] = 1;
            if (values[i] <= -1e-6 || values[i] >= 1e-6) {
                adjMat[equations[i].second]
                      [equations[i].first] = 1.0 / values[i];
                dis[equations[i].second][equations[i].first] = 1;
            }
        }
        int nodesLen = nodes.size();
        vector<string> nodesVec(nodes.begin(), nodes.end());
        for (int k = 0; k < nodesLen; k++) {
            for (int i = 0; i < nodesLen; i++) {
                for (int j = i + 1; j < nodesLen; j++) {
                    int disIJ = (1 << 29), disJI = (1 << 29),
                        disIK = (1 << 29), disKI = (1 << 29),
                        disKJ = (1 << 29), disJK = (1 << 29);
                    if (dis.find(nodesVec[i]) != dis.end()) {
                        if (dis[nodesVec[i]].find(nodesVec[j]) !=
                            dis[nodesVec[i]].end())
                            disIJ = dis[nodesVec[i]][nodesVec[j]];
                        if (dis[nodesVec[i]].find(nodesVec[k]) !=
                            dis[nodesVec[i]].end())
                            disIK = dis[nodesVec[i]][nodesVec[k]];
                    }
                    if (dis.find(nodesVec[j]) != dis.end()) {
                        if (dis[nodesVec[j]].find(nodesVec[i]) !=
                            dis[nodesVec[j]].end())
                            disJI = dis[nodesVec[j]][nodesVec[i]];
                        if (dis[nodesVec[j]].find(nodesVec[k]) !=
                            dis[nodesVec[j]].end())
                            disJK = dis[nodesVec[j]][nodesVec[k]];
                    }
                    if (dis.find(nodesVec[k]) != dis.end()) {
                        if (dis[nodesVec[k]].find(nodesVec[i]) !=
                            dis[nodesVec[k]].end())
                            disKI = dis[nodesVec[k]][nodesVec[i]];
                        if (dis[nodesVec[k]].find(nodesVec[j]) !=
                            dis[nodesVec[k]].end())
                            disKJ = dis[nodesVec[k]][nodesVec[j]];
                    }
                    if (disIK + disKJ < disIJ) {
                        dis[nodesVec[i]][nodesVec[j]] = disIK + disKJ;
                        adjMat[nodesVec[i]][nodesVec[j]] =
                            adjMat[nodesVec[i]][nodesVec[k]] *
                            adjMat[nodesVec[k]][nodesVec[j]];
                    }
                    if (disJK + disKI < disJI) {
                        dis[nodesVec[j]][nodesVec[i]] = disJK + disKI;
                        adjMat[nodesVec[j]][nodesVec[i]] =
                            adjMat[nodesVec[j]][nodesVec[k]] *
                            adjMat[nodesVec[k]][nodesVec[i]];
                    }
                }
            }
        }
        int queryNum = queries.size();
        vector<double> result;
        for (int i = 0; i < queryNum; i++) {
            if (adjMat.find(queries[i].first) != adjMat.end() &&
                adjMat[queries[i].first].find(queries[i].second) !=
                adjMat[queries[i].first].end()) {
                result.push_back(adjMat[queries[i].first]
                                       [queries[i].second]);
            } else if (queries[i].first == queries[i].second &&
                       nodes.count(queries[i].first)) {
                result.push_back(1.0);
            } else {
                result.push_back(-1.0);
            }
        }
        return result;
    }
};