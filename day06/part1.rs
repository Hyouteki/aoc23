use std::{io::{BufRead, BufReader}, fs::File};

fn parse_num(line: &mut String) -> i32 {
    let (mut num, mut len) = (0, 0);
    let mut flag: bool = false;
    for ch in line.chars() {
        if ch == ' ' && flag {break;}
        if ch.is_numeric() {
            num = num*10 + ch as i32 - '0' as i32;
            flag = true;
        }
        len += 1;
    }
    *line = line[len..].to_string();
    num
}

fn main() {
    let mut content: Vec<String> = BufReader::new(
        File::open("doc.txt").expect("could not open file"))
        .lines().map(|line| line.expect("could not parse line"))
        .collect();
    let mut time: Vec<i32> = Vec::new();
    while content[0].len() > 0 {
        time.push(parse_num(&mut content[0]));
    }
    let mut distance: Vec<i32> = Vec::new();
    while content[1].len() > 0 {
        distance.push(parse_num(&mut content[1]));
    }
    let mut ans: i64 = 1;
    for i in 0..time.len() {
        let mut x = 0;
        for j in 1..time[i] {
            if distance[i] < (time[i] - j)*j {x += 1};
        }
        ans *= x;
    }
    println!("ans: {}", ans);
}
