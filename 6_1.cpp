#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

long long int glob;

long long int merge( vector<int> &v, int beg, int mid, int end ) {
  queue< int > left;
  queue< int > right;

  for( int i=beg; i<=mid; ++i ) {
    left.push( v[i] );
  }
  for( int i=mid+1; i<=end; ++i ) {
    right.push( v[i] );
  }

  int index=beg;
  int ret=0;

  while( !left.empty() && !right.empty() ) {
    if( left.front() <= right.front() ) {
      v[index++] = left.front();
      left.pop();
    } else {
      v[index++] = right.front();
      right.pop();
      ret+=left.size();
    }
  }

  while( !left.empty() ) { v[index++]=left.front();left.pop(); }
  while( !right.empty() ) { v[index++]=right.front();right.pop(); }

  return ret;
}

void mergesortInvCount( vector<int> &v, int beg, int end ) {
  if( beg < end ) {
    int mid = (int)((beg+end)/2);
    mergesortInvCount( v, beg, mid );
    mergesortInvCount( v, mid+1, end );
    glob += merge( v, beg, mid, end );
  }
}

int main() {
    ios_base::sync_with_stdio(false);
    int n,numberCount;
    cin >> n;
    while (n--) {
      glob = 0;
      cin >> numberCount;
      vector<int> numbers = vector<int> (numberCount,0);
      int number;
      
      for(int i = 0 ; i <numberCount; i++) {
	cin >> number;
	numbers[i] = number;
      }
      mergesortInvCount(numbers,0,numberCount-1);
      cout << glob%10000 << endl;
    }
    return 0;
}