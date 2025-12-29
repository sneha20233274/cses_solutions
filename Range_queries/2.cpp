// Range MIN Query using Square Root Decomposition
#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,q;
    cin>>n>>q;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    vector<vector<int>>queries(q,vector<int>(2));
    for(int i=0;i<q;i++) cin>>queries[i][0]>>queries[i][1];
    int len = sqrt(n);
    if (len * len < n) len++;
    vector<long long>b(len,1e9);
    for(int i=0;i<n;i++){
      b[i/len]=min(b[i/len],(long long)a[i]);
    }
    vector<long long>ans(q);
    for(int i=0;i<q;i++){
      int l=queries[i][0];
      int r=queries[i][1];
      l--;
      r--;
      long long mini=1e9;
      int j=l;
      while(j<=r){
        if((j%len==0) && (j+len-1)<=r){
          mini=min(mini,b[j/len]);
          j+=len;
        }
        else {
            mini=min(mini,(long long)a[j]);
            j++;
        }
      } 
      ans[i]=mini;
    }
    for(auto it:ans)  cout<<it<<endl;
    return 0;
  }
