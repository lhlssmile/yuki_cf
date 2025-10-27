use std::io::{self, Read};
use std::collections::HashMap;
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

fn main() {
    // 读取所有输入到字符串（全split_whitespace，一次过）
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();

    let t:usize = read!(it => usize);
    for _ in 0..t {
        let n:usize = read!(it => usize);
        let mut a: Vec<i64> = read!(it => vec_i64, n);
        let mut freq:HashMap<i64, usize> = HashMap::new();
        for &x in &a {
            *freq.entry(x).or_insert(0) += 1;
        }
        let mut base: i64 = 0;
        let mut extras: Vec<usize> = Vec::new();
        
        for (&h, &f) in &freq {
            base += (h / 2) * f as i64;
            if h % 2 == 1 {
                extras.push(f);
            }
        }
        
        extras.sort_by(|a, b| b.cmp(a)); // 降序排列
        
        let mut alice_extra: i64 = 0;
        let mut bob_extra: i64 = 0;
        
        for (i, &extra) in extras.iter().enumerate() {
            if i % 2 == 0 {
                alice_extra += extra as i64;
            } else {
                bob_extra += extra as i64;
            }
        }
        
        let alice = base + alice_extra;
        let bob = base + bob_extra;
        
        println!("{} {}", alice, bob);
    }
}