#!/usr/bin/python

import json
import sys
import subprocess

gameName = sys.argv[1] # Ignore file name
side = sys.argv[2] # Your color

while (True):
    process = subprocess.Popen(["curl http://skynet.cs.uaf.edu/?info_game=true -d '{\"name\":\"" + gameName + "\"}'"], stdout=subprocess.PIPE, shell=True)
    (out, err) = process.communicate()
    gameInfo = json.loads(out)
    if (gameInfo["status"] not in ["red_turn", "black_turn"]): break
    
    if ((gameInfo["status"] == "red_turn" and side == "red") or (gameInfo["status"] == "black_turn" and side == "black")):
        lastBoardString = gameInfo["boards"][-1]
        boardProcess = subprocess.Popen(["./makeMove " + lastBoardString + " " + side], stdout=subprocess.PIPE, shell=True)
        (moveChosen, err) = boardProcess.communicate()
        playProcess = subprocess.Popen(["curl http://skynet.cs.uaf.edu/?play_game=true -d '{\"name\":\"" + gameName + "\",\"board\":\"" + moveChosen + "\"}'"], stdout=subprocess.PIPE, shell=True)
        (notUsed, err) = playProcess.communicate()
