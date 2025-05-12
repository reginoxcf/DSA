struct Dinic {
    struct edge {
        ll x, y, w;
    };
    vector<vector<int>> gr;
    vector<edge> edges;
    vector<ll> level;
    vector<ll> edge_sz;
    ll n, source, sink, ec = 0;
    Dinic(ll n, ll source, ll sink) {
        this->n = n;
        this->source = source;
        this->sink = sink;
        gr.resize(n);
        edge_sz.resize(n);
    }
    void add_edge(ll x, ll y, ll w) {
        edges.push_back({x, y, w});
        gr[x].push_back(ec++);
        edges.push_back({y, x, 0});
        gr[y].push_back(ec++);
    }
    bool level_graph() {
        level.clear(); level.resize(n, -1);

        queue<ll> Q;
        Q.push(source);
        level[source] = 0;

        while (!Q.empty()) {
            ll cur = Q.front();
            Q.pop();

            for (auto xx : gr[cur]) {
                ll to = edges[xx].y;
                ll w = edges[xx].w;

                if (w && level[to] == -1) {
                    level[to] = level[cur] + 1;
                    Q.push(to);
                }

            }
        }

        return level[sink] != -1;
    }
    ll augment(ll cur, ll flow) {
        if (cur == sink) {
            return flow;
        }

        for (ll &i = edge_sz[cur]; i >= 0; i--) {
            ll edge_index = gr[cur][i];
            ll w = edges[edge_index].w;
            ll y = edges[edge_index].y;

            if (w && level[y] == level[cur] + 1) {
                ll bottleneck_flow = augment(y, min(w, flow));

                if (bottleneck_flow) {
                    edges[edge_index].w -= bottleneck_flow;
                    edges[edge_index ^ 1].w += bottleneck_flow;

                    return bottleneck_flow;
                }

            }
        }
        return 0;
    }
    ll max_flow() {
        ll total_flow = 0;
        while (level_graph()) {
            for (ll i = 0; i < n; i++) edge_sz[i] = gr[i].size() - 1;
            while (ll flow = augment(source, 1e18)) {
                total_flow += flow;
            }
        }
        return total_flow;
    }
    bool func(ll curr, vector<ll>&path){
        path.push_back(curr);
        if (curr == sink)
            return true;

        for (ll &i = edge_sz[curr]; i >= 0; i--){
            ll edge_index = gr[curr][i];
            if (edge_index & 1)
                continue;
            if (edges[edge_index].w == 0){
                func(edges[edge_index].y, path);
                i--;
                return true;
            }
        }
        return false;
    }
    vector<vector<ll>> get_paths() {
        vector<vector<ll>> ans;
        for (ll i = 0; i < n; i++) edge_sz[i] = gr[i].size() - 1;
        vector<ll> path;
        while (func(source, path)){
            ans.push_back(path);
            path.clear();
        }
        return ans;
    }
};
