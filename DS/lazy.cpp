struct node{
    //define node here
    explicit node(){

    }

    node operator+(const node &o) const{
        return node();
    };
};

struct Lazy{
    //todo: write apply function, clear lazy function
    vector<node> tree, lazy;
    void resize(int n){
        tree.assign(n<<2+3, node());
        lazy.assign(n<<2+3, node());
    }

    void apply(int id, int len, node add){
        //do something (both tree and lazy)
    }
    
    void push(int id, int l, int r){
        int mid = (l+r)/2;
        apply(id << 1, mid - l + 1, lazy[id]);
        apply(id << 1 | 1, r - mid, lazy[id]);
        //clear lazy
    }

    void update(int id, int l, int r, int u, int v, node tmp){
        if(v < l || r < u) return ;
        if(u <= l && r <= v){
            apply(id, r-l+1, tmp);
            return ;
        }
        push(id, l, r);
        int mid = (l+r)/2;
        update(id<<1, l, mid, u, v, tmp);
        update(id<<1|1, mid+1, r, u, v, tmp);
        tree[id] = tree[id<<1] + tree[id<<1|1];
    }
    
    node get(int id, int l, int r, int u, int v){
        if(v < l || r < u) return node();
        if(u <= l && r <= v) return tree[id];
        push(id, l, r);
        int mid = (l+r)/2;
        node lf = get(id<<1, l, mid, u, v);
        node rg = get(id<<1|1, mid+1, r, u, v);
        return lf + rg;
    }
};
