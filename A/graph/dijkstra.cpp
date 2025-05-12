/* 
Dijkstra's algorithm to find single source shortest path from vertex 1
https://cses.fi/problemset/task/1671
*/
#include<bits/stdc++.h>
#define ll long long
#define task "test"
#define pll pair<ll,ll>
using namespace std;
const ll N = 1e5+3;
ll n, m, d[N], last[N];
vector<pll> g[N];
vector<ll> path;
priority_queue<pll, vector<pll>, greater<pll>> pq;

void dijkstra(ll s)
{
    pq.push({0, s}), d[s] = 0;
    pll p;
    while (!pq.empty())
    {
        p = pq.top();
        pq.pop();
        if (d[p.second] != p.first)
            continue;
        for (auto [v, w] : g[p.second])
        {
            if (d[v] > p.first + w)
            {
                d[v] = p.first + w;
                last[v] = p.second;
                pq.push({d[v], v});
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
    ll a, b, c;
    cin >> n >> m;
    for(ll i = 1; i <= m; i++){
        cin >> a >> b >> c;
        g[a].emplace_back(b, c);
    }
    memset(d, 0x3f, sizeof(d));
    dijkstra(1);
    for(ll i = 1; i <= n; i++) cout << d[i] << " ";
    return 0;
}