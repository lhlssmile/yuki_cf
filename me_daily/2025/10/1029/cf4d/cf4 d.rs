use std::io::{self, BufRead};

#[derive(Debug, Clone)]
struct Envelope {
    w: i32,
    h: i32,
    idx: usize,
}

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    
    // 读取第一行
    let first_line = lines.next().unwrap().unwrap();
    let parts: Vec<i32> = first_line
        .split_whitespace()
        .map(|s| s.parse().unwrap())
        .collect();
    let (n, w, h) = (parts[0], parts[1], parts[2]);
    
    let mut envs = Vec::new();
    
    // 读取信封信息
    for i in 0..n {
        let line = lines.next().unwrap().unwrap();
        let parts: Vec<i32> = line
            .split_whitespace()
            .map(|s| s.parse().unwrap())
            .collect();
        let (wi, hi) = (parts[0], parts[1]);
        
        // 只考虑能放下卡片的信封
        if wi > w && hi > h {
            envs.push(Envelope {
                w: wi,
                h: hi,
                idx: i + 1,
            });
        }
    }
    
    if envs.is_empty() {
        println!("0");
        return;
    }
    
    // 按宽度排序
    envs.sort_by_key(|env| env.w);
    
    let m = envs.len();
    let mut dp = vec![1; m];
    let mut parent = vec![-1i32; m];
    
    // DP求最长递增子序列
    for i in 1..m {
        for j in 0..i {
            // 当前信封的宽高都要严格大于前一个
            if envs[i].w > envs[j].w && envs[i].h > envs[j].h {
                if dp[j] + 1 > dp[i] {
                    dp[i] = dp[j] + 1;
                    parent[i] = j as i32;
                }
            }
        }
    }
    
    // 找到最长链的结尾
    let mut max_len = 0;
    let mut end_idx = 0;
    for i in 0..m {
        if dp[i] > max_len {
            max_len = dp[i];
            end_idx = i;
        }
    }
    
    // 重构路径
    let mut path = Vec::new();
    let mut idx = end_idx as i32;
    while idx != -1 {
        path.push(envs[idx as usize].idx);
        idx = parent[idx as usize];
    }
    
    // 反转路径
    path.reverse();
    
    println!("{}", max_len);
    for (i, &v) in path.iter().enumerate() {
        if i > 0 {
            print!(" ");
        }
        print!("{}", v);
    }
    println!();
}