// 边双连通图：不存在割边的图
#include <bits/stdc++.h>
using namespace std;

class Graph{
    public:
    int node_num;
    int service_a_num;
    int service_b_num;
    vector <vector<int>> g;
    vector <int> acc_to_a;
    vector <int> acc_to_b;
    vector <int> dfn;
    vector <int> low;
    vector <pair<int,int>> critical_edge;
    vector <vector<int>> scc;
    int scc_num;
    Graph(){
        int n,m,k,l;
        scanf("%d%d%d%d",&n,&m,&k,&l);
        node_num = n;
        service_a_num = k;
        service_b_num = l;
        g.resize(node_num+1);
        dfn.resize(node_num+1);
        low.resize(node_num+1);
        acc_to_a.resize(node_num+1);
        acc_to_b.resize(node_num+1);
        for (int i=0;i<=node_num;i++){
            dfn[i] = 0;
            low[i] = 0;
            acc_to_a[i]=0;
            acc_to_b[i]=0;
        }
        for (int i=0;i<k;i++){
            int a;
            scanf("%d",&a);
            acc_to_a[a] = 1;
        }
        for (int i=0;i<l;i++){
            int b;
            scanf("%d",&b);
            acc_to_b[b] = 1;
        }
        for (int i=0;i<m;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            add_ndir_Edge(u,v);
        }
    }
    void add_ndir_Edge(int u, int v){
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void explore(int u,int& time,stack <int> &s,bool isInStack[],int father=-1){
        dfn[u] = time;
        low[u] = time;
        time++;
        s.push(u);
        for (int i=0;i<g[u].size();i++){
            int v = g[u][i];
            if (v==father) continue;
            if (!dfn[v]){ 
                explore(v,time,s,isInStack,u);
                low[u] = min(low[u], low[v]);//u的祖先是 u的祖先和v的祖先中更小的那个
                acc_to_a[u] = acc_to_a[u]+acc_to_a[v];
                acc_to_b[u] = acc_to_b[u]+acc_to_b[v];
            }
            else { 
                    low[u] = min(low[u], dfn[v]);//u的祖先是 u的祖先和v中更小的那个
                
            }
        }
        for (int i=0;i<g[u].size();i++){
            int v = g[u][i];
            if (v==father) continue;
            if (low[v]>dfn[u]&&(!acc_to_a[v]||!acc_to_b[v]||acc_to_a[v]==service_a_num||acc_to_b[v]==service_b_num)){ 
                //不能用!acc_to_a[u]来判断，因为u可能有 多个 有service的子树，断了一条边不会发生什么，但acc_to_a[u]==0。所以用v的子树包含了所有的service结点来判断
                critical_edge.push_back(make_pair(u,v));
            }
        }
        

    }
    void find_EBCC(){
        int time=1;
        stack <int> s;
        bool* isInStack=new bool[node_num+1];
        for (int i=0;i<=node_num;i++){
            isInStack[i] = false;
        }
        for (int i=1;i<=node_num;i++){
            if (!dfn[i]){
                explore(i,time,s,isInStack);
            }
        }
        delete[] isInStack;
        printf("%d\n",critical_edge.size());
        for (int i=0;i<critical_edge.size();i++){
            printf("%d %d\n",critical_edge[i].first,critical_edge[i].second);
        }
        return;
    }
};

int main(){
    Graph g;
    g.find_EBCC();
    system("pause");
    return 0;
}
