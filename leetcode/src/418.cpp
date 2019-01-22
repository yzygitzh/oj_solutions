class Solution {
public:
    pair<int, int> findNextPos(vector<string>& sentence,
                               pair<int, int> currPos, int cols) {
        for (auto itr = sentence.begin(); itr != sentence.end(); ++itr) {
            int offset = (currPos.second == 0 ? 0 : 1);
            if (currPos.second + offset + itr->length() <= cols) {
                currPos.second += offset + itr->length();
                if (currPos.second == cols) {
                    currPos.first++;
                    currPos.second = 0;
                }
            } else {
                currPos.first++;
                currPos.second = itr->length();
            }
        }
        return currPos;
    }
    
    int wordsTyping(vector<string>& sentence, int rows, int cols) {
        for (auto itr = sentence.begin(); itr != sentence.end(); ++itr) {
            if (itr->length() > cols) return 0;
        }
        
        pair<int, int> currPos;
        currPos.first = currPos.second = 0;
        
        // row, sentenceIdx
        vector<vector<int>> colsOccupied(cols, vector<int>(2, 0));
        
        int headSentence = 0;
        int loopSentence = 0;
        int deltaRows = 0;
        
        // first find loop
        while (true) {
            currPos = findNextPos(sentence, currPos, cols);
            if (currPos.first == rows && currPos.second > 0 ||
                currPos.first > rows) {
                return loopSentence;
            }
            if (colsOccupied[currPos.second][1] > 0) {
                headSentence = colsOccupied[currPos.second][1];
                loopSentence = loopSentence + 1 - headSentence;
                deltaRows = currPos.first - colsOccupied[currPos.second][0];
                break;                   
            }
            loopSentence++;
            colsOccupied[currPos.second] = vector<int>{currPos.first,
                                                       loopSentence};
        }
        
        int totalSentence = headSentence + loopSentence;
        pair<int, int> lastCurrPos;
        while (true) {
            lastCurrPos = currPos;
            currPos.first += deltaRows;
            if (currPos.first == rows && currPos.second > 0 ||
                currPos.first > rows) {
                currPos = lastCurrPos;
                break;
            }
            totalSentence += loopSentence;
        }
        
        while (true) {
            currPos = findNextPos(sentence, currPos, cols);
            if (currPos.first == rows && currPos.second > 0 ||
                currPos.first > rows) {
                return totalSentence;
            }
            totalSentence++;
        }
    }
};