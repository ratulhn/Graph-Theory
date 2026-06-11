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
const int inf=1e9;







void solve() {

    int n,m,r,c,x,y; cin>>n>>m>>r>>c>>x>>y;
    vector<string>adj(n); lp(i,0,n) cin>>adj[i];
    r--;c--;
    vector<vector<int>>left(n,vector<int>(m,inf));
    left[r][c]=0;
    deque<pair<int,int>>q;
    q.push_back({r,c});

    auto good=[&](int i, int j) {
        if(i<0||j<0||i>=n||j>=m||adj[i][j]=='*') return false;
        return true;
    };

    while(!q.empty()) {
        auto [cur_r,cur_c] = q.front(); q.pop_front();
        int L=left[cur_r][cur_c];
        int R=L+(cur_c-c);

        if(good(cur_r-1,cur_c)&&L<left[cur_r-1][cur_c]) {
            q.push_front({cur_r-1,cur_c});
            left[cur_r-1][cur_c]=L;
        }
        if(good(cur_r+1,cur_c)&&L<left[cur_r+1][cur_c]) {
            q.push_front({cur_r+1,cur_c});
            left[cur_r+1][cur_c]=L;
        }

        if(good(cur_r,cur_c+1) && R+1<=y &&L<left[cur_r][cur_c+1]) {
            q.push_front({cur_r,cur_c+1});
            left[cur_r][cur_c+1]=L;
        }

        if(good(cur_r,cur_c-1) && L+1<=x && L+1<left[cur_r][cur_c-1]) {
            q.push_back({cur_r,cur_c-1});
            left[cur_r][cur_c-1]=L+1;
        }
    }
    
    int res=0;
    lp(i,0,n) lp(j,0,m) if(left[i][j]!=inf) res++;

    cout << res << "\n";

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
