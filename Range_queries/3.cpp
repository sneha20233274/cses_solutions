// Range Sum Query using Square Root Decomposition
#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,q;
    cin>>n>>q;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    vector<vector<int>>queries(q,vector<int>(3));
    for(int i=0;i<q;i++) cin>>queries[i][0]>>queries[i][1]>>queries[i][2];
    int len = sqrt(n);
    if (len * len < n) len++;
    vector<long long>b(len,0);
    for(int i=0;i<n;i++){
      b[i/len]+=a[i];
    }
    vector<long long>ans;
    for(int i=0;i<q;i++){
      int qtype=queries[i][0];
      if(qtype==2){
        int l=queries[i][1];
        int r=queries[i][2];
        l--;
        r--;
        long long sum=0;
        int j=l;
        while(j<=r){
          if((j%len==0) && (j+len-1)<=r){
            sum+=b[j/len];
            j+=len;
          }
          else {
            sum+=a[j];
              j++;
          }
        } 
        ans.push_back(sum);
      }
      else {
        int index=queries[i][1];
        int value=queries[i][2];
        index--;
        int block=index/len;
        b[block]=b[block]-a[index]+value;
        a[index]=value;
      }
    }
    for(auto it:ans)  cout<<it<<endl;
    return 0;
  }
