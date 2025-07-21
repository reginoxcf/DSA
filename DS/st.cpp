struct node{
    //define node here

    explicit node(){

    }

    node operator+(const node &o) const{
        return node();
    };
};

struct SegTree{
    vector<node> tree;
    void resize(int n){
        tree.assign(n * 4 + 3, node());
    }
    void update(int id, int l, int r, int u, node v){
        if(r < u || u < l) return ;
        if(l == r){
            tree[id] = v;
            return ;
        }
        int mid = l + (r-l)/2;
        update(id<<1, l, mid, u, v);
        update(id<<1|1, mid+1, r, u, v);
        tree[id] = tree[id<<1] + tree[id<<1|1];
    }
    node get(int id, int l, int r, int u, int v){
        if(r < u || v < l) return node();
        if(u <= l && r <= v) return tree[id];
        int mid = l + (r-l)/2;
        node lf = get(id<<1, l, mid, u, v);
        node rg = get(id<<1|1, mid+1, r, u, v);
        return lf + rg;
    }
};
