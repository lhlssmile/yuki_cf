use std::io::{self, Read};
use std::collections::{HashSet, HashMap};

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

macro_rules! print_vec {
    ($vec:expr) => {
        if $vec.is_empty() {
            println!();
        } else {
            let mut first = true;
            for x in &$vec {
                if first {
                    print!("{}", x);
                    first = false;
                } else {
                    print!(" {}", x);
                }
            }
            println!();
        }
    };
}

macro_rules! print_slice {
    ($slice:expr) => {
        if $slice.is_empty() {
            println!();
        } else {
            let mut first = true;
            for x in $slice {
                if first {
                    print!("{}", x);
                    first = false;
                } else {
                    print!(" {}", x);
                }
            }
            println!();
        }
    };
}

macro_rules! fast_print_vec {
    ($vec:expr) => {
        use std::io::{BufWriter, Write};
        let stdout = std::io::stdout();
        let mut writer = BufWriter::new(stdout.lock());
        if !$vec.is_empty() {
            for (i, x) in $vec.iter().enumerate() {
                if i > 0 {
                    write!(writer, " {}", x).unwrap();
                } else {
                    write!(writer, "{}", x).unwrap();
                }
            }
        }
        writeln!(writer).unwrap();
    };
}

macro_rules! fast_print_slice {
    ($slice:expr) => {
        use std::io::{BufWriter, Write};
        let stdout = std::io::stdout();
        let mut writer = BufWriter::new(stdout.lock());
        if !$slice.is_empty() {
            for (i, x) in $slice.iter().enumerate() {
                if i > 0 {
                    write!(writer, " {}", x).unwrap();
                } else {
                    write!(writer, "{}", x).unwrap();
                }
            }
        }
        writeln!(writer).unwrap();
    };
}

fn main() {
    // 读取所有输入到字符串（全split_whitespace，一次过）
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();

    let t = read!(it=>usize);
    for _ in 0..t {
        let (n, k_i64) = multi_read!(it => usize, i64);
        let a: Vec<i64> = read!(it=>vec_i64, n);
        // 思路：
        // - 设 S 为 a 的去重集合。若取 b ∈ B，则其所有正倍数 ≤ k 必须都在 S 中，因此 b 必须属于 S（否则倍数集合中包含 b 本身）。
        // - 定义 Good 候选：S 中的值 v，满足 v,2v,...,⌊k/v⌋·v 全部在 S 中。
        // - B 必须是 Good 的子集，并覆盖所有 a：对每个 a[i]，至少有一个 Good 的 b 能整除它。
        // - 最小化 B：对每个 a[i] 选“最小的 Good 因子”，收集其去重集合即为一个最小解；若某个 a[i] 没有 Good 因子则不存在解。

        let k = k_i64;
        let mut present: HashSet<i64> = HashSet::with_capacity(n);
        for &x in &a { present.insert(x); }

        // 去重后的值列表
        let vals: Vec<i64> = present.iter().copied().collect();

        // 计算 Good 列表：对 v ∈ S，检查所有倍数是否都在 S 中（遇缺即失败，尽早退出）
        let mut good: Vec<i64> = Vec::new();
        for &v in &vals {
            let mut ok = true;
            let mut tmul: i64 = 1;
            while v * tmul <= k {
                if !present.contains(&(v * tmul)) { ok = false; break; }
                tmul += 1;
            }
            if ok { good.push(v); }
        }

        // 为每个 a[i] 找到最小的 Good 因子：
        // 做法：遍历每个 Good v，把其倍数（在 S 中的）尝试更新为更小的 v。
        let mut min_good_div: HashMap<i64, i64> = HashMap::new();
        for &v in &good {
            let mut tmul: i64 = 1;
            while v * tmul <= k {
                let m = v * tmul;
                if present.contains(&m) {
                    let e = min_good_div.entry(m).or_insert(v);
                    if v < *e { *e = v; }
                }
                tmul += 1;
            }
        }

        // 检查每个 a[i] 是否有 Good 因子，并收集答案集合
        let mut ans_set: HashSet<i64> = HashSet::new();
        let mut possible = true;
        for &x in &a {
            if let Some(&gdiv) = min_good_div.get(&x) {
                ans_set.insert(gdiv);
            } else {
                possible = false;
                break;
            }
        }

        if !possible {
            println!("-1");
        } else {
            let mut ans: Vec<i64> = ans_set.into_iter().collect();
            ans.sort_unstable();
            println!("{}", ans.len());
            if !ans.is_empty() {
                for i in 0..ans.len() {
                    if i > 0 { print!(" "); }
                    print!("{}", ans[i]);
                }
            }
            println!();
        }
    }
}
