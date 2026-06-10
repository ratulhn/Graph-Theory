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
const ll inf=1e18;







void solve() {

    int n,m,q; cin>>n>>m>>q;
    vector<vector<ll>> d(n + 1, vector<ll>(n + 1, inf));
    for(int i=1; i<=n; i++) d[i][i]=0;

    for(int i=0; i<m; i++) {
        int a,b,w; cin>>a>>b>>w;
        d[a][b]=min(d[a][b],(ll)w);
        d[b][a]=min(d[b][a],(ll)w);
    }
    for(int k=1; k<=n; k++) {
        for(int i=1; i<=n; i++) {
            for(int j=1; j<=n; j++) {
                d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
            }
        }
    }

    while(q--) {
        int a,b; cin>>a>>b;
        if(d[a][b]==inf) cout << "-1\n";
        else cout << d[a][b] << "\n";
    } 


}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
