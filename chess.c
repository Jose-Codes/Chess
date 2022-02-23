/**
 * @file chess.c
 * Jose Pujol, PantherID: 6293900
 * @brief 
 * @version 0.1
 * @date 2022-02-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "chess.h"
square board[8][8];
int turn; 
char white_name[100], black_name[100];
int w = 0, b = 0, r = 0, import = 0, t = 0, c = 0, u = 0;
char source[3], target[3];

static void resetBoard() {
    turn = WHITE;//WHITE moves first
    int i, j;
    for (i = 2; i < 6;i++)
        for (j = 0;j < 8;j++)
            board[i][j] = EMPTY;
    for (j = 0;j < 8;j++) {
        board[1][j] = BLACK * PAWN;
        board[6][j] = WHITE * PAWN;
    }
    board[0][0] = board[0][7] = BLACK * ROOK;
    board[7][0] = board[7][7] = WHITE * ROOK;
    board[0][1] = board[0][6] = BLACK * KNIGHT;
    board[7][1] = board[7][6] = WHITE * KNIGHT;
    board[0][2] = board[0][5] = BLACK * BISHOP;
    board[7][2] = board[7][5] = WHITE * BISHOP;
    board[0][3] = BLACK * QUEEN;
    board[7][3] = WHITE * QUEEN;
    board[0][4] = BLACK * KING;
    board[7][4] = WHITE * KING;
}
char getCommandWord(char command[], int maxLength) {
    char lastCharacter;//either space or new line
    int i;
    for (i = 0; (lastCharacter = getchar()) == ' '; i++);//skip leading white spaces
    if (lastCharacter == '\n') {
        command[0] = '\0';
        return lastCharacter;
    }
    command[0] = lastCharacter;
    for (i = 1; i < maxLength - 1 && (command[i] = getchar()) != ' ' && command[i] != '\n'; i++);
    lastCharacter = command[i];
    command[i] = '\0';
    return lastCharacter;
}
main(int argc, char** argv) {
    /*
    * You can access all the command-line arguments here
    * argv[1], argv[2], ...
    * Example of import option: -i d2d4,d7d5,e2e4,d5xe4,Ng1h3,Ke8d7,Qd1d3
    * which is equivalent to a new game started this way:
    * mv d2 d4
    * mv d7 d5
    * mv e2 e4
    * cp d5 e4
    * mv g1 h3
    * mv e8 d7
    * mv d1 d3
    */
       resetBoard();
    
	int i = -1, j, index = 0, timer;
	for(i = 1; i < argc;i++){//while(argv[++i])
		if(argv[i][0] == '-'){
			j = 1;
			while(argv[i][j]){
                switch (argv[i][j])
                {
                case 'w':
                    w = 1;
                    strcpy(white_name, argv[i+1]);
                    break;
                case 'b':
                    b = 1;
		            strcpy(black_name, argv[i+1]);
                    break;
                case 'r':
                    r = 1;
                    break;
                case 'i':
                    import = 1;
                    char game[100];
                    strcpy(game, argv[i+1]);
                    char* token; 
                    int first_time = 1;
                    while(1){
                        if(first_time){
                            first_time = 0;
                            token = strtok(game, ",");
                        }else
                            token = strtok(NULL, ",");
                        if(!token)
                            break;
                        if(isupper(*token))
                            token++;
                        if(token[2] == 'x')//deal with capture
                        {
                            strncpy(source, token, 2); 
                            strncpy(target, token + 3, 2);
                            capture(source,target);
                        }
                        else {
                            strncpy(source, token, 2); 
                            strncpy(target, token + 2, 2);
                            move(source, target);
                        }
                    }
                    break;
                case 't':
                    t = 1;
                    timer = (atoi(argv[i+1])) * 60;
                    break;
                case 'c':
                    c = 1;
                    break;
                case 'u':
                    u = 1;
                    break;
                default:
                    fprintf(stderr, "The flag -%c is not supported. Exiting...", argv[i][j]);
		    exit(1);
                    break;
                }
		j++;
            	}
			
	    }
    }
    //import implementation    

    char command[MAX_COMMAND_TOKEN_LENGTH];
    char lastCharacter;
    time_t white_time_start, white_time_end, black_time_start, black_time_end;
    int white_time = timer, black_time = timer;
    printf("Start the game using a mv command! Valid commands are quit, show, mv and cp.\n");
    while (1) {//infinite while loop...
        printf(">>");
        if(turn > 0)
            white_time_start = time(NULL);
        else
            black_time_start = time(NULL);

        lastCharacter = getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH);
    if(t){
        // timer enforced
        if(turn > 0 && (!strcmp(command, "mv") || !strcmp(command, "cp")) ){
            white_time_end = time(NULL);
            white_time -= (white_time_end - white_time_start);
            printf("\nWhite timer: %d seconds\n", white_time);
        }
        else if ( turn < 0 && (!strcmp(command, "mv") || !strcmp(command, "cp")) ) {
            black_time_end = time(NULL);
            black_time -= (black_time_end - black_time_start);
            printf("\nBlack timer: %d seconds\n", black_time);
        }

        if(white_time <= 0){
            printf("\nWhite player is out of time, black wins!");
            exit(1);
        }
        else if(black_time <= 0){
            printf("\nBlack player has ran out of time, white wins!");
            exit(1);
        }
    }

        if (strcmp(command, "quit") == 0)//if command === "quit"
            break;
        else if (!strcmp(command, "mv"))//if command == "mv"
        {
            if (lastCharacter == '\n')//mv\n
                printf("Too few arguments for mv command! It must be in the form of mv ai bj.\n");
            else
                handleMove();
        }
        else if (!strcmp(command, "cp"))//if command == "cp"
        {
            if (lastCharacter == '\n')//cp\n
                printf("Too few arguments for cp command! It must be in the form of cp ai bj.\n");
            else
                handleCapture();
        }
        else if (!strcmp(command, "show"))//if command == "show"
        {
            if (lastCharacter != '\n') {//show x\n
                printf("Too many arguments for show command! It must be in the form of show.\n");
                while (getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH) != '\n');//skip the ramainder of the invalid show command...	
            }
            else
                    handleShow();
        }
        else {
            printf("invalid command! Your command must start either with quit, show, mv or cp.\n");
            while (lastCharacter != '\n')//skip the remainder of my invalid command...
                lastCharacter = getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH);
        }
    }
}
