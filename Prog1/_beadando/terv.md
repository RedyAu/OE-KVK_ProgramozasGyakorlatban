# Terv

## UI

Tábla print:
```
Basic:
###################
# # # # # # # # # #
###################
# # # # # # # # # #
###################
# # # # # # # # # #
###################
# # # # # # # # # #
###################
# # # # # # # # # #
###################
# # # # # # # # # #
###################
# # # # # # # # # #
###################
# # # # # # # # # #
###################
# # # # # # # # # #
###################

With box drawing chars:
╔═╤═╤═╦═╤═╤═╦═╤═╤═╗
║O│ │ ║\   /║     ║
╟─┼─┼─╫ \ / ╫┌───┐╢
║ │X│ ║  X  ║|   |║
╟─┼─┼─╫ / \ ╫└───┘╢
║X│ │X║/   \║     ║
╠═╪═╪═╬═╪═╪═╬═╪═╪═╣
║ │ │ ║ │X│ ║ │ │ ║
╟─┼─┼─╫─┼─┼─╫─┼─┼─╢
║ │ │ ║O│ │ ║ │ │ ║
╟─┼─┼─╫─┼─┼─╫─┼─┼─╢
║ │ │ ║ │ │X║ │ │ ║
╠═╪═╪═╬═╪═╪═╬═╪═╪═╣
║ │ │ ║ │ │ ║ │ │ ║
╟─┼─┼─╫─┼─┼─╫─┼─┼─╢
║ │ │ ║ │ │ ║ │ │ ║
╟─┼─┼─╫─┼─┼─╫─┼─┼─╢
║ │ │ ║ │ │ ║ │ │ ║
╚═╧═╧═╩═╧═╧═╩═╧═╧═╝

Alternate version without inner lines:
╔═══╦═══╦═══╗
║ O ║\ /║┌─┐║
║XOX║ X ║| |║
║OX ║/ \║└─┘║
╠═══╬═══╬═══╣
║   ║ X ║   ║
║   ║O  ║   ║
║   ║  X║   ║
╠═══╬═══╬═══╣
║   ║   ║   ║
║   ║   ║   ║
║   ║   ║   ║
╚═══╩═══╩═══╝
```

## Data

### Storing states:

#### Numbering:
```
#####
#678#
#345#
#012#
#####
```

#### Local boards:
 - `0` = Blank
 - `1` = X
 - `2` = O

#### Global boards:
 - `0` = Local
 - `1` = Big X
 - `2` = Big O
  
### Structure:
Two dimensional array, first dimension global, second dimension local board.\
`game[9][9];`

### Control flow:
#### Variable for current player:
 - `0` = X
 - `1` = 0

#### Variable for selected global board:
`0`-`8` : Selected board
`9` : Unknown (game start or invalid), ask player next time

 - Game begins. Initial conditions: Player is X, Selected board is 9 (unknown)
 - X can move. Unknown global board, so X has to choose a local board.
 - Local board validation, then X chooses field to place tick.
 - Validation, then setting local to equivalent as field.
 - O can move. Validation of selected global board, if right, O places a mark.
 - etc.
