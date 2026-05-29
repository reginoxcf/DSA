typedef long double ld;
const ld eps = 1e-10;
const ld inf = 1e18;
 
struct point {
	ld Ox, Oy;
	point() {}
	point(ld x, ld y) : Ox(x), Oy(y) {}
	friend istream& operator >> (istream& in, point& o) {
		in >> o.Ox >> o.Oy;
		return in;
	}
	friend ostream& operator << (ostream& out, const point& o) {
		out << o.Ox << ' ' << o.Oy;
		return out;
	}
	friend point operator + (const point& A, const point& B) {return point(A.Ox + B.Ox, A.Oy + B.Oy);}
	friend point operator - (const point& A, const point& B) {return point(A.Ox - B.Ox, A.Oy - B.Oy);}
	friend point operator * (const point& A, const ld& x) {return point(A.Ox * x, A.Oy * x);}
	friend point operator / (const point& A, const ld& x) {return point(A.Ox / x, A.Oy / x);}
	ld cross(const point& B) const {return Ox * B.Oy - Oy * B.Ox;}
	ld cross(const point& B, const point& C) const {return (B - *this).cross(C - *this);}
	ld dot(const point& B) {return Ox * B.Ox + Oy * B.Oy;}
 
	ld angle() const {return atan2l(Oy, Ox);}
	point perp() const {return point(Oy, -Ox);} // rotate 90 ccw
	ld length() const {return sqrtl(Ox * Ox + Oy * Oy);}
	ld dist(const point& A) const {return (A - *this).length();}

  bool operator==(const point &o){return Ox==o.Ox && Oy==o.Oy;}
};
 
bool acute(const point& A, const point& B, const point& C) { // checks angle ABC
	return (A - B).dot(C - B) > -eps;
}
 
ld angle(const point& A, const point& B, const point& C) {
	return acosl(min(1.0L, (A - B).dot(C - B) / ((A - B).length() * (C - B).length())));
}

int orientation(const point& A, const point& B, const point& C) {
  // Returns the orientation sign: +1 for CCW, -1 for CW, 0 for collinear/flat
  ld cross_product = A.cross(B, C);
  if (abs(cross_product) < eps) return 0;
  return (cross_product > 0) ? 1 : -1;
}
 
struct line {
	ld a, b, c; // ax + by + c = 0
	line() {}
	line(const point& A, const point& B) {
		a = A.Oy - B.Oy; b = B.Ox - A.Ox;
		c = -(a * A.Ox + b * A.Oy);
	}
	friend istream& operator >> (istream& in, line& d) {
		in >> d.a >> d.b >> d.c;
		return in;
	}
	friend ostream& operator << (ostream& out, const line& d) {
		out << d.a << ' ' << d.b << ' ' << d.c;
		return out;
	}
 
	ld dist(const point& A) const {return abs(a * A.Ox + b * A.Oy + c) / sqrtl(a * a + b * b);}
	point eval(ld x) const {return point(x, (-c - a * x) / b);}
	point intersect(const line& d) const {
		if (abs(a * d.b - b * d.a) < eps) return point(inf, inf);
		return point(b * d.c - d.b * c, -a * d.c + d.a * c) / (a * d.b - d.a * b);
	}
};

ld triarea(ld a, ld b, ld c){
  ld p = (a + b + c)/2;
  return sqrtl(p*(p-a)*(p-b)*(p-c));
}

point circumcenter(point a, point b, point c){
  ld d = 2 * (a.Ox * (b.Oy - c.Oy) + b.Ox * (c.Oy - a.Oy) + c.Ox * (a.Oy - b.Oy));
  if(d == 0) return point(inf, inf);
  else{
    ld xO = (a.length() * a.length() * (b.Oy - c.Oy) + b.length() * b.length() * (c.Oy - a.Oy) + c.length() * c.length() * (a.Oy - b.Oy)) / d;
    ld yO = (a.length() * a.length() * (c.Ox - b.Ox) + b.length() * b.length() * (a.Ox - c.Ox) + c.length() * c.length() * (b.Ox - a.Ox)) / d;
    return point(xO, yO);
  }
}

point reflect_point(point p, point c){
  return point(2*c.Ox - p.Ox, 2*c.Oy - p.Oy);
}

pair<line, line> angle_bisector(const line& l1, const line& l2){
  ld norm1 = sqrtl(l1.a * l1.a + l1.b * l1.b);
  ld norm2 = sqrtl(l2.a * l2.a + l2.b * l2.b);

  line b1, b2;

  // First bisector (+)
  b1.a = l1.a * norm2 - l2.a * norm1;
  b1.b = l1.b * norm2 - l2.b * norm1;
  b1.c = l1.c * norm2 - l2.c * norm1;

  // Second bisector (-)
  b2.a = l1.a * norm2 + l2.a * norm1;
  b2.b = l1.b * norm2 + l2.b * norm1;
  b2.c = l1.c * norm2 + l2.c * norm1;

  return {b1, b2};
}
