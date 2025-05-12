//Depth First Search
#include<bits/stdc++.h>
#define ll long long
#define task "test"
using namespace std;
const ll N = 1e6+3;
ll n, m, s, t, a, b;
bool vis[N], r[N];
vector<ll> g[N], path, res, re;
queue<ll> q;

void dfs(ll st){
	if(st==t && res.empty()){
		for(auto x:path) res.push_back(x);
	}
	vis[st] = true;
	if(r[st]==false) re.push_back(st);
	r[st] = true;
	for(auto x:g[st]){
		if(vis[x]==false){
			path.push_back(x);
			dfs(x);
			path.pop_back();
		}
	}
	vis[st] = false;
}
int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	if(fopen(task".inp","r")){
		freopen(task".inp","r",stdin);
		freopen(task".out","w",stdout);
	}
	cin >> n >> m >> s >> t;
	for(ll i = 1; i <= m; i++){
		cin >> a >> b;
		g[a].push_back(b);
	}
	dfs(s);
	cout << "Reachable vertices from " << s << ":\n";
	for(auto x:re) cout << x << ", ";
	cout << "\n";
	cout << "The path from " << s << " to " << t << "\n";
	reverse(res.begin(), res.end());
	for(auto x:res) cout << x << " <- ";
	cout << s;
	return 0;
}	