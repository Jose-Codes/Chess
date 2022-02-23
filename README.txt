# Project 2 - *Assignment 3*
Jose Pujol, 6293900
Date: 02/22/2022

## Command Line Argumnets implemented:

The following **required** functionality is completed:

  - [x] User can input the white player's name using the -w command
  - [x] User can input the black player's name using the -b command
  - [x] User can reverse the board using the -r command
  - [x] A game can be imported using the -i command and passing a string of moves.
        Example: -i, e2e4,e7e5,...
  - [x] The timer can be specified using the -t flag
  - [x] Castling flag can be set to true using -c
  - [x] Underpromtion allowed using -u

The following **optional** features are implemented:

- [x] -u flag promotion of white/black pawn to a queen, knight, rook or bishop once it reaches to the eighth/first rank. 
- [x] -c flag supports castling for the white pieces and black pieces, wither short or long castle. 
- [x] -t flag enforces the time limit, when time is up the player out of time loses and the game stops. 

## Testing the **optional** features:

To make it easier to check for the optional features I will provide a set of imported game to demonstrate each:

###To **castle** with the white pieces, import the following games and make sure to pass the -c command:
    Short castle:
    command: ./chess -i e2e4,e7e5,g1f3,b8c6,g8f6 -c 
    - run the program
    - type show to see the board
    - type mv e1 g1 
    - show the board once again, the king should be in g1 and the rook on f1

    Long castle:
    command: ./chess -i d2d4,d7d5,c2c4,e7e6,b1c3,b8c6,c1g5,a7a6,d1c2,d5xc4 -c
    - run the program
    - type show to see the board
    - type mv e1 c1 
    - show the board once again, the king should be in c1 and the rook on d1

###To **castle** with the black pieces, import the following games and make sure to pass the -c command,
as well as -r to make it easier to see:
    Short castle:
    command: ./chess -i d2d4,g7g6,c2c4,f8g7,g1f3,g8f6,b1c3 -c -r
    - run the program
    - type show to see the board
    - type mv e8 g8
    - show the board once again, the king should be in g8 and the rook on f8

    Long castle:
    command: ./chess -i e2e4,b8c6,d2d4,b7b6,c2c4,c8b7,b1c3,e7e5,g1f3,d8g5,f1e2 -c -r
    - run the program
    - type show to see the board
    - type mv e8 c8 
    - show the board once again, the king should be in c8 and the rook on d8

###To test **Underpromtion** make sure to pass the -u command, the following is an example using the white pieces:
    - command: ./chess -i e2e4,d7d5,e4xd5,e7e5,d5d6,e5e4,d6xc7,e4e3 -u
    - run the program
    - type show to see the board
    - type cp c7 b8
    - type the letter of the piece you want to promote to
    - type show again to see it on the screen

###Testing the timer is very simple, the easiet way is to:
        - command ./chess -t 1
        - wait 60 seconds
        - type a command like mv e2e4
        - you should a message like "White timer: -50 seconds" (the -50 can be any number 0 or below)
                                     "White player is out of time, black wins!" 






