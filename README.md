# Dots-and-Boxes
Dots and Boxes game written in C++

To play, just compile and run `main.cpp` with `-O2` or `-O3` flag.

# How to play
Wikipedia explains it best: The game starts with an empty grid of dots. Usually two players take turns adding a single horizontal or vertical line between two unjoined adjacent dots. A player who completes the fourth side of a 1×1 box earns one point and takes another turn. A point is typically recorded by placing a mark that identifies the player in the box, such as an initial. The game ends when no more lines can be placed. The winner is the player with the most points

# Done
- Board Class
- Interface for player move
- Scoring system
- Minimax with alpha-beta pruning
- Primitive chain analysis

# Todo

- Make chain analysis code cleaner and tighter.
- Nimstring analysis maybe?
- Add a board GUI for easy input
