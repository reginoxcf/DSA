struct DSU{
	int n;
	vector<int> lab;
	DSU(int n){
		this->n = n;
		lab.resize(n+1, -1);
	}
	void resize(int n){
		this->n = n;
		lab.resize(n+1, -1);
	}
	int find(int u){
		if(lab[u] < 0) return u;
		return lab[u] = find(lab[u]);
	}
	void join(int u, int v){
		u = find(u), v = find(v);
		if(u == v) return;
		if(lab[u] > lab[v]) swap(u, v);
		lab[u] += lab[v];
		lab[v] = u;
	}
};