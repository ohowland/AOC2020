import re

re1 = re.compile(r'(\w+):.*')

year_re = re.compile(r'^\w+:([0-9]{4})$')

height_re = re.compile(r'^\w+:(\d+)(in|cm)$')

hair_re = re.compile(r'^\w+:#[0-9a-f]{6}$')

pid_re = re.compile(r'^\w+:[0-9]{9}$')

eye_re = re.compile(r'^\w+:(\w{3})$')

def process(agg):
    print('processing with', agg)
    good = set(['byr', 'iyr', 'eyr', 'hgt', 'hcl', 'ecl', 'pid', 'cid'])
    for item in agg:
        m = re1.match(item)
        clear = False
        try:
            if m:
                if m[1] == 'byr':
                    year = year_re.match(item)
                    if 1920 <= int(year[1]) <= 2002:
                        clear = True
                if m[1] == 'iyr':
                   year = year_re.match(item)
                   if 2010 <= int(year[1]) <= 2020:
                       clear = True
                if m[1] == 'eyr':
                    year = year_re.match(item)
                    if 2020 <= int(year[1]) <= 2030:
                        clear = True
                if m[1] == 'hgt':
                    height = height_re.match(item)
                    if height[2] == 'in':
                        if 59 <= int(height[1]) <= 76:
                            clear = True
                    if height[2] == 'cm':
                        if 150 <= int(height[1]) <= 193:
                            clear = True
                if m[1] == 'hcl':
                    if hair_re.match(item):
                        clear = True
                if m[1] == 'ecl':
                    eye = eye_re.match(item)
                    if eye[1] in set(['amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth']):
                        clear = True
                if m[1] == 'pid' and pid_re.match(item):
                    clear = True
                if m[1] == 'cid':
                    clear = True
        except:
            pass
        if clear:
            try:
                good.remove(m[1])
            except:
                pass
    
    if good == set() or good == set(['cid']):
        return True
    else:
        return False

    

def main():
    with open("./day4.in", "r") as file:
    #with open("./day4.in", "r") as file:
        agg = []
        count = 0
        flag = False
        for i, line in enumerate(file):
            if line == '\n':
                if process(agg):
                    count += 1
                agg = []
                flag = False 
            else:
                agg.extend([x.strip() for x in line.split(' ')])
                flag = True

        if flag == True:
            if process(agg):
                count += 1

    print(count)

if __name__ == '__main__':
    main()