#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
vector <int> g[10005];
int color[10005]= {0};
void explore(int u,int& cnt1,int& cnt2){
    for (int i=0;i<g[u].size();i++){
        int v=g[u][i];
        if (color[v]==0){
            color[v]=-color[u];
            if (color[v]==1){
                cnt1++;
            }
            else if (color[v]==-1){
                cnt2++;
            }
            explore(v,cnt1,cnt2);
        }
        else if (color[v]==color[u]){
            cout<<"Impossible"<<endl;
            system("pause");
            exit(0);
        }
        else if (color[v]==-color[u]){
            continue;
        }
    }
}
int dfs(int n){
    int cnt=0;
    for (int i=1;i<=n;i++){
        if (color[i]==0){
            color[i]=1;
            int cnt1=1,cnt2=0;
            explore(i,cnt1,cnt2);
            cnt+=min(cnt1,cnt2);
        }
    }
    return cnt;
}
int main(){
    int n,m;
    cin>>n>>m;
    for (int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cout<<dfs(n)<<endl;
    system("pause");
    return 0;
}