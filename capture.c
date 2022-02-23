#include "chess.h"
 int isLegalCapture(int srcI, int srcJ, int trgI, int trgJ) {
    int i;
    char promoted_option[3];
    char promotion_choice, lastCharacter;
    int piece = board[srcI][srcJ];//capturing piece...
    int pieceType = abs(piece);
    int pieceColor = piece > 0 ? WHITE : BLACK;
    switch (pieceType) {
    case ROOK:
        if (srcI != trgI && srcJ != trgJ)
            return 0;
        if (srcI == trgI) {//capture along a rank
            for (i = 1; i < abs(srcJ - trgJ); i++)//check middle squares
                if (srcJ<trgJ && board[srcI][srcJ + i] != EMPTY
                    || srcJ > trgJ && board[srcI][srcJ - i] != EMPTY)
                    return 0;
        }
        else//capture along a file
            for (i = 1; i < abs(srcI - trgI); i++)//check middle squares
                if (srcI<trgI && board[srcI + i][srcJ] != EMPTY
                    || srcI > trgI && board[srcI - i][srcJ] != EMPTY)
                    return 0;
        break;
    case PAWN:
            if(trgI == 7 && pieceColor == BLACK && turn < 0){ // handle promotion
                printf("\nEnter the letter of the piece you would like to promote to:\nq: Queen");
                printf("\nr: Rook\nk: Knight\nb: Bishop\n");
                lastCharacter = getCommandWord(promoted_option, 3);
                promotion_choice = promoted_option[0];
                int valid = 0;
                while(!valid){
                switch (promotion_choice)
                {
                case 'q':
                    board[srcI][srcJ] = QUEEN * BLACK;
                    valid = 1;
                    break;
                case 'r':
                    board[srcI][srcJ] = ROOK * BLACK;
                    valid = 1;
                    break;
                case 'k':
                    board[srcI][srcJ] = KNIGHT * BLACK;
                    valid = 1;
                    break;
                case 'b':
                    board[srcI][srcJ] = BISHOP * BLACK;
                    valid = 1;
                    break;
                
                default:
                    printf("Invalid choice, please choose again\n");
                    lastCharacter = getCommandWord(promoted_option, 3);
                    break;
                 }
                }
            }
            else if(trgI == 0 && pieceColor == WHITE && turn > 0){ // handle promotion
                printf("\nEnter the letter of the piece you would like to promote to:\nq: Queen");
                printf("\nr: Rook\nk: Knight\nb: Bishop\n");
                lastCharacter = getCommandWord(promoted_option, 3);
                // promotion_choice = promoted_option[0];
                int valid = 0;
                while(!valid){
                switch (promoted_option[0])
                {
                case 'q':
                    board[srcI][srcJ] = QUEEN * WHITE;
                    valid = 1;
                    break;
                case 'r':
                    board[srcI][srcJ] = ROOK * WHITE;
                    valid = 1;
                    break;
                case 'k':
                    board[srcI][srcJ] = KNIGHT * WHITE;
                    valid = 1;
                    break;
                case 'b':
                    board[srcI][srcJ] = BISHOP * WHITE;
                    valid = 1;
                    break;
                
                default:
                    printf("Invalid choice, please choose again\n");
                    lastCharacter = getCommandWord(promoted_option, 3);
                    break;
                 }
                }
            }
        return abs(srcJ - trgJ) * (srcI - trgI) == pieceColor;
    case KNIGHT://L shape
        return abs((srcI - trgI) * (srcJ - trgJ)) == 2;
    case BISHOP:
        if (abs(srcI - trgI) != abs(srcJ - trgJ))
            return 0;//not a diagonal capture... return false...
        if (srcI < trgI) {//capturing down the board
            for (i = 1; i < abs(srcI - trgI); i++)//check middle squares
                if (srcJ < trgJ && board[srcI + i][srcJ + i] != EMPTY
                    || srcJ > trgJ && board[srcI + i][srcJ - i] != EMPTY)
                    return 0;
        }
        else//capturing up the board
            for (i = 1; i < abs(srcI - trgI);i++)//check middle squares
                if (srcJ < trgJ && board[srcI - i][srcJ + i] != EMPTY
                    || srcJ > trgJ && board[srcI - i][srcJ - i] != EMPTY)
                    return 0;
        break;
    case QUEEN:
        if (srcI == trgI || srcJ == trgJ) {//capture like a rook
            if (srcI == trgI) {//capture along a rank
                for (i = 1; i < abs(srcJ - trgJ); i++)//check middle squares
                    if (srcJ<trgJ && board[srcI][srcJ + i] != EMPTY
                        || srcJ > trgJ && board[srcI][srcJ - i] != EMPTY)
                        return 0;
            }
            else//capture along a file
                for (i = 1; i < abs(srcI - trgI); i++)//check middle squares
                    if (srcI<trgI && board[srcI + i][srcJ] != EMPTY
                        || srcI > trgI && board[srcI - i][srcJ] != EMPTY)
                        return 0;
        }
        else if (abs(srcI - trgI) == abs(srcJ - trgJ)) {//capture like a bishop
            if (srcI < trgI) {//capturing down the board
                for (i = 1; i < abs(srcI - trgI); i++)//check middle squares
                    if (srcJ < trgJ && board[srcI + i][srcJ + i] != EMPTY
                        || srcJ > trgJ && board[srcI + i][srcJ - i] != EMPTY)
                        return 0;
            }
            else//capturing up the board
                for (i = 1; i < abs(srcI - trgI);i++)//check middle squares
                    if (srcJ < trgJ && board[srcI - i][srcJ + i] != EMPTY
                        || srcJ > trgJ && board[srcI - i][srcJ - i] != EMPTY)
                        return 0;
        }
        else
            return 0;
        break;
    case KING:
        return abs(srcI - trgI) + abs(srcJ - trgJ) == 1
            || abs(srcI - trgI) * abs(srcJ - trgJ) == 1;
    }
    return 1;//legal capture
}

