int reverse(int x) {
    int output = 0;
    
    if (x == 0)
        return 0;
    
    if (x > 0)
        while (x != 0){
            int tmp = output;
            for (int i = 0; i < 9; i++){
                tmp += output;
                if (output != 0 && (tmp & (1 << 31)))
                    return 0;
            }
            output = tmp;
            output += (x - (x / 10) * 10);
            if ((x - (x / 10) * 10) && (output & (1 << 31)))
                return 0;
            x /= 10;
        }
    else
        while (x != 0){
            int tmp = output;
            for (int i = 0; i < 9; i++){
                tmp += output;
                if (output && !(tmp & (1 << 31)))
                    return 0;
            }
            output = tmp;
            output += (x - (x / 10) * 10);
            if ((x - (x / 10) * 10) && !(output & (1 << 31)))
                return 0;
            x /= 10;
        }
    
    return output;
}