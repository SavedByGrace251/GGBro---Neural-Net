from graphics import *

redPiece = []
blackPiece = []
win = GraphWin("Checkers Board", 800, 800)
win.setBackground('grey')

def buildBoard():
	n = 0
	for r in range(1,9):
		for x in range(1,5):
			rect = Rectangle(Point((8-((x*2)-1-(r%2)))*100,(r-1)*100), Point((8-((x*2)-(r%2)))*100,r*100))
			rect.setFill('white')
			rect.draw(win)
			n = r*4-x
			idx = Text(Point((8-((x*2)-1-(r%2)))*100-50,(r-1)*100+50), str(n))
			idx.draw(win)

def setPieces():
	for r in range(1,4):
		for x in range(1,5):
			piece = Circle(Point((8-((x*2)-1-(r%2)))*100-50,(r-1)*100+50), 35)
			piece.setWidth(20)
			piece.setOutline('red')
			piece.draw(win)
	for r in range(6,9):
		for x in range(1,5):
			piece = Circle(Point((8-((x*2)-1-(r%2)))*100-50,(r-1)*100+50), 35)
			piece.setWidth(20)
			piece.setOutline('black')
			piece.draw(win)
	pass
	
def main():
	win.getMouse() # Pause to view result
	win.close()    # Close window when done

buildBoard()
setPieces()
main()