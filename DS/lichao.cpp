struct LiChao{
  static const ll INF = 0x3f3f3f3f3f3f3f3f;
  struct Line{
    ll m, b;
    Line(ll _m = 0, ll _b = -INF): m(_m), b(_b) {}
    ll operator() (ll x) const{
      return m * x + b;
    }
  };

  struct Node{
    Line f;
    Node *l, *r;

    Node(Line _f): f(_f), l(nullptr), r(nullptr) {}
  };

  ll MN, MX;
  Node *root;

  LiChao(ll L = -1e9, ll R = 1e9): MN(L), MX(R), root(nullptr) {}

  void add(Node *&id, ll L, ll R, Line a){
    if(!id){
      id = new Node(a);
      return ;
    }

    ll mid = L + (R - L) / 2;
    bool lf = a(L) > id->f(L);
    bool md = a(mid) > id->f(mid);

    if(md) swap(id->f, a);
    if(L == R) return ;

    if(lf != md) add(id->l, L, mid, a);
    else add(id->r, mid+1, R, a);
  }

  ll query(Node *id, ll L, ll R, ll x){
    if(!id) return -INF;
    ll ans = id->f(x);
    if(L == R) return ans;
    ll mid = L + (R - L) / 2;
    if(x <= mid) return max(ans, query(id->l, L, mid, x));
    else return max(ans, query(id->r, mid+1, R, x)); 
  }

  void add(ll m, ll b){return add(root, MN, MX, Line(m, b));}
  ll query(ll x){return query(root, MN, MX, x);}
};
