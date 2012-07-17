/*
TASK:
LANG: C++
 */
#include <algorithm>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <iterator>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <list>
#include <bitset>
#include <cstring>
#include <climits>
#include <deque>
#include <utility>
#include <complex>
#include <numeric>
#include <functional>
#include <stack>
#include <iomanip>
#include <ctime>
#include <valarray>
//#include "vc.h"
#ifdef _MSC_VER
#include <hash_set>
#include <hash_map>
using namespace stdext;
#else
#if __GNUC__ > 2
#include <ext/hash_set>
#include <ext/hash_map>
using namespace __gnu_cxx;
#else
#include <hash_set>
#include <hash_map>
#endif
#endif

template<class key>
struct hashtemp
{

	enum
	{
		bucket_size = 4, min_buckets = 8
	};
	virtual size_t operator()(const key &p) const=0;

};

using namespace std;
#ifndef M_PI
const long double M_PI=acos((long double)-1);
#endif
#define rep(i,n) for(int  i=0;i<(int)(n);++i)
long double ZERO=0;
const long double INF=1/ZERO,EPSILON=1e-12;
#define all(c) (c).begin(),(c).end()
#define rep2(i,a,b) for(int i=(a);i<=((int)b);++i)
#define foreach(it,c) for(__typeof((c).begin()) it=(c).begin();it!=(c).end();++it)

#define sz(v) ((int)((v).size()))
#define let(x,y) __typeof(y) x(y)

#define rrep(i,n) for(int  i=((int)n)-1;i>=0;--i)
#define rall(c) (c).rbegin(),(c).rend()
#define rrep2(i,a,b) for(int i=(a);i>=((int)b);--i)
#define rforeach(it,c) for(__typeof((c).rbegin()) it=(c).rbegin();it!=(c).rend();++it)
#define rep2d(i, j, v) rep(i, sz(v)) rep(j, sz(v[i]))
#define foreach2d(i, j, v) foreach(i,v) foreach(j,*i)


#define MAXLENGTH 600010

char str[MAXLENGTH+1]; //the string we are building its suffix array
int suf[MAXLENGTH+1]; // the sorted array of suffix indices
int group[MAXLENGTH+1]; //index in this array is the same as suffix index
int sorGroup[MAXLENGTH+1<128?128:MAXLENGTH+1]; //index in this array is the same as the
int groupStart[MAXLENGTH+1]; //the start index in the sorted array of the current group
int newSuf[MAXLENGTH+1]; //temp array to store in it the new sorted array

void buildSuffixArray()
{
	int n;//number of suffixes
	memset(sorGroup,-1,(sizeof sorGroup[0])*128);
	for(n=0;n-1<0 || str[n-1];n++)  //count sort on the first char of suffix
									//treat sorGroup as head of linked list and newSuf as next
		newSuf[n]=sorGroup[str[n]],sorGroup[str[n]]=n;
	int numGroup=-1,j=0; //using the data computed in count sort
	for(int i=0;i<128;i++) //compute the groups and groupStart and starting suf
		if(sorGroup[i]!=-1)
		{
			groupStart[++numGroup]=j;
			int cur=sorGroup[i];
			while(cur!=-1)
			{
				suf[j++]=cur;
				group[cur]=numGroup;
				cur=newSuf[cur];
			}
		}
	sorGroup[0]=sorGroup[n-1]=0; //assume that the first group index 0 for next iteration;
	newSuf[0]=suf[0]; //put the empty suffix to be the smallest suffix
	for(int h=1;sorGroup[n-1]!=n-1;h<<=1) //loop until the number of groups=number of suffixes
	{
		for(int i=0;i<n;i++) //sort using 2h in the array newSuf
		{
			int j=suf[i]-h;
			if(j<0) continue;
			newSuf[groupStart[group[j]]++]=j;
		}
		for(int i=1;i<n;i++) //compute the 2h group data given h group data
		{
			bool newgroup=(group[newSuf[i-1]]<group[newSuf[i]] || group[newSuf[i-1]]==group[newSuf[i]] && group[newSuf[i-1]+h]<group[newSuf[i]+h]);
			sorGroup[i]=sorGroup[i-1] + newgroup;
			if(newgroup)
				groupStart[sorGroup[i]]=i;
		}
		for(int i=0;i<n;i++) //copy the computed newSuf groups to the group and suf array
		{
			suf[i]=newSuf[i];
			group[suf[i]]=sorGroup[i];
		}
	}
}
int main() {
std::ios_base::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen("1.in","rt",stdin);
	//freopen("1.out","wt",stdout);
#endif
	while(gets(str))
	{
		int len=strlen(str);
		str[len]=str[0];
		rep(i,len)
		{
			int dif=(str[i+1]-str[i]+8)&7;
			str[i]=dif+'0';
		}
		memcpy(str+len,str,len);
		str[2*len]=0;
		buildSuffixArray();
		rep(i,2*len+1)
		{
			if(suf[i]<len)
			{
				str[suf[i]+len]=0;
				cout<<str+suf[i]<<endl;
				break;
			}
		}
	}
	return 0;
}
