class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        // theorem 1: if gas sum >= cost sum, we can always find solution.
        // if we can't, the circle can be divided into non-intersecting
        // intervals, where gas sum < cost sum.
        // as a result, total gas sum < total cost sum, which is not true.
        
        // theorem 2: startIdx must be the first element of some interval
        // that all elements of it are gas sum > cost sum.
        
        // theorem 3: from incorrect start, we can never walk to correct start.
        // because the correct start can go to anywhere, then we have 2 starts.
        
        int gasLen = gas.size();
        int costLen = cost.size();
        
        if (gasLen == 0) return -1;
        if (gasLen == 1) return gas[0] < cost[0] ? -1 : 0;
        
        int gasSum = 0;
        for (int i = 0; i < gasLen; i++) {
            gasSum += gas[i];
        }
        int costSum = 0;
        for (int i = 0; i < costLen; i++) {
            costSum += cost[i];
        }
        
        if (gasSum < costSum) {
            return -1;
        } else {
            // invariant: left can go to right
            int left = 0;
            while (gas[left] > cost[left]) left = (left + 1) % gasLen;
            while (gas[left] < cost[left]) left = (left + 1) % gasLen;
            int currCost = 0;
            int right = left;
            while (gas[right] > cost[right]) {
                currCost += gas[right] - cost[right];
                right = (right + 1) % gasLen;
            }
            while (gas[right] < cost[right]) {
                currCost += gas[right] - cost[right];
                right = (right + 1) % gasLen;
            }
            right = (right - 1 + gasLen) % gasLen;
            
            // try to expand using two pointers
            // invariant: left at positive interval left, right at negative interval right
            while (((right + 1) % gasLen) != left) {
                if (currCost < 0) {
                    // find next left
                    left = (left - 1 + gasLen) % gasLen;
                    while (gas[left] < cost[left]) {
                        currCost += gas[left] - cost[left];
                        left = (left - 1 + gasLen) % gasLen;
                    }
                    while (gas[left] > cost[left]) {
                        currCost += gas[left] - cost[left];
                        left = (left - 1 + gasLen) % gasLen;
                    }
                    left = (left + 1) % gasLen;
                } else {
                    // find next right
                    right = (right + 1) % gasLen;
                    while (gas[right] > cost[right]) {
                        currCost += gas[right] - cost[right];
                        right = (right + 1) % gasLen;
                    }
                    while (gas[right] < cost[right]) {
                        currCost += gas[right] - cost[right];
                        right = (right + 1) % gasLen;
                    }
                    right = (right - 1 + gasLen) % gasLen;
                }
            }
            return left;
        }
    }
};