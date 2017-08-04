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
Point c;

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
int cross(Point a, Point b) {
  return a.x*b.y - b.x*a.y;
}
double dist(Point a, Point b){
  return sqrt((double)((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)));
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
bool comp2(Point a, Point b) {
  // Point c must be set before
  if(ccw(c,a,b) == 0) 
    return a.y > b.y;
  return ccw(c,a,b) > 0;
}
bool inBetween(Point a, Point b, Point toCheck) {
  if(abs(toCheck.y -a.y)*(b.x-a.x) -(toCheck.x -a.x) * (b.y-a.y) != 0) {
    return false;
  }
  int dotP =(toCheck.x-a.x) * (b.x-a.x) + (toCheck.y-a.y)*(b.y-a.y);
  if(dotP < 0) {
    return false;
  }
  if((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y) < dotP) {
    return false;
  }
  return true;
}
int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
	int nofTrees;
	double distance = 0;
	cin >> nofTrees;
	vector<Point> trees;
	
	int t1, t2;
	for(int i = 0; i < nofTrees; i++) {
	  cin >> t1 >> t2;
	  Point p; p.x = t1; p.y = t2;
	  trees.push_back(p);
	}

	// find pivot index
	int pivot_index = 0;
	for(int i = 1; i < nofTrees; i++) {
	  if(trees[i].y < trees[pivot_index].y) {
	    pivot_index = i;
	  }
	  else if(trees[i].y == trees[pivot_index].y) {
	    if(trees[i].x < trees[pivot_index].x) {
	      pivot_index = i;
	    }
	  }
	}
	
	swap(trees[0],trees[pivot_index]);
	Point c1;
	c1.x = trees[0].x; c1.y = trees[0].y;
	c = c1;
	sort(trees.begin()+1, trees.end(),comp2);
	trees.push_back(trees[0]); // to close loop
	vector<Point> S; S.push_back(trees[0]); S.push_back(trees[1]);
	for(int i = 2; i < trees.size(); ++i) {
	  int j = S.size();
	  while(ccw(S[j-2],S[j-1],trees[i]) < 0) {
	    S.pop_back();
	    j = S.size();
	  }
	  //check if not on line between previous two points
	  if(!inBetween(S[j-2],S[j-1],trees[i]) || i == trees.size()-1) {
	    S.push_back(trees[i]);
	  }
	}
	
// 	for(int i = 0; i < trees.size(); i++) {
// 	  cout << trees[i].x << "/" << trees[i].y << endl;
// 	}
// 	cout << "S: ";
// 		for(int i = 0; i < S.size(); i++) {
// 	  cout << S[i].x << "/" << S[i].y << endl;
// 	}
	// trees are ordered in S
	for(int i = 0; i < S.size()-1; i++) {
	  distance += dist(S[i],S[i+1]);
	}
	cout.precision(3);
	cout << fixed << distance << endl;
    }
    return 0;
}


























