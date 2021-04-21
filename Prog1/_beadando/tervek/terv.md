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

─ │ 
┌┐
└┘
├┤┬┴
┼

╔═══╗
║   ║
║   ║
║   ║
╚═══╝
╔═══╗\n║   ║\n║   ║\n║   ║\n╚═══╝
    ╔═══╗
    ║   ║
    ║   ║
    ║   ║
    ╚═══╝
    ╔═══╗\n    ║   ║\n    ║   ║\n    ║   ║\n    ╚═══╝
        ╔═══╗
        ║   ║
        ║   ║
        ║   ║
        ╚═══╝
        ╔═══╗\n        ║   ║\n        ║   ║\n        ║   ║\n        ╚═══╝

  /-\
  | |
  \-/

  ┌─┐
  │ │
  └─┘

  012
  345
  678

  \ /
   X 
  / \


┌───┬───┬───┐
│   │   │   │
│   │   │   │
│   │   │   │
├───┼───┼───┤
│   │┌─┐│\ /│
│   ││ ││ X │
│   │└─┘│/ \│
├───┼───┼───┤
│   │   │   │
│   │   │   │
│   │   │   │
└───┴───┴───┘

┌───┬───┬───┐\n│   │   │   │\n│   │   │   │\n│   │   │   │\n├───┼───┼───┤\n│   │   │   │\n│   │   │   │\n│   │   │   │\n├───┼───┼───┤\n│   │   │   │\n│   │   │   │\n│   │   │   │\n└───┴───┴───┘

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

#### Figuring out which column or row we are in:
```
678 : /3 = 2
345 : /3 = 1
012 : /3 = 0
  |_: %3 = 2
 |__: %3 = 1
|___: %3 = 0
```

#### Local boards:
 - `0` = Blank
 - `1` = X
 - `2` = O

#### Global boards:
 - `0` = Local
 - `1` = Big X
 - `2` = Big O
 - `3` = Draw
  
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
 - Validation, then setting local to equivalent as field, then validate.
 - O can move. If invalid board, get board. Then, O places a mark.
 - etc.
