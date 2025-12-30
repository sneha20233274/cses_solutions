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
            seg[idx]=1;
            return;
        }
        int mid = (s + e) / 2;
        build(2*idx+1, s, mid, arr);
        build(2*idx+2, mid+1, e, arr);
        seg[idx]=seg[2*idx+1]+seg[2*idx+2];
    }
    int query(int idx, int  index,int s, int e,vector<int>&arr) {
      if(s==e) {
        if(seg[idx]!=0){
          seg[idx]=0;
          return s;
        }
        return -1;
      }
      int mid=(s+e)/2;
      int ans=0;
      if(seg[2*idx+1] >  index) ans= query(2*idx+1,index,s,mid,arr);
      else                                ans= query(2*idx+2,(index-seg[2*idx+1]),mid+1,e,arr);
      seg[idx]=seg[2*idx+1]+seg[2*idx+2];
      return ans;
    }
  };
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    segment_tree st(n);
    st.build(0, 0, n-1, arr);

    vector<int> ans;
    int sz=n;
    while (sz--) {
        int index;
        cin>>index;
        index--;
        ans.push_back(arr[st.query(0,index,0,n-1,arr)]);
      }
    for (auto x : ans) cout << x <<" ";
    return 0;
}
