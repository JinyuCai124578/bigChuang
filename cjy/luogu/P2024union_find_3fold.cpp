#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
// 三倍并查集
int find_father(int father_array[], int x) {

    if (father_array[x] == x) return x;
    return father_array[x] = find_father(father_array, father_array[x]); // 边找边更新!非常巧妙
}
int main() {
    int n, k;
    int ans=0;
    scanf("%d%d", &n, &k);
    int father[3*n+10];
    for (int i = 0; i < 3*n+10; ++i) {
        father[i] = i;
    }
    for (int i = 0; i < k; ++i) {
        int index,animal1,animal2;
        scanf("%d%d%d", &index, &animal1, &animal2);
        if (animal1>n||animal2>n) {ans++;continue;}
        if (index==2&&animal1==animal2) {ans++;continue;}
        if (index==1){
            if (
                find_father(father,animal1+n)==find_father(father,animal2)||
                find_father(father,animal2+n)==find_father(father,animal1)){
                    ans++;
                    continue;
                }
            father[find_father(father,animal1)]=find_father(father,animal2);
            father[find_father(father,animal1+n)]=find_father(father,animal2+n);
            father[find_father(father,animal1+2*n)]=find_father(father,animal2+2*n);
        }
        else if (index==2){
            if (
                find_father(father,animal1)==find_father(father,animal2)||
                find_father(father,animal2+2*n)==find_father(father,animal1)){
                    ans++;
                    continue;
                }
            father[find_father(father,animal2+n)]=find_father(father,animal1);
            father[find_father(father,animal2+2*n)]=find_father(father,animal1+n);
            father[find_father(father,animal2)]=find_father(father,animal1+2*n);
        }
    }
    printf("%d",ans);
    system("pause");
    return 0;
}