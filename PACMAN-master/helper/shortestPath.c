#include <stdio.h>
#define NODENUM 36
// 57 edges
/*
1  2  9 2 3
1  3  5 1 3
1  4  8 0 3
2  3  4 0 2
3  4  3 0 2
3  9  3 1 3
9 14  2 1 3
2 14  9 1 2
4  5  6 0 2
5 32 12 3 1
5  6  6 0 2
5 10  3 1 3
6  8 14 3 2
8 17 15 3 3
6  7  4 0 2
7  8  6 0 1
7 13  3 1 3
6 12  3 1 3
10 11  3 0 2
11 12  3 0 2
13 16  2 1 3
12 16  6 1 2
13 17  8 0 2
9 15  8 0 2
10 15  5 2 3
11 19  4 1 3
15 18  2 1 3
18 21  2 1 3
18 19  6 0 2
14 20  4 0 2
19 26  4 1 3
16 22  4 1 3
17 23  4 1 3
20 24  2 1 3
24 21  8 0 2
20 29  9 2 3
24 30  3 1 3
29 30  4 0 2
29 35  9 1 2
30 35  5 1 3
31 35  8 1 0
30 31  3 0 2
31 32  6 0 2
21 25  5 1 2
25 26  3 0 2
25 32  3 1 3
32 33  6 0 2
26 27  3 0 2
22 27  6 2 3
22 28  2 1 3
27 33  3 1 3
33 34  4 0 2
28 34  3 1 3
33 36 14 1 2
23 36 15 1 1
34 36  6 0 3
23 28  8 2 0
*/

int find_closet_vertex_on_shortest_path(int src, int dst, int intermediate[NODENUM][NODENUM]){
    if (intermediate[src][dst] == -1) return dst;
    return find_closet_vertex_on_shortest_path(src, intermediate[src][dst], intermediate);
}
int find_dir_node(int wtfDir, int node, int dir[NODENUM][NODENUM]){
    for (int i = 0; i < NODENUM; i++){
        if (dir[node][i] == wtfDir){
            return i;
        }
    }
    return -1;
}
int main(){
    
    int adjma[NODENUM][NODENUM];
    int intermediate[NODENUM][NODENUM];
    int dir[NODENUM][NODENUM];
    FILE* fp = fopen("./shortestPathInfo.txt", "w");

    for (int i = 0; i < NODENUM; i++){
        for (int j = 0; j < NODENUM; j++){
            adjma[i][j] = -1;
            intermediate[i][j] = -1;
            dir[i][j] = -1;
        }
    }
        
            
    for (int i = 0; i < NODENUM; i++){
        adjma[i][i] = 0;
        intermediate[i][i] = -1;
    }
        

    int p1, p2, w, dir122, dir221;
    while (scanf("%d%d%d%d%d", &p1, &p2, &w, &dir122, &dir221) != EOF){
        adjma[p1-1][p2-1] = w;
        adjma[p2-1][p1-1] = w;
        dir[p1-1][p2-1] = dir122;
        dir[p2-1][p1-1] = dir221;
    }
    
    // Floyd-Warshall
    for (int k = 0; k < NODENUM; k++){
        for (int i = 0; i < NODENUM; i++){
            for (int j = 0; j < NODENUM; j++){
                if ((adjma[i][k] != -1 && adjma[k][j] != -1) && ((adjma[i][j] == -1) || (adjma[i][j] > adjma[i][k] + adjma[k][j]))){
                    adjma[i][j] = adjma[i][k] + adjma[k][j];
                    intermediate[i][j] = k;
                }
            }
        }
    }

    /* fprintf(fp, "path length\n");
    for (int i = 0; i < NODENUM; i++){
        for (int j = 0; j < NODENUM; j++){
            fprintf(fp, "%2d ", adjma[i][j]);
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "path intermediate\n");
    for (int i = 0; i < NODENUM; i++){
        for (int j = 0; j < NODENUM; j++){
            fprintf(fp, "%2d ", intermediate[i][j]);
        }
        fprintf(fp, "\n");
    } */
    fprintf(fp, "closet path direction\n");
    for (int i = 0; i < NODENUM; i++){
        fprintf(fp, "let ptrs[%2d] = Draw.map_row_generator(", i);
        for (int j = 0; j < NODENUM; j++){
            if (j != NODENUM - 1)
                fprintf(fp, "%2d, ", dir[i][find_closet_vertex_on_shortest_path(i, j, intermediate)]);
            else
                fprintf(fp, "%2d", dir[i][find_closet_vertex_on_shortest_path(i, j, intermediate)]);
        }
        fprintf(fp, ");\n");
    }
    fprintf(fp, "each node path\n");
    
    for (int i = 0; i < NODENUM; i++){
        fprintf(fp, "let ptrs[%2d] = array_set_helper(", i);
        for (int j = 0; j < 4; j++){
            if (j != 3)
                fprintf(fp, "%d, ", find_dir_node(j, i, dir));
            else
                fprintf(fp, "%d);\n", find_dir_node(j, i, dir));
        }
    }
    fclose(fp);

    return 0;
}