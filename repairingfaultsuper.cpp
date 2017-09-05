#include<string>
#include<cstdlib>
#include<queue>
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
using namespace std;
//------------------------------defined tokens-----------------------------------//
#define mfor(i,n) for(int i=0;i<n;i++)
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define RFOR(i,a,b) for(int i=a;i>=b;i--)
#define SCANFILE freopen("input.txt","r",stdin)
#define OUTPUT freopen("output.txt","w",stdout)
#define pb push_back
#define mp make_pair
#define IS_ODD( num ) ((num) & 1)
#define MEM(dest,val) memset(dest,val,sizeof(dest))
#define INF 1000000000
//-------------------------------type definitions---------------------------------//
typedef pair<int,int>ii;
typedef vector<int>vi;
typedef vector<ii>vii;
typedef pair<int,string>is;
//--------------------------------global variables---------------------------------------//
vector<vii>AdjListV;
vi p;
map<int,string> initgraph,curgraph;
map<int,string>::iterator it;
map<int,set<int> > AdjList,tempAdjList,initAdjList;
map<int,set<int> >::iterator adjit;
set<int>WhiteSet,BlackSet,GreySet,CheckBlackSet,ConnectedtoFailed;
set<int>::iterator setit,setit1,setit2;
map<pair<int,string>,int >AdjacentColor;
map<pair<int,string>,int >::iterator adjclriter;
int num_of_nodes,num_of_edges,failed,size_of_graph;
int source,target;
void printPathandChngetoWhite(int u){
    curgraph[u]="white";
    if(u==source)return;//{printf("%d",u);return; }
    printPathandChngetoWhite(p[u]);
    //printf(" %d\n",u);
    curgraph[u]="white";
}
void updateAdjacntNodeWBGSet(){
    AdjacentColor.clear();BlackSet.clear();WhiteSet.clear();GreySet.clear();
    for(adjit=AdjList.begin();adjit!=AdjList.end();adjit++){
        int tar1=0,tar2=0,tar3=0;
        AdjacentColor[mp(adjit->first,"black") ]=0;
        AdjacentColor[mp(adjit->first,"grey") ]=0;
        AdjacentColor[mp(adjit->first,"white") ]=0;
        for(setit=adjit->second.begin();setit!=adjit->second.end();setit++){
            if(curgraph[*setit]=="black"){AdjacentColor[mp(adjit->first,"black") ]++;}
            else if(curgraph[*setit]=="grey"){AdjacentColor[mp(adjit->first,"grey") ]++;}
            else if(curgraph[*setit]=="white"){AdjacentColor[mp(adjit->first,"white") ]++;}
        }

    }
    //update color sets

    assert(WhiteSet.size()==0 && BlackSet.size()==0 && GreySet.size()==0);
    for(it=curgraph.begin();it!=curgraph.end();it++){
        if(it->second=="white")WhiteSet.insert(it->first);
        else
        if(it->second=="black")BlackSet.insert(it->first);
        else
        if(it->second=="grey")GreySet.insert(it->first);
    }
    assert((AdjacentColor.size()/3)==AdjList.size());
    assert(AdjList.size()==curgraph.size());
    //cout<<"t=   "<<(BlackSet.size()+WhiteSet.size()+GreySet.size());
    //cout<<"\nsize of curgraph=  "<<curgraph.size()<<endl;
    int t=(BlackSet.size()+WhiteSet.size()+GreySet.size());
    assert(curgraph.size()==t);
}
void initCDS(){
    //make all nodes white
    for(it=curgraph.begin();it!=curgraph.end();it++){
        it->second="white";
    }
    updateAdjacntNodeWBGSet();
    //select the node with greatest number of white nodes and then turn it black
    //then change its adjacent to grey if it is not black
    //repeat these two steps until there is no white


    //first step different as u r reqd to choose from white connected to max white
    assert(WhiteSet.size()==curgraph.size());//all are white
    for(it=curgraph.begin();it!=curgraph.end();it++){
        assert(AdjacentColor[mp(it->first,"grey")]==0);
        assert(AdjacentColor[mp(it->first,"black")]==0);
    }
    int tar=-1;int mx=-1;
    for(it=curgraph.begin();it!=curgraph.end();it++){
        if(AdjacentColor[mp(it->first,"white") ]>mx){mx=AdjacentColor[mp(it->first,"white") ];tar=it->first;assert(it->second=="white");}
    }
    assert(tar>=0);
    curgraph[tar]="black";
    updateAdjacntNodeWBGSet();
    //convert its adjacents to grey
    for(setit=AdjList[tar].begin();setit!=AdjList[tar].end();setit++){
        curgraph[*setit]="grey";
    }
    updateAdjacntNodeWBGSet();
    //cout<<"tar ==  "<<tar<<endl;
    //now u r reqd to choose from grey

    while(WhiteSet.size()!=0){
        mx=-1;tar=-1;
        for(setit1=GreySet.begin();setit1!=GreySet.end();setit1++){
            int t=AdjacentColor[mp(*setit1,"white") ];
            if(t>mx){mx=t;tar=*setit1;}
        }
        assert(mx>0 && tar>=0);
        assert(GreySet.find(tar)!=GreySet.end());
        curgraph[tar]="black";
        updateAdjacntNodeWBGSet();
        //converting its adjacents to grey which are not black
        for(setit1=AdjList[tar].begin();setit1!=AdjList[tar].end();setit1++){
            if(curgraph[*setit1]!="black")curgraph[*setit1]="grey";
        }
        updateAdjacntNodeWBGSet();

    }
}
bool poss(){
    cout<<"removing node  "<<failed<<endl;
    //creating temporary variables
    tempAdjList.clear();
    assert(tempAdjList.size()==0);
    tempAdjList.insert(AdjList.begin(),AdjList.end());
    assert(tempAdjList.size()==AdjList.size());
    //clearing tempAdjlist
    assert(tempAdjList.find(failed)!=tempAdjList.end());
    ConnectedtoFailed.clear();
    assert(ConnectedtoFailed.size()==0);
    ConnectedtoFailed.insert(tempAdjList[failed].begin(),tempAdjList[failed].end());
    assert(ConnectedtoFailed.size()==tempAdjList[failed].size());
    tempAdjList.erase(failed);
    for(adjit=tempAdjList.begin();adjit!=tempAdjList.end();adjit++){
        if(adjit->second.find(failed)!=adjit->second.end()){adjit->second.erase(failed);}
    }
    //search for a node connected to no other node and if there is even one delete it
    for(adjit=tempAdjList.begin();adjit!=tempAdjList.end();adjit++){
        if(adjit->second.size()==0)tempAdjList.erase(adjit->first);
    }
    //if size of tempadjlist is only one less then graph is connected else not
    if(tempAdjList.size()==(AdjList.size()-1)){
        AdjList.clear();
        assert(AdjList.size()==0);
        AdjList.insert(tempAdjList.begin(),tempAdjList.end());
        assert(AdjList.size()==tempAdjList.size());
        curgraph.erase(failed);
        updateAdjacntNodeWBGSet();
        return true;
    }
    else return false;
}
void GenCDS(){
    //make all white nodes grey connected to any of black nodes
    for(setit1=BlackSet.begin();setit1!=BlackSet.end();setit1++){
        for(setit=AdjList[*setit1].begin();setit!=AdjList[*setit1].end();setit++){
            if(curgraph[*setit]=="white")curgraph[*setit]="grey";
        }
    }
    updateAdjacntNodeWBGSet();
    //make all white nodes grey connected to the target
    assert(BlackSet.find(target)!=BlackSet.end());
    for(setit=AdjList[target].begin();setit!=AdjList[target].end();setit++){
        if(curgraph[*setit]=="white")curgraph[*setit]="grey";
    }
    updateAdjacntNodeWBGSet();
    while(WhiteSet.size()!=0){
        int mx=-1,tar=-1;
        for(setit1=GreySet.begin();setit1!=GreySet.end();setit1++){
            if(AdjacentColor[mp(*setit1,"white") ]>mx){mx=AdjacentColor[mp(*setit1,"white") ];tar=*setit1;}
        }
        assert(tar>=0);
        curgraph[tar]="black";
        //making its neighbours grey if they are white
        for(setit1=AdjList[tar].begin();setit1!=AdjList[tar].end();setit1++){
            if(curgraph[*setit1]=="white")curgraph[*setit1]="grey";
        }
        updateAdjacntNodeWBGSet();

    }
    assert(WhiteSet.size()==0);
    assert(curgraph.size()==(GreySet.size()+BlackSet.size()));
}
int main(){
    SCANFILE;
    //OUTPUT;
    scanf("%d",&num_of_nodes);
    scanf("%d",&size_of_graph);
    scanf("%d",&num_of_edges);
    AdjList.clear();
    mfor(i,num_of_edges){
        int t1,t2;
        scanf("%d %d",&t1,&t2);
        AdjList[t1].insert(t2);
        AdjList[t2].insert(t1);
        curgraph[t1]="white";
        curgraph[t2]="white";
    }
    initCDS();
    updateAdjacntNodeWBGSet();
    //for(it=curgraph.begin();it!=curgraph.end();it++)cout<<it->first<<"   "<<it->second<<endl;
    cout<<"number of nodes in the graph  "<<size_of_graph<<endl;
    cout<<"size of dominant nodes in the graph  "<<BlackSet.size()<<endl;
    initgraph.clear();
    assert(initgraph.size()==0);
    initgraph.insert(curgraph.begin(),curgraph.end());
    assert(initgraph.size()==curgraph.size());
    initAdjList.clear();
    assert(initAdjList.size()==0);
    initAdjList.insert(AdjList.begin(),AdjList.end());
    assert(initAdjList.size()==AdjList.size());
    CheckBlackSet.clear();
    assert(CheckBlackSet.size()==0);
    CheckBlackSet.insert(BlackSet.begin(),BlackSet.end());
    assert(CheckBlackSet.size()==BlackSet.size());
    assert(CheckBlackSet.size()>3);
    int c=0;
    float totcnt=0.00,cnt=0.00,cntfail=0.00;
    //------------------------------------------failing the node---------------------------//
    for(setit2=CheckBlackSet.begin();setit2!=CheckBlackSet.end();setit2++){
        failed=*setit2;
        if(!poss()){
            break;}
        else{
            cnt=0;
            //if(c>((CheckBlackSet.size())/10))break;
            cntfail++;
            //------------------turning all nodes connected to failed node white except those which are white and connected to mpre than one including at least
            //--------------------one black--------------------------//
            for(setit1=ConnectedtoFailed.begin();setit1!=ConnectedtoFailed.end();setit1++){
                if(curgraph[*setit1]=="black" && AdjList[*setit1].size()>1 && AdjacentColor[mp(*setit1,"black")]>=1);
                else curgraph[*setit1]="white";
            }
            updateAdjacntNodeWBGSet();
            if(WhiteSet.size()==0)break;//reason for breaking at this point is there may be a case where there is existence of CDS
            //even after failure of a dominant node because Guha is not an optimal algorithm
            assert(WhiteSet.size()>0);
            assert(BlackSet.size()>2);
            //---------------------------choosing the node for source of bfs------------------------------------//
            //------------------------choose white node connected to most number of 1.black 2.grey 3.white----------------//
            int mx1=-1,mx2=-1,mx3=-1,tar1=-1,tar2=-1,tar3=-1;source=-1;
            for(it=curgraph.begin();it!=curgraph.end();it++){
                if(it->second=="white"){
                    if(AdjacentColor[mp(it->first,"black") ]>mx1){mx1=AdjacentColor[mp(it->first,"black") ];tar1=it->first;}
                    else if(AdjacentColor[mp(it->first,"grey") ]>mx2){mx2=AdjacentColor[mp(it->first,"grey") ];tar2=it->first;}
                    else if(AdjacentColor[mp(it->first,"white") ]>mx3){mx3=AdjacentColor[mp(it->first,"white") ];tar3=it->first;}
                }
            }
            if(mx1>0)source=tar1;
            else if(mx2>0)source=tar2;
            else if(mx3>0)source=tar3;
            //---------------------------starting bfs-----------------------------//
            assert(source>=0);
            assert(WhiteSet.find(source)!=WhiteSet.end());
            AdjListV.clear();
            assert(AdjListV.size()==0);
            AdjListV.assign(num_of_nodes,vii());
            for(adjit=AdjList.begin();adjit!=AdjList.end();adjit++){
                for(setit=adjit->second.begin();setit!=adjit->second.end();setit++){
                    AdjListV[adjit->first].pb(ii(*setit,0));
                }
            }
            //assert(AdjList.size()==AdjListV.size());//not true because there are some nodes
            //having no adjacent nodes
            target=-1;
            p.clear();
            assert(p.size()==0);
            vi dist(size_of_graph,1000000000);dist[source]=0;
            queue<int>q;q.push(source);
            p.assign(num_of_nodes,-1);
            int layer=-1;
            while(!q.empty()){
                int u=q.front();q.pop();
                //if(dist[u]!=layer)printf("\nlayer %d:",dist[u]);
                layer=dist[u];
                //printf("visit %d, ",u);
                mfor(j,AdjListV[u].size()){
                    ii v=AdjListV[u][j];
                    if(dist[v.first]==1000000000){
                        dist[v.first]=dist[u]+1;
                        p[v.first]=u;
                        if(BlackSet.find(v.first)!=BlackSet.end()){target=v.first;goto l1;}//as soon as we find element of Dominating Set we break
                        q.push(v.first);
                    }
                }
            }
            l1:
            assert(BlackSet.find(target)!=BlackSet.end());
            printPathandChngetoWhite(target);
            curgraph[target]="black";
            updateAdjacntNodeWBGSet();
            assert(WhiteSet.size()!=0);
            GenCDS();
            updateAdjacntNodeWBGSet();
            //-------------------deducing results----------------------------//
            //cnt is the number of grey nodes converted to black in this session
            //cntfail is variable used to keep track of number of single node failures
            for(it=initgraph.begin();it!=initgraph.end();it++){
                if(it->second=="grey" && BlackSet.find(it->first)!=BlackSet.end())cnt++;
            }
            cout<<"number of non dominants converting to dominants in this case is  "<<cnt<<endl;
            totcnt+=cnt;
            //-------------making curgraph & adjlist ready for next iteration-------------------------//
            curgraph.clear();
            AdjList.clear();
            assert(curgraph.size()==0 && AdjList.size()==0);
            curgraph.insert(initgraph.begin(),initgraph.end());
            assert(curgraph.size()==initgraph.size());
            assert(AdjList.size()==0);
            AdjList.insert(initAdjList.begin(),initAdjList.end());
            updateAdjacntNodeWBGSet();
            c++;
        }
    }
    cout<<"------------------Results---------------------------------"<<endl;
    cout<<"total single node failures  "<<cntfail<<" out of "<<BlackSet.size()<<endl;
    float res=totcnt/cntfail;
    cout<<"average non dominant nodes converting to dominant nodes  "<<(totcnt/cntfail)<<endl;
    //cout<<"sum is "<<totcnt<<endl;
    return 0;
}
