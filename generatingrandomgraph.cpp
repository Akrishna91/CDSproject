#include<cstdlib>
#include<string>
#include<iostream>
#include <unordered_map>
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
#define WRITE freopen("in.txt","w",stdout)
#define pb push_back
#define mp make_pair
#define IS_ODD( num ) ((num) & 1)
#define IS_EVEN( num ) (!IS_ODD( (num) ))
#define MEM(dest,val) memset(dest,val,sizeof(dest))
int main(){
    ofstream out("in.txt");
    cout<<"enter the number of nodes of graph"<<endl;
    SND(num);
    int range=100;
    out<<num<<"\n"<<range<<endl;
    float t1,t2;
    int temp1,temp2;
    unordered_map<float,float>mymap;
    mymap.clear();
    unordered_map<float,float>::iterator it;
    while(mymap.size()!=num){
        t1=(rand()%100)/100.00;
        t2=(rand()%100)/100.00;
        //cout<<t1<<" "<<t2<<endl;
        temp1=rand()%500;
        temp2=rand()%500;
        mymap[temp1+t1]=temp2+t2;
    }
    //int ct=0;
    for(it=mymap.begin();it!=mymap.end();it++){
        out<<it->first<<" "<<it->second<<"\n";//ct++;
    }
    //vector<float,float>vec(mymap.begin(),)
    return 0;
}
