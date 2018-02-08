#!python3

import json, sys, subprocess, os, requests

gameName = sys.argv[1] # Ignore file name
side = sys.argv[2] # Your color
gameInfoHeader = '{"name":"'+gameName+'"}'
print(gameInfoHeader)
server = requests.Session()

while (True):
	gameInfo = server.post("http://skynet.cs.uaf.edu/?info_game=true", data=gameInfoHeader).json()
	if (gameInfo["status"] not in ["red_turn", "black_turn"]):
		break
	if ((gameInfo["status"] == "red_turn" and side == "red") or (gameInfo["status"] == "black_turn" and side == "black")):
		lastBoardString = gameInfo["boards"][-1]
		boardPick = subprocess.run(["makeMove.exe", lastBoardString, side], stdout=subprocess.PIPE, universal_newlines=True)
		if (boardPick.returncode > 0):
			moveHeader = '{"name":"'+gameName+'","board":"'+boardPick.stdout+'"}'
			print(moveHeader)
			server.post("http://skynet.cs.uaf.edu/?play_game=true", data=moveHeader)
			moveHeader = '{"name":"'+gameName+'","board":"rrrrrrrrrrrr________bbbbbbbbbbbb"}'
			server.post("http://skynet.cs.uaf.edu/?play_game=true", data=moveHeader)
		else:
			moveHeader = '{"name":"'+gameName+'","board":"'+boardPick.stdout+'"}'
			server.post("http://skynet.cs.uaf.edu/?play_game=true", data=moveHeader)
			print(moveHeader)

