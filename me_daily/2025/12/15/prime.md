

## 概述
Miller-Rabin 素数测试是一种概率性（或确定性）算法，用于高效判断大整数是否为素数。它基于费马小定理的扩展，特别适用于加密领域（如 RSA 密钥生成），因为它能快速处理超大数（时间复杂度 O(k log³ n)，k 为测试轮数）。与试除法不同，它避免了穷举因子，错误率极低（随机版 < 1/4^k；确定性版对特定范围 100% 准确）。

- **输入**：奇整数 n (> 2)。
- **输出**：True（大概率/确定为素数）或 False（复合数）。

## 数学原理
### 费马小定理回顾
若 n 为素数，且 1 < a < n（a 与 n 互素），则 \( a^{n-1} \equiv 1 \pmod{n} \)。  
反之，若不成立，则 n 复合。但存在“伪素数”（Carmichael 数），费马测试易误判。

### Miller-Rabin 加强
将 n-1 分解为 \( n-1 = 2^s \cdot d \)（d 为奇数，s ≥ 1）。  
对于见证者 a（2 ≤ a < n），计算序列：  
\( x_0 = a^d \pmod{n} \)  
\( x_r = x_{r-1}^2 \pmod{n} \)（r = 1 到 s-1）。  

n 为强伪素数（通过测试）当且仅当：  
- \( x_0 \equiv 1 \pmod{n} \) 或  
- 存在 r (0 ≤ r < s) 使 \( x_r \equiv -1 \pmod{n} \)。  

若任意 a 不满足，n 复合。随机 a 概率准；固定 a 集（针对 n < 2^64）确定准。

## 算法步骤
1. **预检查**：n < 2 → False；n = 2/3 → True；n 偶 → False。小素数列表（2,3,5,...）快速筛。
2. **分解 n-1**：d = n-1, s=0；while d 偶：d /= 2, s++。
3. **测试轮**（k 轮或固定 bases）：  
   - 选 a（随机或固定，如 [2, 325, 9375, 28178, 450775, 9780504, 1795265022]）。  
   - x = a^d mod n。  
   - 若 x ≡ 1 或 x ≡ n-1：通过。  
   - 否则，for r=1 to s-1：x = x² mod n；若 x ≡ n-1：通过。  
   - 未通过：复合，返回 False。  
4. 全轮通过：素数。

## 关键子函数
### 安全模乘 (mulmod)
用于避免 uint64 乘法溢出。基于二进制展开：  
\[ (a \times b) \mod m = \sum (a \times 2^i \mod m) \]（b 的 1 位）。  

Go 实现：
```go
func mulmod(a, b, mod uint64) uint64 {
    res := uint64(0)
    a %= mod
    for b > 0 {
        if b&1 == 1 {
            if res >= mod-a {
                res -= (mod - a)  // res + a - mod
            } else {
                res += a
            }
        }
        if a >= mod-a {
            a -= (mod - a)  // a + a - mod
        } else {
            a += a
        }
        b >>= 1
    }
    return res % mod
}
```

### 快速模幂 (powmod)
二进制指数：  
Go 实现：
```go
func powmod(a, d, mod uint64) uint64 {
    res := uint64(1)
    for d > 0 {
        if d&1 == 1 {
            res = mulmod(res, a, mod)
        }
        a = mulmod(a, a, mod)
        d >>= 1
    }
    return res
}
```

## 完整 Go 实现
```go
package main

import "fmt"

func mulmod(a, b, mod uint64) uint64 {
    // 如上实现
}

func powmod(a, d, mod uint64) uint64 {
    // 如上实现
}

func isPrimeMR(n uint64) bool {
    if n < 2 { return false }
    small := []uint64{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}
    for _, p := range small {
        if n == p { return true }
        if n % p == 0 { return false }
    }
    d := n - 1
    s := 0
    for d&1 == 0 {
        d >>= 1
        s++
    }
    bases := []uint64{2, 325, 9375, 28178, 450775, 9780504, 1795265022}
    for _, a := range bases {
        if a % n == 0 { continue }
        a %= n
        x := powmod(a, d, n)
        if x == 1 || x == n-1 { continue }
        composite := true
        for r := 1; r < s; r++ {
            x = mulmod(x, x, n)
            if x == n-1 {
                composite = false
                break
            }
        }
        if composite { return false }
    }
    return true
}

func main() {
    tests := []uint64{17, 15, 91}
    for _, n := range tests {
        fmt.Printf("%d 是素数？ %t\n", n, isPrimeMR(n))
    }
    // 输出: 17 true; 15 false; 91 false
}
```

## 示例
- **n=17** (素)：n-1=16=2^4·1 (s=4,d=1)。a=2: 2^1=2 mod17≠1/-1；平方1:4≠-1；2:16≡-1。通过。
- **n=15** (复合)：n-1=14=2^1·7 (s=1,d=7)。a=2:2^7=128≡8 mod15≠1/-1；s=1，无平方循环。通过失败。

## 注意事项
- **确定性**：上述 bases 确保 n < 2^64 无误判（参考 Jaeschke 论文）。
- **性能**：适合大 n；大整数用 `math/big`。
- **扩展**：随机版用 `crypto/rand` 选 a，k=10-20 轮概率 >99.9%。
