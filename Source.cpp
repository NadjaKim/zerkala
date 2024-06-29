#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

unsigned long long read_file(const char *filein) {
    FILE* fin = fopen(filein, "r");
    unsigned long long number, a = 0;
    if (fin) {
        if (fscanf(fin, "%llu", &number) < 1)
            return a;
        fclose(fin);
        return number;
    }
    return a;
}

unsigned long long make_mirror(unsigned long long source) {
    unsigned long long target = 0;
    int last_bit;
    for (int i = 0; i < 8; i++) {
        last_bit = source & 1;
        target = (target << (unsigned long long)1) | (unsigned long long)last_bit;
        source = source >> (unsigned long long)1;
    }
    return target;
}

void solution(unsigned long long number, const char* fileout) { 
    FILE* fout = fopen(fileout, "w");
    if (fout) {
        for (unsigned long long j = 1; j < number + 1; j++) {
            unsigned long long answer = 0;
            unsigned long long k = j, sdvig_for_tiv = -8, sdvig_for_target = -16;
            while (k > 0) {
                unsigned long long this_iteration_value = k % 256;
                k = k / 256;
                sdvig_for_tiv = sdvig_for_tiv + 16;
                sdvig_for_target = sdvig_for_target + 16;
                unsigned long long target = 0;
                target = make_mirror(this_iteration_value);
                answer = answer | (this_iteration_value << sdvig_for_tiv) | (target << sdvig_for_target);
            }
            fprintf(fout, "%llu ", answer);
        }
        fclose(fout);
    }
}

int main(int argc, char* argv[]) {
    if (argc == 3) {
        unsigned long long number;
        number = read_file(argv[1]);
        solution(number, argv[2]);
    }
    return 1;
}