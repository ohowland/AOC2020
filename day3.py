
def move(i, j, width):
    i = i+1
    j = j+2
    if i >= width:
        i = i-width
    return (i, j)

def main():
    matrix = []
    width = 0
    with open("./day3.in", "r") as file:
    #with open("./day3.in", "r") as file:
        for i, line in enumerate(file):
            numline = line.replace('.', '0').replace('#', '1').strip()
            row = list()
            for j, c in enumerate(numline):
                row.append(int(c))
            matrix.append(row)
    
    width = len(matrix[0])
    #print(width)
    length = len(matrix)
    #print(length)

    i = j = 0 
    count = 0
    while j < length-1:
        i, j = move(i, j, width)
        print(i, j)
        if matrix[j][i] == 1:
            count += 1

    print(count)


if __name__ == '__main__':
    main()