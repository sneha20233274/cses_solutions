#include <bits/stdc++.h>
using namespace std;
class segment_tree {
public:
    vector<long long> seg;
    segment_tree(int n) {
        seg.assign(4*n+1, 0);     
    }
    void insert(int idx,int index,int val,int s,int e){
      if(s==e){
        seg[idx]=seg[idx]+val;
        return;
      }
      int mid=(s+e)/2;
      if(index <=mid) insert(2*idx+1,index,val,s,mid);
      else insert(2*idx+2,index,val,mid+1,e);
      seg[idx]=seg[2*idx+1]+seg[2*idx+2];
    }

    int query(int idx, int l,int r,int s, int e) {
       if(l > e ||  r < s) return 0;
       else if(l <= s && r >= e) return seg[idx];
       int mid=(s+e)/2;
       return query(2*idx+1,l,r,s,mid)+query(2*idx+2,l,r,mid+1,e);
    }
  };
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m;
    cin >> n>>m;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    int sz=100006;
    sort(arr.begin(),arr.end());
    unordered_map<int,int>mp;
    int val=0;
    for(int i=0;i<n;i++){
       if(mp.find(arr[i])==mp.end()) mp[arr[i]]=val++;
    }
    segment_tree st(sz);
    for(int i=0;i<n;i++){
      st.insert(0,mp[arr[i]],1,0,sz-1);
    }
   
    
    vector<int> ans;
    while (m--) {
       char c;
       cin>>c;
       if(c=='?'){
        int l,r;
        cin>>l>>r;
        int idx1=lower_bound(arr.begin(),arr.end(),l)-arr.begin();
        if(idx1==n) {
          ans.push_back(0);
          continue;
        }
        int idx2=upper_bound(arr.begin(),arr.end(),r)-arr.begin();
        idx2--;
        if(idx2 < 0 || idx2 < idx1){
          ans.push_back(0);
          continue;
        }
        ans.push_back(st.query(0,mp[arr[idx1]],mp[arr[idx2]],0,sz-1));
       }
       else{
        int k,x;
        cin>>k>>x;
        k--;

        st.insert(0,mp[arr[k]],-1,0,val-1);
        arr[k]=x;
        if(mp.find(x)==mp.end()) mp[x]=val++;
        st.insert(0,mp[x],1,0,sz-1);
       }
    }
    for (auto x : ans) cout << x <<endl;
    return 0;
}
