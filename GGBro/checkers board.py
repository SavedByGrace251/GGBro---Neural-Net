from graphics import *

redPieces = []
blackPieces = []
positions = []
boardSpot = []
boards = []
for i in range(32):
	boardSpot.append([1,1])
boardSize = 800
gridSize = boardSize/8
win = GraphWin("Checkers Board", boardSize, boardSize)
win.setBackground('grey')

def loadBoards():
	file = open("boards.chk")
	boardStr = file.read()
	global boards
	boards = boardStr.split('\n')

def buildBoard():
	n = 0
	for r in range(1,9):
		for x in range(1,5):
			rect = Rectangle(Point((8-((x*2)-1-(r%2)))*gridSize,(r-1)*gridSize), Point((8-((x*2)-(r%2)))*gridSize,r*gridSize))
			rect.setFill('white')
			rect.draw(win)
			n = r*4-x
			label = Text(Point((8-((x*2)-1-(r%2)))*gridSize-(gridSize/2),(r-1)*gridSize+(gridSize/2)), str(n))
			label.setTextColor('blue')
			label.setStyle('bold')
			label.setSize(26)
			positions.append(label)
			boardSpot[n] = [((8-((x*2)-1-(r%2)))*gridSize-(gridSize/2)),(r-1)*gridSize+(gridSize/2)]

def buildBlackPiece(position):
	blackPieces.append(Circle(Point(boardSpot[position][0], boardSpot[position][1]), gridSize/3))
	blackPieces[-1].setFill('black')
	blackPieces[-1].setOutline('black')
	blackPieces[-1].draw(win)

def buildRedPiece(position):
	redPieces.append(Circle(Point(boardSpot[position][0], boardSpot[position][1]), gridSize/3))
	redPieces[-1].setFill('red')
	redPieces[-1].setOutline('red')
	redPieces[-1].draw(win)

def printBoard(board):
	n = 0
	for p in board:
		if p == 'r' or p == 'R':
			buildRedPiece(n)
		elif p == 'b' or p == 'B':
			buildBlackPiece(n)
		n += 1

def iterateBoards():
	global boards, positions, redPieces, blackPieces
	for b in boards:
		printBoard(b)
		for i in positions:
			i.draw(win)
		win.getMouse() # Pause to view result
		for r in redPieces:
			r.undraw()
		for b in blackPieces:
			b.undraw()
		for i in positions:
			i.undraw()
		redPieces = []
		blackPieces = []
	
def main():
	buildBoard()
	loadBoards()
	iterateBoards()
	win.close()    # Close window when done

main()