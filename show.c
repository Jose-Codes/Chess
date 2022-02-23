#include"chess.h"
handleShow() {
    int i, j;
    if(!r){
    printf("\t%s\n", black_name);
    printf("board\t"); // \t before board
    for (i = 0; i < 8; i++)//file labels...
        printf("%c%c", 'a' + i, i == 7 ? '\n' : '\t');

    for (i = 0; i < 8; i++) {//table itself
        for (j = 0; j < 9; j++){
            printf("%d%c", j == 0 ? 8 - i : board[i][j - 1], j == 8 ? '\n' : '\t'); // \t before %d
		    }
	    }
        printf("\t%s\n", white_name);
    }
    else{
        printf("\t%s\n", white_name);
        printf("board\t"); // \t before board
    for (i = 7; i >= 0; i--)//file labels...
        printf("%c%c", 'a' + i, i == 0 ? '\n' : '\t');

    for (i = 8; i > 0; i--) {//table itself
        for (j = 9; j > 0; j--){
            printf("%d%c", j == 9 ? j-i : board[i - 1][j - 1], j == 1 ? '\n' : '\t'); // \t before %d
		    }
	    }
        printf("\t%s\n", black_name);
    }
}