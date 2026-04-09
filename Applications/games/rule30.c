#include <stdio.h>
#include <stdint.h>
#include <string.h>  // Add this

#define N 40
#define N_ITER 24

int rule30(int x1, int x2, int x3) {
    return !((x1 & (x2 | x3)) | (!x1 & !x2 & !x3));
}

int main(){
    int i;
    int k;

    int r1[N];
    int r2[N];

    int *p1;
    int *p2;
    int *temp;

    // Initialize arrays to zero
    memset(r1, 0, sizeof(r1));
    memset(r2, 0, sizeof(r2));

    p1 = &r1[0];
    p2 = &r2[0];

    r1[N/2] = 1;

    for (k=1; k<N_ITER; k++) {
        for (i=1; i<N-1; i++) {
            printf("%s ", *(p1+i) ? "#" : ".");
            *(p2+i) = rule30(*(p1+i-1), *(p1+i), *(p1+i+1));
        }
        printf("\n");
        temp = p1;
        p1 = p2;
        p2 = temp;
    }

    return 0;
}
