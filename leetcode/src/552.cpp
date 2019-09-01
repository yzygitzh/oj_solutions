class Solution {
public:
    void addMod(int& target, int delta) {
        target += delta;
        target %= 1000000007;
    }
    
    int checkRecord(int n) {
        // "A", "L", "P"
        if (n == 1) {
            return 3;
        }
        // recordNum: number of records ends with "XX"
        // recordNum[0]: 0 A, recordNum[1]: 1 A
        int recordNum[2][8] = {0};
        
        int IDX_LL = 0;
        int IDX_PL = 1;
        int IDX_LP = 2;
        int IDX_PP = 3;
        int IDX_AL = 4;
        int IDX_AP = 5;
        int IDX_LA = 6;
        int IDX_PA = 7;
        
        recordNum[0][IDX_LL] = 1;
        recordNum[0][IDX_PL] = 1;
        recordNum[0][IDX_LP] = 1;
        recordNum[0][IDX_PP] = 1;
        
        recordNum[1][IDX_LL] = 0;
        recordNum[1][IDX_PL] = 0;
        recordNum[1][IDX_LP] = 0;
        recordNum[1][IDX_PP] = 0;
        recordNum[1][IDX_AL] = 1;
        recordNum[1][IDX_AP] = 1;
        recordNum[1][IDX_LA] = 1;
        recordNum[1][IDX_PA] = 1;
        
        for (int i = 3; i <= n; i++) {
            int LL0 = 0;
            addMod(LL0, recordNum[0][IDX_PL]);
            int LP0 = LL0;
            addMod(LP0, recordNum[0][IDX_LL]);
            int LA1 = LP0;
            
            int LL1 = 0;
            addMod(LL1, recordNum[1][IDX_AL]);
            addMod(LL1, recordNum[1][IDX_PL]);
            int LP1 = LL1;
            addMod(LP1, recordNum[1][IDX_LL]);

            int PL0 = 0;
            addMod(PL0, recordNum[0][IDX_LP]);
            addMod(PL0, recordNum[0][IDX_PP]);
            int PP0 = PL0;
            int PA1 = PP0;

            int PL1 = 0;
            addMod(PL1, recordNum[1][IDX_LP]);
            addMod(PL1, recordNum[1][IDX_PP]);
            addMod(PL1, recordNum[1][IDX_AP]);
            int PP1 = PL1;
            
            int AL1 = 0;
            addMod(AL1, recordNum[1][IDX_LA]);
            addMod(AL1, recordNum[1][IDX_PA]);
            int AP1 = AL1;
            
            recordNum[0][IDX_LL] = LL0;
            recordNum[0][IDX_PL] = PL0;
            recordNum[0][IDX_LP] = LP0;
            recordNum[0][IDX_PP] = PP0;

            recordNum[1][IDX_LL] = LL1;
            recordNum[1][IDX_PL] = PL1;
            recordNum[1][IDX_LP] = LP1;
            recordNum[1][IDX_PP] = PP1;
            recordNum[1][IDX_AL] = AL1;
            recordNum[1][IDX_AP] = AP1;
            recordNum[1][IDX_LA] = LA1;
            recordNum[1][IDX_PA] = PA1;
        }
        int result = 0;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 8; j++)
                addMod(result, recordNum[i][j]);
        }
        return result;
    }
};