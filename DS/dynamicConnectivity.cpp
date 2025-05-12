struct dsuQuery{
    int v, lbv, u, lbu;

    dsuQuery() {}

    dsuQuery(int _v, int _lbv, int _u, int _lbu)
        : v(_v), lbv(_lbv), u(_u), lbu(_lbu) {}
};
struct dsuRollback{
    vector<int> lab;
    int cc;
    stack<dsuQuery> op;

    dsuRollback(){}

    dsuRollback(int n){
        lab.clear(); lab.resize(n, -1);
        cc = n;
    }

    int Find(int u){
        if(lab[u] < 0) return u;
        else return Find(lab[u]);
    }

    bool Union(int u, int v){
        u = Find(u), v = Find(v);
        if(u == v) return false;
        if(lab[u] > lab[v]) swap(u, v);
        op.push(dsuQuery(v, lab[v], u, lab[u]));
        cc--;
        lab[u] += lab[v];
        lab[v] = u;
        return true;
    }

    void Rollback(){
        if(op.empty()) return ;
        dsuQuery tp = op.top(); op.pop();
        cc++;
        lab[tp.v] = tp.lbv;
        lab[tp.u] = tp.lbu;
    }
};

struct query {
    int v, u;
    bool united; // v, u in same CC
    query(int _v, int _u) : v(_v), u(_u) {
    }
};

struct DCTree{
    //dynamic connectivity tree
    vector<vector<query>> T;
    dsuRollback dsu;
    int N;

    DCTree() {}

    DCTree (int N){
        dsu = dsuRollback(N);
        this -> N = N;
        T.resize(N * 4 + 4);
    }

    void add(int id, int l, int r, int L, int R, query& q){
        if(L > R) return ;
        if(L == l && R == r){
            T[id].push_back(q);
            return ;
        }
        int mid = (l+r) >> 1;
        add(id * 2, l, mid, L, min(R, mid), q);
        add(id * 2 + 1, mid + 1, r, max(L, mid+1), R, q);
    }

    void addQuery(query q, int l, int r) {
        add(1, 0, N - 1, l, r, q);
    }

    void dfs(int id, int l, int r, vector<int> &ans){
        for(auto &x : T[id]){
            x.united = dsu.Union(x.v, x.u);
        }
        if(l == r){
            ans[l] = dsu.cc;
        }
        else{
            int mid = (l+r)>>1;
            dfs(id*2, l, mid, ans);
            dfs(id*2+1, mid+1, r, ans);
        }
        for(auto &x:T[id]){
            if(x.united) dsu.Rollback();
        }
    }

    vector<int> solve(){
        vector<int> ans(N);
        dfs(1, 0, N-1, ans);
        return ans;
    }
};