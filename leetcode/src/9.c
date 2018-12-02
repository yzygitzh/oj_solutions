bool isPalindrome(int x) {
    int num_width = 0;
    
    if (x < 0)
        return false;
    else if (x == 0)
        return true;
    else {
        int tmp = x;
        while (tmp){
            tmp /= 10;
            num_width++;
        }
        while (num_width > 1){
            int minus_up = 1;
            for (int i = 1; i < num_width; i++)
                minus_up *= 10;
            if (x / minus_up == (x - x / 10 * 10)){
                x -= (x / minus_up * minus_up) + (x - x / 10 * 10);
                x /= 10;
                num_width -= 2;
            }
            else
                return false;
        }
        return true;
    }
}