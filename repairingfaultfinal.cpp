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
#define SCAND(x)  scanf("%d",&(x))
#define LL long long int
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
map<int,set<int> > AdjList;
map<int,set<int> >::iterator adjit;
set<int>WhiteSet,BlackSet,GreySet,FailedSet,CheckBlackSet;
set<int>::iterator setit,setit1,setit2;
map<pair<int,string>,int >AdjacentColor;
map<pair<int,string>,int >::iterator adjclriter;
int num_of_nodes,num_of_edges,failed,size_of_graph;
int id,u,v,source,target,mx;
string color;
void printPathandChngetoWhite(int u){
    curgraph[u]="white";
    if(u==source)return;//{printf("%d",u);return; }
    printPathandChngetoWhite(p[u]);
    //printf(" %d\n",u);
    curgraph[u]="white";
}
void initCDS(){
    //choose the white node connected to max number of white nodes
    //make it black and then make its all adjacent grey
    //choose grey with maximum number of white
    //repeat until none is white

    int mxsz=0,tar;
    for(adjit=AdjList.begin();adjit!=AdjList.end();adjit++)
        if(adjit->second.size()>=mxsz){mxsz=adjit->second.size();tar=adjit->first;}
    //cout<<"first black node is "<<tar<<endl;
    for(setit=AdjList[tar].begin();setit!=AdjList[tar].end();setit++){
            //cout<<*setit;
            curgraph[*setit]="grey";GreySet.insert(*setit);WhiteSet.erase(*setit);
    }

    WhiteSet.erase(tar);BlackSet.insert(tar);
    /*for(auto i:GreySet)cout<<i<<"        ";cout<<endl;
        for(auto i:WhiteSet)cout<<i<<"        ";cout<<endl;
        for(auto i:BlackSet)cout<<i<<"        ";cout<<endl;*/
    //-------choose grey having max umber of white---------------------//
    while(WhiteSet.size()!=0){
        mxsz=0;int cnt=0;tar=-1;
        /*cout<<"greyset";for(auto i:GreySet)cout<<i<<"  ";cout<<endl;
        cout<<"whiteset";for(auto i:WhiteSet)cout<<i<<"  ";cout<<endl;
        cout<<"blacksetset";for(auto i:BlackSet)cout<<i<<"  ";cout<<endl;*/
        assert(GreySet.size()!=0 && WhiteSet.size()!=0);
        for(setit=GreySet.begin();setit!=GreySet.end();setit++){
            cnt=0;//cout<<*setit<<endl;
            for(setit1=AdjList[*setit].begin();setit1!=AdjList[*setit].end();setit1++)
                if(WhiteSet.find(*setit1)!=WhiteSet.end())cnt++;
            if(cnt>mxsz){mxsz=cnt;tar=*setit;}
        }
        BlackSet.insert(tar);GreySet.erase(tar);//cout<<tar<<endl;

        for(setit=AdjList[tar].begin();setit!=AdjList[tar].end();setit++){
            if(WhiteSet.find(*setit)!=WhiteSet.end()){
                //cout<<*setit<<endl;
                WhiteSet.erase(*setit);GreySet.insert(*setit);
            }
        }
    }

}

