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

    int x0,y0,x1,y1; cin>>x0>>y0>>x1>>y1;
    int n; cin>>n;
    set<pair<int,int>>st;
    for(int i=0; i<n; i++) {
        int r,a,b; cin>>r>>a>>b;
        for(int c=a; c<=b; c++) st.insert({r,c});
    }

    queue<pair<int,int>>q;
    map<pair<int,int>,int>dis;

    vector<pair<int,int>>d={
        {1,1},{-1,-1},{1,-1},{-1,1},
        {1,0},{0,1},{-1,0},{0,-1}
    };

    q.push({x0,y0});
    dis[{x0,y0}]=0;

    while(!q.empty()) {
        auto &[x,y]=q.front();
        q.pop();
        if(x==x1&&y==y1) {
            cout << dis[{x,y}] << "\n"; return;
        }
        for(auto &[a,b]:d) {
            int l=x+a,r=y+b;
            if(st.count({l,r})) {
                st.erase({l,r});
                q.push({l,r});
                dis[{l,r}]=dis[{x,y}]+1;
            }
        }
    }

    cout << "-1\n";

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
