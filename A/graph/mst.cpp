/* AC code to https://cses.fi/problemset/task/1675/ using Kruskal's MST algorithm */
#include<bits/stdc++.h>
#define ll long long
#define task "test"
#define pll pair<ll,ll>
#define ppll pair<ll,pair<ll,ll>>
#define fi first
#define se second
using namespace std;
const ll N = 1e6+3;
struct DSU{
	ll par[N], sz[N];
	void make_set(ll u){
		par[u]=u;
		sz[u]=1;
	}
	ll find_set(ll u){
		if(u==par[u]) return u;
		return par[u]=find_set(par[u]);
	}
	void union_set(ll u, ll v){
		u = find_set(u), v = find_set(v);
		if(u!=v){
			if(sz[u]<sz[v]) swap(u, v);
			par[v] = u;
			sz[u]+=sz[v];
		}
	}	
} dsu;
ll n, m, x, y, w;
vector<ppll> v;
 
ll kruskal(){
	for(ll i = 1; i <= n; i++) dsu.make_set(i);
	sort(v.begin(), v.end());
	ll cost = 0, cnt = 0;
	for(auto [w, u]:v){
		if(dsu.find_set(u.fi) == dsu.find_set(u.se)) continue;
		cost += w;
		dsu.union_set(u.fi, u.se);
		cnt++;
		if(cnt == n-1) break;
	}
	if(cnt != n-1) cost = -1;
	return cost;
}
 
int main(){
	if(fopen(task".inp","r")){
		freopen(task".inp","r",stdin);
		freopen(task".out","w",stdout);
	}
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for(ll i = 1; i <= m; i++){
		cin >> x >> y >> w;
		v.push_back({w, {x, y}});
	}
	ll kr = kruskal();
	if(kr < 0) cout << "IMPOSSIBLE";
	else cout << kr;
	return 0;
}