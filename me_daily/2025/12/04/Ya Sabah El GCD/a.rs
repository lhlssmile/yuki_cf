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
fn gcd(mut a: i64, mut b: i64) -> i64 {
    while b > 0 {
        let t = a % b;
        a = b;
        b = t;
    }
    a
}
fn get_primes(mut x: i64) -> Vec<i64> {
    let mut res: Vec<i64> = Vec::new();
    let mut i: i64 = 2;
    while i * i <= x {
        if x % i == 0 {
            res.push(i);
            while x % i == 0 {
                x /= i;
            }
        }
        i += 1;
    }
    if x > 1 {
        res.push(x);
    }
    res
}
fn main() {
    // 读取所有输入到字符串（全split_whitespace，一次过）
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();

    let n = read!(it=>usize);
    let a = read!(it=>vec_i64, n);
    let b = read!(it=>vec_i64, n);

    let mut g: i64 = a[0];
    for i in 1..n {
        g = gcd(g, a[i])
    }
    if g == 1 {
        println!("{}", 0)
    } else {
        let primes = get_primes(g);
        let k = primes.len();
        let mut covers: Vec<usize> = vec![0; n];
        for i in 0..n {
            let mut mask: usize = 0;
            for j in 0..k {
                let p = primes[j];
                if b[i] % p != 0 {
                    mask |= 1_usize << j;
                }
            }
            covers[i] = mask;
        }
        const INF: i64 = 1_i64 << 60;
        let mut f: Vec<i64> = vec![INF; 1 << k];
        f[0] = 0;
        for i in 0..n {
            let cost: i64 = (i as i64 + 1) * (i as i64 + 2);
            let mask_i: usize = covers[i];
            let mut new_f = f.clone();
            for prev in 0..(1 << k) {
                if f[prev] == INF { continue; }
                let new_m = prev | mask_i;
                let val = f[prev] + cost;
                if val < new_f[new_m] { new_f[new_m] = val; }
            }
            f = new_f;
        }
        if f[(1 << k) - 1] == INF {
            println!("{}", -1);
        } else {
            println!("{}", f[(1 << k) - 1]);
        }
    }
}
