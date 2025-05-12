const int N = 1e6+3;
struct LazySegTree{
	//Segment tree lazy propagation subarray sum
	int tree[N*4+1], lazy[N*4+1];
	void reset(){
		memset(tree,0,sizeof(tree));
		memset(lazy,0,sizeof(lazy));
	}
	void down(int id){
		int t = lazy[id];
		tree[id*2+1]+=t;
		tree[id*2]+=t;
		lazy[id*2+1]+=t;
		lazy[id*2]+=t;
		lazy[id]=0;
	}
	void upd(int id, int l, int r, int u, int v, int val){
		if(l>r||u>v) return ;
		if(v<l||r<u) return ;
		if(u<=l&&r<=v){
			tree[id]+=val;
			lazy[id]+=val;
			return ;
		}
		down(id);
		upd(id*2,l,(l+r)/2,u,v,val);
		upd(id*2+1,(l+r+2)/2,r,u,v,val);
		tree[id]=tree[id*2]+tree[id*2+1];
	}
	int get(int id, int l, int r, int u, int v){
		if(u>v||l>r) return 0;
		if(v<l||r<u) return 0;
		if(u<=l&&r<=v) return tree[id];
		down(id);
		return get(id*2, l, (l+r)/2, u, v)+get(id*2+1, (l+r+2)/2, r, u, v);
	}
} tree;

/*
UNTESTED CODE
struct LazyST{
    int n;
	vector<pair<int,int>> t;
	void resize(int n){
		this->n = n;
		t.resize(n*4+3);
	}
	LazyST(int n){
		this->n = n;
		resize(n);
	}
	void push(int id){
		int &x = t[id].second;
		t[id*2].first += x;
		t[id*2+1].first += x;
		t[id*2].second += x;
		t[id*2+1].second += x;
		x = 0;
	}
	void update(int id, int l, int r, int L, int R, int v){
		if(L > r || R < l) return;
		if(L <= l && r <= R){
			t[id].first += v;
			t[id].second += v;
			return;
		}
		push(id);
		update(id*2, l, (l+r)/2, L, R, v);
		update(id*2+1, (l+r+2)/2, r, L, R, v);
		t[id].first = t[id*2].first + t[id*2+1].first;
	}
	int get(int id, int l, int r, int L, int R){
		if(L > r || R < l) return 0;
		if(L <= l && r <= R) return t[id].first;
		push(id);
		return get(id*2, l, (l+r)/2, L, R) + get(id*2+1, (l+r+2)/2, r, L, R);
	}
	int walk(int id, int l, int r, int v){
		if(t[id].first < v) return n+1; 
		if(l == r) return l;
		push(id);
		if(t[id*2].first >= v) return walk(id*2, l, (l+r)/2, v);
		return walk(id*2+1, (l+r+2)/2, r, v-t[id*2].first);
	}
};
*/
