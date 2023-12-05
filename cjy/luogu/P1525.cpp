#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int find_father(int father_array[], int x) {

    if (father_array[x] == x) return x;
    return father_array[x] = find_father(father_array, father_array[x]); // 边找边更新!非常巧妙
}
struct edge
{
    int criminal1, criminal2, rage;
    edge(int criminal1, int criminal2, int rage) : criminal1(criminal1), criminal2(criminal2), rage(rage) {}
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int father_array[2*n + 1];
    for (int i = 0; i <= 2*n; ++i) father_array[i] = i;
    vector <edge> edges;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        edges.push_back(edge(a, b, c));
    }
    sort(edges.begin(), edges.end(), [] (const edge &a, const edge &b) {return a.rage > b.rage;});
    for (int i = 0; i < m; ++i) {
        if (find_father(father_array, edges[i].criminal1) == find_father(father_array, edges[i].criminal2)){
            printf("%d",edges[i].rage);
            system("pause");
            return 0;
        }
        father_array[find_father(father_array, edges[i].criminal1)] = find_father(father_array, edges[i].criminal2+n);
        father_array[find_father(father_array, edges[i].criminal1+n)] = find_father(father_array, edges[i].criminal2);
    }
    printf("0");
    system("pause");
    return 0;

}