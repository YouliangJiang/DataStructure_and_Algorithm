//
//  main.c
//  merge_sorting
//
//  Created by stephjiang on 2022/1/21.
//

#include <stdio.h>
#include <stdlib.h>

void MergeSort(int* A, int length){
    
    int i, left_min, left_max, right_min, right_max, next;
    int *B = (int*)malloc(sizeof(int) * length);
    
    if (B == NULL){
        fputs("Error: out of memory\n", stderr);
        abort();
    }
    
    for (i = 1; i < length; i *= 2){ // i为步长，1,2,4,8……
        
        for(left_min = 0; left_min < length - i; left_min = right_max){
            
            right_min = left_max = left_min + i;
            right_max = left_max + i;
            
            if(right_max > length)
                right_max = length;
            
            next = 0;
            while(left_min < left_max && right_min < right_max)
                B[next++] = A[left_min] > A[right_min] ? A[right_min++] : A[left_min++];
            while(left_min < left_max)
                A[--right_min] = A[--left_max];
            while(next>0)
                A[--right_min] = B[--next];
        }
    }
    
    free(B);
}

int main(int argc, const char * argv[]) {

    int a[10] = {3, 4, 5, 6, 7, 0, 1, 2, 9, 8};
    for(int i=0; i<10; i++)
        printf("%d ", a[i]);
    printf("\n");

    MergeSort(a, 10);
    for(int i=0; i<10; i++)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}