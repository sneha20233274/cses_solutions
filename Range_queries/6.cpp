#include <bits/stdc++.h>
using namespace std;

class segment_tree {
public:
    vector<long long> seg, lazy;

    segment_tree(int n) {
        seg.assign(4*n+1, 0);
        lazy.assign(4*n+1, 0);
    }

    void build(int idx, int s, int e, vector<int>& arr) {
        if (s == e) {
            seg[idx] = arr[s];
            return;
        }
        int mid = (s + e) / 2;
        build(2*idx+1, s, mid, arr);
        build(2*idx+2, mid+1, e, arr);
        seg[idx] = seg[2*idx+1] + seg[2*idx+2];
    }

    void push(int idx, int s, int e) {
        if (lazy[idx] != 0) {
            seg[idx] += (e - s + 1) * lazy[idx];
            if (s != e) {
                lazy[2*idx+1] += lazy[idx];
                lazy[2*idx+2] += lazy[idx];
            }
            lazy[idx] = 0;
        }
    }

    void update(int idx, int l, int r, int s, int e, long long val) {
        push(idx, s, e);

        if (e < l || s > r) return;

        if (s >= l && e <= r) {
            lazy[idx] += val;
            push(idx, s, e);
            return;
        }

        int mid = (s + e) / 2;
        update(2*idx+1, l, r, s, mid, val);
        update(2*idx+2, l, r, mid+1, e, val);
        seg[idx] = seg[2*idx+1] + seg[2*idx+2];
    }

    long long query(int idx, int l, int r, int s, int e) {
        push(idx, s, e);

        if (e < l || s > r) return 0;

        if (s >= l && e <= r)
            return seg[idx];

        int mid = (s + e) / 2;
        return query(2*idx+1, l, r, s, mid)
             + query(2*idx+2, l, r, mid+1, e);
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
        int type;
        cin >> type;

        if (type == 1) {
            int l, r;
            long long val;
            cin >> l >> r >> val;
            l--; r--;
            st.update(0, l, r, 0, n-1, val);
        } else {
            int idx;
            cin >> idx;
            idx--;
            ans.push_back(st.query(0, idx, idx, 0, n-1));
        }
    }

    for (auto x : ans) cout << x << '\n';
    return 0;
}
