//Breadth First Search
#include<bits/stdc++.h>
#define ll long long
#define task "test"
using namespace std;
const ll N = 1e6+3;
ll n, m, s, t, a, b, par[N];
bool vis[N];
vector<ll> g[N];
vector<ll> res, re;
queue<ll> q;

void bfs(){
	while(!q.empty()){
		ll st = q.front();
		q.pop();
		re.push_back(st);
		for(auto x:g[st]){
			if(vis[x]==false){
				par[x] = st;
				vis[x] = true;
				q.push(x);
			}
		}
	}
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
	q.push(s);
	vis[s] = true;
	bfs();
	cout << "Reachable vertices from " << s << ":\n";
	for(auto x:re) cout << x << ", ";
	cout << "\n";
	cout << "The path from " << s << " to " << t << "\n";
	for(ll i = t; i != s; i = par[i]) res.push_back(i);
	for(auto x:res) cout << x << " <- ";
	cout << s;
	return 0;
}	