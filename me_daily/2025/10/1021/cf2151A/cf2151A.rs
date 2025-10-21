use std::io::{self, Read};

fn main() {
    // 读取全部输入
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut iter = input.split_whitespace();

    let mut next = || iter.next().unwrap().parse::<i32>().unwrap();

    let t: i32 = next();
    for _ in 0..t {
        let n: i32 = next();
        let m: i32 = next();
        let mut fsb: Vec<i32> = vec![];
        for _ in 0..m {
            fsb.push(next());
        }
        let mut inc = 0;
        for i in 1..m as usize {
            if fsb[i] > fsb[i - 1] {
                inc += 1;
            } else {
                inc = 0;
            }
        }
        if inc == m - 1 {
            let ans = n - fsb[(m as usize) - 1] + 1;
            println!("{}", ans);
        } else {
            println!("1");
        }
    }
}
