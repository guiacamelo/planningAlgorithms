#ifndef UNIONFIND_H
#define UNIONFIND_H

#include<vector>
using namespace std;
class UnionFind
{
private:
vector <int> p;
vector <int> rank;
// remember: vi is vector<int>

public:
     UnionFind(int N);
     int findSet(int i);
     bool isSameSet(int i, int j);
     void unionSet(int i, int j);
};

#endif // UNIONFIND_H
