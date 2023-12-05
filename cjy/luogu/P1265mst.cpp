#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
struct edge {
    int v;
    double w;
};
struct position
{
    int x,y;
};
vector <position> pos;
vector <edge> g[5005];
bool visited[5005]={0};
void add_edge (int u, int v) {
    double w=0;
    // w=sqrt(pow((u.x-v.x),2)+pow((u.y-v.y),2));
    // w=sqrt(pow((pos[u].x-pos[v].x),2)+pow((pos[u].y-pos[v].y),2));
    g[u].push_back({v, w});
    g[v].push_back({u, w});
}
double get_distance (int u, int v) {
    return sqrt(pow((pos[u].x-pos[v].x),2)+pow((pos[u].y-pos[v].y),2));
}
void  add_edge_to_vec( vector<pair<double,int>> &vec, double w,int v,int n){
    if(w>=vec[n-1].first) return;
    for (int i=n-1;i>=0;i--){
        if(w<vec[i].first){
            continue;
        }
        if (w>=vec[i].first){
            vec.insert(vec.begin()+i+1, {w, v});
            vec.pop_back();
            cout<<w<<" "<<v<<" insert to "<<i+1<<endl;
            return;
        }
    }
    vec.insert(vec.begin(), {w, v});
    vec.pop_back();
    cout<<w<<" "<<v<<" insert to 0"<<endl;
    return;
}
int main () {
    int n;
    scanf("%d", &n);
    pos.resize(n+1);
    for (int i = 1; i <= n; ++i) {
        int xi,yi;
        scanf("%d %d", &xi, &yi);
        pos[i].x=xi;pos[i].y=yi;
    }
    priority_queue <pair <double, int> > q;
    vector < pair<double, int> > vec(n);
    for (int i=0;i<n;i++){
        vec[i].first=1e14;
    }
    // printf("vec init\n");
    add_edge_to_vec(vec, 0, 1, n);
    int cnt=1;
    double total_cost=0;
    while(cnt<=n){
        int u=vec[0].second;
        double cost_u=vec[0].first;
        vec.erase(vec.begin());
        vec.push_back({1e14, 0});
        if (visited[u]) continue;
        visited[u]=true;
        total_cost+=cost_u;
        
        for (int i=1;i<=n;i++){
            int v = i;
            if (visited[v]||u==v) continue;
            double w_uv = get_distance(u, v);
            if(!visited[v]){
                add_edge_to_vec(vec, w_uv, v, n);
            }
        }
        cnt++;
    }
    printf("%.2lf", total_cost);
    cout<<vec.size()<<endl;
    system("pause");
    return 0;
}