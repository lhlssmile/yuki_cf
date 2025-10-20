use std::io::{self, Read};

fn solve(a: &Vec<i64>) -> i64 {
    let mut sum_even = 0i64;
    let mut odd_vals: Vec<i64> = Vec::new();
    for &x in a {
        if x % 2 == 0 {
            sum_even += x;
        } else {
            odd_vals.push(x);
        }
    }
    let k = odd_vals.len();
    if k == 0 {
        return 0;
    }
    odd_vals.sort_unstable(); // 升序，小的在前好牺牲
    let sum_odd: i64 = odd_vals.iter().sum();
    let num_sac = k / 2; // floor(k/2)
    let sum_sac: i64 = odd_vals.iter().take(num_sac).sum();
    sum_even + sum_odd - sum_sac
}
fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut iter = input.split_whitespace();

    let mut next = || iter.next().unwrap();

    let t: usize = next().parse().unwrap();
    for _ in 0..t {
        let n: usize = next().parse().unwrap();
        let a: Vec<i64> = (0..n).map(|_| next().parse().unwrap()).collect();
        println!("{}", solve(&a));
    }
}
