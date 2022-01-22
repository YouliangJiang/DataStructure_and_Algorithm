//
//  main.c
//  merge_sorting
//
//  Created by stephjiang on 2022/1/21.
//

#include <stdio.h>
#include <stdlib.h>

// A[low...mid]与A[mid+1...high]各自有序，将两个子列归并
void Merge(int A[], int low, int mid, int high){
    int i, j, k;
    int* B=(int*)malloc((high-low)*sizeof(int)); // helper array
    
    for(k=low; k<=high; k++)
        B[k] = A[k];    // 将A中所有元素复制到B中
    for(i=low, j=mid+1, k=i; i<=mid&&j<=high; k++){
        if(B[i]<=B[j])
            A[k] = B[i++];  // 将较小值复制到A中
        else
            A[k] = B[j++];
    }
    while(i<=mid)
        A[k++] = B[i++];
    while(j<=high)
        A[k++] = B[j++];
    
    free(B);
}

void MergeSort(int A[], int low, int high){
    if(low<high){
        int mid=(low+high)/2;   // 从中间划分
        MergeSort(A, low, mid); // 对左半部分归并排序
        MergeSort(A, mid+1, high);  // 对右半部分归并排序
        Merge(A, low, mid, high);   // 归并
    }
}

int main(int argc, const char * argv[]) {
    
    int a[10] = {3, 4, 5, 6, 7, 0, 1, 2, 9, 8};
    for(int i=0; i<10; i++)
        printf("%d ", a[i]);
    printf("\n");
    
    MergeSort(a, 0, 9);
    for(int i=0; i<10; i++)
        printf("%d ", a[i]);
    printf("\n");
    
    return 0;
}