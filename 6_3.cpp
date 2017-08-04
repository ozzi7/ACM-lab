#include<iostream>
#include<vector>
#include<cmath>
#include <climits>
using namespace std;

vector<pair<long,long> >A;
int n;
long one,two,Dis(pair<long,long>,pair<long,long>);
pair<pair<long,long>,pair<long,long> >Find(long,long),Ans;

int main()
{
  ios_base::sync_with_stdio(false);
  int testcases;
  cin >> testcases;
  while(testcases--) {
    int points;
    cin >> points;
    long t1 = 0;
    long t2 = 0;
    A.clear();
    A.resize(points,make_pair(t1,t2));
    for(int u = 0; u < points;u++) {
      cin >> t1; cin >> t2;
      A[u] = make_pair(t1,t2);
    }
    Ans=Find(0,points-1);
    cout << Dis(Ans.first,Ans.second) << endl;
  }
  return 0;
}

pair<pair<long,long>,pair<long,long> >Find(long  L,long  R)
{
	long Min=LONG_MAX,temp;
	pair<pair<long,long>,pair<long,long> >Ans;
	
	if(R-L<=6)
	{
		for (int i=L+1;i<=R;i++)
		{
			for (int j=L;j<i;j++)
			{
				if(Dis(A[i],A[j])<Min)
				{
					Min=Dis(A[i],A[j]);
					Ans=make_pair(A[i],A[j]);
				}
			}
		}
		
		return Ans;	
		
	}
	
	else
	{
		int mid=floor((R+L)/2);
		pair<pair<long,long>,pair<long,long> >Ch,Ra;
		long LM,RM;
		
		Ch=Find(L,mid);
		Ra=Find(mid+1,R);
		
		LM=Dis(Ch.first,Ch.second);
		RM=Dis(Ra.first,Ra.second);
		
		for (int i=L;i<=mid;i++)
		{
			for (int j=mid+1;j<=R;j++)
			{
				if(Dis(A[i],A[j])<Min)
				{
					Min=Dis(A[i],A[j]);
					Ans=make_pair(A[i],A[j]);
				}
			}
		}
		
		if(LM<Min || RM<Min)
		{
			if(RM<LM)
			return Ra;
			
			return Ch;
		}
		
		return Ans;
	}
}

long Dis(pair<long ,long > A,pair<long ,long >B)
{
	long xdif,ydif;
	
	xdif=pow(A.first-B.first,2);
	ydif=pow(A.second-B.second,2);
	
	xdif+=ydif;
	
	return xdif;
}
 