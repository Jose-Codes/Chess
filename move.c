#include "chess.h"
static int isLegalMove(int srcI, int srcJ, int trgI, int trgJ) {
    int i;
    char promoted_option[3];
    char promotion_choice, lastCharacter;
    int piece = board[srcI][srcJ];//moved piece...
    int check_piece;
    int pieceType = abs(piece);
    int pieceColor = piece > 0 ? WHITE : BLACK;
    switch (pieceType) {
    case ROOK:
        if (srcI != trgI && srcJ != trgJ)
            return 0;
        if (srcI == trgI) {//move along a rank
            for (i = 1; i < abs(srcJ - trgJ); i++)//check middle squares
                if (srcJ<trgJ && board[srcI][srcJ + i] != EMPTY
                    || srcJ > trgJ && board[srcI][srcJ - i] != EMPTY)
                    return 0;
        }
        else//move along a file
            for (i = 1; i < abs(srcI - trgI); i++)//check middle squares
                if (srcI<trgI && board[srcI + i][srcJ] != EMPTY
                    || srcI > trgI && board[srcI - i][srcJ] != EMPTY)
                    return 0;
        break;
    case PAWN:
        if (srcJ != trgJ)
            return 0;

        if (pieceColor == BLACK) {
            if (srcI == 1)//starting position
                return trgI == 2 || trgI == 3;
            else if(trgI == 7 && turn < 0){ // handle promotion
                printf("\nEnter the letter of the piece you would like to promote to:\nq: Queen");
                printf("\nr: Rook\nk: Knight\nb: Bishop\n");
                lastCharacter = getCommandWord(promoted_option, 3);
                // promotion_choice = promoted_option[0];
                //printf("\nThe choice made was: %c\n", promoted_option);
                int valid = 0;
                while(!valid){
                switch (promoted_option[0])
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
            else
                return trgI == srcI + 1;
        }
        else {
            if (srcI == 6)//starting position
                return trgI == 5 || trgI == 4;
            else if(trgI == 0 && turn > 0){ // handle promotion
                printf("\nEnter the letter of the piece you would like to promote to:\nq: Queen");
                printf("\nr: Rook\nk: Knight\nb: Bishop\n");
                lastCharacter = getCommandWord(promoted_option, 3);
                // promotion_choice = promoted_option[0];
                //printf("\nThe choice made was: %c\n", promoted_option);
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
            else
                return trgI == srcI - 1;
        }
        break;
    case KNIGHT://L shape
        return abs((srcI - trgI) * (srcJ - trgJ)) == 2;
    case BISHOP:
        if (abs(srcI - trgI) != abs(srcJ - trgJ))
            return 0;//not a diagonal move... return false...
        if (srcI < trgI) {//moving down the board
            for (i = 1; i < abs(srcI - trgI); i++)//check middle squares
                if (srcJ < trgJ && board[srcI + i][srcJ + i] != EMPTY
                    || srcJ > trgJ && board[srcI + i][srcJ - i] != EMPTY)
                    return 0;
        }
        else//moving up the board
            for (i = 1; i < abs(srcI - trgI);i++)//check middle squares
                if (srcJ < trgJ && board[srcI - i][srcJ + i] != EMPTY
                    || srcJ > trgJ && board[srcI - i][srcJ - i] != EMPTY)
                    return 0;
        break;
    case QUEEN:
        if (srcI == trgI || srcJ == trgJ) {//move like a rook
            if (srcI == trgI) {//move along a rank
                for (i = 1; i < abs(srcJ - trgJ); i++)//check middle squares
                    if (srcJ<trgJ && board[srcI][srcJ + i] != EMPTY
                        || srcJ > trgJ && board[srcI][srcJ - i] != EMPTY)
                        return 0;
            }
            else//move along a file
                for (i = 1; i < abs(srcI - trgI); i++)//check middle squares
                    if (srcI<trgI && board[srcI + i][srcJ] != EMPTY
                        || srcI > trgI && board[srcI - i][srcJ] != EMPTY)
                        return 0;
        }
        else if (abs(srcI - trgI) == abs(srcJ - trgJ)) {//move like a bishop
            if (srcI < trgI) {//moving down the board
                for (i = 1; i < abs(srcI - trgI); i++)//check middle squares
                    if (srcJ < trgJ && board[srcI + i][srcJ + i] != EMPTY
                        || srcJ > trgJ && board[srcI + i][srcJ - i] != EMPTY)
                        return 0;
            }
            else//moving up the board
                for (i = 1; i < abs(srcI - trgI);i++)//check middle squares
                    if (srcJ < trgJ && board[srcI - i][srcJ + i] != EMPTY
                        || srcJ > trgJ && board[srcI - i][srcJ - i] != EMPTY)
                        return 0;
        }
        else
            return 0;
        break;
    case KING:
        // Steps for castling
        if(c){ // check that castling is allowed
        
            if(pieceColor == WHITE){
                //check that the king is in his original position
                if(trgI == 7 && trgJ == 6){ // check that the king wants to move two sqaures to the right, King Side castle
                    if(board[7][4] != WHITE*KING){
                        printf("\nCannot castle, king is not in starting square\n");
                        return 0;
                    }
                    else if(board[7][5] != EMPTY || board[7][6] != EMPTY){
                        printf("\nCannot castle, the adjacent squares are not empty\n");
                        return 0;
                    }
                    else if (board[7][7] != ROOK *WHITE){
                        printf("\nCannot castle, rook is not in starting square\n");
                        return 0;
                    }
                    else{ // iterate through the entire board to check each piece
                        for (int i = 0; i <= 7; i++){ // Squares beign checked are board[7][5] and board[7][6] 
                            for(int j = 0; j <= 7; j++){
                                check_piece = board[i][j];
                                    if(check_piece < 0){
                                        if(isLegalMove(i,j,7,5) || isLegalMove(i,j,7,6)){
                                            printf("\nCannot castle, because adjacent squares are in check\n");
                                            return 0;
                                        }
                                        if(isLegalCapture(i,j,7,4)){
                                            printf("\nCannot castle, because the king is in check\n");
                                            return 0;
                                        }
                                    }
                                }
                            }
                            // Done with error checking
                            board[7][7] = EMPTY;
                            board[7][5] = ROOK *WHITE;
                            return 1;
                        }
                } else if (trgI == 7 && trgJ == 2){ // queen side castle
                    if(board[7][4] != 6){
                        printf("\nCannot castle, king is not in starting square\n");
                        return 0;
                    }
                    else if(board[7][3] != EMPTY || board[7][2] != EMPTY || board[7][1] != EMPTY){
                        printf("\nCannot castle, the adjacent squares are not empty\n");
                        return 0;
                    }
                    else if (board[7][0] != ROOK *WHITE){
                        printf("\nCannot castle, rook is not in starting square\n");
                        return 0;
                    }
                    else{ // iterate through the entire board to check each piece
                        for (int i = 0; i <= 7; i++){ // Squares being checked are board[7][3], board[7][2], and board [7][1]
                            for(int j = 0; j <= 7; j++){
                                check_piece = board[i][j];
                                if(check_piece < 0){
                                    if(isLegalMove(i,j,7,3) || isLegalMove(i,j,7,2) || isLegalMove(i,j,7,1)){
                                        printf("\nCannot castle, because adjacent squares are in check\n");
                                        return 0;
                                    }
                                    if(isLegalCapture(i,j,7,4)){
                                        printf("\nCannot castle, because the king is in check\n");
                                        return 0;
                                    }
                                }
                              }
                            }
                            // Done with error checking
                            board[7][0] = EMPTY;
                            board[7][3] = ROOK *WHITE;
                            return 1;
                        }
                }
            }
            else{ // castling with the black pieces
                //check that the king is in his original position
                if(trgI == 0 && trgJ == 6){ // check that the king wants to move two sqaures to the right, King Side castle
                    if(board[0][4] != BLACK*KING){
                        printf("\nCannot castle, king is not in starting square\n");
                        return 0;
                    }
                    else if(board[0][5] != EMPTY || board[0][6] != EMPTY){
                        printf("\nCannot castle, the adjacent squares are not empty\n");
                        return 0;
                    }
                    else if (board[0][0] != ROOK *BLACK){
                        printf("\nCannot castle, rook is not in starting square\n");
                        return 0;
                    }
                    else{ // iterate through the entire board to check each piece
                        for (int i = 0; i <= 7; i++){ // Squares beign checked are board[7][5] and board[7][6] 
                            for(int j = 0; j <= 7; j++){
                                check_piece = board[i][j];
                                    if(check_piece > 0){
                                        if(isLegalMove(i,j,0,5) || isLegalMove(i,j,0,6)){
                                            printf("\nCannot castle, because adjacent squares are in check\n");
                                            return 0;
                                        }
                                        if(isLegalCapture(i,j,0,4)){
                                            printf("\nCannot castle, because the king is in check\n");
                                            return 0;
                                        }
                                    }
                                }
                            }
                            // Done with error checking
                            board[0][7] = EMPTY;
                            board[0][5] = ROOK *BLACK;
                            return 1;
                        }
                } else if (trgI == 0 && trgJ == 2){ // queen side castle
                    if(board[0][4] != BLACK*KING){
                        printf("\nCannot castle, king is not in starting square\n");
                        return 0;
                    }
                    else if(board[0][3] != EMPTY || board[0][2] != EMPTY || board[0][1] != EMPTY){
                        printf("\nCannot castle, the adjacent squares are not empty\n");
                        return 0;
                    }
                    else if (board[0][0] != ROOK*BLACK){
                        printf("board [0][0] = %d\nCannot castle, rook is not in starting square\n",board[0][0]);
                        return 0;
                    }
                    else{ // iterate through the entire board to check each piece
                        for (int i = 0; i <= 7; i++){ // Squares being checked are board[7][3], board[7][2], and board [7][1]
                            for(int j = 0; j <= 7; j++){
                                check_piece = board[i][j];
                                if(check_piece > 0){
                                    if(isLegalMove(i,j,0,3) || isLegalMove(i,j,0,2) || isLegalMove(i,j,0,1)){
                                        printf("\nCannot castle, because adjacent squares are in check\n");
                                        return 0;
                                    }
                                    if(isLegalCapture(i,j,0,4)){
                                        printf("\nCannot castle, because the king is in check\n");
                                        return 0;
                                    }
                                }
                              }
                            }
                            // Done with error checking
                            board[0][0] = EMPTY;
                            board[0][3] = ROOK*BLACK;
                            return 1;
                        }
                }
            }
        }
        return abs(srcI - trgI) + abs(srcJ - trgJ) == 1 
            || abs(srcI - trgI) * abs(srcJ - trgJ) == 1;
    }
    return 1;//legal move
}


    move(char * source, char* target){
        int sourceFile, sourceRank, targetFile, targetRank, sourceI, sourceJ, targetI, targetJ;
        sourceFile = source[0];//source = "a5", sourceFile = 'a'
        targetFile = target[0];
        sourceRank = source[1] - '0';//source = "a5", sourceRank = 5
        targetRank = target[1] - '0';
        //board[sourceI][sourceJ]: source square...
        //board[targetI][targetJ]: target square...
        sourceI = 8 - sourceRank;
        sourceJ = sourceFile - 'a';
        targetI = 8 - targetRank;
        targetJ = targetFile - 'a';
        if (sourceI < 0 || sourceJ < 0 || targetI < 0 || targetJ < 0
            || sourceI > 7 || sourceJ > 7 || targetI > 7 || targetJ > 7) {
            printf("Invalid mv arguments\n");
            return;
        }
        //checking the turn first
        if ((int)(board[sourceI][sourceJ] * turn) < 0) {
            printf("Turn violation, it's %s to move\n", turn == WHITE ? "white" : "black");
            return;
        }
        if (board[sourceI][sourceJ] == EMPTY || board[targetI][targetJ] != EMPTY) {
            printf("Invalid move: either source square is empty or target square is not empty\n");
            return;
        }
        if (!isLegalMove(sourceI, sourceJ, targetI, targetJ)) {
            printf("Illegal chess move\n");
            return;
        }
        //end of error checking....

        board[targetI][targetJ] = board[sourceI][sourceJ];
        board[sourceI][sourceJ] = EMPTY;
        turn *= -1;//WHITE --> BLACK and BLACK --> WHITE
    }

handleMove() {
    char source[MAX_COMMAND_TOKEN_LENGTH];//placeholder for argument 1 (initial square)
    char target[MAX_COMMAND_TOKEN_LENGTH];//placeholder for argument 2 (final square)
    char lastCharacter;
    //source SQUARE: board[sourceI][sourceJ]
    //target SQUARE: board[targetI][targetJ]
    lastCharacter = getCommandWord(source, MAX_COMMAND_TOKEN_LENGTH);
    if (lastCharacter == '\n') {
        printf("Too few arguments for mv command! It must be in the form of mv ai bj.\n");
        return;
    }
    lastCharacter = getCommandWord(target, MAX_COMMAND_TOKEN_LENGTH);
    if (lastCharacter != '\n') {
        printf("Too many arguments for mv command! It must be in the form of mv ai bj.\n");
        while (getCommandWord(target, MAX_COMMAND_TOKEN_LENGTH) != '\n');//skip the rest of illegal command..
        return;
    }
    move(source, target);
}

