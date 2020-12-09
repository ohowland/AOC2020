import copy

def process_iter(target, rest, x):
    if not rest:
        return False

    for z in rest:
        if x+z == target:
            return True 
    
    return False


def process(target, pre):
    for x in pre:
        rest = copy.copy(pre)
        rest.remove(x)
        found = process_iter(target, rest, x)
        if found:
            return True
    
    return False


def process_iter2(target, contig, agg):
    s = sum(agg)
    #print(agg)
    if s == target:
        agg.sort()
        print ("sum: ", s, "\nagg: ", agg, "\nstart, end: ", agg[0], agg[-1], "\nthesum: ", agg[0]+agg[-1])
        return agg[0] + agg[-1]

    if s > target or not contig:
        return 0

    if s < target:
        agg.append(contig[0])
        return process_iter2(target, contig[1:], agg)
    
    return 0

def process2(target, contig):
    v = copy.copy(contig)
    for x in contig:
        agg = list()
        v.remove(x)
        #print(x, v)
        agg.append(x)
        found = process_iter2(target, v, agg)
        if found: 
            return found
    
    return 0


def main():
    invalid = 23278925
    #invalid = 127
    runlen = 5
    with open("./day9.in", "r") as file:
        x = [int(x.strip()) for x in file.readlines()]

    '''
    i = runlen
    j = 0
    while(True):
        if not process(x[i], x[j:runlen+j]):
            print(x[i])
            break
        i += 1
        j += 1
    '''

    #x.remove(invalid)
    print(process2(invalid, x))



if __name__ == '__main__':
    main()