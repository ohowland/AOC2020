
def process(grp):
    #print(grp)
    finalset = grp[0]
    for s in grp[1:]:
        finalset = finalset.intersection(s)

    #print(finalset)
    return len(finalset)

def main():
    with open("./day6.in", "r") as file:
        agg = list()
        grp = list() 
        flag = False
        for i, line in enumerate(file):
            if line == '\n':
                agg.append(process(grp))
                grp = list()
                flag = False 
            else:
                sub = set()
                for l in line:
                    if l == '\n':
                        pass
                    else:
                        sub.add(l)
                grp.append(sub)
                flag = True

        if flag == True:
            agg.append(process(grp))
        
        print(agg)
        print(sum(agg))

if __name__ == '__main__':
    main()