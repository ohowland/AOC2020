def process_iter(inst, i, acc, seen, flag):
    if i in seen:
        #print('failed')
        return acc
    
    try:
        test = inst[i]
    except IndexError:
        print('success')
        print(acc)
        return acc
    
    seen.append(i)
    
    cmd, val = inst[i]
    if cmd == 'nop':
        acc = process_iter(inst, i+1, acc, seen, flag)
        if flag == False:
            acc = process_iter(inst, i+val, acc, seen, True)
        
    elif cmd == 'acc':
        acc = process_iter(inst, i+1, acc+val, seen, flag)

    elif cmd == 'jmp':
        acc = process_iter(inst, i+val, acc, seen, flag)
        if flag == False:
            acc = process_iter(inst, i+1, acc, seen, True)

    return acc

def process(inst):

    return process_iter(inst, 0, 0, [], False)

def main():
    bag_map = dict()
    with open("./day8.in", "r") as file:
        seen = set()
        acc = 0
        instructions = list()
        for line in file:
            x, y = line.strip().split(' ')
            instructions.append((x, int(y)))
        
    x = process(instructions)
    #print(process(instructions))

if __name__ == '__main__':
    main()