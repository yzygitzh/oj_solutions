/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: palsquare
LANG: C++
*/
/* LANG can be C++20 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

const char *digits = "0123456789ABCDEFGHIJK";

char num_by_base_result[100];
char reverse_result[100];

void num_by_base(int num, int base) {
    int i = 0;
    while (num) {
       num_by_base_result[i++] = digits[num % base];
       num /= base;
    }
    num_by_base_result[i] = '\0';
}

bool is_parlin() {
    int len = 0;
    while (num_by_base_result[len]) len++;
    int left = 0, right = len - 1;
    while (left + 1 < right) {
        if (num_by_base_result[left++] != num_by_base_result[right--]) return false;
    }
    if (left + 1 == right) {
        return num_by_base_result[left++] == num_by_base_result[right--];
    }
    return true;
}

void reverse_output() {
    int len = 0;
    while (num_by_base_result[len]) len++;
    for (int i = 0; i < len; i++) {
        reverse_result[i] = num_by_base_result[len - i - 1];
    }
    reverse_result[len] = '\0';
}

int main() {
    ofstream fout ("palsquare.out");
    ifstream fin ("palsquare.in");

    int N;
    fin >> N;

    for (int i = 1; i <= 300; i++) {
        num_by_base(i * i, N);
        if (is_parlin()) {
            num_by_base(i, N); 
            reverse_output();
            fout << reverse_result << " ";
            num_by_base(i * i, N); 
            fout << num_by_base_result << endl;
        }
    }

    return 0;
}

