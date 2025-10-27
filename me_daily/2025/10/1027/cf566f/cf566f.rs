// use std::io::{self, Read};

// macro_rules! read {
//     // 单个值：read!(it => usize)
//     ($it:ident => $t:ty) => {
//         $it.next().unwrap().parse::<$t>().unwrap()
//     };
//     // 向量版本：read!(it => vec_usize, n)
//     ($it:ident => vec_usize, $n:expr) => {
//         (0..$n).map(|_| read!($it => usize)).collect::<Vec<_>>()
//     };
//     ($it:ident => vec_i64, $n:expr) => {
//         (0..$n).map(|_| read!($it => i64)).collect::<Vec<_>>()
//     };
// }

// fn main() {
//     // 快速读入
//     let mut input = String::new();
//     io::stdin().read_to_string(&mut input).unwrap();
//     let mut it = input.split_whitespace();

//     const MAX: usize = 1_000_001;
//     let n: usize = read!(it => usize);
//     let a: Vec<usize> = read!(it => vec_usize, n);

//     let mut exist = vec![false; MAX];
//     let mut f = vec![0; MAX];
//     let mut ans = 0;

//     for &x in &a {
//         exist[x] = true;
//     }

//     for x in 1..MAX {
//         if !exist[x] {
//             continue;
//         }
//         f[x] = f[x].max(1);
//         for y in (x * 2..MAX).step_by(x) {
//             if exist[y] {
//                 f[y] = f[y].max(f[x] + 1);
//             }
//         }
//         ans = ans.max(f[x]);
//     }

//     println!("{}", ans);
// }
