
#include<iostream>
using namespace std;

///1.Game board using 1d array
char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

//2.display the board
void drawBoard(){
    cout<<"\n";
    cout<<" "<<board[0]<<" | "<<board[1]<<" | "<<board[2]<<"\n";
    cout<<"---|---|---\n";
    cout<<" "<<board[3]<<" | "<<board[4]<<" | "<<board[5]<<"\n";
    cout<<"---|---|---\n";
    cout<<" "<<board[6]<<" | "<<board[7]<<" | "<<board[8]<<"\n";
    cout<<"\n";
}

//3.player input
//4.update the board

//5.switch player
char currentPlayer = 'X';
void switchPlayer(){
    currentPlayer = (currentPlayer == 'X') ? 'O':'X';
}

//6.check win
bool isWinner(){
    int wins[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };

    for(auto &line : wins){
        if(board[line[0]] == currentPlayer && board[line[1]] == currentPlayer && board[line[2]] == currentPlayer){
            return true;
        }
    }
    return false;
}

//7.check draw
bool isDraw(){
    for(int i=0; i<9; i++){
        if(board[i] != 'X' && board[i] != 'O'){
            return false;
        }
    }
    return true;
}


////////////////////////////////////////////////////
void playGame(){
    int move;

    while(true){
        drawBoard();
        cout<<"Player "<<currentPlayer<<", Enter your move (1-9): ";
        cin>>move;

        //valid
        if(cin.fail() || move<1 || move>9 || board[move-1] == 'X' || board[move-1] == 'O'){
            cin.clear();            //clear error flag
            cin.ignore(1000, '\n'); //invalid input
            cout<<"Invalid move. Try again. \n";
            continue;
        }

        board[move-1] = currentPlayer;
        if(isWinner()){
            drawBoard();
            cout<<"Player "<<currentPlayer <<" wins!\n";
            break;
        }

        if(isDraw()){
            drawBoard();
            cout<<"It's a draw!\n";
            break;
        }

        switchPlayer();
    }
}



int main(){
    char playAgain;

    do{
        //reset board
        for(int i=0; i<9; i++){
            board[i] ='1' + i;
        }
        currentPlayer = 'X';

        playGame();

        cout<<"Play again? (y/n): ";
        cin>>playAgain;
    }while(playAgain == 'y' || playAgain == 'Y');

    cout<<"Thanks for playing!\n";
    return 0;
}


////using AI->O
///AI uses Minimax to simulate all possible outcomes and choose the best one
#include<limits>

