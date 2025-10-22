use std::io::{self, Read};

fn main() {
    // 读取全部输入
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut iter = input.split_whitespace();

    let mut next = || iter.next().unwrap();
    let t: usize = next().parse().unwrap();
    for _ in 0..t {
        let n: usize = next().parse().unwrap();
        let a: Vec<i64> = (0..n).map(|_| next().parse().unwrap()).collect();

        let mut m: Vec<i64> = vec![0; n + 1];
        m[1] = a[0];
        for i in 1..n {
            m[i + 1] = m[i].max(a[i])
        }
        let mut ans = 0i64;
        for i in (0..n).step_by(2) {
            if i == 0 {
                let u = m[2] - 1;
                let b = a[i].min(0.max(u));
                ans += a[i] - b;
            } else if i == n - 1 {
                let u = m[n - 1] - 1;
                let b = a[i].min(0.max(u));
                ans += a[i] - b;
            } else {
                let u = m[i].min(m[i + 2]) - 1;
                let b = a[i].min(0.max(u));
                ans += a[i] - b;
            }
        }
        println!("{:?}", ans);
    }
}
