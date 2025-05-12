//uoc orz nhu huutuan

struct node{
	//define custom data type
	
   //some variables

	node(/*values to set*/){
		//set to node variables
	}

    node operator+(const node &o) const {
        return node(/*combine nodes*/);
    }
};

/*
IF NEEDED
ostream& operator<<(ostream& c, const node &o){
	return c << something;
}

node newNode(ll v){
	return node(v, v, v);
}
*/

struct ST2d{

	int n, m;
	vector<vector<node>> t;

	void resize(int n, int m){
		this->n = n, this->m = m;
		t.assign(4*n+6, vector<node>(4*m+6, node()));
	}

	ST2d(int n, int m){
		resize(n, m);
	}

   void build_y(int kx, int lx, int rx, int ky, int ly, int ry){
      if (ly==ry){
         if (lx==rx){
            t[kx][ky]=newNode(a[lx][ly]);
         }else{
            t[kx][ky]=t[kx<<1][ky]+t[kx<<1|1][ky];
         }
      }else{
         int midy=(ly+ry)>>1;
         build_y(kx, lx, rx, ky<<1, ly, midy);
         build_y(kx, lx, rx, ky<<1|1, midy+1, ry);
         t[kx][ky]=t[kx][ky<<1]+t[kx][ky<<1|1];
      }
   }
   void build_x(int k, int l, int r){
      if (l!=r){
         int mid=(l+r)>>1;
         build_x(k<<1, l, mid);
         build_x(k<<1|1, mid+1, r);
      }
      build_y(k, l, r, 1, 1, m);
   }
   void update_y(int kx, int lx, int rx, int ky, int ly, int ry, int x, int y, node val){
      if (ly==ry){
         if (lx==rx){
            t[kx][ky]=val;
         }else{
            t[kx][ky]=t[kx<<1][ky]+t[kx<<1|1][ky];
         }
      }else{
         int midy=(ly+ry)>>1;
         if (y<=midy) update_y(kx, lx, rx, ky<<1, ly, midy, x, y, val);
         else update_y(kx, lx, rx, ky<<1|1, midy+1, ry, x, y, val);
         t[kx][ky]=t[kx][ky<<1]+t[kx][ky<<1|1];
      }
   }
   void update_x(int kx, int lx, int rx, int x, int y, node val){
      if (lx!=rx){
         int midx=(lx+rx)>>1;
         if (x<=midx) update_x(kx<<1, lx, midx, x, y, val);
         else update_x(kx<<1|1, midx+1, rx, x, y, val);
      }
      update_y(kx, lx, rx, 1, 1, m, x, y, val);
   }
   node get_y(int kx, int ky, int ly, int ry, int y1, int y2){
      if (ry<y1 || y2<ly) return node();
      if (y1<=ly && ry<=y2) return t[kx][ky];
      int midy=(ly+ry)>>1;
      return get_y(kx, ky<<1, ly, midy, y1, y2)+get_y(kx, ky<<1|1, midy+1, ry, y1, y2);
   }
   node get_x(int kx, int lx, int rx, int x1, int y1, int x2, int y2){
      if (rx<x1 || x2<lx) return node();
      if (x1<=lx && rx<=x2) return get_y(kx, 1, 1, m, y1, y2);
      int midx=(lx+rx)>>1;
      return get_x(kx<<1, lx, midx, x1, y1, x2, y2)+get_x(kx<<1|1, midx+1, rx, x1, y1, x2, y2);
   }
};
