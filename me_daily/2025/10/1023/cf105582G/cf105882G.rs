use std::collections::HashMap;
use std::io::{self, Read};

macro_rules! read {
    ($it:ident, $t:ty) => {
        $it.next().unwrap().parse::<$t>().unwrap()
    };

    ($it:ident, str) => {
        $it.next().unwrap().to_string()
    };
}

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();

    let n: usize = read!(it, usize);
    let a: usize = read!(it, usize); // usize，但calc转i64
    let b: usize = read!(it, usize);
    let k1 = n / 2;
    let k2 = n - k1;
    let mut v1: Vec<i64> = vec![0; k1];
    let mut v2: Vec<i64> = vec![0; k2];

    // 第一半：读k1对，赋值v1[i]
    for i in 0..k1 {
        let m: i64 = read!(it, i64);
        let t: i64 = read!(it, i64);
        v1[i] = m * (b as i64) - (a as i64) * t; // cast usize to i64
    }
    // 第二半：读k2对，赋值v2[i]
    for i in 0..k2 {
        let m: i64 = read!(it, i64);
        let t: i64 = read!(it, i64);
        v2[i] = m * (b as i64) - (a as i64) * t;
    }

    let mut mp: HashMap<i64, usize> = HashMap::new();
    // 第一半mask：枚举所有子集sum
    for mask in 0..(1usize << k1) {
        let mut val: i64 = 0i64;
        for j in 0..k1 {
            if (mask & (1usize << j)) != 0 {
                val += v1[j];
            }
        }
        *mp.entry(val).or_insert(0) += 1;
    }

    let mut ans: usize = 0; // 加定义！
                            // 第二半mask：枚举，查mp[-val]
    for mask in 0..(1usize << k2) {
        let mut val: i64 = 0i64;
        for j in 0..k2 {
            if (mask & (1usize << j)) != 0 {
                val += v2[j];
            }
        }
        if let Some(&cnt) = mp.get(&-val) {
            ans += cnt;
        }
    }
    println!("{}", ans.saturating_sub(1)); // -1，但防usize负（虽ans>=1）
}
