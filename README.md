rubiks_cube
===========

Rubik's cube solver using PDB, developed in C++.

Solution
========

+ We'll be using three (3) different PDBs:
    + A PDB showing the distance from any given configuration of the **eight (8) corners** of the cube to the desired configuration *(goal)* of the corners.
    + A PDB showing the distance from any given configuration of **six (6) (or seven (7) or eight (8)) edges** of the cube to the desired configuration *(goal)* of said edges.
    + A PDB showing the distance from any given configuration of the **remaining six (6) (or five (5) or four (4)) edges** of the cube to the desired configuration *(goal)* of said edges.
+ IDA*

The cube in ASCII art


    front  = white
    back   = yellow
    right  = red
    left   = orange
    top    = blue
    down   = green
           ____________
          /   /   /   /\
         /___/___/___/  \
        /   / T /   /\  /\
      L/___/___/___/  \/  \B
      /   /   /   /\  /\  /\
     /___/___/___/  \/  \/  \
     \   \   \   \  /\R /\  /
      \___\___\___\/  \/  \/
       \   \ F \   \  /\  /
        \___\___\___\/  \/D
         \   \   \   \  /
          \___\___\___\/
