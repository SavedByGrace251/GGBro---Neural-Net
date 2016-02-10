from graphics import *

redPiece = []
blackPiece = []
positions = []
boardSize = 600
gridSize = boardSize/8
win = GraphWin("Checkers Board", boardSize, boardSize)
win.setBackground('grey')

def buildBoard():
	n = 0
	for r in range(1,9):
		for x in range(1,5):
			rect = Rectangle(Point((8-((x*2)-1-(r%2)))*gridSize,(r-1)*gridSize), Point((8-((x*2)-(r%2)))*gridSize,r*gridSize))
			rect.setFill('white')
			rect.draw(win)
			n = r*4-x
			positions.append(Text(Point((8-((x*2)-1-(r%2)))*gridSize-(gridSize/2),(r-1)*gridSize+(gridSize/2)), str(n)))

def setPieces():
	for r in range(1,4):
		for x in range(1,5):
			piece = Circle(Point((8-((x*2)-1-(r%2)))*gridSize-(gridSize/2),(r-1)*gridSize+(gridSize/2)), gridSize/3)
			piece.setFill('red')
			piece.setOutline('red')
			piece.draw(win)
	for r in range(6,9):
		for x in range(1,5):
			piece = Circle(Point((8-((x*2)-1-(r%2)))*gridSize-(gridSize/2),(r-1)*gridSize+(gridSize/2)), gridSize/3)
			piece.setFill('black')
			piece.setOutline('black')
			piece.draw(win)
	pass
	
def main():
	print("Default Checkers Board")
	for idx in positions:
		idx.setTextColor('blue')
		idx.draw(win)
	win.getMouse() # Pause to view result
	win.close()    # Close window when done

buildBoard()
setPieces()
main()