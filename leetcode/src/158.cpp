// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    queue<char> buf4;
    
    int read(char *buf, int n) {
        int rest = n;
        int bufIdx = 0;
        
        // try to read from read4
        while (true) {
            while (buf4.size() > 0 && rest > 0) {
                buf[bufIdx] = buf4.front();
                buf4.pop();
                bufIdx++;
                rest--;
            }
            if (rest == 0) return n;
            char buf4Read[4];
            int buf4ReadNum = read4(buf4Read);
            if (buf4ReadNum == 0) return n - rest;
            for (int i = 0; i < buf4ReadNum; i++) {
                buf4.push(buf4Read[i]);
            }
        }
    }
};