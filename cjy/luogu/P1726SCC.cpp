#include <bits/stdc++.h>
using namespace std;

class Graph{
    public:
    vector <vector<int>> g;
    vector <vector<int>> g_invert;
    int node_num;
    Graph(int n){
        node_num = n;
        g.resize(node_num+1);
        g_invert.resize(node_num+1);
    }
    void addEdge(int u, int v){
        g[u].push_back(v);
    }
    void addEdge_invert(int u, int v){
        g_invert[u].push_back(v);
    }
    void createGraph(int m){
        for (int i=0;i<m;i++){
            int a, b, t;
            scanf("%d %d %d", &a, &b, &t);
            if (t==1){
                addEdge(a, b);
                addEdge_invert(b, a);
            }
            if (t==2){
                addEdge(a, b);
                addEdge(b, a);
                addEdge_invert(a, b);
                addEdge_invert(b, a);
            }
        }
    }
    void explore_invert(int u,stack<int> &s, bool visited[]){
        visited[u] = true;
        for (int i=0;i<g_invert[u].size();i++){
            int v = g_invert[u][i];
            if (visited[v]) continue;
            explore_invert(v, s ,visited);
        } 
        s.push(u);
    }
    void explore(int u, int& cnt,vector <int> &scc_id,bool visited[]){
        visited[u] = true;
        scc_id.push_back(u);
        cnt++;
        for (int i=0;i<g[u].size();i++){
            int v = g[u][i];
            if (visited[v]) continue;
            explore(v, cnt, scc_id, visited);
        }
    }
    void findSCC (){
        bool* visited = new bool[node_num + 1]; 
        for (int i = 0; i <= node_num; i++) {
            visited[i] = false;
        }
        stack <int> s;
        for (int i=1;i<=node_num;i++){
            if (visited[i]) continue;
            explore_invert(i, s, visited);
        }
        delete[] visited;
        bool* visited2 = new bool[node_num + 1]; 
        for (int i = 0; i <= node_num; i++) {
            visited2[i] = false;
        }
        int max_scc_node_num=0;
        vector <int> max_scc_id;
        while (!s.empty()){
            int u = s.top();
            s.pop();
            if (visited2[u]) continue;
            int scc_node_num=0;
            vector <int> scc_id;
            explore(u, scc_node_num, scc_id,visited2);
            if (scc_node_num>max_scc_node_num){
                max_scc_node_num = scc_node_num;
                max_scc_id = scc_id;
            }
        }
        cout << max_scc_node_num << endl;
        sort(max_scc_id.begin(), max_scc_id.end());
        for (int i=0;i<max_scc_id.size();i++){
            if (i==max_scc_id.size()-1) cout << max_scc_id[i] ;
            else cout << max_scc_id[i] << " ";
        }
        delete[] visited2;
    }
};

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    Graph g(n);
    g.createGraph(m);
    g.findSCC();
    system("pause");
    return 0;
}