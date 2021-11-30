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
    for(i=-1; i<g->vertexNum; i++){
        for(j=-1; j<g->vertexNum; j++){
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

void prim(PGraph g, PGraph tree){
    int i=0, j, k;
    int index;  // 指向权值最小的边
    ArrayNode edgeArray[MAX_VERTEX_NUM*2]; // 辅助数组
    int length = 0; // 数组长度
    int n = 1; // 统计数组已加入了多少个顶点
    // 初始状态把第一个顶点加入树中
    tree->vertex[0] = 'A';
    printf("%-3c", tree->vertex[0]);
    while(1){
        // 寻找与顶点i相接且这条边的另一个顶点不在树中的边，存入edgeArray数组中
        for(j=0; j<g->vertexNum; j++){
            if(g->arc[i][j]){
                // 判断这条边的另一个顶点在不在树中
                for(k=0; k<tree->vertexNum; k++){
                    if(tree->vertex[k] == g->vertex[j])
                        break;
                }
                if(k == tree->vertexNum){
                    edgeArray[length].from = i;
                    edgeArray[length].to = j;
                    edgeArray[length].weight = g->arc[i][j];
                    edgeArray[length].flag = 0;
                    length++;
                }
            }
        }
        // 从数组中选择权值最小的边
        index = -1;
        for(j=0; j<length; j++){
            if(index==-1 && edgeArray[j].flag==0)
                index = j;
            if(edgeArray[j].flag==0 && edgeArray[j].weight<edgeArray[index].weight)
                index = j;
        }
        // 在树中加入一个顶点，且把这条权值最小的边加入树中
        tree->vertex[edgeArray[index].to] = 'A' + edgeArray[index].to;
        edgeArray[index].flag = 1;
        tree->arc[edgeArray[index].from][edgeArray[index].to] = edgeArray[index].weight;
        tree->arc[edgeArray[index].to][edgeArray[index].from] = edgeArray[index].weight;
        // 当这个顶点加入树中时，与这个顶点相邻的边不可加入树中
        for(k=0; k<length; k++){
            if(edgeArray[k].to == edgeArray[index].to)
                edgeArray[k].flag = 1;
        }
        i = edgeArray[index].to;
        printf("%-3c", tree->vertex[i]);
        n++;
        // 当有g->vertexNum个顶点时，最小生成树构造完成
        if(n == g->vertexNum)
            break;
    }
    printf("\n");
}

int main(int argc, const char * argv[]) {
    
    Graph graph, tree;
    createGraph(&graph);
    initTree(&tree);
    printf("Prim's Sequence:\n");
    prim(&graph, &tree);
    
    return 0;
}
