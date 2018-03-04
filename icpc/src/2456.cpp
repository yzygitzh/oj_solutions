/*
 * ICPC 2456 - Library
 *
 * NOTE: When a shelf is fully cut, it's considered as being removed.
 */

#include <cstdio>
#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;

int XN, YN, XT, YT;
int shelfNum;

struct Shelf {
    int yi, xi, li, x1i, x2i;
} shelves[110];

struct Result {
    int pegNum, plankLen;
};

int countLeftMost(int idx) {
    Shelf shelf = shelves[idx];
    int leftPeg = shelf.xi + shelf.x2i - shelf.li;
    int leftCenter = shelf.xi - ((int)(shelf.li / 2) - shelf.x1i); // less than half if .5
    int leftMost = leftPeg > leftCenter ? leftPeg : leftCenter;
    return leftMost > 0 ? leftMost : 0;
}

int countRightMost(int idx) {
    Shelf shelf = shelves[idx];
    int rightPeg = shelf.xi + shelf.x1i + shelf.li;
    int rightCenter = shelf.xi + shelf.li + (shelf.x2i - (int)((shelf.li + 1) / 2)); // more than half if .5
    int rightMost = rightPeg < rightCenter ? rightPeg : rightCenter;
    return rightMost < XN ? rightMost : XN;
}

Result findBestLoad(int idx, int bookPos) {
    Result bestResult;
    bestResult.pegNum = bestResult.plankLen = 10000000;
    Shelf shelf = shelves[idx];
    // not enough length
    if (shelf.li < XT) {
        bestResult.pegNum = bestResult.plankLen = -1;
        return bestResult;
    }
    // no peg movement
    if (countLeftMost(idx) <= bookPos && countRightMost(idx) >= bookPos + XT) {
        bestResult.pegNum = bestResult.plankLen = 0;
        return bestResult;
    }
    // move peg
    if (shelf.xi + shelf.x1i - shelf.li <= bookPos &&
        shelf.xi + shelf.x2i + shelf.li >= bookPos + XT) {
        bestResult.pegNum = 1;
        bestResult.plankLen = 0;
        return bestResult;
    }
    // move peg && cut plank: no need
    // cannot load: not possible
    bestResult.pegNum = bestResult.plankLen = -1;
    return bestResult;
}

Result findBestAvoid(int idx, int bookPos) {
    Result bestResult;
    bestResult.pegNum = bestResult.plankLen = 10000000;
    Shelf shelf = shelves[idx];
    if (countLeftMost(idx) + shelf.li <= bookPos ||
        // no cut: [leftMost, rightMost] doesn't hit the book
        countRightMost(idx) - shelf.li >= bookPos + XT) {
        bestResult.pegNum = bestResult.plankLen = 0;
        return bestResult;
    } else if (shelf.xi + shelf.x2i <= bookPos) {
        // cut plank: right peg < bookPos or leftpeg > bookPos + XT
        // NOTE: after the cut, the leftMost no longer holds!
        bestResult.pegNum = 0;
        int balancedLen = 2 * (bookPos - (shelf.xi + shelf.x1i));
        int simpleCutLen = bookPos - countLeftMost(idx);
        if (balancedLen < simpleCutLen)
            bestResult.plankLen = shelf.li - balancedLen;
        else
            bestResult.plankLen = shelf.li - simpleCutLen;
        return bestResult;
    } else if (shelf.xi + shelf.x1i >= bookPos + XT) {
        // cut plank: leftpeg > bookPos + XT
        bestResult.pegNum = 0;
        int balancedLen = 2 * ((shelf.xi + shelf.x2i) - (bookPos + XT));
        int simpleCutLen = countRightMost(idx) - (bookPos + XT);
        if (balancedLen < simpleCutLen)
            bestResult.plankLen = shelf.li - balancedLen;
        else
            bestResult.plankLen = shelf.li - simpleCutLen;
        return bestResult;
    } else if (shelf.xi + shelf.x1i <= bookPos && bookPos >= shelf.li ||
               shelf.xi + shelf.x2i >= bookPos + XT && bookPos + XT + shelf.li <= XN) {
        // move peg: right peg turn out to be >= bookPos;
        //           left peg <= bookPos. vice versa. enough room for book.
        bestResult.pegNum = 1;
        bestResult.plankLen = 0;
        return bestResult;
    } else if (shelf.xi + shelf.x1i <= bookPos || shelf.xi + shelf.x2i >= bookPos + XT) {
        // move peg && cut plank: right peg turn out to be >= bookPos, and
        //                        no enough room for book.
        bestResult.pegNum = 1;
        int leftLen = 100000000, rightLen = 100000000;
        if (shelf.xi + shelf.x1i <= bookPos)
            leftLen = shelf.li - bookPos;
        if (shelf.xi + shelf.x2i >= bookPos + XT)
            rightLen = shelf.li - (XN - (bookPos + XT));
        bestResult.plankLen = leftLen < rightLen ? leftLen : rightLen;
        if (bestResult.plankLen < shelf.li)
            return bestResult;
    }
    // remove all
    bestResult.pegNum = 2;
    bestResult.plankLen = shelf.li;
    return bestResult;
}

Result findBestSolution() {
    Result bestResult, currResult, tmpResult;
    bestResult.pegNum = bestResult.plankLen = 100000000;

    for (int i = 0; i < shelfNum; i++) {
        // book breaks the niche top
        if (YN - shelves[i].yi < YT) continue;
        // book too wide, cannot be loaded
        if (XT > shelves[i].li) continue;

        for (int j = 0; j <= XN - XT; j++) {
            currResult.pegNum = currResult.plankLen = 0;

            tmpResult = findBestLoad(i, j);
            if (tmpResult.pegNum < 0) continue;
            currResult.pegNum += tmpResult.pegNum;
            currResult.plankLen += tmpResult.plankLen;

            for (int k = 0; k < shelfNum; k++) {
                // shelf k is under the book
                if (shelves[k].yi <= shelves[i].yi) continue;
                // shelf k is higher than the book
                if (shelves[k].yi >= shelves[i].yi + YT) continue;
                tmpResult = findBestAvoid(k, j);
                currResult.pegNum += tmpResult.pegNum;
                currResult.plankLen += tmpResult.plankLen;
            }

            if (currResult.pegNum < bestResult.pegNum ||
                currResult.pegNum == bestResult.pegNum &&
                currResult.plankLen < bestResult.plankLen)
                bestResult = currResult;
        }
    }
    return bestResult;
}

int main() {
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--) {
        scanf("%d%d%d%d", &XN, &YN, &XT, &YT);
        scanf("%d", &shelfNum);
        for (int i = 0; i < shelfNum; i++) {
            scanf("%d%d%d%d%d",
                  &shelves[i].yi,
                  &shelves[i].xi,
                  &shelves[i].li,
                  &shelves[i].x1i,
                  &shelves[i].x2i);
        }
        Result result = findBestSolution();
        printf("%d %d\n", result.pegNum, result.plankLen);
        if (caseNum) printf("\n");
    }
    return 0;
}
