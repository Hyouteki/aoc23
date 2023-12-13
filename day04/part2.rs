use std::{io::{BufRead, BufReader}, fs::File};
use std::collections::HashSet;

fn slurp_file() -> Vec<String> {
    BufReader::new(File::open("doc.txt")
        .expect("could not open file")).lines()
        .map(|line| line.expect("could not parse line"))
        .collect()
}

fn parse_num(s: &mut String) -> i32 {
    let (mut num, mut len) = (0, 0);
    let mut flag: bool = false;
    for ch in s.chars() {
        if ch == ' ' || ch == '|' {
            if flag {break;}
            len += 1;
            continue;
        }
        if ch.is_numeric() {
            num = num*10 + ch as i32 - '0' as i32;
            len += 1;
            flag = true;
        }
    }
    *s = s[len..].to_string();
    num
}

fn main() {
    let mut content: Vec<String> = slurp_file();
    let mut cards: Vec<i32> = vec![1; content.len()];
    for i in 0..content.len() {
        // eat 'Card '
        content[i] = content[i][5..].to_string();
        { // eat till ': '
            let mut x: usize = 1;
            while content[i].chars().nth(x) != Some(':') {
                x += 1;
            }
            x += 2;
            content[i] = content[i][x..].to_string();
        }
        let mut set: HashSet<i32> = HashSet::new();
        for _ in 0..10 {
            set.insert(parse_num(&mut content[i]));
        }
        let mut x: usize = 0;
        for _ in 0..25 {
            let num: i32 = parse_num(&mut content[i]);
            if set.contains(&num) {x += 1};
        }
        for j in i+1..i+1+x {
            if cards.len() <= j {break;}
            cards[j] += cards[i];
        }
    }
    println!("ans: {}", cards.iter().sum::<i32>());
}
