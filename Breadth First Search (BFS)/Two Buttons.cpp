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

const int M = 1e5+7;








void solve() {

    int n,m; cin>>n>>m;
    vector<int>dis(M,1e9);
    queue<int>q;
    q.push(n);
    dis[n]=0;
    int ans=1e9;

    while(!q.empty()) {
        int x=q.front(); q.pop();
        
        if(x==m) {
            ans=dis[x];break;
        }
        if(x>0 && dis[x]+1<dis[x-1]) {
            dis[x-1]=dis[x]+1;
            q.push(x-1);
        }
        if(x<=m && dis[x]+1<dis[x*2]) {
            dis[x*2]=dis[x]+1;
            q.push(x*2);
        }

    }

    cout << ans << "\n";


}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
