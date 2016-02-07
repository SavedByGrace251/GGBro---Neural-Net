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
	n = 0
	for r in range(1,4):
		for x in range(1,5):
			piece = Circle(Point(((x*2)-1-(r%2))*100,(r-1)*100-50), )
			rect.setFill('white')
			rect.draw(win)
	pass

def main():
	# piece = Circle(Point(150,50), 40)
	# piece.setFill('red')
	# piece.draw(win)
	# piece = Circle(Point(50,750), 40)
	# piece.setFill('black')
	# piece.draw(win)
	win.getMouse() # Pause to view result
	win.close()    # Close window when done

buildBoard()
main()