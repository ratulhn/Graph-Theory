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
const ll INF = 1e18 + 7;

struct State {
    int u,v,d;
    bool operator>(const State &s) const {
        return d>s.d;
    }
};

int mask(string &s) {
    int res=0;
    for(auto &c:s) {
        res = (res<<1)+(c-'0');
    }
    return res;
}



void solve() {

    int n,m; cin>>n>>m;
    string s; cin>>s;
    int start = mask(s);
    vector<State>adj;
    for(int i=0; i<m; i++) {
        int d; cin>>d;
        string u,v; cin>>u>>v;
        int u_=mask(u);
        int v_=mask(v);
        adj.push_back({u_,v_,d});
    }
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>>pq;

    int tot = 1<<n;
    vector<ll>dist(tot,INF);
    pq.push({0,start});
    dist[start]=0;
    while(!pq.empty()) {
        auto [curr_days,st] = pq.top(); pq.pop();
        if(curr_days>dist[st]) continue;
        if(st==0) {
            cout << curr_days << "\n";
            return;
        }
        for(int i=0; i<m; i++) {
            auto &[cure,tox,next] = adj[i];
            int cur = (st&(~cure))|tox;
            if(dist[st]+next<dist[cur]) {
                dist[cur]=dist[st]+next;
                pq.push({dist[cur],cur});
            }
        }
    }
    cout << "-1\n";
}

int main() {
    FastIO


    int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
