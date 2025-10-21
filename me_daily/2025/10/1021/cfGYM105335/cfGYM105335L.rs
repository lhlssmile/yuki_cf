use std::io::{self, Read};

fn main() {
    // 读取全部输入
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut iter = input.split_whitespace();

    let mut next = || iter.next().unwrap().parse::<usize>().unwrap();

    // 读取n和a
    let n: usize = next();
    let mut a: Vec<usize> = Vec::with_capacity(n);
    for _ in 0..n {
        a.push(next());
    }

    if n == 1 {
        println!("1");
        return;
    }
    if n == 2 {
        println!("{} {}", 3 - a[0], 3 - a[1]);
        return;
    }

    // 前两个计算（模拟k1,k2偏移）
    let mut tmp0 = a[0] as isize - 1;
    let mut tmp1 = a[1] as isize - 1;
    if tmp1 > tmp0 {
        tmp1 -= 1;
    }
    tmp1 += (n as isize * (n - 1) as isize) / 2;
    tmp0 += tmp1 / ((n - 1) as isize);
    tmp1 %= (n - 1) as isize;
    tmp0 %= n as isize;
    let mut ans0 = (tmp0 + 1) as usize;
    let mut ans1 = (tmp1 + 1) as usize;
    if ans1 >= ans0 {
        ans1 += 1;
    }
    if ans1 > n {
        ans1 = n; // 防超n
    }

    // 标记（vis1: p后缀值出现=1；vis2: q可用=1）
    let mut vis1: Vec<bool> = vec![false; n + 1];
    let mut vis2: Vec<bool> = vec![true; n + 1]; // 1~n true
    for i in 2..n {
        vis1[a[i]] = true;
    }
    vis2[ans0] = false;
    vis2[ans1] = false;

    // 映射（双指针配对剩余）
    let mut mapping: Vec<usize> = vec![0; n + 1];
    let mut p1 = 1usize;
    let mut p2 = 1usize;
    for _ in 0..(n - 2) {
        while p1 <= n && !vis1[p1] {
            p1 += 1;
        }
        while p2 <= n && !vis2[p2] {
            p2 += 1;
        }
        if p1 > n || p2 > n {
            break;
        }
        mapping[p1] = p2;
        p1 += 1;
        p2 += 1;
    }

    // 构建ans
    let mut ans: Vec<usize> = Vec::with_capacity(n);
    ans.push(ans0);
    ans.push(ans1);
    for i in 2..n {
        ans.push(mapping[a[i]]);
    }

    // 输出一行空格
    print!("{}", ans[0]);
    for i in 1..n {
        print!(" {}", ans[i]);
    }
    println!();
}
