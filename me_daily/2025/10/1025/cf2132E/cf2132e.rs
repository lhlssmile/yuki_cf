use std::io::{self, Read};

fn next<T: std::str::FromStr>(it: &mut std::str::SplitWhitespace) -> T
where
    T::Err: std::fmt::Debug,
{
    it.next().unwrap().parse::<T>().unwrap()
}

fn read_vec_i64(it: &mut std::str::SplitWhitespace, n: usize) -> Vec<i64> {
    (0..n).map(|_| next::<i64>(it)).collect()
}

fn read_vec_usize(it: &mut std::str::SplitWhitespace, n: usize) -> Vec<usize> {
    (0..n).map(|_| next::<usize>(it)).collect()
}

fn main() {
    // 读取所有输入
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();

    let t: usize = next(&mut it);
    for _case in 0..t {
        let n: usize = next(&mut it);
        let m: usize = next(&mut it);
        let q: usize = next(&mut it);

        let mut a: Vec<i64> = read_vec_i64(&mut it, n);
        let mut b: Vec<i64> = read_vec_i64(&mut it, m);

        let mut queries: Vec<[usize; 3]> = vec![[0usize; 3]; q];
        for i in 0..q {
            let x = next::<usize>(&mut it);
            let y = next::<usize>(&mut it);
            let z = next::<usize>(&mut it);
            queries[i] = [x, y, z];
        }

        // 按降序
        a.sort_unstable_by(|x, y| y.cmp(x));
        b.sort_unstable_by(|x, y| y.cmp(x));

        // 前缀和
        let mut prefix_a: Vec<i64> = vec![0; n + 1];
        let mut prefix_b: Vec<i64> = vec![0; m + 1];
        for i in 0..n {
            prefix_a[i + 1] = prefix_a[i] + a[i];
        }
        for i in 0..m {
            prefix_b[i + 1] = prefix_b[i] + b[i];
        }

        for qi in queries {
            let x = qi[0];
            let y = qi[1];
            let z = qi[2];

            if z == 0 {
                println!("0");
                continue;
            }

            // l = max(0, z - y), r = min(z, x)
            let l = if z > y { z - y } else { 0 };
            let r = if z < x { z } else { x };

            if l > r {
                println!("0");
                continue;
            }

            // ternary_search(k) = prefix_a[k] + prefix_b[z-k]
            // 注意边界：k in [l..=r], prefix vectors 已经是 n+1, m+1
            let ternary = |k: usize| -> i64 {
                // safe because prefix vectors have size >= needed indices when input valid
                prefix_a[k] + prefix_b[z.saturating_sub(k)]
            };

            let mut lo = l;
            let mut hi = r;
            while hi.saturating_sub(lo) >= 3 {
                let m1 = lo + (hi - lo) / 3;
                let m2 = hi - (hi - lo) / 3;
                if ternary(m1) > ternary(m2) {
                    hi = m2;
                } else {
                    lo = m1;
                }
            }

            let mut mx: i64 = i64::MIN;
            for k in lo..=hi {
                mx = mx.max(ternary(k));
            }

            println!("{}", mx);
        }
    }
}