void updAjntClrBWGset(){
    //------------------finding the color of neighbours of each node----------------//

    assert(curgraph.size()!=0);
    AdjacentColor.clear();

    BlackSet.clear();

    WhiteSet.clear();

    GreySet.clear();

    for(adjit=AdjList.begin();adjit!=AdjList.end();adjit++){

        int cnt1=0,cnt2=0,cnt3=0;
        for(setit=adjit->second.begin();setit!=adjit->second.end();setit++){
            if(curgraph[*setit]=="white"){cnt1++;WhiteSet.insert(*setit);}
            else if(curgraph[*setit]=="black"){cnt2++;BlackSet.insert(*setit);}
            else {cnt3++;GreySet.insert(*setit);}
        }
        AdjacentColor[mp(adjit->first,"black")]=cnt2;
        AdjacentColor[mp(adjit->first,"grey")]=cnt3;
        AdjacentColor[mp(adjit->first,"white")]=cnt1;
        if((cnt1+cnt2+cnt3)==0){                       //node is not connected to the graph
            int temp=adjit->first;
            AdjacentColor.erase(AdjacentColor.find(mp(temp,"black")));
            AdjacentColor.erase(AdjacentColor.find(mp(temp,"grey")));
            AdjacentColor.erase(AdjacentColor.find(mp(temp,"white")));
            curgraph.erase(curgraph.find(temp));
            WhiteSet.erase(temp);BlackSet.erase(temp);GreySet.erase(temp);
        }
    }
}
void genCDS(){
    //------------------------clean up-------------------------------//
    //general CDS
    //choose the white node and change all non black connected to it and
    //not connected to any black node to white
    //change all white nodes connected to black nodes to grey

    cout<<"whteset size  "<<WhiteSet.size()<<endl;
    for(setit1=WhiteSet.begin();setit1!=WhiteSet.end();setit1++){
        for(setit=AdjList[*setit1].begin();setit!=AdjList[*setit1].end();setit++){
            if(BlackSet.find(*setit)==BlackSet.end() && AdjacentColor[mp(*setit,"black")]==0)
                curgraph[*setit]="white";
        }
    }
    for(setit1=BlackSet.begin();setit1!=BlackSet.end();setit1++){
        for(setit=AdjList[*setit1].begin();setit!=AdjList[*setit1].end();setit++){
            if(WhiteSet.find(*setit)!=WhiteSet.end())
                curgraph[*setit]="grey";
        }
    }
    updAjntClrBWGset();
    int tar=source;
    //cout<<curgraph[tar];
    //assert(curgraph[tar]=="grey");
    //---------------------choose grey with max number of white---------------------//
    while(AdjacentColor[mp(tar,"white") ]!=0){
        curgraph[tar]="black";
        for(setit1=AdjList[tar].begin();setit1!=AdjList[tar].end();setit1++){
            if(curgraph[*setit1]=="white")curgraph[*setit1]="grey";
        }
        updAjntClrBWGset();
        //tar will be the grey guy having max number of white
        int mx=0,t;is x;
        for(adjclriter=AdjacentColor.begin();adjclriter!=AdjacentColor.end();adjclriter++){
            x=adjclriter->first;
            if(GreySet.find(x.first)!=GreySet.end() && AdjacentColor[mp(x.first,"white") ]>mx){
                mx=AdjacentColor[mp(x.first,"white") ];tar=x.first;
            }
        }
        updAjntClrBWGset();
    }

}
int main(){
    SCANFILE;
    //OUTPUT;
    int c=0;
    SCAND(size_of_graph);
    SCAND(num_of_nodes);
    cout<<"number of nodes in this graph   "<<num_of_nodes<<endl;
    //mfor(i,num_of_nodes){initgraph[i]="white";WhiteSet.insert(i);}
    SCAND(num_of_edges);
    mfor(i,num_of_edges){
        int t1,t2;
        scanf("%d %d",&t1,&t2);
        AdjList[t1].insert(t2);
        AdjList[t2].insert(t1);
        initgraph[t1]="white";
        initgraph[t2]="white";
        WhiteSet.insert(t1);
        WhiteSet.insert(t2);
    }
    curgraph.insert(initgraph.begin(),initgraph.end());
    //updAjntClrBWGset();

    initCDS();
    initgraph.clear();
    initgraph.insert(curgraph.begin(),curgraph.end());
    assert(BlackSet.size()>3);
    //position of graph
    //printf("=================in initial graph=============\n");
    assert(WhiteSet.size()==0);
    /*printf("black nodes are\n");
    for(setit1=BlackSet.begin();setit1!=BlackSet.end();setit1++){
        printf("%d\n",*setit1);
    }

    printf("grey nodes are\n");
    for(setit1=GreySet.begin();setit1!=GreySet.end();setit1++){
        printf("%d\n",*setit1);
    }*/
    //-------------------------------Updating the initial graph map-----------------------------------------------//
    initgraph.clear();
    for(auto i:WhiteSet)initgraph[i]="white";
    for(auto i:BlackSet)initgraph[i]="black";
    for(auto i:GreySet)initgraph[i]="grey";
    //copying contents into Current working graph
    curgraph.clear();
    curgraph.insert(initgraph.begin(),initgraph.end());
    updAjntClrBWGset();
    //for(it=initgraph.begin();it!=initgraph.end();it++)cout<<it->first<<"    "<<it->second<<endl;
    //for(it=curgraph.begin();it!=curgraph.end();it++)cout<<it->first<<"    "<<it->second<<endl;
    //---------------------------------------------now failing the nodes------------------------------------------//
    //printf("enter number of nodes to be failed\n");
    //SCAND(failed);//taking input
    CheckBlackSet.clear();
    CheckBlackSet.insert(BlackSet.begin(),BlackSet.end());
    cout<<"size of Blackset is  "<<BlackSet.size()<<"   "<<CheckBlackSet.size()<<endl;
    for(setit2=CheckBlackSet.begin();setit2!=CheckBlackSet.end();setit2++)

        {


    failed=1;
    curgraph.clear();
    curgraph.insert(initgraph.begin(),initgraph.end());
    updAjntClrBWGset();
    //assert(BlackSet.size()>=failed);
    /*for(setit1=BlackSet.begin();setit1!=BlackSet.end();setit1++){
        printf("%d\n",*setit1);
    }

    printf("grey nodes are\n");
    for(setit1=GreySet.begin();setit1!=GreySet.end();setit1++){
        printf("%d\n",*setit1);
    }*/
    //assert(BlackSet.size()>=failed);
    //making a vector to store the elements of BlackSet to facilitate random selection
    vector<int>BlackVector(BlackSet.begin(),BlackSet.end());
   // assert(BlackSet.size()==BlackVector.size());
    FailedSet.clear();
    while(FailedSet.size()!=failed)
        FailedSet.insert(*setit2);
    cout<<"failed Black Nodes are\n   ";for(auto i:FailedSet)cout<<i<<"      ";cout<<endl;
    //making all failed nodes deleted from graph Blackset and Adjacency list
    for(setit1=FailedSet.begin();setit1!=FailedSet.end();setit1++){
        BlackSet.erase(*setit1);curgraph.erase(curgraph.find(*setit1));
        for(adjit =AdjList.begin();adjit!=AdjList.end();adjit++)      //erasing link if it is connected to some other nodes
            if(adjit->second.find(*setit1)!=adjit->second.end())
                adjit->second.erase(*setit1);
    }
    updAjntClrBWGset();
    BlackVector.clear();BlackVector.assign(BlackSet.begin(),BlackSet.end());
    for(setit1=FailedSet.begin();setit1!=FailedSet.end();setit1++){
        for(setit=AdjList[*setit1].begin();setit!=AdjList[*setit1].end();setit++){
            if(curgraph[*setit]=="black" && AdjList[*setit].size()>1 && AdjacentColor[mp(*setit,"black")]>=1);
            else curgraph[*setit]="white";
        }
    }
    updAjntClrBWGset();
    //deleting nodes connected to failed nodes
    for(setit1=FailedSet.begin();setit1!=FailedSet.end();setit1++)AdjList.erase(*setit1);
    /*cout<<"checking adcent color datastructuren\n";
    for(it=curgraph.begin();it!=curgraph.end();it++){
        cout<<it->first<<"       "<<it->second<<endl;
        /*cout<<AdjacentColor[mp((it->first),"white")]<<"  ";
        cout<<AdjacentColor[mp((it->first),"black")]<<"  ";
        cout<<AdjacentColor[mp((it->first),"grey")]<<"  ";
        cout<<endl;
    }*/

    //checking if the graph obtained is connected or not
    //reqd to be done
    //getting rid of nodes having no adjacents
    //cout<<"printing Adjlist\n";
    /*for(adjit=AdjList.begin();adjit!=AdjList.end();adjit++)
        if(adjit->second.size()==0)
            AdjList.erase(AdjList.find(adjit->first));*/
    /*for(adjit=AdjList.begin();adjit!=AdjList.end();adjit++)
    {
        cout<<adjit->first<<"=====>            ";
        for(setit=adjit->second.begin();setit!=adjit->second.end();setit++)cout<<*setit<<"   ";
        cout<<endl;
    }*/

    //cout<<BlackSet.size();
    //---------------------------all cleanup done------------------------------------------//
    if(BlackSet.size()==0){//no advantage of this algorithm
        //make all nodes white and then use the INItial CdS
        for(it=curgraph.begin();it!=curgraph.end();it++)
            it->second="white";


        updAjntClrBWGset();
        initCDS();

        //updated result in blackset and previous result in initgraph
        //compare the white nodes converted to black
    }
    else{

        //bfs to nearest blacknode
        AdjListV.assign(size_of_graph,vii());
        for(adjit=AdjList.begin();adjit!=AdjList.end();adjit++){
            for(setit=adjit->second.begin();setit!=adjit->second.end();setit++){
                AdjListV[adjit->first].pb(ii(*setit,0));
            }
        }
        //viewing new adjacency list vector
   /* mfor(i,AdjListV.size()){
        cout<<i<<"====>  ";
        mfor(j,AdjListV[i].size()){

            ii x=AdjListV[i][j];
            cout<<x.first<<"            ";
        }
        cout<<endl;
    }*/
    //first selecting a source
    //should be a white node connected to max nodes in order1.black 2.grey 3.white
    //traversing through whiteclrset set to make a vector containing white nodes
    if(WhiteSet.size()==0)break;
    vi Whitevec;
    for(setit=WhiteSet.begin();setit!=WhiteSet.end();setit++){
        Whitevec.pb(*setit);
    }

    //cout<<"size of Blackset is  "<<BlackSet.size()<<endl;
    //traversing through adjacent color set to find nodes of particular color
    int black=AdjacentColor[mp(Whitevec[0],"black")];
    int grey=AdjacentColor[mp(Whitevec[0],"grey")];
    int white=AdjacentColor[mp(Whitevec[0],"white")];
    int tar1=Whitevec[0],tar2=Whitevec[0],tar3=Whitevec[0];
    FOR(i,1,Whitevec.size()-1){
        if(AdjacentColor[mp(Whitevec[i],"black")]>black){tar1=Whitevec[i];black=AdjacentColor[mp(Whitevec[i],"black")];}
        if(AdjacentColor[mp(Whitevec[i],"grey")]>grey){tar1=Whitevec[i];grey=AdjacentColor[mp(Whitevec[i],"grey")];}
        if(AdjacentColor[mp(Whitevec[i],"white")]>white){tar1=Whitevec[i];white=AdjacentColor[mp(Whitevec[i],"white")];}
    }

    if(black>0)source=tar1;
    else if(grey>0)source=tar2;
    else if(white>0)source=tar3;
    target=-1;
    cout<<"our source for breadth first search is      "<<source<<endl;
    //-------------------------starting bfs-------------------------------------//
    //while(WhiteSet.size()!=0){
            vi dist(size_of_graph,1000000000);dist[source]=0;
            queue<int>q;q.push(source);
            p.assign(num_of_nodes,-1);
            int layer=-1;
            while(!q.empty()){
                int u=q.front();q.pop();
                if(dist[u]!=layer)printf("\nlayer %d:",dist[u]);
                layer=dist[u];
                printf("visit %d, ",u);
                mfor(j,AdjListV[u].size()){
                    ii v=AdjListV[u][j];
                    if(dist[v.first]==1000000000){
                        dist[v.first]=dist[u]+1;
                        p[v.first]=u;
                        if(BlackSet.find(v.first)!=BlackSet.end()){target=v.first;goto l;}//as soon as we find element of Dominating Set we break
                        q.push(v.first);
                    }
                }
            }
            l:
            cout<<"target is           "<<target<<endl;

            printPathandChngetoWhite(target);
            curgraph[target]="black";
            updAjntClrBWGset();
            /*cout<<"black===>";for(auto i:BlackSet)cout<<i<<"        ";cout<<endl;
            cout<<"white===>";for(auto i:WhiteSet)cout<<i<<"        ";cout<<endl;
            cout<<"grey===>";for(auto i:GreySet)cout<<i<<"        ";cout<<endl;
            */
            genCDS();
            updAjntClrBWGset();
            /*cout<<"black===>";for(auto i:BlackSet)cout<<i<<"        ";cout<<endl;
            cout<<"white===>";for(auto i:WhiteSet)cout<<i<<"        ";cout<<endl;
            cout<<"grey===>";for(auto i:GreySet)cout<<i<<"        ";cout<<endl;
            */
    //}
    //now the number of non dominating nodes changed to dominating can be get by
    //comparing initgraph and blackset
    }
    /*cout<<"final arrangement"<<endl;
    cout<<"black===>";for(auto i:BlackSet)cout<<i<<"        ";cout<<endl;
    cout<<"white===>";for(auto i:WhiteSet)cout<<i<<"        ";cout<<endl;
    cout<<"grey===>";for(auto i:GreySet)cout<<i<<"        ";cout<<endl;
    */
    cout<<"number of non dominant nodes which converted to dominant nodes are\n";
    //assert(WhiteSet.size()==0);//assuring that every node s just black or white
    c=0;
    for(it=initgraph.begin();it!=initgraph.end();it++){
        if(it->second=="grey" && BlackSet.find(it->first)!=BlackSet.end())
            c++;
    }
    cout<<c<<endl;
    curgraph.clear();
    curgraph.insert(initgraph.begin(),initgraph.end());
    updAjntClrBWGset();
}
    cout<<"\t"<<(c/CheckBlackSet.size())<<endl;
    return 0;
}
