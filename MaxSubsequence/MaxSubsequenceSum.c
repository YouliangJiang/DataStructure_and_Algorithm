//
//  main.c
//  MaxSubsequenceSum
//
//  Created by Youliang Jiang on 8/20/20.
//  Copyright © 2020 Youliang Jiang. All rights reserved.
//

#include <stdio.h>

#define MAXSIZE 100000

int main(int argc, const char * argv[]) {
    unsigned int K,N;
    unsigned int i=0;
    int max=0,sum=0;
    int seq[MAXSIZE];
    
    printf("input sequence length:\n");
    scanf("%d", &K);
    N = K;
    printf("input sequence value:\n");
    while(N--){
        scanf("%d",&seq[i]);
        i++;
    }
    max = seq[0];
    for(i=0;i<K;i++){
        sum += seq[i];
        if(sum>max)
            max = sum;
        else if(sum<0)
            sum = 0;
    }
    printf("%d",max);
    return 0;
}
