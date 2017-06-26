#include "unionfind.h"
//algorithm from book competitivwe programing 3
UnionFind::UnionFind(int N)
{
    rank.assign(N, 0);
    p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i;

}
int UnionFind::findSet(int i) {
    return (p[i] == i) ? i : (p[i] = findSet(p[i]));
}
bool UnionFind::isSameSet(int i, int j) {
    return findSet(i) == findSet(j);
}
void UnionFind::unionSet(int i, int j) {
    if (!isSameSet(i, j)) {
        // if from different set
        int x = findSet(i), y = findSet(j);
        if (rank[x] > rank[y]) p[y] = x;
        // rank keeps the tree short
        else {
            p[x] = y;
            if (rank[x] == rank[y]) rank[y]++; }
    }
}
