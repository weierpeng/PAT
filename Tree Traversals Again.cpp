


#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace::std;

string FindPostOrder( string pre_order, string in_order )
{
    if( pre_order.length() != in_order.length() )   //前序中序元素个数不相等出错
    {
        cout << "0" << endl;
        exit(1);
    }
    
    if( pre_order.length() == 1 )                //递归终止
    {
        if( pre_order != in_order )               //一个元素时前序中序不相等
        {
            cout << "0" <<endl;
            exit(1);
        }
        return pre_order;
    }
    
    if( pre_order.length() == 0)                  //前序为空时，后序也为空
        return string();
    
    char node = pre_order[0];					//取第一个元素
    size_t index = in_order.find( node );			//找到其在中序中的位置
    
    if( index == string::npos )					//没有找到，则出错
    {
        cout << "0" <<endl;
        exit(1);
    }
    size_t len = pre_order.length();
    
    //左子树的后序
    
    string left_part = FindPostOrder( pre_order.substr(1,index), in_order.substr(0,index) );
    //右子树的后序
    string right_part = FindPostOrder( pre_order.substr(1+index, len-index-1), in_order.substr(1+index,len-index-1) );
    
    return left_part+right_part+node; //串联起来
    
}

int main(int argc,const char* argv[])
{
    int N,temp;
    cin>>N;
    string op;
    stack<int> s;
    string Pop("Pop"),Push("Push");
    string preorder,midorder,postorder;
    while (midorder.size() <= N) {
        cin>>op;if(!cin)break;
        if (op == Push) {
            cin>>temp;
            s.push(temp);
            preorder.push_back(temp);
        }else{
            temp = s.top();
            midorder.push_back(temp);
            s.pop();
        }
    }
    postorder = FindPostOrder(preorder, midorder);
    
    for (string::iterator iter = postorder.begin(); iter != postorder.end(); iter++) {
        if (iter == postorder.begin()) {
            cout<<(int)*iter;
        }else{
            cout<<" "<<(int)*iter;
        }
    }
    
    return 0;
}
