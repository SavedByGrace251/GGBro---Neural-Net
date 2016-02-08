from graphics import *

redPiece = []
blackPiece = []
positions = []
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
			positions.append(Text(Point((8-((x*2)-1-(r%2)))*100-50,(r-1)*100+50), str(n)))

def setPieces():
	for r in range(1,4):
		for x in range(1,5):
			piece = Circle(Point((8-((x*2)-1-(r%2)))*100-50,(r-1)*100+50), 40)
			piece.setFill('red')
			piece.setOutline('red')
			piece.draw(win)
	for r in range(6,9):
		for x in range(1,5):
			piece = Circle(Point((8-((x*2)-1-(r%2)))*100-50,(r-1)*100+50), 40)
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