# DFS

## 框架

```c++
void dfs(参数) {
    if (终止条件) {
        存放结果;
        return;
    }
    for (选择：本节点所连接的其他节点) {
        处理节点;
        dfs(图，选择的节点); // 递归
        回溯，撤销处理结果
    }
}
```



## LeetCode

### 200.岛屿数量

```c++
class Solution {
public:
    bool isBoundary(vector<vector<char>>& grid, int x, int y){
        return (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size());
    }
    void dfs(vector<vector<char>>& grid, int x, int y){
        if(isBoundary(grid, x, y)){
            return;
        }
        if(grid[x][y] != '1'){
            return;
        }
        grid[x][y] = '2';
        dfs(grid, x + 1, y);
        dfs(grid, x, y + 1);
        dfs(grid, x - 1, y);
        dfs(grid, x, y - 1);
    }
    int numIslands(vector<vector<char>>& grid) {
        int ans = 0;
        for(int i = 0; i < grid.size(); ++ i){
            for(int j = 0; j < grid[0].size(); ++ j){
                if(grid[i][j] == '1'){
                    ans ++;
                    dfs(grid, i, j);
                }
            }
        }
        return ans;
    }
};
```

### 463.岛屿的周长

**岛屿的周长就是岛屿方格和非岛屿方格相邻的边的数量**。每当在 DFS 遍历中，从一个岛屿方格走向一个非岛屿方格，就将周长加 1。

```c++
class Solution {
public:
    int res = 0;
    bool isBoundary(vector<vector<int>>& grid, int x, int y){
        return (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size());
    } 
    void dfs(vector<vector<int>>& grid, int x, int y){
        if(isBoundary(grid, x, y)){
            res ++;
            return;
        }
        if(grid[x][y] == 0){
            res ++;
            return;
        }
        if(grid[x][y] == 2){
            return;
        }
        grid[x][y] = 2;
        dfs(grid, x + 1, y);
        dfs(grid, x, y + 1);
        dfs(grid, x, y - 1);
        dfs(grid, x - 1, y);
    }
    int islandPerimeter(vector<vector<int>>& grid) {
        for(int i = 0; i < grid.size(); ++ i){
            bool flag = 0;
            for(int j = 0; j < grid[0].size(); ++ j){
                if(grid[i][j] == 1){
                    dfs(grid, i, j);
                    flag = 1;
                    break;
                }
            }
            if(flag) break;
        }
        return res;
    }
};
```

官方题解：

```c++
class Solution {
    constexpr static int dx[4] = {0, 1, 0, -1};
    constexpr static int dy[4] = {1, 0, -1, 0};
public:
    int dfs(int x, int y, vector<vector<int>> &grid, int n, int m) {
        if (x < 0 || x >= n || y < 0 || y >= m || grid[x][y] == 0) {
            return 1;
        }
        if (grid[x][y] == 2) {
            return 0;
        }
        grid[x][y] = 2;
        int res = 0;
        for (int i = 0; i < 4; ++i) {
            int tx = x + dx[i];
            int ty = y + dy[i];
            res += dfs(tx, ty, grid, n, m);
        }
        return res;
    }
    int islandPerimeter(vector<vector<int>> &grid) {
        int n = grid.size(), m = grid[0].size();
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1) {
                    ans += dfs(i, j, grid, n, m);
                }
            }
        }
        return ans;
    }
};
```

### 695.岛屿的最大面积

```c++
class Solution {
public:
    int res = 0;
    bool isBoundary(vector<vector<int>>& grid, int x, int y){
        return (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size());
    }
    void dfs(vector<vector<int>>& grid, int x, int y, int &area){
        if(isBoundary(grid, x, y)){
            return;
        }
        if(grid[x][y] != 1){
            return;
        }
        grid[x][y] = 2;
        area ++;
        dfs(grid, x, y + 1, area);
        dfs(grid, x, y - 1, area);
        dfs(grid, x - 1, y, area);
        dfs(grid, x + 1, y, area);
    }
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        for(int i = 0; i < grid.size(); ++ i){
            for(int j = 0; j < grid[0].size(); ++ j){
                if(grid[i][j] == 1){
                    int area = 0;
                    dfs(grid, i, j , area);
                    if(area > res){
                        res = area;
                    }
                }
            }
        }
        return res;
    }
};
```

