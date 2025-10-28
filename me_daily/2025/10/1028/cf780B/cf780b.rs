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

fn possible(t: f64, x: &Vec<i64>, v: &Vec<i64>, n: usize) -> bool {
    let mut lmx: f64 = -1e18;
    let mut rmx: f64 = 1e18;
    for i in 0..n {
        let left = x[i] as f64 - v[i] as f64 * t;
        let right = x[i] as f64 + v[i] as f64 * t;
        lmx = lmx.max(left);
        rmx = rmx.min(right);
    }
    lmx <= rmx
}
fn main() {
    // 读取所有输入到字符串（全split_whitespace，一次过）
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();

    let n: usize = read!(it => usize);
    let x: Vec<i64> = read!(it => vec_i64, n);
    let v: Vec<i64> = read!(it => vec_i64, n);
    let mut l = 0.0_f64;
    let mut r = 2e9_f64;
    for _ in 0..100 {
        let mid = l + (r - l) / 2.0;
        if possible(mid, &x, &v, n) {
            r = mid;
        } else {
            l = mid;
        }
    }
    println!("{:.12}", l);
}
