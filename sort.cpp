#include<iostream>
using namespace std;

int instr[]={12,13,2,0,6,45,39,21};

class btree
{
public:
    int *m_str;
    int btree_size;
    int sort_count;
    
    
    btree(int *str, int size)
        :m_str(str-1),btree_size(size){
        sort_count=0;
        
    }
    void swap(int& x, int& y){ int tmp= x;x=y;y=tmp;sort_count++;}
    int left(int i){   return 2*i;  }
    int right(int i){  return 2*i+1;}
    int parent(int i){ return i/2;  }
//树以序号1开头，C采用数组指针前移的方式，不改变树的算法
    void build(int *str, int len);
    void max_heapify(int len);
    int sort();
};

void btree::build(int *str, int len){
    int i;
    m_str = str;
    btree_size = len;
    
    for(i = btree_size/2; i>0 ;i--)
        max_heapify(i);
}
// root up from 1
void btree::max_heapify(int root){
    int l,r,largest;
    l = left(root);
    r = right(root);
    if(root >btree_size/2)
        return;

    
    if(l <= btree_size && m_str[l] > m_str[root])
        largest = l;
    else
        largest = root;
    if( r <= btree_size && m_str[r] > m_str[largest])
        largest = r;


    if( largest != root){
        swap(m_str[root],m_str[largest]);
        
        max_heapify(largest);
    }
    
}
int btree::sort(){
    int i;
    sort_count=0;
    
    build(m_str,btree_size);
    for(i=btree_size; i>1; i--){
        swap(m_str[i],m_str[1]);
        btree_size--;
        max_heapify(1);
    }
    return sort_count;
    
}

class mysort{
public:
    int sort_count;
    mysort():sort_count(0){}
    int sort_insert(int *str, int len);
    void swap(int& x, int& y){ int tmp= x;x=y;y=tmp;sort_count++;}

    int sort_quick(int *str, int low, int high);
    int sort_quick2(int *str, int low, int high);
    int sort_quick2b(int *str, int low, int high);

    int sort_dui(int *str, int len);
    
    
};
/*
 可以将插入看作是冒泡的优化版本，既不是沉到底
 而是按密度沉到合适的位置
 最坏为为(N^2)，平均无法估计
 */ 
int mysort::sort_insert(int *str, int len){
    int i,j,m;
    m = 0;
    for( i =1 ;i<len; i++){
        for(j =i; j>0; j--)
            if( str[j]<str[j-1]){
                swap(str[j],str[j-1]);
                m++;
            }
    }
    return m;
    
}

/*
 *可以随机选择base值，以给算法添加随机性来适应大数组
 */
int mysort::sort_quick2(int *str, int low, int high){
    
    int i,j;
    int base = str[low];

    i = low;
    j = high;
    
    while(i<j){
        while(str[j]>=base&& i<j)j--;
        if(i<j)
            swap(str[j],str[i++]);
            //i++不是必要的,下面的while自动会++，只是减少了比较
        
        while(str[i]<=base&& i<j)i++;
        if(i<j)
            swap(str[i],str[j--]);
    }
    
    return i;
}

/*
 最坏情况是O(n(n^2),平均是nlg(，但quick2b在有序时会多交换
 */ 
int mysort::sort_quick2b(int *str, int low, int high)
{
    if(low>=high)
        return 0;
    int i,j,m,n;
    int base = str[high];
    
    i = low;
    j = low;
    for (j = low;j<high;j++){
        if(str[j]<base)
            swap(str[j],str[i++]);
    }
    swap(str[high],str[i]);
    return i;
}

int mysort::sort_quick(int *str, int low, int high)
{
    if(low >= high)
        return 0;
    int p = sort_quick2b(str, low, high);
    
    sort_quick(str,low,p-1);
    sort_quick(str,p+1,high);
    return 0;
    
}

int main(){
    
    mysort a;
    int m;
    
//    int m = a.sort_insert(instr,sizeof(instr)/sizeof(int));
    a.sort_count = 0;
    
//    a.sort_quick(instr,0,sizeof(instr)/sizeof(int)-1);
    btree bt(instr,sizeof(instr)/sizeof(int));
    bt.sort();
    
    for(int i=0;i<sizeof(instr)/sizeof(int);i++)
        cout<<instr[i]<<" ";
    cout<<": "<<bt.sort_count<<" for "<<sizeof(instr)/sizeof(int)<<endl;
    
    return 0;
}
