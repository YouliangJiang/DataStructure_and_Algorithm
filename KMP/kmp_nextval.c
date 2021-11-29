//
//  main.c
//  kmp_nextval
//
//  Created by Youliang Jiang on 11/29/21.
//  Copyright © 2021 Youliang Jiang. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#define MAXLEN 255
typedef struct{
    char ch[MAXLEN];
    int length;
}SString;

void get_next(SString T, int next[]){
    
    int i=1, j=0;
    next[1] = 0;
    while(i<T.length){
        // 若数组下标从1开始，则判断的是T.ch[i]==T.ch[j]
        if(j==0 || T.ch[i-1]==T.ch[j-1]){
            ++i; ++j;
            // 若pi=pj，则next[j+1]=next[j]+1
            next[i] = j;
        }
        else
            j = next[j];
    }
}

void get_nextval(SString T, int* next, int* nextval){
    
    nextval[1] = 0;
    get_next(T, next);
    for(int j=2; j<=T.length; j++){
        if(T.ch[next[j]-1]==T.ch[j-1])
            nextval[j] = nextval[next[j]];
        else
            nextval[j] = next[j];
    }
}

/*
 S是主串，T是模式串
 */
int Index_KMP(SString S, SString T){
    
    int i=1, j=1;
    int next[T.length], nextval[T.length];
    
    get_nextval(T, next, nextval);
    while(i<=S.length && j<=T.length){
        // 若数组下标从1开始，则判断的是S.ch[i]==T.ch[j]
        if(j==0 || S.ch[i-1]==T.ch[j-1]){
            ++i;
            ++j;    // 继续比较后继字符
        }
        else
            j = nextval[j];    // 模式串向右移动
    }
    if(j>T.length)
        // 若数组下标从1开始，则return i-T.length
        return i-T.length-1;  // 匹配成功
    else
        return -1;
}

int main(int argc, const char * argv[]) {
    
    printf("main string: %s\n", argv[1]);
    // The correct format to print a size_t is %zu
    size_t main_len = strlen(argv[1]);
    printf("len of main string: %zu\n", main_len);
    printf("pattern string: %s\n", argv[2]);
    size_t pattern_len = strlen(argv[2]);
    printf("len of pattern string: %zu\n", pattern_len);
    if(pattern_len>main_len){
        printf("input format error.\n");
        return -1;
    }
    
    SString mainStr;
    strncpy(mainStr.ch, argv[1], main_len);
    mainStr.length = (int)main_len;
    
    SString patternStr;
    strncpy(patternStr.ch, argv[2], pattern_len);
    patternStr.length = (int)pattern_len;
    
    int next[MAXLEN];
    get_next(patternStr, next);
    printf("next array: ");
    for(int i=1; i<=pattern_len; i++){
        printf("%d ", next[i]);
    }
    printf("\n");
    
    int idx = Index_KMP(mainStr, patternStr);
    if(idx>=0)
        printf("the first pattern string is at: %d.\n", idx);
    else
        printf("no pattern string in the main string.");
    
    return 0;
}
