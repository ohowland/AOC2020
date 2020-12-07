acct = list()
with open("./day1.in", "r") as file:
    for line in file:
        acct.append(int(line))

final = 2020

for x in acct:
    for y in acct:
        for z in acct:
            if (x + y + z == final):
                print(x, y, z, (x*y*z))