#include <bits/stdc++.h>
// 学会逆向思维 先看全部打击完之后的图，再逆着看，把边一条一条接起来
// 并查集思想 把node一个个不断合并，每个node 记录它的父节点，而不是记录他们的联通分量编号
// 用树的思想理解并查集
using namespace std;
typedef long long LL;
class Graph{
    public:
        vector <vector<int>> g;
        int node_num;
        int SCC_cnt;
        int destroy_cnt;
        stack<int> destroyed_node;
        vector<int> father;
        stack<int> SCC_record;
        Graph(int n){
            g.resize(n);
            destroy_cnt = 0;
            SCC_cnt = 0;
            node_num = n;
            for (int i = 0;i < n;++i){
                father.push_back(i);
            }
        };
        int find_father(int x){
            if (father[x] != x){
                return father[x]=find_father(father[x]);}
            return x;
        };
        void add_edge(int x, int y){
            g[x].push_back(y);
            g[y].push_back(x);
        };
        void dfs(){
            bool visited[node_num]={0};
            for (int i = 0; i < node_num; ++i){
                if (!visited[i]&&father[i] != -1){
                    explore(i,visited,i);
                    SCC_cnt++;
                }
            }
            SCC_record.push(SCC_cnt);
        };
        void explore(int x, bool visited[],int father_id){
            visited[x] = true;
            father[x] = father_id;
            for (int i = 0;i < g[x].size();++i){
                if (!visited[g[x][i]]&&father[g[x][i]] != -1){
                    explore(g[x][i],visited,father_id);
                }
            }
        };
        void destroy(int x){
            destroy_cnt++;
            destroyed_node.push(x);
            father[x] = -1;
        }
        void repair(){
            while (!destroyed_node.empty()){
                int x = destroyed_node.top();
                destroyed_node.pop();
                SCC_cnt++;father[x]=x;
                for (int i = 0;i < g[x].size();++i){
                    if (father[g[x][i]]==-1) continue;
                    if (find_father(g[x][i])!=find_father(x)){
                        srand((unsigned)time(NULL));//随机合并防止毒瘤出题人故意卡深度（自己都不知道会怎么并）
                            if(rand()%2){
                                father[find_father(x)]=find_father(g[x][i]);
                            }else{
                                father[find_father(g[x][i])]=find_father(x);
                            }
                        SCC_cnt--;
                    }
                }
                SCC_record.push(SCC_cnt);
            }
            while (!SCC_record.empty()){
                int SCC_num = SCC_record.top();
                SCC_record.pop();
                cout<<SCC_num<<endl;
            }
        }
        
};


int main(){
    int n,m;
    cin >> n >> m;
    Graph g(n);
    for (int i = 0;i < m;++i){
        int x,y;
        cin >> x >> y;
        g.add_edge(x,y);
    }
    int k;
    cin >> k;
    for (int i = 0;i < k;++i){
        int x;
        cin >> x;
        g.destroy(x);
    }
    g.dfs();
    g.repair();
    system("pause");
    return 0;
}