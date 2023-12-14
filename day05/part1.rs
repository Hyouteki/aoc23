use std::{io::{BufRead, BufReader}, fs::File};

fn parse_num(line: &mut String) -> i64 {
    let (mut num, mut len) = (0, 0);
    let mut flag: bool = false;
    for ch in line.chars() {
        if ch == ' ' && flag {break;}
        if ch.is_numeric() {
            num = num*10 + ch as i64 - '0' as i64;
            flag = true;
        }
        len += 1;
    }
    *line = line[len..].to_string();
    num
}

fn parse_line(line: &mut String) -> (i64, i64, i64) {
    let dst_start = parse_num(line);
    let src_start = parse_num(line);
    let len = parse_num(line);
    (dst_start, src_start, len)
}

fn map_nums(content: &mut Vec<String>, nums: &mut Vec<i64>) {
    let mut n: usize = 0;
    while n < content.len() && content[n].len() != 0 {n += 1;}
    let mut map: Vec<(i64, i64, i64)> = Vec::new();
    {
        let mut i: usize = 0;
        while i < n {        
            map.push(parse_line(&mut content[0]));
            *content = content[1..].to_vec();
            i += 1;
        }
    }
    for i in 0..nums.len() {
        for (dst_start, src_start, len) in map.iter() {
            if src_start <= &nums[i] && nums[i] < src_start + len {
                nums[i] = dst_start + nums[i] - src_start;
                break; 
            }               
        }
    }
    if content.len() > 0 {
        *content = content[2..].to_vec();
    }
}

fn main() {
    let mut content: Vec<String> = BufReader::new(
        File::open("doc.txt").expect("could not open file")).lines()
        .map(|line| line.expect("could not parse line")).collect();
    
    let mut seeds: Vec<i64> = Vec::new();
    content[0] = content[0][7..].to_string();
    while content[0].len() != 0 {
        seeds.push(parse_num(&mut content[0]));
    }
    content = content[3..].to_vec();
    while content.len() != 0 {
        map_nums(&mut content, &mut seeds);
    }
    println!("ans: {}", &seeds.iter().min().unwrap());
}
