#include<bits/stdc++.h>
using namespace std;
typedef
struct fpnode{
    int item;
    int f=0;
    fpnode *children[10];
    fpnode(int item)
    {
        for(int i=0;i<10;i++) this->children[i]=NULL;
        this->item = item;
        this->f++;
    }
}*fpptr;
vector<int> total_items;
void insert(fpptr &fp,vector<int> &items,int n)
{
    if(n==-1) return;
    if(fp==NULL) // fp is NULL
    {
        cout<<"Creating Node "<<items[n]<<endl;
        fp = new fpnode(items[n]);
        if(n>0) insert(fp->children[items[n-1]],items,n-1);
    }
    else // fp is not NULL
    {   
        if(fp->item == items[n])
        {
            cout<<"Proceeding Node "<<items[n]<<endl;
            fp->f++;
            if(n>0) insert(fp->children[items[n-1]],items,n-1);            
        }
        else
        {
            if(fp->item!=-1)
            {
                cout<<"Creating NULL Node "<<items[n]<<endl;
                fpptr f1 = fp;
                fpptr f2 = new fpnode(items[n]);
                fp = new fpnode(-1);
                fp->f = f1->f + f2->f;
                fp->children[f1->item] = f1;
                fp->children[f2->item] = f2;
                if(n>0) insert(f2->children[items[n-1]],items,n-1);                
            }
            else
            {
                fp->f++;
                if(n>0) insert(fp->children[items[n]],items,n);
            }
        }
    }
}
bool comp(int i1,int i2)
{
    return total_items[i1]<total_items[i2];
}
void get_frequency_and_sort(vector<vector<int> > &trans)
{
    for(int i=0;i<trans.size();i++)
    {
        for(int j=0;j<trans[i].size();j++)
        {
            total_items[trans[i][j]]++;
        }
    }
    for(int i=0;i<trans.size();i++)
    {
        sort(trans[i].begin(),trans[i].end(),comp);
    }
}
void print(fpptr fp)
{
    if(fp==NULL) return;
    cout<<"( "<<fp->item<<" , "<<fp->f<<"): ";
    for(int i=0;i<10;i++)
    {
        if(fp->children[i]) 
        {
            cout<<"("<<fp->children[i]->item<<" ,"<<fp->children[i]->f<<"), ";
        }
    }
    cout<<endl;
    for(int i=0;i<10;i++)
    {
        print(fp->children[i]);
    }
}
int main()
{
    vector<vector<int> > trans = 
    {
        {1,2,5},
        {2,4},
        {2,3},
        {1,2,4},
        {1,3},
        {2,3},
        {1,3,6},
        {1,2,3,5},
        {1,2,3}
    };
    total_items.assign(7,0);
    get_frequency_and_sort(trans);
    for(auto v:trans)
    {
        for(auto x:v) cout<<x<<" ";
        cout<<endl; 
    }
    fpptr fp = NULL;
    for(int i=0;i<trans.size();i++)
    {
        insert(fp,trans[i],trans[i].size()-1);
        cout<<endl;
    }
    print(fp);
}

