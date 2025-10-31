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

fn has_future_div2(divs: &str, start: usize) -> bool {
    // 从start位置开始，检查后面是否有'2'（Rust的str.contains超简单！）
    divs[start..].contains('2')
}

fn main() {
    // 读取所有输入到字符串（全split_whitespace，一次过）
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();

    let t = read!(it => usize);
    for _ in 0..t {
        let (r0, x, d, n) = multi_read!(it => i32, i32, i32, usize);
        let divs = read!(it => str);
        let mut ans = 0i32;
        let mut cur_s = r0;
        for i in 0..n {
            let ch = divs.as_bytes()[i]; // 用as_bytes()取u8，方便比b'1'
            if ch == b'1' {
                ans += 1;
                // 如果后面有'2'，降rating
                if i < n - 1 && has_future_div2(&divs, i + 1) {
                    cur_s = (cur_s - d).max(0);
                }
            } else {
                // '2'
                if cur_s < x {
                    ans += 1;
                    // 参加后，如果后面有'2'，降rating
                    if i < n - 1 && divs[i + 1..].contains('2') {
                        cur_s = (cur_s - d).max(0);
                    }
                }
            }
        }
        println!("{}", ans)
    }
}
