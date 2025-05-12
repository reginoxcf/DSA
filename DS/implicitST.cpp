const long long N = 1e6+3, inf = 1ll<<60;
struct implicitST{
    //Implicit(dynamic) segment tree - point add range sum
    //Update: log(inf), about 61
    //Query: log(inf), about 61
    long long cl[N*4], cr[N*4], cnt=1;
    long long st[N*4];
    void update(long long id, long long l, long long r, long long u, long long val){
        if(u < l || r < u) return ;
        if(l == r){
            st[id] = val;
            return ;
        }
        long long mid = (l+r)>>1;
        if(cl[id] == 0) cl[id] = ++cnt;
        update(cl[id], l, mid, u, val);
        if(cr[id] == 0) cr[id] = ++cnt;
        update(cr[id], mid+1, r, u, val);
        st[id] = st[cr[id]] + st[cl[id]];
    }
    long long query(long long id, long long l, long long r, long long u, long long v){
        if(v < l || r < u || l > r || u > v) return 0;
        if(u <= l && r <= v) return st[id];
        long long vl, vr, mid = (l+r)>>1;
        if(cl[id] == 0) vl = 0;
        else vl = query(cl[id], l, mid, u, v);
        if(cr[id] == 0) vr = 0;
        else vr = query(cr[id], mid+1, r, u, v);
        return vl + vr;
    }
} tree;
//Usage
//- update(1, -inf, inf, u, v): set a[u] to v (-inf <= u <= inf)
//- query(1, -inf, inf, l, r): find a[l] + a[l+1] + ... + a[r] (-inf <= l <= r <= inf)
