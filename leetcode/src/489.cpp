/**
 * // This is the robot's control interface.
 * // You should not implement it, or speculate about its implementation
 * class Robot {
 *   public:
 *     // Returns true if the cell in front is open and robot moves into the cell.
 *     // Returns false if the cell in front is blocked and robot stays in the current cell.
 *     bool move();
 *
 *     // Robot will stay in the same cell after calling turnLeft/turnRight.
 *     // Each turn will be 90 degrees.
 *     void turnLeft();
 *     void turnRight();
 *
 *     // Clean the current cell.
 *     void clean();
 * };
 */
class Solution {
public:
    set<pair<int, int>> memo;
    
    void cleanRoom(Robot& robot) {
        dfs(make_pair(0, 0), 0, robot);
    }
    
    pair<int, int> dirToPos(pair<int, int> pos, int dir) {
        if (dir == 0) pos.first -= 1;
        else if (dir == 1) pos.second += 1;
        else if (dir == 2) pos.first += 1;
        else pos.second -= 1;
        return pos;
    }
    
    void turnBack(Robot& robot) {
        robot.turnRight();
        robot.turnRight();
    }
    
    void dfs(pair<int, int> pos, int dir, Robot& robot) {
        robot.clean();
        memo.insert(pos);
        for (int i = 0; i < 4; i++) {
            if (!memo.count(dirToPos(pos, (dir + i) % 4))) {
                if (robot.move()) {
                    dfs(dirToPos(pos, (dir + i) % 4), (dir + i) % 4, robot);
                    turnBack(robot);
                }
            }
            robot.turnRight();
        }
        turnBack(robot);
        robot.move();
    }
};