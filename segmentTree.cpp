#include <iostream>
#include <vector>
using namespace std;


// Range Sum Query (with lazy propagation)

class segmentTree{  //note arr must be 1 based arr
public:
    int N;
    vector<int>ar,segT,lazy;

    segmentTree(vector<int>&arr){ // size of array must be a power of 2 + 1 (one-based)
        N =(int) arr.size()-1;
        ar = arr;
        lazy.resize(N<<1); // no of nodes is 2N-1 but we add 1 to be 1 index
        segT.resize(N<<1);
        build(1,1,N);
    }
    void build(int node,int l,int r){ //o (2n)
        if(l==r){
            segT[node] = ar[l];
            return;
        }
        int mid= l+r >> 1;

        build(node<<1,l,mid);
        build(node<<1|1,mid+1,r);
        segT[node]=segT[node<<1]+segT[node<<1|1];
    }

    int query(int i,int j){
        return query(1,1,N,i,j);
    }
    int query(int node,int l ,int r,int i,int j){  // O(log n)
        if(i>r || j <l)
            return 0;
        if(i<=l && j>=r){
            return segT[node];
        }
        int mid=l+r>>1;
        // propagate(node, l, r);
        return query(node<<1,l,mid,i,j) + query(node<<1|1,mid+1,r,i,j);
    }

    void updatePoint(int idx,int val){  // O(log n)
        int cur=idx+ N-1;
        segT[cur] += val;
        while(cur!=1){
            cur>>=1; //divide by 2 to get the parent
            segT[cur]=segT[cur<<1]+segT[cur<<1|1];
        }
    }

    void propagate(int node,int l,int r){ // o(1)
        int mid = r + l >> 1;
        lazy[node<<1] += lazy[node];
        lazy[node<<1|1] += lazy[node];

        segT[node<<1] += lazy[node]*(mid-l+l);
        segT[node<<1|1] += lazy[node] *(r - mid);
        lazy[node]=0;
    }

    void updateRange(int i,int j,int val){
        updateRange(1,1,N, i, j , val);

    }
    void updateRange(int node ,int l,int r,int i,int j,int val) {  //O(log n)
        if(i>r || j <l)
            return ;
        if (i <= l && r <= j) { // if I took the whole node
            lazy[node] += val;
            segT[node] += val * (r - l + 1) ;
            return;
        } else {
            int mid = r + l >> 1;
            propagate(node,l,r);
            updateRange(node<<1,l,mid,i,j,val);
            updateRange(node<<1|1,mid+1,r,i,j,val);
            segT[node]=segT[node<<1]+segT[node<<1|1];
        }

    }
};


int main(){

    int n;cin>>n;
    int N=1;

    while(N < n){
        N <<= 1;   //padding
    }
    vector<int>arr(N+1);
    for (int i = 1; i <=n ; ++i) {
        cin>>arr[i];
    }

    for(int i=n+1;i<=N;i++){
        arr[i]=0;
    }

    segmentTree sg(arr);

    int q;cin>>q;
    while(q--){
        int l,r;cin>>l>>r;
        cout<<sg.query(l,r)<<endl;

    }


    return 0;
}

