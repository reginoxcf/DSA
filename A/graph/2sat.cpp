struct TwoSatSolver {
  int n_vars, n_vertices;
  vector<vector<int>> adj;

  vector<int> num, low, comp;
  vector<int> st;
  vector<bool> in_stack;
  vector<bool> assignment;

  int timer, scc_cnt;

  TwoSatSolver(int _n_vars = 0)
    : n_vars(_n_vars),
      n_vertices(2 * n_vars),
      adj(n_vertices),
      num(n_vertices, 0),
      low(n_vertices, 0),
      comp(n_vertices, -1),
      in_stack(n_vertices, false),
      assignment(n_vars, false),
      timer(0),
      scc_cnt(0) {}

  void tarjan(int u) {
    num[u] = low[u] = ++timer;
    st.push_back(u);
    in_stack[u] = true;

    for (int v : adj[u]) {
      if (!num[v]) {
        tarjan(v);
        low[u] = min(low[u], low[v]);
      }
      else if (in_stack[v]) {
        low[u] = min(low[u], num[v]);
      }
    }

    if (low[u] == num[u]) {
      while (true) {
        int v = st.back();
        st.pop_back();
        in_stack[v] = false;
        comp[v] = scc_cnt;

        if (v == u) break;
      }
      scc_cnt++;
    }
  }

  bool solve_2SAT() {
    fill(num.begin(), num.end(), 0);
    fill(low.begin(), low.end(), 0);
    fill(comp.begin(), comp.end(), -1);
    fill(in_stack.begin(), in_stack.end(), false);

    st.clear();
    timer = 0;
    scc_cnt = 0;

    for (int i = 0; i < n_vertices; i++) {
      if (!num[i]) tarjan(i);
    }

    assignment.assign(n_vars, false);

    for (int i = 0; i < n_vars; i++) {
      if (comp[2 * i] == comp[2 * i + 1])
        return false;

      assignment[i] = comp[2 * i] < comp[2 * i + 1];
    }

    return true;
  }

  void add_edge(int a, bool na, int b, bool nb) {
    a = (2 * a) ^ na;
    b = (2 * b) ^ nb;
    adj[a].push_back(b);
  }

  void add_disjunction(int a, bool na, int b, bool nb) {
    // na and nb signify whether a and b are to be negated 
    add_edge(a, !na, b, nb);
    add_edge(b, !nb, a, na);
  }
}  D;