capture(char * source, char*target){
    int sourceFile, sourceRank, targetFile, targetRank, sourceI, sourceJ, targetI, targetJ;
    sourceFile = source[0];
    targetFile = target[0];
    sourceRank = source[1] - '0';
    targetRank = target[1] - '0';
    sourceI = 8 - sourceRank;
    sourceJ = sourceFile - 'a';
    targetI = 8 - targetRank;
    targetJ = targetFile - 'a';
    if (sourceI < 0 || sourceJ < 0 || targetI < 0 || targetJ < 0
        || sourceI > 7 || sourceJ > 7 || targetI > 7 || targetJ > 7) {
        printf("invalid cp arguments\n");
        return;
    }
    //checking the turn first
    if ((int)(board[sourceI][sourceJ] * turn) < 0) {
        printf("Turn violation, it's %s to move\n", turn == WHITE ? "WHITE" : "BLACK");
        return;
    }
    if ((int)board[sourceI][sourceJ] * (int)board[targetI][targetJ] > 0) {
        printf("Violation, %s cannot capture its own piece.\n", turn == WHITE ? "WHITE" : "BLACK",board[sourceI][sourceJ], board[targetI][targetJ]);
        return;
    }
    if (board[sourceI][sourceJ] == EMPTY || board[targetI][targetJ] == EMPTY) {
        printf("Invalid capture: either source square is empty or target square is empty\n");
        return;
    }
    if (!isLegalCapture(sourceI, sourceJ, targetI, targetJ)) {
        printf("Illegal chess capture\n");
        return;
    }
    //end of error checking....
    board[targetI][targetJ] = board[sourceI][sourceJ];
    board[sourceI][sourceJ] = 0;
    turn *= -1;
}

handleCapture() {
    char source[MAX_COMMAND_TOKEN_LENGTH];
    char target[MAX_COMMAND_TOKEN_LENGTH];
    char lastCharacter;
    lastCharacter = getCommandWord(source, MAX_COMMAND_TOKEN_LENGTH);
    if (lastCharacter == '\n') {
        printf("Too few arguments for cp command! It must be in the form of cp ai bj.\n");
        return;
    }
    lastCharacter = getCommandWord(target, MAX_COMMAND_TOKEN_LENGTH);
    if (lastCharacter != '\n') {
        printf("Too many arguments for cp command! It must be in the form of cp ai bj.\n");
        while (getCommandWord(target, MAX_COMMAND_TOKEN_LENGTH) != '\n');
        return;
    }
    capture(source,target);
}