//
//  main.c
//  MST
//
//  Created by Youliang Jiang on 11/30/21.
//  Copyright © 2021 Youliang Jiang. All rights reserved.
//

#include <stdio.h>

#define MAX_VERTEX_NUM 20
// 邻接矩阵存储图
typedef struct{
    int vertexNum;
    int edgeNum;
    char vertex[MAX_VERTEX_NUM];
    int arc[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
}Graph, *PGraph;

// 辅助数组元素
typedef struct{
    int from;
    int to;
    int weight;
    int flag;
}ArrayNode;

void showGraph(PGraph g){
    
    for(int i=-1; i<g->vertexNum; i++){
        for(int j=-1; j<g->vertexNum; j++){
            if(i<0){
                if(j<0)
                    printf("%2c",' ');
                else
                    printf("%2c", 'A'+j);
            }
            else{
                if(j<0)
                    printf("%2c", 'A'+i);
                else
                    printf("%2d", g->arc[i][j]);
            }
        }
        printf("\n");
    }
}

// 构造无向网
/*
 *   A B C D E F
 * A 0 6 1 5 0 0
 * B 6 0 5 0 3 0
 * C 1 5 0 5 6 4
 * D 5 0 5 0 0 2
 * E 0 3 6 0 0 6
 * F 0 0 4 2 6 0
 */
void createGraph(PGraph g){
    int i, j;
    g->vertexNum = 6;
    g->edgeNum = 10;
    for(i=0; i<g->vertexNum; i++)
        g->vertex[i] = 'A' + i;
    for(i=0; i<g->vertexNum; i++)
        for(j=0; j<g->vertexNum; j++)
            g->arc[i][j]=0;
    g->arc[0][1] = 6; g->arc[0][2] = 1; g->arc[0][3] = 5;
    g->arc[1][0] = 6; g->arc[1][2] = 5; g->arc[1][4] = 3;
    g->arc[2][0] = 1; g->arc[2][1] = 5; g->arc[2][3] = 5; g->arc[2][4] = 6; g->arc[2][5] = 4;
    g->arc[3][0] = 5; g->arc[3][2] = 5; g->arc[3][5] = 2;
    g->arc[4][1] = 3; g->arc[4][2] = 6; g->arc[4][5] = 6;
    g->arc[5][2] = 4; g->arc[5][3] = 2; g->arc[5][4] = 6;
    
    printf("the adjacency matrix:\n");
    showGraph(g);
}

// 初始化最小生成树
void initTree(PGraph tree){
    int i, j;
    tree->vertexNum = 6;
    tree->edgeNum = 5;
    for(i=0; i<tree->vertexNum; i++)
        tree->vertex[i] = '0';
    for(i=0; i<tree->vertexNum; i++)
        for(j=0; j<tree->vertexNum; j++)
            tree->arc[i][j] = 0;
}

// 判断两个顶点是否连通（广度优先搜索）
int adjacent(PGraph tree, int from, int to){
    int i, j, k;
    int vertex[MAX_VERTEX_NUM]; // 队列
    int front, rear;
    if(from==to)
        return 1;
    front = rear = 0;
    // 把第一个顶点存入数组
    vertex[rear++] = from;
    // 遍历tree
    while (front<rear) {
        i = vertex[front];
        for(j=0; j<tree->vertexNum; j++)
            if(tree->arc[i][j]>0){
                if(j==to)
                    return 1;
                // 判断此顶点是否在队列中
                for(k=0; k<rear; k++)
                    if(vertex[k]==j)
                        break;
                if(k==rear)
                    vertex[rear++] = j;
            }
        front++;
    }
    return 0;
}

void kruskal(PGraph g, PGraph tree){
    ArrayNode edgeArray[MAX_VERTEX_NUM]; // 辅助数组
    int length = 0;
    int i, j, k, index, n;
    // 顶点先加入树中
    for(i=0; i<tree->vertexNum; i++)
        tree->vertex[i] = i+'A';
    // 1. 把所有的边有序（从小到大）的插入edgeArray数组中
    for(i=0; i<g->vertexNum; i++){
        for(j=0; j<g->vertexNum; j++){
            if(i<j && g->arc[i][j]>0){
                // 寻找插入的位置index
                for(k=0; k<length; k++){
                    if(edgeArray[k].weight>g->arc[i][j])
                        break;
                }
                index = k;
                // 移位
                for(k=length; k>index; k--)
                    edgeArray[k] = edgeArray[k-1];
                // 插入
                length++;
                edgeArray[index].flag = 0;
                edgeArray[index].from = i;
                edgeArray[index].to = j;
                edgeArray[index].weight = g->arc[i][j];
            }
        }
    }
    // 2. 从小到大取出n-1条边构造最小生成树
    n = 0;
    while (n<g->vertexNum-1) {
        // 从小到大取一条符合要求的边
        for(k=0; k<length; k++)
            if(edgeArray[k].flag==0 && adjacent(tree, edgeArray[k].from, edgeArray[k].to)==0)
                break;
        // 把这条边加入树中
        tree->arc[edgeArray[k].from][edgeArray[k].to] = edgeArray[k].weight;
        tree->arc[edgeArray[k].to][edgeArray[k].from] = edgeArray[k].weight;
        edgeArray[k].flag = 1;
        n++;
    }
    printf("the MST:\n");
    showGraph(tree);
    printf("\n");
}

int main(int argc, const char * argv[]) {
    
    Graph graph, tree;
    createGraph(&graph);
    initTree(&tree);
    
    kruskal(&graph, &tree);

    return 0;
}
