// 点双连通图：图中任意两不同点之间都有至少两条点不重复的路径;不存在割点的图
// 与强连通分量等不同，一个点可能属于多个点双，但是一条边属于恰好一个点双（如果定义采用前者则有可能不属于任何点双）。
// 在圆方树中，原来的每个点对应一个圆点，每一个点双对应一个方点。
#include <bits/stdc++.h>
using namespace std;

class Graph{
    public:
    vector <vector<int>> g;
    int node_num;
    vector <int> dfn;
    vector <int> low;
    vector <int> father_record;
    vector <vector<int>> scc;
    int center1,center2;
    priority_queue <int, vector<int>, greater<int> >  cut_node;
    int scc_num;
    Graph(int n){
        node_num = n;
        scc_num = 0;
        g.resize(node_num+1);
        dfn.resize(node_num+1);
        low.resize(node_num+1);
        father_record.resize(node_num+1);
        for (int i=0;i<=node_num;i++){
            dfn[i] = 0;
            low[i] = 0;
        }
    }
    void addEdge(int u, int v){
        g[u].push_back(v);
    }
    void createGraph(){
        while (true){
            int u,v;
            scanf("%d%d",&u,&v);
            if (u==0&&v==0) break;
            addEdge(u,v);
            addEdge(v,u);
        }
        int a,b;
        scanf("%d%d",&a,&b);
        center1 = a;
        center2 = b;
    }
    void explore(int u,int& time,stack <int> &s,bool isInStack[],int father=-1){
        dfn[u] = time;
        low[u] = time;
        time++;
        s.push(u);
        father_record[u] = father;
        isInStack[u] = true;
        for (int i=0;i<g[u].size();i++){
            int v = g[u][i];
            if (v==father) continue;
            if (!dfn[v]){ 
                explore(v,time,s,isInStack,u);
                low[u] = min(low[u], low[v]);//u的祖先是 u的祖先和v的祖先中更小的那个
                if(low[v]>=dfn[u]&&dfn[center2]>=dfn[v]&&u!=center1){//v无法回溯u之前的点，且center2在v的子树中，且u不是center1 表示断开u则center2无法回溯到前面的点
                    cut_node.push(u);
                }
            }
            else { 
                if (isInStack[v]){
                    low[u] = min(low[u], dfn[v]);//u的祖先是 u的祖先和v中更小的那个
                }
                
            }
        }
        

    }
    void find_PBCC(){
        int time=1;
        stack <int> s;
        bool* isInStack=new bool[node_num+1];
        for (int i=0;i<=node_num;i++){
            isInStack[i] = false;
        }
        explore(center1,time,s,isInStack);
        if(dfn[center2]==0){
            cout<<"No solution";
            return;
        }
        if(cut_node.size()==0){
            cout<<"No solution";
            return;
        }
        cout<<cut_node.top();
        return;
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
    int n;
    scanf("%d", &n);
    Graph g(n);
    g.createGraph();
    g.find_PBCC();
    system("pause");
    return 0;
}
