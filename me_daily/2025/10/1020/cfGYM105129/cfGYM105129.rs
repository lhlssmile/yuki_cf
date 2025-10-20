use std::io::{self, Read};

const PRE: [i32; 15] = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47];

fn build_to_check() -> Vec<i64> {
    let mut to_check = vec![1i64];
    for &x in PRE.iter() {
        let k = to_check.len();
        let mut tmp = Vec::with_capacity(k);
        for &v in to_check.iter() {
            let new_val = v * x as i64;
            tmp.push(new_val);
        }
        to_check.extend(tmp);
    }
    to_check.sort();
    to_check.dedup();
    to_check
}

fn gcd(mut a: i64, mut b: i64) -> i64 {
    while b > 0 {
        let t = b;
        b = a % b;
        a = t;
    }
    a
}

fn main() {
    // 直接构造 to_check 一次
    let to_check = build_to_check();

    // 读入所有输入
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();
    let t: usize = it.next().unwrap().parse().unwrap();

    for _ in 0..t {
        let n: usize = it.next().unwrap().parse().unwrap();
        let mut vis = vec![0i32; 51];
        for _ in 0..n {
            let x: usize = it.next().unwrap().parse().unwrap();
            vis[x] = 1;
        }

        'outer: for &v in to_check.iter() {
            let mut flg = true;
            for i in 1..=50 {
                if vis[i] == 1 && gcd(v, i as i64) == 1 {
                    flg = false;
                    break;
                }
            }
            if flg {
                println!("{}", v);
                break 'outer;
            }
        }
    }
}
