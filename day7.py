import re

bag_re = re.compile(r'^(\w+ \w+) bags contain (.*)$')
bag_inner_re = re.compile(r'^[\s]?(\d) (\w+ \w+)')


def process_iter(bag_map, bag_list):
    if 'shiny gold' in bag_list:
        return 1
    
    elif not bag_list:
        return 0

    else:
        for bag in bag_list:
            found = process_iter(bag_map, bag_map[bag])
            if found == 1:
                return 1
    
    return 0



def process(bag_map):
    d = dict()
    for key, val in bag_map.items():
        d[key] = process_iter(bag_map, val)
    
    return d


def process2_iter(bag_map, agg, counter):
    if not agg:
        return counter

    else:
        for bag in agg:
            bags = bag_map[bag]
            counter = process2_iter(bag_map, bags, counter+1)
    
    return counter


def process2(bag_map):
    counter = process2_iter(bag_map, bag_map['shiny gold'], 0)

    return counter

def main():
    bag_map = dict()
    with open("./day7.in", "r") as file:
        for line in file:
            first = bag_re.match(line)
            bag = first.group(1)

            second = first.group(2).split(',')
            contained = list()
            for l in second:
                l = l.strip()
                sub = bag_inner_re.match(l)
                #print(sub)
                if sub:
                    contained.extend([sub.group(2)]*int(sub.group(1)))
            
            bag_map[bag] = contained

    import time
    t1 = time.time()
    count = 0
    r = process(bag_map)
    for key, val in r.items():
        if val == 1:
            count += 1
    t2 = time.time()
    print(count)
    print(t2-t1)

    #r = process2(bag_map)
    #print(r)

if __name__ == '__main__':
    main()