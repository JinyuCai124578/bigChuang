#include <bits/stdc++.h>
using namespace std;

class Graph{
    public:
    vector <vector<int>> g;
    int node_num;
    vector <int> dfn;
    vector <int> low;
    vector <bool> visited;
    vector <vector<int>> scc;
    int scc_num;
    Graph(int n){
        node_num = n;
        scc_num = 0;
        g.resize(node_num+1);
        dfn.resize(node_num+1);
        low.resize(node_num+1);
        visited.resize(node_num+1);
        for (int i=0;i<=node_num;i++){
            visited[i] = false;
            dfn[i] = 0;
            low[i] = 0;
        }
    }
    void addEdge(int u, int v){
        g[u].push_back(v);
    }
    void createGraph(int m){
        for (int i=0;i<m;i++){
            int a, b, t;
            scanf("%d %d %d", &a, &b, &t);
            if (t==1){
                addEdge(a, b);
            }
            if (t==2){
                addEdge(a, b);
                addEdge(b, a);
            }
        }
    }
    void explore(int u,int& time,stack <int> &s,bool isInStack[]){
        dfn[u] = time;
        low[u] = time;
        time++;
        s.push(u);
        isInStack[u] = true;
        for (int i=0;i<g[u].size();i++){
            int v = g[u][i];
            if (!dfn[v]){ 
                explore(v,time,s,isInStack);
                low[u] = min(low[u], low[v]);//u的祖先是 u的祖先和v的祖先中更小的那个
            }
            else { 
                if (isInStack[v]){
                    low[u] = min(low[u], dfn[v]);//u的祖先是 u的祖先和v中更小的那个
                }
                
            }
        }
        if (dfn[u]==low[u]){//说明u是一个强连通分量的根
            vector <int> scc_temp;
            int v;
            do{
                v = s.top();
                s.pop();
                isInStack[v] = false;
                scc_temp.push_back(v);
            }while(v!=u);
            scc.push_back(scc_temp);
            scc_num++;
        }
    }
    void tarjan(){
        int time=0;
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
    }
    void find_max_SCC(){
        int max_size = 0;
        int max_index = 0;
        for (int i=0;i<scc.size();i++){
            if (scc[i].size()>max_size){
                max_size = scc[i].size();
                max_index = i;
            }
        }
        cout << max_size << endl;
        sort(scc[max_index].begin(), scc[max_index].end());
        for (int i=0;i<scc[max_index].size();i++){
            cout << scc[max_index][i] << " ";
        }
    }
};

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    Graph g(n);
    g.createGraph(m);
    g.tarjan();
    g.find_max_SCC();
    system("pause");
    return 0;
}