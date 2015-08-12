
#include <iostream>
#include <vector>
#include <algorithm>

using namespace::std;


class Tree {
public:
    int value;
    Tree *L,*R;
    Tree(int v):value(v),L(NULL),R(NULL){}
};

int in_order(Tree *node,vector<int> & p)
{
    if (node == NULL) return 0;
    in_order(node->L, p);
    p.push_back(node->value);
    in_order(node->R, p);
    return 0;
}

int main(int argc,const char* argv[])
{
    int N,M;
    int temp;
    vector<int> q,p;
    Tree *root=NULL,*parent=NULL;
    cin>>N>>M;
    for (int i=0; i<N; i++) {
        
        for (int j=0; j<M; j++) {
            cin>>temp;
            q.push_back(temp);
            if (root == NULL){
               parent = root = new Tree(temp);
                continue;
            }
            if (temp > parent->value) {
                parent->R = new Tree(temp);
                parent = parent->R;
            }else {
                parent->L = new Tree(temp);
                parent = parent->L;
            }
        }
        sort(q.begin(), q.end());
        in_order(root, p);
        if (p == q)cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
        q.clear();
        p.clear();
        root = NULL;
    }
    
    
}