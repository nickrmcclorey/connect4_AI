# Connect 4 AI

This is a c++ program that uses recursion to look at thousands of possibilities to play connect4. The bot currently looks at all the possibilities in the next six turns. It builds a hashlist of moves that could end the game, marking them as good or bad. It then tries to find traps. Traps are situations where a player can't do anything to prevent defeat. The bot tries to prevent bad traps and produce good traps.

### Future Improvements
I'd like to create a better system for finding traps. The program can search thousands of possibilites efficiently. However, it struggles to properly use this data to find a path that ensures victory. I'd like to implement a tree data structure to store the game ending moves. I'd like to recursivly search this tree for ways to ensure victory.
