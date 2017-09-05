#include<string>
#include<iostream>
#include <map>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#include<set>
#include<bitset>
#include<utility>
#include<cstring>
#include<climits>
#include<cassert>
#include<fstream>
using namespace std;
#define LL long long int
#define mfor(i,n) for(int i=0;i<n;i++)
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define FORL(i,a,b) for(long long int i=a;i<=b;i++)
#define RFOR(i,a,b) for(int i=a;i>=b;i--)
#define SND(x) int (x); cin>>x;
#define SNF(x) float (x); cin>>x;
#define OPEN freopen("input.txt","r",stdin)
#define WRITE freopen("input.txt","w",stdout)
#define pb push_back
#define mp make_pair
#define IS_ODD( num ) ((num) & 1)
#define IS_EVEN( num ) (!IS_ODD( (num) ))
#define MEM(dest,val) memset(dest,val,sizeof(dest))
float dist(float x1,float y1,float x2,float y2){
    float X,Y;
    X=abs(x1-x2);
    Y=abs(y1-y2);
    return sqrt((X*X)+(Y*Y));
}
int main(){
    OPEN;
    int num_of_edges,num_of_nodes=10,fuck1,fuck2;
    //f1>>num_of_nodes;
    //f1>>fuck1;
    vector<pair<float,float> >vec;
    float a[]={1.81 ,11.27,1.92, 16.82,2.91, 13.04,5.62, 5.64,7.18, 6.95,7.95 ,16.42,9.71, 12.38,14.41, 0.67,15.67, 14.99,18.69, 18.24};
    for(int i=0;i<19;i+=2){
        //int t1,t2;
        //f1>>t1>>t2;
        vec.pb(mp(a[i],a[i+1]));
    }
    assert(vec.size()==num_of_nodes);
    cin>>fuck1;
    cin>>fuck2;
    cin>>num_of_edges;
    mfor(i,num_of_edges){
        int t1,t2;
        cin>>t1>>t2;
        cout<<i<<"   distance between "<<t1<<" and "<<t2<<"  =  "<<dist(vec[t1].first,vec[t1].second,vec[t2].first,vec[t2].second)<<endl;
    }
    return 0;
}
