#Sudoku Solver
#Sudoku Solver

import pprint

def loadGrid(fname): #2d array of 9x9
    grid = []
    ifile = open(fname, 'r')
    for line in ifile:
        grid.append(map(lambda t: int(t), line.split(',')))
    ifile.close()    
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
            if isinstance(elem, int):
                vals -= set([elem])
    return vals

def sudokuSolver(fname):
    initGrid = loadGrid(fname)
    workingGrid = loadGrid(fname)
    #terminating condition:
    for i, row in enumerate(initGrid):
        for j, val in enumerate(row):
            workingGrid[i][j] = val if val > 0 else []

    def moveon(workingGrid, idx, iter_count):
        i, j = idx % 9, idx / 9
        if idx == 81:
            pprint.pprint(workingGrid)
            return True
        if isinstance(workingGrid[i][j], int) and workingGrid[i][j] > 0:
            return moveon(workingGrid, idx + 1, iter_count + 1)
        else:
            possibilities = getPossibilities(workingGrid, i, j)
            #print '%d: (%d,%d): %s' % (iter_count, i, j, possibilities)
            pprint.pprint(workingGrid)
            if not len(possibilities):
                workingGrid[i][j] = 0
                return False
            for p in possibilities:
                workingGrid[i][j] = p
                if moveon(workingGrid, idx + 1, iter_count + 1):
                    return True
            workingGrid[i][j] = 0
            #print '%d: (%d, %d) %s: no poss found going back' % (iter_count, i, j, possibilities)


    print 'has Solution %s' % moveon(initGrid, 0, 0)

sudokuSolver('initSudoku')
