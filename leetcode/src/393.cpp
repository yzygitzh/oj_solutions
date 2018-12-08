class Solution {
public:
    bool validUtf8(vector<int>& data) {
        int dataLen = data.size();
        int dataIdx = 0;
        
        while (dataIdx < dataLen) {
            // invariant: check next chracter
            if ((0x80 & data[dataIdx]) == 0) {
                dataIdx += 1;
            } else if (dataIdx + 1 < dataLen &&
                       (0xE0 & data[dataIdx]) == 0xC0 &&
                       (0xC0 & data[dataIdx + 1]) == 0x80) {
                dataIdx += 2;
            } else if (dataIdx + 2 < dataLen &&
                       (0xF0 & data[dataIdx]) == 0xE0 &&
                       (0xC0 & data[dataIdx + 1]) == 0x80 &&
                       (0xC0 & data[dataIdx + 2]) == 0x80) {
                dataIdx += 3;
            } else if (dataIdx + 3 < dataLen &&
                       (0xF8 & data[dataIdx]) == 0xF0 &&
                       (0xC0 & data[dataIdx + 1]) == 0x80 &&
                       (0xC0 & data[dataIdx + 2]) == 0x80 &&
                       (0xC0 & data[dataIdx + 3]) == 0x80) {
                dataIdx += 4;
            } else {
                return false;
            }
        }
        
        return true;
    }
};