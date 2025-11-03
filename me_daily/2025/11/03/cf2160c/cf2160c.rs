use std::io::{self, Read};

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut lines = input.lines();
    
    let t: usize = lines.next().unwrap().parse().unwrap();
    
    for _ in 0..t {
        let n: u64 = lines.next().unwrap().parse().unwrap();
        let binary = format!("{:b}", n);
        let mut ans = "NO";
        
        for i in 1..64 {
            if binary.len() <= i {
                let padded = format!("{:0width$}", binary.parse::<u64>().unwrap_or(0), width = i);
                let padded_str = format!("{:0width$b}", binary.parse::<u64>().unwrap_or(0), width = i);
                
                // Check if it's a palindrome
                let is_palindrome = padded_str == padded_str.chars().rev().collect::<String>();
                
                let mut valid = is_palindrome;
                
                // If odd length, middle bit must be 0
                if i % 2 == 1 {
                    let middle_char = padded_str.chars().nth(i / 2).unwrap();
                    valid = valid && middle_char == '0';
                }
                
                if valid {
                    ans = "YES";
                    break;
                }
            }
        }
        
        println!("{}", ans);
    }
}