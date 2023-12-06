## 拓扑排序
### P1038
```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
class Graph{
    public:
    int n;
    vector <vector <pair<int,int>>> g;
    vector <vector <pair<int,int>>> g_invert;
    vector <int> initial_state;
    vector <int> threshold;
    int* finish_time;
    bool has_output=false;
    Graph(int node_num,int edge_num){
            n=node_num;
            finish_time=new int[node_num+1]{0};
            g.resize(node_num+1);
            g_invert.resize(node_num+1);
            initial_state.resize(node_num+1,0);
            threshold.resize(node_num+1,0);
            for(int i=1;i<=node_num;++i){
                int initial_s,thres;
                scanf("%d%d",&initial_s,&thres);
                initial_state[i]=initial_s;
                threshold[i]=thres;
            }
            for (int i=1;i<=edge_num;++i){
                int u,v,w;
                scanf("%d%d%d",&u,&v,&w);
                g[u].push_back({v,w});
                g_invert[v].push_back({u,w});
            }
        };
    void dfs(int u,int& current_time){
        for (int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i].first, w = g[u][i].second;
            if (finish_time[v]==0) {
                dfs(v, current_time);
            }
        }
        finish_time[u]=current_time;
        current_time++;
    }
    void renew_state(int u,vector <pair<int,int>>& last_layer_node){
        int renewed_state=initial_state[u];
        for (int i = 0; i < g_invert[u].size(); ++i) {
            int v = g_invert[u][i].first, w = g_invert[u][i].second;
            renewed_state+=initial_state[v]*w;

        }
        renewed_state-=threshold[u];
        initial_state[u]=renewed_state>0?renewed_state:0;
        // printf("renewing:%d %d\n",u,renewed_state);
        if (renewed_state>=0&&g[u].size()==0) {
            last_layer_node.push_back({u,renewed_state});
            // printf("last layer:%d %d\n",u,renewed_state);
        }

    }
    void topo_sort_and_renew_state(){
        vector <pair<int,int>> topo_sort_node;
        int time=1;
        for (int i=1;i<=n;++i){
            if (finish_time[i]==0){
                dfs(i,time);
            }
        }
        for (int i=1;i<=n;++i){
            topo_sort_node.push_back({finish_time[i],i});
        }
        sort(topo_sort_node.begin(),topo_sort_node.end(),[](pair<int,int> a,pair<int,int> b){return a.first>b.first;});
        vector <pair<int,int>> last_layer_node;
        for (int i=0;i<topo_sort_node.size();++i){
            int u=topo_sort_node[i].second;
            renew_state(u,last_layer_node);
        }
        sort(last_layer_node.begin(),last_layer_node.end(),[](pair<int,int> a,pair<int,int > b){return a.first<b.first;});
        if (last_layer_node.size()==0) printf("NULL");
        else{
            for (int i=0;i<last_layer_node.size();++i){
                printf("%d %d\n",last_layer_node[i].first,last_layer_node[i].second);
            }
        }
    }
};
int main(){
    int node_num,edge_num;
    scanf("%d%d",&node_num,&edge_num);
    Graph g(node_num,edge_num);
    g.topo_sort_and_renew_state();
    system("pause");
    return 0;
}
```