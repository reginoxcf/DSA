struct HLD{
    vector<int> sz, depth, anc; //subtree size, node depth, heavy path root
    vector<bool> hv; //heavy node or not
    vector<pair<int, int>> hid; //heavy path # and index
    vector<vector<int>> sp; //sparse table for LCA
    vector<int> ord; // node number in HLD-tree
    int hsz; //heavy paths #

    int timer = 0; //for node numbering

    int n, L; //tree size, log (for sparse table)
    void init(int n){
        this->n = n;
        this->L = __lg(n) + 1;
        n++;
        sz.resize(n); fill(all(sz), 0);
        depth.resize(n); fill(all(depth), 0);
        anc.resize(n); fill(all(anc), 0);
        hv.resize(n); fill(all(hv), false);
        hid.resize(n); fill(all(hid), make_pair(-1, -1));
        sp.resize(n); fill(all(sp), vector<int>(L+1, 0));
        ord.resize(n); fill(all(ord), 0);
    }

    void find_sz(int u = 1, int p = 0){
        depth[u] = depth[p] + 1;
        sz[u] = 1;
        for(int i = 1; i <= L; i++) sp[u][i] = sp[sp[u][i-1]][i-1];
        int mx = -1;
        for(auto v:g[u]){ 
            if(v == p) continue;
            sp[v][0] = u;
            find_sz(v, u);
            sz[u] += sz[v];
            if(mx == -1 || sz[mx] < sz[v]) mx = v;
        }
        if(mx != -1){
            hv[mx] = 1;
        }
    }

    void find_hld(int u = 1, int p = 0){
        if(hid[u].first == -1){
            hid[u].first = ++hsz;
            hid[u].second = 1;
            anc[u] = u;
        }
        ord[u] = ++timer;
        for(auto v:g[u]){
            if(v == p) continue;
            if(hv[v] == 1){
                hid[v].first = hid[u].first;
                hid[v].second = hid[u].second + 1;
                anc[v] = anc[u];
                find_hld(v, u); 
            }
        }
        for(auto v:g[u]){
            if(v == p) continue;
            if(hv[v] == 0) find_hld(v, u);
        }
    }

    int LCA(int u, int v){
        if(depth[u] > depth[v]) swap(u, v);
        int diff = depth[v] - depth[u];
        for(int l = L; l >= 0; l--){
            if((diff >> l) & 1){
                v = sp[v][l];
            }
        }
        if(u == v) return u;
        for(int l = L; l >= 0; l--){
            if(sp[u][l] != sp[v][l]){
                u = sp[u][l];
                v = sp[v][l];
            }
        }
        return sp[u][0];
    }
} ;
