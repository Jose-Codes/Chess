#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
extern char white_name[100];
extern char black_name[100];
extern char source[3];
extern char target[3];
extern int w;
extern int b;
extern int r;
extern int import;
extern int t;
extern int c;
extern int u;
#define MAX_COMMAND_TOKEN_LENGTH 6
#define WHITE 1
#define BLACK -1
typedef enum {
    EMPTY,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
}square;

typedef enum {
    NONE = 0,
    WHITE_SHORT = 1,
    WHITE_LONG = 2,
    BLACK_SHORT = 4,
    BLACK_LONG = 8
}castle;
extern square board[8][8];
extern int turn;
char getCommandWord(char command[], int maxLength);
handleShow();
handleCapture();
handleMove();
capture(char *, char*);
move(char * , char*);
int isLegalCapture(int , int , int , int );
