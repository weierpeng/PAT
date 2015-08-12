
#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
using namespace::std;


struct HuffmanCodesNode {
    bool isLeaf;
    int frequence;
    char c;
    int d;
    HuffmanCodesNode *Child[2];

    HuffmanCodesNode(char ch,int f){
        Child[0]=NULL;
        Child[1]=NULL;
        c=ch;
        frequence=f;
        isLeaf=true;
        d=0;
    }
    HuffmanCodesNode(HuffmanCodesNode *h1=NULL,HuffmanCodesNode *h2=NULL):isLeaf(false),frequence(0),c(0),d(0){
        Child[0]=h1;
        Child[1]=h2;
    }

    void clear(){
        if(Child[0]!=NULL){Child[0]->clear();delete Child[0];}
        if(Child[1]!=NULL){Child[1]->clear();delete Child[1];}
        
    }
    int computeWPL(int depth,unsigned int &WPL){
        if(Child[0]==NULL && Child[1]==NULL)WPL+=depth*this->frequence;
        else{
            Child[0]->computeWPL(depth+1, WPL);
            Child[1]->computeWPL(depth+1, WPL);
        }
        return 0;
    }

    friend bool operator<(HuffmanCodesNode a,HuffmanCodesNode b){
        return a.frequence>b.frequence;
    }

};

unsigned int computeWPLwithFrequencyMap(map<char,int> &f){
    priority_queue<HuffmanCodesNode> q;
    HuffmanCodesNode *p1,*p2;
    unsigned int WPL=0;
    for (map<char,int>::iterator iter=f.begin(); iter!=f.end(); ++iter) {
        HuffmanCodesNode temp(iter->first, iter->second);
        q.push(temp);
    }
    while (q.size()>1) {
        p1=new HuffmanCodesNode(q.top());
        q.pop();
        p2=new HuffmanCodesNode(q.top());
        q.pop();
        HuffmanCodesNode temp(p1,p2);
        temp.frequence=p1->frequence+p2->frequence;
        q.push(temp);
    }
    p1=new HuffmanCodesNode(q.top());
    p1->computeWPL(0, WPL);
    return WPL;
}
bool compare(const string& a ,const string& b){
    if (a.length() < b.length()) {
        return true;
    }else if(a.length() == b.length() && a < b){
        return true;
    }
    return false;
}
bool checkPrefix(vector<string>& s){
    sort(s.begin(), s.end(),compare);
    HuffmanCodesNode *root = new HuffmanCodesNode,*p=root;
    int t;
    bool check=false;
    for (vector<string>::iterator i=s.begin();i!=s.end();++i){
        p=root;
        for (string::iterator iter = i->begin(); iter!=i->end(); iter++) {
            t=*iter-'0';
            if(p->Child[t]==NULL)p->Child[t]=new HuffmanCodesNode;
            p=p->Child[t];
            if(p->isLeaf){root->clear();return false;}
        }
        if(p->Child[0]!=NULL || p->Child[1]!=NULL)check=true;
        if(check){root->clear();return false;}
        p->isLeaf = true;
    }
    root->clear();
    if (!check)return true;
    else return false;
}
int main(int argc,const char* argv[])
{
    ios::sync_with_stdio(false);
    
    int N;cin>>N;
    char c;int frequence;
    string s;
    map<char, int> f;
    for (int i=0; i<N; i++) {
        cin>>c;
        cin>>frequence;
        f[c]=frequence;
    }
    unsigned int WPL=computeWPLwithFrequencyMap(f);
    int M;cin>>M;
    for (int i=0; i<M; i++) {
        unsigned int t_WPL=0;
        vector<string> t;
        for (int j=0; j<N; j++) {
            cin>>c;
            cin>>s;
            t_WPL+=f[c]*s.size();
            t.push_back(s);
        }
        if ( t_WPL == WPL && checkPrefix(t)){
            cout<<"Yes"<<endl;
        }else{
            cout<<"No"<<endl;
        }
    }
    
    
}