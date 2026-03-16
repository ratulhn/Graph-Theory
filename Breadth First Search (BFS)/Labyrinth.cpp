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








void solve() {

    int n,m; cin>>n>>m;
    vector<bool> vis(n*m);
    int s,e;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            char ch; cin>>ch;
            if(ch=='#') {
                vis[i*m+j]=1;
            } else if(ch=='A') {
                s=i*m+j;
            } else if(ch=='B') {
                e=i*m+j;
            }
        }
    }

    vector<pair<int,int>>dir={
        {1,0},{-1,0},{0,1},{0,-1}
    };
    vector<char>ch={'D','U','R','L'};
    queue<int>q;
    vector<pair<int,char>> par(n*m);

    q.push(s);
    vis[s]=1;

    while(!q.empty()) {
        int cur = q.front(); q.pop();
        if(cur==e) {
            cout << "YES\n";
            string path;
            while(e!=s) {
                path.push_back(par[e].second);
                e=par[e].first;
            }
            cout << path.size() << "\n";
            reverse(path.begin(),path.end());
            for(auto &c:path) cout << c; return;
        }
        int y=cur%m,x=cur/m;
        int k=0;
        for(auto &[r,c]:dir) {
            int nxt=(x+r)*m+(y+c);
            if((x+r)>=0&&(x+r)<n&&(y+c)>=0&&(y+c)<m&&!vis[nxt]) {
                q.push(nxt);
                vis[nxt]=1;
                par[nxt]={cur,ch[k]};
            }
            k++;
        }
    }

    cout << "NO\n";
}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
