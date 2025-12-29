#include <bits/stdc++.h>
using namespace std;

class segment_tree {
public:
    vector<long long> seg;

    segment_tree(int n) {
        seg.assign(4*n+1, 0);
       
    }
    void build(int idx, int s, int e, vector<int>& arr) {
        if (s == e) {
            seg[idx] = s;
            return;
        }
        int mid = (s + e) / 2;
        build(2*idx+1, s, mid, arr);
        build(2*idx+2, mid+1, e, arr);
        if(arr[seg[2*idx+1]] >= arr[seg[2*idx+2]]){
          seg[idx]=seg[2*idx+1];
        }
        else {
          seg[idx]=seg[2*idx+2];
       }
    }
    long long query(int idx, int  val,int s, int e,vector<int>&arr) {
      if(s==e) {
        if(arr[seg[idx]] >=val)  return seg[idx];
        else return -1;

      }
      int mid=(s+e)/2;
      if(arr[seg[2*idx+1]] >=val){
        return query(2*idx+1,val,s,mid,arr);
      }
      return query(2*idx+2,val,mid+1,e,arr);
    }
    void update(int idx,int s,int e,vector<int>&arr,int pos,int val){
      if(s==e){
        if(s==pos) arr[pos]-=val;
        return;
      }
      int mid=(s+e)/2;
      if(pos <=mid){
        update(2*idx+1,s,mid,arr,pos,val);
      }
      else {
        update(2*idx+2,mid+1,e,arr,pos,val);
      }

      if(arr[seg[2*idx+1]] >= arr[seg[2*idx+2]]){
        seg[idx]=seg[2*idx+1];
      }
      else {
        seg[idx]=seg[2*idx+2];
    }
  }
  };
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    segment_tree st(n);
    st.build(0, 0, n-1, arr);

    vector<long long> ans;

    while (q--) {
        int val;
        cin>>val;
        long long pos=st.query(0,val,0,n-1,arr);
        if(pos==-1){
          ans.push_back(0);
        }
        else {
          ans.push_back(pos+1);
          st.update(0,0,n-1,arr,pos,val);
          //
       
        }
    }

    for (auto x : ans) cout << x <<" ";
    return 0;
}
