struct Fenwick2D{
	int n, m; vector<vector<ll>> t;
	Fenwick2D(int n, int m){
		this->n = n;
		this->m = m;
		t.resize(n+1, vector<ll>(m+1, 0));
	}
	void add(int x, int y, ll v){
		for(int i = x; i <= n; i += i & -i)
			for(int j = y; j <= m; j += j & -j)
				t[i][j] += v;
		return ;
	}
	ll get(int x, int y){
		ll res = 0;
		for(int i = x; i >= 1; i -= i & -i){
			for(int j = y; j >= 1; j -= j & -j){
				res += t[i][j];
			}
		}
		return res;
	}
	ll sum(int x, int y, int u, int v){
		return get(u, v) - get(x-1, v) - get(u, y-1) + get(x-1, y-1);
	}
};
