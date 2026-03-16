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

    string s,e; cin>>s>>e;
    int x0=s[0]-'a'+1,y0=s[1]-'0',x1=e[0]-'a'+1,y1=e[1]-'0';

    auto good=[&](int i, int j) {
        if(i<1||i>8||j<1||j>8) return false;
        return true;
    };
    
    vector<pair<int,int>>dir={
        {2,1},{2,-1},{-2,1},{-2,-1},
        {1,2},{-1,2},{1,-2},{-1,-2}
    };

    queue<pair<int,int>>q;
    map<pair<int,int>,int>dis;
    set<pair<int,int>>st;

    q.push({x0,y0});
    st.insert({x0,y0});
    dis[{x0,y0}]=0;

    while(!q.empty()) {
        auto &[x,y]=q.front();
        q.pop();
        if(x==x1&&y==y1) {
            cout << dis[{x,y}] << "\n";return;
        }
        for(auto &[r,c]:dir) {
            if(good(x+r,y+c)&&!st.count({x+r,y+c})) {
                st.insert({x+r,y+c});
                dis[{x+r,y+c}]=dis[{x,y}]+1;
                q.push({x+r,y+c});
            }
        }
    }

    
}

int main() {
    FastIO


    int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
