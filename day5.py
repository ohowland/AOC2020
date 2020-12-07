
def validate():
    pass

class Node:
    def __init__(self, left, right, val):
        self.left = left
        self.right = right
        self.val = val

def build_graph_iter(vals, depth):
    if depth == 0:
        #left = Node(None, None, vals[0])
        #right = Node(None, None, vals[0])
        return Node(None, None, [x for x in vals])
    
    else:
        half = int(len(vals)/2)
        left = build_graph_iter(vals[:half], depth - 1)
        right = build_graph_iter(vals[half:], depth - 1)
    
    return Node(left, right, vals)

def build_graph(size, depth):
    return build_graph_iter(range(size), depth)
            
def seek(node, direct):
    for i in direct:
        #print(i)
        if i == 'F' or i == 'L':
            node = node.left
        else:
            node = node.right
    return node.val

def main():
    with open("./day5.in", "r") as file:
        agg = list()
        for line in file:
            rows=128
            cols=8
            line = line.strip()
            row_seek = line[:7]
            col_seek = line[7:]

            node_row = build_graph(rows, 7)
            row = seek(node_row, row_seek)
            
            node_col = build_graph(cols, 3)
            col = seek(node_col, col_seek)

            #print(row, col)
            id = row[0]*8+col[0]
            agg.append((row[0], col[0]))
            
        
        all_seats = set()
        for i in range(1,127):
            for j in range(cols):
                all_seats.add((i, j))

        for seat in agg:
            all_seats.remove(seat)

        #print(all_seats)

        rem_ids = list()
        for x in all_seats:
            (i, j) = x
            rem_ids.append(i*8+j)

        rem_ids.sort()
        print(rem_ids)
            


        

    #print(max(agg))
    

if __name__ == '__main__':
    main()