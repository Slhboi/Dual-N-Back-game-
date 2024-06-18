// note we will have to download these libs in order to run locally 

// Omar Salah Sayed Mahmoud 1201101928
// Mohtady Ehab Barakat 1211305618


#include <iostream>
#include <ctime>
#include <unistd.h> 
using namespace std;

// Random Position Generator using time
int randomPositionGen(){
    return (time(NULL) % 9);
    
}

// Random Letter Generator using time
char randomLetterGen(){
    int letter = 'a';
    return char(letter + (time(NULL))%26);
    
}

// Starting message 
void startMessage(){
    cout << "\t\t\t\t\tWelcome to the game of Dual-N-Back!!!\n\t\t\tInput your choice of N and R (Choose Carefully!) : \n\tInputs: p => position, l => letter, b => both, n => neither, q => quit";
}

// Displays grid

void displayGrid(char character, int pos) {
    system("clear");
    int pos_x = (pos%3);
    int pos_y = ((pos - pos_x)/3);
    cout << pos_x <<endl;
    cout << pos_y <<endl;
    char grid [3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    for (int i = 0; i <= 2; i ++){
		for (int j =0; j <= 2; j++){
			if (i == pos_x && j == pos_y)
				cout << character;
			else
			    cout << "-";
				cout << grid[i][j];
			    
		}
		cout << endl;
	}
}

// fucntion for user to input answer
char userInput(int n){
// function take user input and validate it
    char temp_input;
    bool isInvalid; 
    while(1){
        cout << "\n\nIs this grid the same as " << n << " before: ";
        cin >> temp_input;
        
        if (temp_input == 'p' or temp_input == 'l' or temp_input == 'n' or temp_input == 'b' or temp_input == 'q'){
            return temp_input; 
        }
        else{
            cout << "\nINVALID INPUT, INPUT AGAIN";
            continue;
        }
    }
}
       



// calculates wrong and right for user along with final score
int calculateScore(int n, char let_hist_arr[], char input_hist_arr[], int pos_hist_arr[], int r){
    char correction[r]; 
    int score = 0; 
    // loop to create correction array
    for (int i = 0; i < r; i ++){
        if (i < n){
            correction[i] = 'n';
            continue; 
        }
        if ((let_hist_arr[i] == let_hist_arr[i-n] && input_hist_arr[i] == 'l') ||(pos_hist_arr[i] == pos_hist_arr[i-n] && input_hist_arr[i] == 'p') || 
            (let_hist_arr[i] == let_hist_arr[i-n] && pos_hist_arr[i] == pos_hist_arr[i-n]
            && input_hist_arr[i] == 'b')){
            correction[i] = 'c'; 
            }
        else if (input_hist_arr[i] == 'q'){
            for (int j = i; j < r; j++){
                correction[j] = 'n';
            }
            continue;
        }
        else {
            correction[i] = 'w';
        }
        
    }
    
    // loop to calculate score
    for(int i = 0; i < r; i ++){
        if (correction[i] == 'c'){
            score += 10*n; 
        }
            else {
                continue;
            }
        
    }
    
    return score;
}

// output message
void endMessage(int score){
    cout << "\n\n\nYour score is: " << score << "\n\nThank you for playing the game!!" << endl;
}


int main() {
        int n;
        int r;
        startMessage();
        cout << endl;
        cin >> n;
        cin >> r;
        char let_hist_arr[r], input_hist_arr[r];
        int pos_hist_arr[r]; 
        // int correction_arr[10*n]; if we want to check per input
        for(int i = 0; i < r; i ++){
            int temp_pos = randomPositionGen();
            char temp_let = randomLetterGen();
            let_hist_arr[i] = temp_let;
            pos_hist_arr[i] = temp_pos;
            displayGrid(temp_let, temp_pos);
            //sleep(3);
            char temp_input = userInput(n);
            if (temp_input == 'q'){
                break;
            }
            input_hist_arr[i] = temp_input;
        }
        
        int score = calculateScore(n, let_hist_arr, input_hist_arr, pos_hist_arr, r); 
        endMessage(score);
        
    
    return 0;
}