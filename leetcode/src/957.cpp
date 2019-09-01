class Solution {
public:
    int cellsToInt(vector<int>& cells) {
        int result = 0;
        for (auto cell : cells) {
            result <<= 1;
            result += cell;
        }
        return result;
    }
    
    void intToCells(vector<int>& cells, int state) {
        for (int i = 0; i < cells.size(); i++) {
            int shiftDis = (cells.size() - i - 1);
            cells[i] = ((state & (1 << shiftDis)) >> shiftDis);
        }
    }
    
    void changeCells(vector<int>& cells) {
        for (int i = 1; i < cells.size() - 1; i++) {
            if ((cells[i - 1] & 1) == (cells[i + 1] & 1)) {
                cells[i] |= 0x2;
            }
        }
        for (auto& cell : cells) {
            cell >>= 1;
        }
    }
    
    vector<int> prisonAfterNDays(vector<int>& cells, int N) {
        vector<int> minStep(256, -1);
        vector<int> visitedStates;
        int step = 0;
        while (minStep[cellsToInt(cells)] == -1) {
            minStep[cellsToInt(cells)] = step;
            visitedStates.push_back(cellsToInt(cells));
            if (step == N) {
                return cells;
            }
            changeCells(cells);
            step++;
        }
        int loopStartState = cellsToInt(cells);
        int stepsBeforeLoop = minStep[loopStartState];
        int resultIdx = stepsBeforeLoop +
                        (N - stepsBeforeLoop) %
                        (visitedStates.size() - stepsBeforeLoop);
        intToCells(cells, visitedStates[resultIdx]);
        return cells;
    }
};