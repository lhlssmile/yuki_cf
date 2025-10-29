use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    
    let first_line = lines.next().unwrap().unwrap();
    let mut parts = first_line.split_whitespace();
    let n: usize = parts.next().unwrap().parse().unwrap();
    let m: usize = parts.next().unwrap().parse().unwrap();
    
    let mut idxs1 = Vec::new();
    let mut idxs2 = Vec::new();
    
    for i in 1..=m {
        let line = lines.next().unwrap().unwrap();
        let mut parts = line.split_whitespace();
        let ai: i32 = parts.next().unwrap().parse().unwrap();
        let bi: i32 = parts.next().unwrap().parse().unwrap();
        
        if ai > bi {
            idxs1.push(i);
        } else {
            idxs2.push(i);
        }
    }
    
    println!("YES");
    
    if idxs1.len() > idxs2.len() {
        println!("{}", idxs1.len());
        let result: Vec<String> = idxs1.iter().map(|x| x.to_string()).collect();
        println!("{}", result.join(" "));
    } else {
        println!("{}", idxs2.len());
        let result: Vec<String> = idxs2.iter().map(|x| x.to_string()).collect();
        println!("{}", result.join(" "));
    }
}