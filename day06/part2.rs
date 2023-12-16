use std::{io::{BufRead, BufReader}, fs::File};

fn parse_num(line: &String) -> i64 {
    let mut num = 0;
    for ch in line.chars() {
        if ch.is_numeric() {
            num = num*10 + ch as i64 - '0' as i64;
        }
    }
    num
}

fn main() {
    let content: Vec<String> = BufReader::new(
        File::open("doc.txt").expect("could not open file"))
        .lines().map(|line| line.expect("could not parse line"))
        .collect();
    let time: i64 = parse_num(&content[0]);
    let distance: i64 = parse_num(&content[1]);
    let mut ans: i64 = 0;
    for i in 1..time {
        if distance < (time - i)*i {ans += 1};
    }
    println!("ans: {}", ans);
}
