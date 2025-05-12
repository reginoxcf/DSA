const ll N = 1e6+3;
struct SegTree{
    //Segment tree subarray sum
    ll tree[N*4+1];
    void reset(){
        memset(tree,0,sizeof(tree));
    }
    void upd(ll id, ll l, ll r, ll u, ll val){
        if(r<u||u<l) return ;
        if(l==r){
            tree[id]=val;
            return;
        }
        ll mid=(l+r)>>1;
        upd(id*2,l,mid,u,val);
        upd(id*2+1,mid+1,r,u,val);
        tree[id]=tree[id*2]+tree[id*2+1];
    }
    ll get(ll id, ll l, ll r, ll u, ll v){
        if(u>v||l>r) return 0;
        if(v<l||r<u) return 0;
        if(u<=l&&r<=v) return tree[id];
        ll mid=(l+r)>>1;
        return get(id*2, l, mid, u, v)+get(id*2+1, mid+1, r, u, v);
    }
} tree;