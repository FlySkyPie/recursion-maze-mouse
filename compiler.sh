#!/bin/bash
#PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH
echo "Starting compile your soure code...... \n"
g++ -c main.cpp -o main.o -Wall
g++ main.o -o Maze_Rat.out -Wall
echo "Compile finish \n"
read -n1 -r -p "Press any key to continue..." key
exit 0
