class Solution {
public:
    vector<string> splitIP(string IP, char delim) {
        vector<string> segs;
        int IPLen = IP.length(), idx = 0;
        string currSeg;
        while (idx < IPLen) {
            if (IP[idx] == delim) {
                segs.push_back(currSeg);
                currSeg = "";
            } else {
                currSeg += IP[idx];
            }
            idx++;
        }
        segs.push_back(currSeg);
        return segs;
    }

    bool validateSeg(string seg, bool isV6) {
        int segLen = seg.length();
        if (segLen == 0) return false;
        if (!isV6 && segLen > 1 && seg[0] == '0' ||
            isV6 && segLen > 4 && seg[0] == '0') return false;
        int segNum = 0;
        for (auto itr = seg.begin(); itr != seg.end(); ++itr) {
            // valid char
            if (!isV6 && !((*itr) >= '0' && (*itr) <= '9') ||
                isV6 && !((*itr) >= '0' && (*itr) <= '9' ||
                          (*itr) >= 'A' && (*itr) <= 'F' ||
                          (*itr) >= 'a' && (*itr) <= 'f')) return false;
            // update segNum
            if (!isV6) {
                segNum *= 10;
                segNum += (*itr) - '0';
            } else {
                segNum *= 16;
                if ((*itr) >= '0' && (*itr) <= '9') segNum += (*itr) - '0';
                else if ((*itr) >= 'A' && (*itr) <= 'F') segNum += (*itr) - 'A';
                else if ((*itr) >= 'a' && (*itr) <= 'f') segNum += (*itr) - 'a';
            }
        }
        return !isV6 && 0 <= segNum && segNum <= 0xFFL ||
               isV6 && 0 <= segNum && segNum <= 0xFFFFL;
    }
    
    bool validateIP(string IP, bool isV6) {
        vector<string> segs = splitIP(IP, isV6 ? ':' : '.');
        if (segs.size() != (isV6 ? 8 : 4)) return false;
        for (auto itr = segs.begin(); itr != segs.end(); ++itr) {
            if (!validateSeg(*itr, isV6)) return false;
        }
        return true;
    }

    string validIPAddress(string IP) {
        int IPLen = IP.length();
        for (int i = 0; i < IPLen; i++) {
            if (IP[i] == '.' && validateIP(IP, false)) return "IPv4";
            else if (IP[i] == ':' && validateIP(IP, true)) return "IPv6";
        }
        return "Neither";
    }
};