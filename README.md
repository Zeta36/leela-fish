# LeelaFish
UCI chess playing engine derived from Stockfish and LeelaChess Zero: https://github.com/LeelaChessZero, https://github.com/official-stockfish/Stockfish

# Introduction
This is a chess engine based in the Stockfish tree search but where we use the LCZero value head as evaluation function. So in this project we are just using the Stockfish code but replacing the human developed evaluation function for the neural network value head of the LeelaChess Zero project.

This is a kind of experiment in which we try to figure out if the results are good even without the use of the MCTS LCZero does.

# Results
Results are very promising and in a 1:1 ratio (when the number of nodes used by the original Stockfish or LCZero are forced to be equal to the number of nodes used by LeelaFish) our development is able to beat both SF and LCZero. We used for these tests the LCZero network tesnet 10510.

One thing is clear: the value head of the network is as good as the original manually programmed evaluation function of SF.

# Future work
- It would be great to test depthly the performance of LeelaFish and the optimal ratio in which it's able to perform as good or better than SF and/or LCZero.  
- It would be a good idea to use instead of LCZero the more recent lc0 source code of the LeelaZero project.

# Licence
LeelaFish Copyright (C) 2018  Samuel Graván and contributors. 
Based on:
Leela Chess Copyright (C) 2017 benediamond
Leela Zero Copyright (C) 2017-2018  Gian-Carlo Pascutto and contributors
Stockfish Copyright (C) 2017  Tord Romstad, Marco Costalba, Joona Kiiski, Gary Linscott

LeelaFish is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Leela Chess is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Leela Chess. If not, see http://www.gnu.org/licenses/.
