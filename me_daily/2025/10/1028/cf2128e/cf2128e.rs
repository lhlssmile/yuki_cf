use std::io::{self, Read};

macro_rules! read {
    // 单个值：read!(it => usize) 或 read!(it => i64)
    ($it:ident => $t:ty) => {
        $it.next().unwrap().parse::<$t>().unwrap()
    };
    ($it:ident => str) => {
        $it.next().unwrap().to_string()
    };
    // Vec：read!(it => vec_i64(n)) 读n个i64成Vec<i64>
    ($it:ident => vec_usize($n:expr)) => {
        (0..$n).map(|_| read!($it => usize)).collect::<Vec<_>>()
    };
    ($it:ident => vec_i64($n:expr)) => {
        (0..$n).map(|_| read!($it => i64)).collect::<Vec<_>>()
    };
    ($it:ident => vec_str($n:expr)) => {
        (0..$n).map(|_| read!($it => str)).collect::<Vec<_>>()
    };
    // 简化版本，直接接受数量参数
    ($it:ident => vec_usize, $n:expr) => {
        (0..$n).map(|_| read!($it => usize)).collect::<Vec<_>>()
    };
    ($it:ident => vec_i64, $n:expr) => {
        (0..$n).map(|_| read!($it => i64)).collect::<Vec<_>>()
    };
    ($it:ident => vec_str, $n:expr) => {
        (0..$n).map(|_| read!($it => str)).collect::<Vec<_>>()
    };
}

macro_rules! multi_read {
    // 多值一行：multi_read!(it => usize, usize, usize) → (n, a, b)
    ($it:ident => $($t:ty),+ $(,)?) => {
        ($(read!($it => $t)),+)
    };
}

#[derive(Clone, Copy)]
struct Result {
    left: usize,
    right: usize,
}

fn check(vi: i64, n: usize, a: &[i64], k: usize) -> Result {
    let mut s = vec![0i64; n + 1];
    
    for i in 1..=n {
        let val = if a[i] >= vi { 1 } else { -1 };
        s[i] = s[i - 1] + val;
    }
    
    let mut pos = 0;
    for i in k..=n {
        if s[i - k] < s[pos] {
            pos = i - k;
        }
        if s[i] - s[pos] >= 0 {
            return Result {
                left: pos + 1,
                right: i,
            };
        }
    }
    Result { left: 0, right: 0 }
}

fn solve(a: &[i64], n: usize, k: usize) {
    let mut lo = 1;
    let mut hi = n;
    let mut ans = 0;
    let mut final_res = Result { left: 0, right: 0 };
    
    while lo <= hi {
        let vi = lo + (hi - lo) / 2;
        let lr = check(vi as i64, n, a, k);
        if lr.left > 0 {
            ans = vi;
            final_res = lr;
            lo = vi + 1;
        } else {
            hi = vi - 1;
        }
    }
    println!("{} {} {}", ans, final_res.left, final_res.right);
}

fn main() {
    // 读取所有输入到字符串（全split_whitespace，一次过）
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();

    let t = read!(it => usize);
    for _ in 0..t {
        let (n, k) = multi_read!(it => usize, usize);
        let mut a = vec![0i64; n + 1];
        for i in 1..=n {
            a[i] = read!(it => i64);
        }
        solve(&a, n, k);
    }
}
