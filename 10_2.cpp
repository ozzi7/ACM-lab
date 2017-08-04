#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <math.h>

using namespace std;

struct Point {
  int x, y;
};
struct DPoint {
  int x;
  double y;
};

struct Vec {
  int x, y;
  Vec(Point p, Point q) {
    x = q.x -p.x;
    y = q.y -p.y;
  }
};

double dot(Vec v, Vec u) {
  return v.x*u.x+v.y*u.y;
}
double norm(Vec v) {
  return sqrt(dot(v,v));
}
double angle(Vec v, Vec u) {
  return acos(dot(v,u)/(norm(v)*norm(u)));
}
int cross(Vec v, Vec u) {
  return v.x*u.y - u.x*v.y;
}
// counter clockwise test
int ccw(Point p, Point q, Point r) {
  return cross(Vec(p,q),Vec(p,r));
}
bool contains(vector<Point> p, Point q) {
  double sum = 0.0;
  for(int i = 0; i < p.size()-1; i++) {
    if(ccw(q,p[i],p[i+1]) >= 0) {
      sum += angle(Vec(q,p[i]), Vec(q,p[i+1]));
    } else {
      sum -= angle(Vec(q,p[i]), Vec(q,p[i+1]));
    }
  }
  return (sum > 3.14);
}
double area(vector<Point> p) {
  int result = 0;
  for(int i = 0; i < p.size()-1; i++) {
    result += p[i].x*p[i+1].y - p[i+1].x*p[i].y;
  }
  return (double)result/2.0;
}
bool comp(DPoint a, DPoint b) {
  if(a.y == b.y) {
    return a.x < b.x;
  } else {
    return a.y < b.y;
  }
}
int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
	int nofShots,nofSpaceS;
	cin >> nofShots >> nofSpaceS;
	vector<vector<Point> > ships;
	vector<Point> shots;
	vector<DPoint> indexAndArea;
	
	int t1,t2;
	for(int i = 0; i < nofShots; i++) {
	  cin >> t1 >> t2;
	  Point p; p.x = t1; p.y = t2;
	  shots.push_back(p);
	}
	int nofEdges;
	for(int i = 0; i < nofSpaceS; i++) {
	  cin >> nofEdges;
	  vector<Point> ship;
	  for(int j = 0; j < nofEdges; j++) {
	    cin >> t1 >> t2;
	    Point p; p.x = t1; p.y = t2;
	    ship.push_back(p);
	  }
	  ship.push_back(ship[0]);
	  ships.push_back(ship);
	}
	// calculate sizes
	for(int i = 0; i < ships.size(); i++) {
	  double s = area(ships[i]);
	  DPoint p;
	  p.x = i; p.y = s;
	  indexAndArea.push_back(p);
	}
	sort(indexAndArea.begin(),indexAndArea.end(),comp);
	
	double sizeOfShip = -1;
	for(int i = 0; i < indexAndArea.size(); i++) {
	  for(int j = 0; j < nofShots; j++) {
	    if(contains(ships[indexAndArea[i].x],shots[j])) {
	      sizeOfShip = indexAndArea[i].y;
	      goto end;
	    }
	  }
	}
	end:
	if(sizeOfShip != -1){
	  cout << sizeOfShip << endl;
	} else {
	  cout << "fail" << endl;
	}
    }
    return 0;
}