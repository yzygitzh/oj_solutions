/*
 * LeetCode 803 Bricks Falling When Hit
 * Union Find
 */

class Solution {
public:
  int m, n;
  vector<int> parent, setSize;

  int findParent(int idx) {
    if (idx != parent[idx]) {
      parent[idx] = findParent(parent[idx]);
    }
    return parent[idx];
  }

  bool withWall(int idx) {
    return idx < n;
  }

  // idx1's parent will be idx2's parent. return value is bricks sticked.
  int unionSet(int idx1, int idx2) {
    int parent1 = findParent(idx1);
    int parent2 = findParent(idx2);
    if (parent1 == parent2) return 0;
    // merge to the wall
    if (withWall(parent1) && !withWall(parent2)) {
      parent[parent2] = parent1;
      setSize[parent1] += setSize[parent2];
      return setSize[parent2];
    } else if (withWall(parent2) && !withWall(parent1)) {
      parent[parent1] = parent2;
      setSize[parent2] += setSize[parent1];
      return setSize[parent1];
    } else {
      parent[parent2] = parent1;
      setSize[parent1] += setSize[parent2];
      return 0;
    }
  }

  vector<int> hitBricks(vector<vector<int>>& grid,
                        vector<vector<int>>& hits) {
    m = grid.size(), n = grid[0].size();
    parent = vector<int>(m * n), setSize = vector<int>(m * n, 1);
    for (int i = 0; i < m * n; i++) parent[i] = i;
    // eliminate hit bricks
    for (auto& hit: hits) {
      grid[hit[0]][hit[1]]--;
    }
    // union bricks
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == 1) {
          if (i - 1 >= 0 && grid[i - 1][j] == 1) {
            unionSet((i - 1) * n + j, i * n + j);
          }
          if (j - 1 >= 0 && grid[i][j - 1] == 1) {
            unionSet(i * n + j - 1, i * n + j);
          }
        }
      }
    }      
    // reverse hits
    vector<int> result;
    for (auto itr = hits.rbegin(); itr != hits.rend(); ++itr) {
      int row = (*itr)[0], col = (*itr)[1];
      grid[row][col]++;
      int falls = 0;
      if (grid[row][col] == 1) {
        // union four directions first
        vector<int> setIdx;
        if (row - 1 >= 0 && grid[row - 1][col] == 1) {
          setIdx.push_back((row - 1) * n + col);
        }
        if (row + 1 < m && grid[row + 1][col] == 1) {
          setIdx.push_back((row + 1) * n + col);
        }
        if (col - 1 >= 0 && grid[row][col - 1] == 1) {
          setIdx.push_back(row * n + col - 1);
        }
        if (col + 1 < n && grid[row][col + 1] == 1) {
          setIdx.push_back(row * n + col + 1);
        }
        if (setIdx.size() > 0) {
          for (int i = 1; i < setIdx.size(); i++) {
            falls += unionSet(setIdx[0], setIdx[i]);
          }
          int delta = unionSet(setIdx[0], row * n + col);
          if (delta > 0 && !withWall(row * n + col)) delta -= 1;
          falls += delta;
        }
      }
      result.push_back(falls);
    }
    reverse(result.begin(), result.end());
    return result;
  }
};
