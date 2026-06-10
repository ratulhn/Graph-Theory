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

    int n; cin>>n;
    int dist[n][n];
    lp(i,0,n) lp(j,0,n) cin>>dist[i][j];
    vector<int>id(n); lp(i,0,n) cin>>id[i],id[i]--;
    vector<bool>st(n,0);
    vector<ll>res;

    for(int step=n-1; step>=0; step--) {
        int k=id[step];
        st[k]=true;
        
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
        

        ll sum=0;
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                if(st[i]&&st[j]) {
                    sum+=dist[i][j];
                }
            }
        }

        res.push_back(sum);

    }

    reverse(res.begin(),res.end());

    for(auto x:res) cout << x << " ";nl;


}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
