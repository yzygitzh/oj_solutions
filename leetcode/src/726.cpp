class Solution {
public:
    string countOfAtoms(string formula) {
        // digits can only appear after atoms or right parenthesis.
        // store map: atom->count in stack.
        // if map is empty, this must be left parenthesis.
        formula = "(" + formula + ")";
        vector<map<string, int>> atomStack;
        int fLen = formula.length(), idx = 0;
        while (idx < fLen) {
            map<string, int> atomCntMap;
            if ('A' <= formula[idx] && 'Z' >= formula[idx]) {
                string atom;
                atom += formula[idx++];
                while (idx < fLen && 'a' <= formula[idx] && 'z' >= formula[idx]) {
                    atom += formula[idx++];
                }
                int atomCnt = 0;
                while (idx < fLen && '0' <= formula[idx] && '9' >= formula[idx]) {
                    atomCnt *= 10;
                    atomCnt += formula[idx++] - '0';
                }
                if (atomCnt == 0) atomCnt = 1;
                atomCntMap[atom] = atomCnt;
            } else if ('(' == formula[idx]) {
                idx++;
            } else if (')' == formula[idx]) {
                idx++;
                int groupCnt = 0;
                while (idx < fLen && '0' <= formula[idx] && '9' >= formula[idx]) {
                    groupCnt *= 10;
                    groupCnt += formula[idx++] - '0';
                }
                if (groupCnt == 0) groupCnt = 1;
                while (atomStack.back().size() > 0) {
                    for (auto itr = atomStack.back().begin();
                         itr != atomStack.back().end(); ++itr) {
                        atomCntMap[itr->first] += itr->second * groupCnt;
                    }
                    atomStack.pop_back();
                }
                atomStack.pop_back();
            }
            atomStack.push_back(atomCntMap);
        }
        string result;
        for (auto itr = atomStack.front().begin();
             itr != atomStack.front().end(); ++itr) {
            result += itr->first;
            if (itr->second > 1) result += to_string(itr->second);
        }
        return result;
    }
};