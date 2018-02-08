#!/usr/bin/python

import json
import sys
import subprocess
from requests import get

gameName = sys.argv[1] # Ignore file name
side = sys.argv[2] # Your color

while (True):
    out = get("http://skynet.cs.uaf.edu/?info_game=true", data='{"name":"' + gameName + '"}').text
    gameInfo = json.loads(out)
    if (gameInfo["status"] not in ["red_turn", "black_turn"]): break
    
    if ((gameInfo["status"] == "red_turn" and side == "red") or (gameInfo["status"] == "black_turn" and side == "black")):
        lastBoardString = gameInfo["boards"][-1]
        boardProcess = subprocess.Popen(["./makeMove "+ lastBoardString + " " + side], stdout=subprocess.PIPE, shell=True)
        (moveChosen, err) = boardProcess.communicate()
        print(gameName)
        print(str(moveChosen))
        playProcess = get("http://skynet.cs.uaf.edu/?play_game=true", data='{"name":"' + gameName + '","board":"' + moveChosen + '"}')