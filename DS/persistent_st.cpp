struct node{
  node *l, *r;
  int sum;
  node(int v) : l(nullptr), r(nullptr), sum(v) {}
  node(node *l, node *r) : l(l), r(r), sum(0){
    if(l) sum += l -> sum;
    if(r) sum += r -> sum;
  }
};

node* build(int l, int r){
  if(l == r) return new node(0);
  int mid = (l+r)/2;
  return new node(build(l, mid), build(mid+1, r));
}

node* up(node *v, int l, int r, int u, int k){
  if(l == r) return new node(v->sum+k);
  int mid = (l+r)/2;
  if(u <= mid) return new node(up(v->l, l, mid, u, k), v->r);
  else return new node(v->l, up(v->r, mid+1, r, u, k));
}

int get(node *i, int l, int r, int u, int v){
  if(i == nullptr || u > r || v < l) return 0;
  if(u <= l && r <= v) return i->sum;
  int mid = (l+r)/2;
  return get(i->l, l, mid, u, v) + get(i->r, mid+1, r, u, v);
}

vector<node*> roots;
