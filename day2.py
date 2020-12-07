from collections import Counter

pass_list = list()
with open("./day2.in", "r") as file:
    for line in file:
        (r, l, p) = line.split(' ')
        lo, hi = r.split('-')
        char = l[0]
        password = p.strip()

        if password[int(lo)-1] == char and password[int(hi)-1] != char :
            pass_list.append(password)
        if password[int(lo)-1] != char and password[int(hi)-1] == char :
            pass_list.append(password)
        
print(len(pass_list))



