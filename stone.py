def stone(y, s):

    for i in s:
    
        if (y!=i and y%i==0):
            return (1 + (y/i)*stone(i, s))
    
    return 0
y=12
s = [4,3,2];
moves = stone(y, s);
print(moves)