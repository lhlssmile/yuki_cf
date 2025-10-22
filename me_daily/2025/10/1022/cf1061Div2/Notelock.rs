use std::io::{self, BufRead};

fn solve(s: &str, k: usize) -> usize {
    let n = s.len();
    let mut ans = 0;
    let mut last = -(k as i32);  // 上一个有效1的位置，初始化为-k确保第一个1会被保护
    
    for (i, ch) in s.chars().enumerate() {
        if ch == '1' {
            let i = i as i32;
            if i - last >= k as i32 {
                // 这个1与前一个有效1距离太远，需要保护它
                ans += 1;
                last = i;
            } else {
                // 距离近，不需要保护，但它也能起到"阻挡"作用
                last = i;
            }
        }
    }
    ans
}

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    
    let t: usize = lines.next().unwrap().unwrap().parse().unwrap();
    
    for _ in 0..t {
        let line = lines.next().unwrap().unwrap();
        let parts: Vec<&str> = line.split_whitespace().collect();
        let n: usize = parts[0].parse().unwrap();
        let k: usize = parts[1].parse().unwrap();
        
        let s = lines.next().unwrap().unwrap();
        
        println!("{}", solve(&s, k));
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_example_1() {
        assert_eq!(solve("11", 2), 1);
    }
    
    #[test]
    fn test_example_2() {
        assert_eq!(solve("100001", 6), 1);
    }
    
    #[test]
    fn test_example_4() {
        assert_eq!(solve("1010101", 2), 4);
    }
    
    #[test]
    fn test_edge_cases() {
        assert_eq!(solve("1", 2), 1);
        assert_eq!(solve("0", 2), 0);
        assert_eq!(solve("101", 2), 2);
        assert_eq!(solve("1001", 3), 2);
    }
}