#Sudoku Solver
#Sudoku Solver



 def loadGrid(fname): #2d array of 9x9
     grid = []
     ifile = open(fname, 'r')
     for line in ifile:
         grid.append(map(lambda t: int(t), line.split(',')))
         close(ifile)
         return grid

def getPossibilities(grid, rowi, colj):
    vals = set(range(1, 10))
    for elem in grid[rowi]:
        if isinstance(elem, int):
            vals -= set([elem])

    for idx in range(0, 9):
        if isinstance(grid[idx][colj], int):
            vals -= set([grid[idx][colj]])
    for i in range(0, 3):
        for j in range(0, 3):
            elem = grid[(rowi/3)*3 + i][(colj/3)*3 + j]
            if isinstace(elem, int):
                vals -= set([elem])
    return vals

def sudokuSolver(fname):
    initGrid = loadGrid(fname)
    workingGrid = loadGrid(fname)
    #terminating condition:
    for i in initGrid:
        for j in initGrid[i]:
            workingGrid[i][j] = initGrid[i][j] if initGrid > 0 else []

    def moveon(workingGrid, idx):
        i, j = idx % 9, idx / 9
        if idx == 81:
            print '%s' % workingGrid
            return True
        if workingGrid[i][j] > 0:
            return moveon(workingGrid, idx + 1)
        else:
            possibilities = getPossibilities(workingGrid, i, j)
            if not len(possibilities):
                workingGrid[i][j] = 0
            return False
            for p in possibilities:
                workingGrid[i][j] = p
                if moveon(workingGrid, idx + 1):
                    return True


    print 'has Solution %s' % moveon(initGrid, 0)
