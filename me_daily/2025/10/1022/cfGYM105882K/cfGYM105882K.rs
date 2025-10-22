use std::io::{self, Read};

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut iter = input.split_whitespace();

    let n: usize = iter.next().unwrap().parse().unwrap();
    let mut xy = Vec::new();

    if n & 1 == 1 {
        xy.push((0, 0));
        let (mut x, mut y) = (0, 0);
        for _ in 0..(n / 2 - 1) {
            y += 25;
            xy.push((x, y));
            x += 25;
            xy.push((x, y));
        }
        x = x.max(25);
        xy.push((x, 0));
        xy.push((x / 25 * 9, x / 25 * -12));
    } else {
        xy.push((0, 0));
        let (mut x, mut y) = (0, 0);
        for _ in 0..(n / 2 - 1) {
            y += 25;
            xy.push((x, y));
            x += 25;
            xy.push((x, y));
        }
        xy.push((x, 0));
    }

    let (dx, dy) = (5, 12);
    for (x, y) in &xy {
        let X = x * dx + y * dy;
        let Y = -dy * x + y * dx;
        println!("{} {}", X, Y);
    }
}
