const int N = 1e6+3;
struct betterLazyST{
    //supports range paint/add/multiply/sum
    ll tree[N*4], lmul[N*4], ladd[N*4], sz[N*4];
    void build(int id, int l, int r){
      sz[id] = r-l+1;
      if(l==r) return ;
      int mid = (l+r)/2;
      build(id<<1, l, mid);
      build(id<<1|1,mid+1, r);
    }
    void resize(int n){
      fill_n(tree+1, n<<2+3, 0);
      fill_n(ladd+1, n<<2+3, 0);
      fill_n(lmul+1, n<<2+3, 1);
      build(1, 1, n);
    }
    void push(ll id){
        ll tl = lmul[id], td = ladd[id];
        for(ll i = id<<1; i <= (id<<1)+1; i++){
            lmul[i]*=tl, ladd[i]*=tl;
            ladd[i]+=td;
            tree[i]=(tree[i]*tl+td*sz[i]);
        }
        lmul[id]=1, ladd[id]=0;
        return ;
    }
    void upd(ll id, ll l, ll r, ll u, ll v, bool t, ll val){
        if(r<u||v<l) return ;
        if(u<=l&&r<=v){
            if(t){
                ladd[id]+=val;
                tree[id]+=val*sz[id];
            }
            else{
                lmul[id]*=val;
                tree[id]*=val;
                ladd[id]*=val;
            }
            return ;
        }
        push(id);
        ll mid = (l+r)>>1;
        upd(id*2, l, mid, u, v, t, val);
        upd(id*2+1, mid+1, r, u, v, t, val);
        tree[id]=((tree[id*2]+tree[id*2+1])*lmul[id]+ladd[id]);
    }
    ll get(ll id, ll l, ll r, ll u, ll v){
        if(v<l||r<u) return 0;
        if(u<=l&&r<=v) return tree[id];
        ll mid = (l+r)>>1;
        push(id);
        return((get(id*2, l, mid, u, v)+get(id*2+1, mid+1, r, u, v)));
    }
    void assign(ll u, ll v, ll l, ll r, ll x){
        upd(1, u, v, l, r, false, 0);
        upd(1, u, v, l, r, true, x);
    }
};
//Usage
//- upd(1, 1, n, u, v, true, x): increases a[u], a[u+1], ..., a[v] by x
//- upd(1, 1, n, u, v, false, x): multiplies a[u], a[u+1], ..., a[v] by x
//- assign(1, n, u, v, x): assigns a[u], a[u+1], ..., a[v] to x
//- get(1, 1, n, u, v): returns value of a[u] + a[u+1] + ... + a[v] 
