#include<iostream>
using namespace std;
const int maxn = 3;
bool isRunning = true;
struct start{
	int x{-1};
	int y{-1};
};
istream& operator>>(istream& is, start& st){
	is >> st.x >> st.y;
	return is;
}
void createBoard(char Board[3][3]){
	cout << "____________" << endl;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			cout << "| " << Board[i][j] << " ";
		}
		cout << "|" << endl;
		cout << "____________" << endl;
	}
}
void isGameOver(char Board[3][3]){
	for(int i = 0; i < 3; i++){
		if(Board[i][0] != ' ' && Board[i][0] == Board[i][1] && Board[i][1] == Board[i][2]){
			isRunning = false;
			return;
		}
	}
	for(int i = 0; i < 3; i++){
		if(Board[0][i] != ' ' && Board[0][i] == Board[1][i] && Board[1][i] == Board[2][i]){
			isRunning = false;
			return;
		}
	}
	if(Board[0][0] != ' ' && Board[0][0] == Board[1][1] && Board[1] [1] == Board[2][2]){
		isRunning = false;
		return;
	}
	if(Board[0][2] != ' '&& Board[0][2] == Board[1][1] && Board[1][1] == Board[2][0]){
		isRunning = false;
		return;
	}
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(Board[i][j] == ' '){
				isRunning = true;
				return;
			}
		}
	}
	isRunning = false;
}
bool isMovesleft(char Board[3][3]){
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if(Board[i][j] == ' ')
				return true;
	return false;
}
int checkbot(char Board[maxn][maxn], char bot){
	for(int i = 0; i < 3; i++){
		if(Board[i][0] != ' ' && Board[i][0] == Board[i][1] && Board[i][1] == Board[i][2]){
			return (Board[i][0] == bot) ? 10 : -10;
		}
	}
	for(int i = 0; i < 3; i++){
		if(Board[0][i] != ' ' && Board[0][i] == Board[1][i] && Board[1][i] == Board[2][i]){
			return (Board[0][i] == bot) ? 10 : -10;
		}
	}
	if(Board[0][0] != ' ' && Board[0][0] == Board[1][1] && Board[1][1] == Board[2][2]){
		return (Board[0][0] == bot) ? 10 : -10;
	}
	return 0;
}
int minimax(char Board[3][3], bool isMax, char bot){
	int score = checkbot(Board, bot);
	if(score == 10)
		return score;
	if(score == -10)
		return score;
	if(isMovesleft(Board) == false)
		return 0;
	if(isMax){
		int best = -1000;
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				if(Board[i][j] == ' '){
					Board[i][j] = bot;
					best = max(best, minimax(Board, !isMax, bot));
					Board[i][j] = ' ';
				}
			}
		}
		return best;
	}
	else{
		int best = 1000;
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				if(Board[i][j] == ' '){
					Board[i][j] = 'O' + 'X' - bot;
					best = min(best, minimax(Board, !isMax, bot));
					Board[i][j] = ' ';
				}
			}
		}
		return best;
	}
}
start findbestMove(char Board[3][3], char bot){
	int bestVal = -1000;
	start st;
	st.x = -1;
	st.y = -1;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(Board[i][j] == ' '){
				Board[i][j] = bot;
				int moveVal = minimax(Board, false, bot);
				Board[i][j] = ' ';
				if(moveVal > bestVal){
					st.x = i;
					st.y = j;
					bestVal = moveVal;
				}
			}
		}
	}
	return st;
}
void PvE(start& st, int player, char Board[3][3], int mode){
	char human, bot;
	if(mode == 2){
		human = 'X';
		bot = 'O';
	}
	else{
		bot = 'X';
		human = 'O';
	}
	while(isRunning){
		if(player %2 == 0){
			cout <<"Make your move: \n";
			cin >> st;
			while(st.x < 1 || st.x > 3 || st.y < 1 || st.y > 3 || Board[st.x-1][st.y-1] != ' '){
				cout << "Hay nhap lai. Toa do khong hop le\n";
				cin >> st;
			}
			int row = st.x - 1;
			int col = st.y -1;
			Board[row][col] = human;
		}
		else{
			start ans = findbestMove(Board, bot);
			Board[ans.x][ans.y] = bot;
		}
		createBoard(Board);
		player++;
		isGameOver(Board);
	}
}
void PvP(start& st, int player, char Board[3][3]){
	while(isRunning){
		char turn = (player%2 == 1) ?'X' : 'O';
		cout << "Make your move:  \n";\
		cin >> st;
			while(st.x < 1 || st.x > 3 || st.y < 1 || st.y > 3){
				cout << "Hay nhap lai. Toa do khong hop le\n";
				cin >> st;
			}
			int row = st.x - 1;
			int col = st.y -1;
			Board[row][col] = turn;
			createBoard(Board);
			player++;
			isGameOver(Board);
	}
}
int evaluate(char Board[3][3]){
	for (int i = 0; i < 3; i++) {
        if (Board[i][0] != ' ' && Board[i][0] == Board[i][1] && Board[i][1] == Board[i][2]) {
            return (Board[i][0] == 'X') ? 1 : -1;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (Board[0][i] != ' ' && Board[0][i] == Board[1][i] && Board[1][i] == Board[2][i]) {
            return (Board[0][1] == 'X') ? 1 : -1;
        }
    }
    if (Board[0][0] != ' ' && Board[0][0] == Board[1][1] && Board[1][1] == Board[2][2]) {
        return (Board[0][0] == 'X') ? 1 : -1;
    }
    if (Board[0][2] != ' ' && Board[0][2] == Board[1][1] && Board[1][1] == Board[2][0]) {
        return (Board[0][2] == 'X') ? 1 : -1;
    }
    return 0;
}

int main(){
	cout << "Choose game mode:\n";
	cout << "1.Player(X) vs Player(O)\n";
	cout << "2.Player(X) vs Computer(O)\n";
	cout << "3.Player(O) vs Computer(X)\n";
	int mode = 0;
	cin >> mode;
	while(mode < 1 || mode > 3){
		cout << "KHong hop le. Hay chon lai\n";
		cin >> mode;
	}
	char Board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
	createBoard(Board);
	if(mode == 1){
		int player = 1;
		start st;
		PvP(st, player, Board);
	} else if (mode == 2){
		int player = 1;
		start st;
		PvE(st, player, Board, mode);
	} else{
		int player = 2;
		start st;
		PvE(st, player, Board, mode);
	}
	int result = evaluate(Board);
	cout << "Game over!";
	cout << (result > 0 ? "X wins!" :(result < 0 ?"O wins!": "Draw!")) << endl;
	return 0;
}
