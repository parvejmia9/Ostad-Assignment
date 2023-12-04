#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <class T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class K, class V> using omap = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;
void __print(int x) {cout << x;} void __print(long long x) {cout << x;}
void __print(double x) {cout << x;} void __print(long double x) {cout << x;}
void __print(char x) {cout << '\'' << x << '\'';} void __print(const char *x) {cout << '\"' << x << '\"';}
void __print(const string &x) {cout << '\"' << x << '\"';} void __print(bool x) {cout << (x ? "True" : "False");}
template<typename T, typename V>
void __print(const pair<T, V>&x) {cout << '{'; __print(x.first); cout << ','; __print(x.second); cout << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cout << '{'; for (auto &i : x)cout << (f++ ? "," : ""), __print(i); cout << "}";}
void _print() {cout << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cout << ", "; _print(v...);}

#ifdef LOCAL
#define debug(x...) cout << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

#define odrkey order_of_key
#define fbodr find_by_order
#define sq(a) ((a)*(a))
#define ull unsigned long long
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define pi 3.1415926536
#define nwl cout <<"\n";
#define ff first
#define ss second
#define pb push_back
#define pf push_front
#define sz(a) ((int)(a).size())
typedef long long ll;
const int mod = 998244353, G = 3;
ll bigmod(ll a, ll b, ll mod) {
    assert(b >= 0);
    ll res = 1;
    while (b) {
        if (b % 2)res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}
ll lcm(ll a, ll b) {
    return (a * b) / __gcd(a, b);
}
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
const int N = 1e5 + 9;
double dp[20][2][2][2];
int ar1[22], ar2[22];
int ans[22][2][2][2];
bool vis[20][2][2][2];
double fun(int pos, int st, bool f1, bool f2) {
    if (pos == 20) {
        if (st)return 0;
        return -1e18;
    }
    if (vis[pos][st][f1][f2])return dp[pos][st][f1][f2];
    double ret = -1e18;
    int l1 = ar1[pos];
    int r1 = 9;
    int l2 = 0;
    int r2 = ar2[pos];
    if (f1)l1 = 0;
    if (f2)r2 = 9;
    int now = 0;
    int l = max(l1, l2);
    int r = min(r1, r2);
    if (!st) {
        if (!l)ret = fun(pos + 1, 0, 0, f2 | 0 < ar2[pos]);
        for (int i = l; i <= r; i++) {
            if (!i)continue;
            double tmp = log(i) + fun(pos + 1, 1, f1 | i > ar1[pos], f2 | i < ar2[pos]);
            if (tmp > ret) {
                ret = tmp;
                now = i;
            }
        }
    }
    else {
        for (int i = l; i <= r; i++) {
            if (!i)continue;
            double tmp = log(i) + fun(pos + 1, 1, f1 | i > ar1[pos], f2 | i < ar2[pos]);
            if (tmp >= ret) {
                ret = tmp;
                now = i;
            }
        }
    }
    ans[pos][st][f1][f2] = now;
    vis[pos][st][f1][f2] = 1;
    return dp[pos][st][f1][f2] = ret;
}
void set_ar(ll x, bool f) {
    int pos = 19;
    while (x) {
        if (f)ar2[pos] = x % 10;
        else ar1[pos] = x % 10;
        x /= 10;
        pos--;
    }
}
vector<int>out;
void fun2(int pos, bool st, bool f1, bool f2) {
    if (pos == 20)return;
    int now = ans[pos][st][f1][f2];
    out.pb(now);
    fun2(pos + 1, st | now, f1 | now > ar1[pos], f2 | now < ar2[pos]);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll a, b;
    cin >> a >> b;
    if (a > b)swap(a, b);
    set_ar(a, 0);
    set_ar(b, 1);
    memset(vis, 0, sizeof vis);
    ll tm = fun(0, 0, 0, 0);
    fun2(0, 0, 0, 0);
    bool id = 0;
    for (int x : out) {
        if (x)id = 1;
        if (id) {
            cout << x;
        }
    }
    cout << '\n';
}
