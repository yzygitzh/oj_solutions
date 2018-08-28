/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: dualpal
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

void num_by_base(long num, long base) {
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

int main() {
    ofstream fout ("dualpal.out");
    ifstream fin ("dualpal.in");

    long N, S;
    fin >> N >> S;

    int hit_count = 0;
    for (long i = 1; hit_count < N; i++) {
        int pal_count = 0;
        for (long j = 2; j <= 10; j++) {
            num_by_base(S + i, j);
            if (is_parlin()) {
                pal_count++;
                if (pal_count == 2) {
                    fout << S + i << endl;
                    hit_count++;
                    break;
                }
            }
        }
    }

    return 0;
}

