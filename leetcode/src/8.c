int myAtoi(char* str) {
    int result = 0, minus_flag = 0, start_flag = 0, num_processed = 0;
    char *ptr = str;
    while (*ptr != '\0'){
        char char_digit = *ptr;
        if (!start_flag && char_digit == '-'){
            minus_flag = 1;
            start_flag = 1;
        }
        else if (!start_flag && char_digit == '+'){
            minus_flag = 0;
            start_flag = 1;
        }
        else if (!start_flag && (char_digit == ' ' || char_digit == '\t' || char_digit == '\n')) ;
        else if ('0' <= char_digit && '9' >= char_digit) {
            int tmp = result;
            start_flag = 1;
            num_processed = 1;
            for (int i = 1; i < 10; i++){
                result += tmp;
                if (tmp && ((int)(minus_flag == 1) ^ (int)(!!(result & (1 << 31)))))
                    return minus_flag ? -2147483648 : 2147483647;
            }
            tmp = minus_flag ? -(int)(char_digit - '0') : (int)(char_digit - '0');
            result += tmp;
            if (tmp && ((int)(minus_flag == 1) ^ (int)(!!(result & (1 << 31)))))
                return minus_flag ? -2147483648 : 2147483647;
        }
        else {
            if (num_processed)
                return result;
            else
                return 0;
        }
        ptr++;
    }
    return result;
}