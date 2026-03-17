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

const int M = 32768;








void solve() {

    int n; cin>>n;
    vector<int>v(n); lp(i,0,n) cin>>v[i];
    vector<int>res(n);
    
    for(int i=0; i<n; i++) {
        if(v[i]==0) {
            res[i]=0; continue;
        }
        queue<int>q;
        vector<int>dis(M,1e9);
        q.push(v[i]);
        dis[v[i]]=0;
        
        while(!q.empty()) {
            
            auto a=q.front(); q.pop();
            int x=(a+1)%M;
            int y=(2*a)%M;
            if(x==0||y==0) {
                res[i]=dis[a]+1; break;
            }
            if(dis[a]+1<dis[x]) {
                dis[x]=dis[a]+1;
                q.push(x);
            }
            if(dis[a]+1<dis[y]) {
                dis[y]=dis[a]+1;
                q.push(y);
            }
        }
    }
    for(auto &x:res) cout << x << " ";nl;

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
