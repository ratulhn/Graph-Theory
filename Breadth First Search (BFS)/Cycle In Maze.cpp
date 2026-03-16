#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> 
using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; // find_by_order, order_of_key

#define FastIO ios::sync_with_stdio(false);cin.tie(nullptr);
#define dbg(v) cout << "Line(" << __LINE__ << ") -> " << #v << " = " << (v) << "\n";
//#include "dbgtest.h"
#define ll long long
#define all(v) v.begin(),v.end()
#define nl cout<<'\n'
#define lp(i,a,n) for(int i=a; i<n; i++)

const int M = 1e9+7;


const int N=1005;
char ch[N][N];
int dis[N][N];
int dir[4]={'D','L','R','U'};
int dx[4]= {1,0,0,-1};
int dy[4]= {0,-1,1,0};
int tx,ty;

void bfs(int x, int y) {
    queue<pair<int,int>>q;
    q.push({x,y});
    memset(dis,-1,sizeof(dis));
    dis[x][y]=0;
    while(!q.empty()) {
        auto &[a,b]=q.front(); q.pop();
        for(int i=0; i<4; i++) {
            tx=a+dx[i];
            ty=b+dy[i];
            if(ch[tx][ty]=='.'&&dis[tx][ty]==-1) {
                dis[tx][ty]=dis[a][b]+1;
                q.push({tx,ty});
            }
        }
    }
}



void solve() {

    int n,m,k; cin>>n>>m>>k;
    int sx,sy;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            cin>>ch[i][j];
            if(ch[i][j]=='X') {
                ch[i][j]='.';
                sx=i,sy=j;
            }
        }
    }
    if(k%2) {
        cout << "IMPOSSIBLE\n"; return;
    }
    bfs(sx,sy);
    string ans;
    while(k>0) {
        bool flag=true;
        for(int i=0; i<4; i++) {
            tx=sx+dx[i];
            ty=sy+dy[i];
            if(ch[tx][ty]=='.'&&dis[tx][ty]<=k) {
                ans+=dir[i];
                sx=tx;
                sy=ty;
                flag=false;
                break;
            }
        }
        if(flag) {
            cout << "IMPOSSIBLE\n"; return;
        }
        k--;
    }
    cout << ans << "\n";

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
