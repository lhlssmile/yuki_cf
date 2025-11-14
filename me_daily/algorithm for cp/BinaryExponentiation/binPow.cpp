#include <bits/stdc++.h>
using ll = long long;
using vi = vector<int>;
using namespace std;
#define For(i, n) for (int i = 0; i < (n); ++i)
using vll = vector<ll>;
ll binpow(ll a, ll b) {
    //recursion
    if (b == 0) {
        return 1;
    }
    ll res = binpow(a, b / 2);
    if (b & 1) {
        return res * res * a;
    }else {
        return res * res;
    }

}

ll binPowNoRecursion(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b&1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

//applications

// 1.有效计算模一个数的大指数
//ex: a * b ≡ (a mod m) * (b mod m) (mod m)
//if m is prime -> x^n = x^ n mod (m - 1) (mod m)
ll binpowMod(ll a, ll b, ll m) {
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b&1) res = res * a % m;
        a = a * a % m;
        b >>= 1; 
    }
    return res;
}

// 2. 快速计算一个斐波那契数F(n)


struct Matrix {
    ll m[2][2];
    Matrix() {memset(m, 0,sizeof(m));}
};

Matrix mul(Matrix a, Matrix b) {
    Matrix c;
    For(i, 2) {
        For(j, 2) {
            For(k, 2) {
                c.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }
    return c;
}

Matrix pow(Matrix a, ll n) {
    Matrix res;
    res.m[0][0] = res.m[1][1] = 1; // 单位矩阵.
    while (n > 0) {
        if (n & 1) res = mul(res, a);
        a = mul(res, a);
        n >>= 1;
    }
    return res;
}

ll fib(ll n) {
    if (n == 0) return 0;
    Matrix M;
    M.m[0][0] = M.m[0][1] = M.m[1][0] = 1;
    M.m[1][1] = 0;
    Matrix res = pow(M, n);
    return res.m[1][0];
}


//3. applying a permutation k times
vi applyPermutation(vi sequence, vi permutation) {
    vi new_sequence(sequence.size());
    For(i, sequence.size()) {
        new_sequence[i] = sequence[permutation[i]];
    }
    return new_sequence;
} 
vector<int> permute(vll sequence, vector<int> permutation, ll k) {
    while(k > 0) {
        if (k & 1) {
            sequence = applyPermutation(sequence, permutation);
        }
        permutation = applyPermutation(permutation, permutation);
        k >>= 1;
    }
}


//4. 长度为k的有向无权图路径条数

const int N = 105;
ll mod = 1e9 + 7;


struct MatrixA {
    ll a[N][N];
    int n;
    MatrixA (int _n) : n(_n) {memset(a, 0, sizeof(a));}
};

MatrixA mul(const MatrixA& A, const MatrixA& B) {
    MatrixA C(A.n);
    For(i, A.n) {
        For(j, A.n) {
            For(k, A.n) {
                C.a[i][j] = (C.a[i][j] + A.a[i][k] * B.a[k][j]) % mod;
            }
        }
    }
    return C;
}
MatrixA pow(MatrixA A, ll k) {
    MatrixA res(A.n);
    For(i, A.n) {
        res.a[i][i] = 1;          //单位矩阵
    }
    while (k) {
        if (k & 1) res = mul(res, A);
        A = mul(A, A);
        k >>= 1;
    }
}