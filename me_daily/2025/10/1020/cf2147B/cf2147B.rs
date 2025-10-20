use std::io::{self, Read};

fn solve(n: usize) -> Vec<i32> {
    let n = n as i32;
    let mut res: Vec<i32> = vec![0; 2 * n as usize];
    for i in 0..n {
        res[i as usize] = n - i;
    }
    for x in (1..=n).rev() {
        for j in (x as usize..2 * n as usize).step_by(x as usize) {
            if res[j] == 0 {
                res[j] = x;
                break;
            }
        }
    }
    res
}

fn main() {
    // 读取全部输入
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut iter = input.split_whitespace();

    let mut next = || iter.next().unwrap().parse().unwrap();
    let t: usize = next();

    for _ in 0..t {
        let n: usize = next();
        let res = solve(n);
        for i in 0..2 * n as usize {
            print!("{}", res[i]);
            if i + 1 < 2 * n as usize {
                print!(" ");
            } else {
                println!();
            }
        }
    }
}
