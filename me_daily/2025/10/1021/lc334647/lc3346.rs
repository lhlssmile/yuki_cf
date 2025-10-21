use std::collections::HashMap;
use std::io::{self, Read};

fn solve(a: &Vec<i32>, k: i32, op: i32) -> i32 {
    let mut cnt: HashMap<i32, i32> = HashMap::new();
    let mut diff: HashMap<i32, i32> = HashMap::new();

    for &x in a {
        *cnt.entry(x).or_insert(0) += 1;
        *diff.entry(x - k).or_insert(0) += 1;
        *diff.entry(x + k + 1).or_insert(0) -= 1;
    }

    let mut items: Vec<_> = diff.into_iter().collect();
    items.sort_by_key(|(x, _)| *x);

    let mut ans = 0;
    let mut sumd = 0;
    for (x, d) in items {
        sumd += d;
        let c = *cnt.get(&x).unwrap_or(&0);
        ans = ans.max(sumd.min(c + op));
    }

    ans
}

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut iter = input.split_whitespace();

    let mut next = || iter.next().unwrap();
    let n: usize = next().parse().unwrap();
    let k: i32 = next().parse().unwrap();
    let op: i32 = next().parse().unwrap();
    let a: Vec<i32> = (0..n).map(|_| next().parse().unwrap()).collect();

    println!("{}", solve(&a, k, op));
}
