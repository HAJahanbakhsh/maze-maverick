#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <windows.h>
#include <iomanip>

using namespace std;

int tool;
bool check= false;
vector<int> order = {1, 2, 3, 4};
string **map_read;
int length_map;
int x_map,y_map;
string map_name;

//----------------------------------------------------------------------------------------------------------------------

typedef enum
{
    BLACK = 0, BLUE = 1, GREEN = 2,
    AQUA = 3, RED = 4, PURPLE = 5,
    YELLOW = 6, WHITE = 7, GRAY = 8,
    LIGHT_BLUE = 9, LIGHT_GREEN = 10,
    LIGHT_AQUA = 11, LIGHT_RED = 12,
    LIGHT_PURPLE = 13, LIGHT_YELLOW = 14,
    LIGHT_WHITE = 15
} ConsoleColors;
typedef HANDLE Handle;
typedef CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
typedef WORD Word;
short setTextColor(const ConsoleColors foreground)
{
    Handle consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    BufferInfo bufferInfo;
    if(!GetConsoleScreenBufferInfo(consoleHandle, &bufferInfo))
        return 0;
    Word color = (bufferInfo.wAttributes & 0xF0) + (foreground & 0x0F);
    SetConsoleTextAttribute(consoleHandle, color);
    return 1;
}

//----------------------------------------------------------------------------------------------------------------------

void history_reader(int command){


    fstream history ("Stats/History.txt",ios::in);
    string line,add;
    while (getline(history,add)){
        line=line+add;
    }

    history.close();


int n=0;
    for (int i = 0; i < line.length(); ++i) {
        if (n%2==0){
            setTextColor(LIGHT_BLUE);
        } else{
            setTextColor(LIGHT_WHITE);
        }
        if(line[i]=='('){
            while (line[i]!='/'){
                setTextColor(LIGHT_GREEN);
                cout<<line[i];
                setTextColor(LIGHT_WHITE);
                i++;
            }
        }
        if (line[i]=='/'){
            cout<<endl;
            n++;
        }
        else if(line[i]=='#'){
                cout<<"   ";
        }

        else {
                cout << line[i];
        }
    }
    setTextColor(LIGHT_WHITE);
}


//----------------------------------------------------------------------------------------------------------------------


void history_maker(string time,string date,string name,string map,string result){


    fstream history ("Stats/History.txt",ios::in);
    string line,add;
    while (getline(history,add)){
        line=line+add;
    }

    history.close();


    //This function first removes the tenth game,
    // then adds one to the queue of the other games, and finally loads the statistics of the new game.

    line.erase(line.find("//(10)"));
    line.erase(line.find("(9)")+1,1);
    line.insert(line.find("()")+1,"10");

    line.erase(line.find("(8)")+1,1);
    line.insert(line.find("()")+1,"9");

    line.erase(line.find("(7)")+1,1);
    line.insert(line.find("()")+1,"8");

    line.erase(line.find("(6)")+1,1);
    line.insert(line.find("()")+1,"7");

    line.erase(line.find("(5)")+1,1);
    line.insert(line.find("()")+1,"6");

    line.erase(line.find("(4)")+1,1);
    line.insert(line.find("()")+1,"5");

    line.erase(line.find("(3)")+1,1);
    line.insert(line.find("()")+1,"4");

    line.erase(line.find("(2)")+1,1);
    line.insert(line.find("()")+1,"3");

    line.erase(line.find("(1)")+1,1);
    line.insert(line.find("()")+1,"2");
    line="//(1)"
            "/#player name :"+name+
            "/#map :"+map+
            "/#time to play :"+time+" Seconds"
            "/#date :"+date+
            "/#result :"+result
         +line;

    fstream delete_history ("Stats/History.txt",ios::out);
    delete_history<<"";
    delete_history.close();

    fstream new_history ("Stats/History.txt",ios::out);


    for (int i = 0; i < line.length(); ++i) {
        if (line[i]=='/'){
            new_history<<endl;
        }

        new_history<<line[i];
    }
}



//----------------------------------------------------------------------------------------------------------------------

void map_reader(int command){
    if(command==1) {
        string names;
        fstream maps("Maps/names.txt", ios::in);
        int m = 0;


        setTextColor(LIGHT_BLUE);

        while (getline(maps, names)) {
            cout << m + 1 << "." << names << endl;
            m++;
        }


        setTextColor(LIGHT_WHITE);
        cout << "Enter the name of the selected map:";
        cin >> map_name;


        maps.close();

        fstream map;
        map.open("Maps/" + map_name + ".txt", ios::in);
        while (!(map.is_open())){
            cerr <<"There is no such map!!\n";
            cout << "Enter the name of the selected map again:";
            cin >> map_name;
            map.close();
            map.open("Maps/" + map_name + ".txt", ios::in);

        }
        string generate, line = "";
        while (getline(map, generate)) {
            line += generate;
        }

         x_map = 0, y_map = 0;
        for (int i = 0; i < line.length(); ++i) {
            if (line[i] == '#') {
                y_map++;
            } else if (line[i] == '!') {
                x_map++;
            }
        }

        y_map = y_map / x_map;


        map_read =new string *[x_map];
        for (int i = 0; i < x_map; ++i) {
            map_read[i]=new string [y_map];
        }

        int k = -1, n = -1;

        string length1;


        for (int i = 0; i < line.length(); ++i) {
            if (line[i] == '#') {
                k++;
            } else if (line[i] == '!') {
                n++;
                k = -1;
            } else if (line[i] == '$') {
                i++;
                while (line[i] != '%') {
                    length1 = length1 + line[i];
                    i++;
                }
            } else {
                map_read[n][k] += line[i];
            }
        }
        length_map = stoi(length1);
        return ;
    }
    else if (command==2){

        setTextColor(LIGHT_GREEN);
        cout << "Enter the number of rows :";
        cin >> x_map;
        cout << "\nEnter the number of columns :";
        cin >> y_map;
        setTextColor(LIGHT_WHITE);


        map_read=new string *[x_map];
        for (int i = 0; i < x_map; ++i) {
            map_read[i]=new string [y_map];
            for (int j = 0; j < y_map ; ++j) {
                system("cls");
                cout<<"\n Enter the [";
                setTextColor(LIGHT_YELLOW);
                cout<<i+1;
                setTextColor(LIGHT_WHITE);
                cout<<"][";
                setTextColor(LIGHT_YELLOW);
                cout<<j+1;
                setTextColor(LIGHT_WHITE);
                cout<<"] Block :";
                cin>>map_read[i][j];
            }
        }
        system("cls");
        setTextColor(LIGHT_GREEN);
        cout<<"\nEnter the length of the path :";
        setTextColor(LIGHT_WHITE);
        cin>>length_map;
        cout<<"Enter the name of the map :";
        cin>>map_name;
        return ;
        system("cls");
    }
}


//----------------------------------------------------------------------------------------------------------------------



void GPS (int x, int y, int target_x , int target_y, int**& copy_maze , int sum , int**& number, int length) {
   if(target_x-x+target_y-y>length){
       return;
   }


    if (length<0){
        return;
    }


    if ( length-1==0 &&sum-copy_maze[x][y] == 0 && (( x + 1 == target_x && y == target_y ) ||( x == target_x && y + 1 == target_y))) {
        check = true;
        copy_maze[x][y]=0;
        return;
    }



        if (copy_maze[x + 1][y] != 0 ) {
            copy_maze[x][y] = 0;
            GPS(x + 1, y, target_x, target_y, copy_maze, sum - number[x][y], number,length-1);
            if (check) {
                return;
            } else {
                copy_maze[x][y] = number[x][y];
            }
        }

         if (copy_maze[x - 1][y] != 0 ) {
            copy_maze[x][y] = 0;
            GPS(x - 1, y, target_x, target_y, copy_maze, sum - number[x][y], number,length-1);
            if (check) {
                return;
            } else {
                copy_maze[x][y] = number[x][y];
            }
        }

         if (copy_maze[x][y + 1] != 0 ) {
            copy_maze[x][y] = 0;
            GPS(x, y + 1, target_x, target_y, copy_maze, sum - number[x][y], number,length-1);
            if (check) {
                return;
            } else {
                copy_maze[x][y] = number[x][y];
            }
        }

         if (copy_maze[x][y - 1] != 0 ) {
            copy_maze[x][y] = 0;
            GPS(x, y - 1, target_x, target_y, copy_maze, sum - number[x][y], number,length-1);
            if (check) {
                return;
            } else {
                copy_maze[x][y] = number[x][y];
            }
        }


    copy_maze[x][y]=number[x][y];

}



//----------------------------------------------------------------------------------------------------------------------

void Solve(string **&playgroud,int length,int x,int y) {

/*First, we make two copies of the received map with length and width plus two,
 * then we set the box blocks equal to zero and the middle blocks equal to the blocks of the original map,
 * then we set the last block of each equal to zero.*/
    int **copy_map;
    copy_map = new int *[x + 2];
    for (int i = 0; i < x + 2; ++i) {
        copy_map[i] = new int[y + 2];
        for (int j = 0; j < y + 2; ++j) {

            copy_map[i][j] = 0;

        }
    }

    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            copy_map[i + 1][j + 1] = stoi(playgroud[i][j]);
        }
    }
    copy_map[x][y] = 0;


    int **number;
    number = new int *[x + 2];

    for (int i = 0; i < x + 2; ++i) {
        number[i] = new int[y + 2];
        for (int j = 0; j < y + 2; ++j) {

            number[i][j] = 0;

        }
    }

    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            number[i + 1][j + 1] = stoi(playgroud[i][j]);
        }
    }
    number[x][y] = 0;



/*This function returns in each block to the adjacent blocks that are allowed inside to find the path*/
    GPS(1,1,x,y,copy_map, stoi(playgroud[x-1][y-1]),number,length);
    if (!check){
        setTextColor(RED);
        cout<<"No path found!";
        setTextColor(LIGHT_WHITE);
        return;
    }
    check= false;

    system("cls");

/*Now the route traveled in the copy of the map is equal to zero, we match it with the original map and display the route in color.*/
    for (int i = 0; i <x ; ++i) {
        for (int j = 0; j <y ; ++j) {
            cout << '|';
            if (copy_map[i+1][j+1] == 0 && stoi(playgroud[i][j]) != 0 && (i != x-1 || j != y-1)) {
                setTextColor(LIGHT_GREEN);
                cout << setw(2) << setfill(' ')<<stoi(playgroud[i][j])<<setw(2)<<setfill(' ') ;
                setTextColor(LIGHT_WHITE);
            }
            else if(copy_map[i+1][j+1] == 0 && stoi(playgroud[i][j]) == 0){
                setTextColor(LIGHT_YELLOW);
                cout << setw(2) << setfill(' ')<<string (1,2)<<setw(2)<<setfill(' ') ;
                setTextColor(LIGHT_WHITE);

            }
            else if (i == x-1 && j == y-1){
                setTextColor(LIGHT_YELLOW);
                cout << setw(2) << setfill(' ')<<stoi(playgroud[i][j])<<setw(2)<<setfill(' ') ;
                setTextColor(LIGHT_WHITE);
            }
            else{
                setTextColor(GRAY);
                cout << setw(2) << setfill(' ')<<stoi(playgroud[i][j])<<setw(2)<<setfill(' ') ;
                setTextColor(LIGHT_WHITE);
            }
        }
        cout<<setw(2)<<setfill(' ')<<"|"<<endl;
    }

}




//----------------------------------------------------------------------------------------------------------------------

void play(string **&playgroud,int length,int x,int y){


    string player_name,result;
    setTextColor(LIGHT_BLUE);
    cout<<"Enter The Username:";
    cin>>player_name;
    setTextColor(LIGHT_WHITE);

    /*First, we will take a copy of the original map to move in it*/

    int **copy_map;
    copy_map = new int *[x + 2];
    for (int i = 0; i < x + 2; ++i) {
        copy_map[i] = new int[y + 2];
        for (int j = 0; j < y + 2; ++j) {

            copy_map[i][j] = 0;

        }
    }

    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            copy_map[i + 1][j + 1] =1;
        }
    }



    char dastoor;
    int x_move=1,y_move=1;

    time_t now= time(0);
    char* date= ctime(&now);
    system("cls");
    clock_t start=clock();
    /*Then we display the function dynamically and move with the desired commands in
     * the copy map and color the path and the block we are in turns red.*/
    while (x_move!=x||y_move!=y) {




        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) {
                cout << '|';
                if (i + 1== x_move &&j + 1 == y_move ) {
                    setTextColor(LIGHT_RED);
                    cout << setw(2) << setfill(' ') << stoi(playgroud[i][j]) << setw(2) << setfill(' ');
                    setTextColor(LIGHT_WHITE);
                }
                else if (copy_map[i + 1][j + 1] == 0 && stoi(playgroud[i][j]) != 0 && (i != x - 1 || j != y - 1)) {
                    setTextColor(LIGHT_BLUE);
                    cout << setw(2) << setfill(' ') << stoi(playgroud[i][j]) << setw(2) << setfill(' ');
                    setTextColor(LIGHT_WHITE);
                } else if (copy_map[i + 1][j + 1] != 0 && stoi(playgroud[i][j]) == 0) {
                    setTextColor(LIGHT_YELLOW);
                    cout << setw(2) << setfill(' ') << string(1, 2) << setw(2) << setfill(' ');
                    setTextColor(LIGHT_WHITE);


                } else if (i == x - 1 && j == y - 1) {
                    setTextColor(LIGHT_YELLOW);
                    cout << setw(2) << setfill(' ') << stoi(playgroud[i][j]) << setw(2) << setfill(' ');
                    setTextColor(LIGHT_WHITE);
                } else {
                    setTextColor(GRAY);
                    cout << setw(2) << setfill(' ') << stoi(playgroud[i][j]) << setw(2) << setfill(' ');
                    setTextColor(LIGHT_WHITE);
                }
            }
            cout << setw(2) << setfill(' ') << "|" << endl;



        }
        cout<<endl<<"move :";


        while (!check) {
            cin>>dastoor;

            if (dastoor == 's' || dastoor == 'S') {
                x_move++;
                check= true;


                if (playgroud[x_move - 1][y_move - 1] == "0" ||x_move>x) {
                    cerr << "you cant go to zero blocks";
                    check= false;
                    x_move--;


                }
            }
            else if (dastoor == 'W' || dastoor == 'w') {
                x_move--;
                check= true;


                if (playgroud[x_move - 1][y_move - 1] == "0"||x_move<1) {
                    cerr << "you cant go to zero blocks";
                    check= false;
                    x_move++;


                }
            }
            else if (dastoor == 'a' || dastoor == 'A') {
                y_move--;
                check= true;


                if (playgroud[x_move - 1][y_move - 1] == "0"||y_move<1) {
                    cerr << "you cant go to zero blocks";
                    check= false;
                    y_move++;


                }
            }
            else if (dastoor == 'D' || dastoor == 'd') {
                y_move++;
                check= true;


                if (playgroud[x_move - 1][y_move - 1] == "0"||y_move>y) {
                    cerr << "you cant go to zero blocks";
                    check= false;
                    y_move--;


                }
                
            }
            system("cls");
        }
        check= false;
        if ( copy_map[x_move][y_move]==0){
            copy_map[x_move][y_move]=1;
        } else{

            if (dastoor == 's' || dastoor == 'S'){
                copy_map[x_move-1][y_move]=0;
            }
            if (dastoor == 'w' || dastoor == 'W'){
                copy_map[x_move+1][y_move]=0;
            }
            if (dastoor == 'a' || dastoor == 'A'){
                copy_map[x_move][y_move+1]=0;
            }
            if (dastoor == 'd' || dastoor == 'D'){
                copy_map[x_move][y_move-1]=0;
            }

        }

    }

    /*The blocks of the path we take will change from one to zero in the copy of the map.
     * Then, when we reach the last block, I add up the numbers of the path,
     * if it is equal to the last house, we win, and if not, we display the correct path.*/
    clock_t finish=clock();

    int sum=0;
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            if (copy_map[i+1][j+1]==0&&playgroud[i][j]!="0"){
                sum+= stoi(playgroud[i][j]);
            }
        }
    }


    if(sum== stoi(playgroud[x-1][y-1])){
        setTextColor(LIGHT_GREEN);
        cout<<"!!victory!!\n";
        setTextColor(LIGHT_WHITE);
        result="victory!";
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) {
                cout << '|';
                if (i + 1== x_move &&j + 1 == y_move ) {
                    setTextColor(LIGHT_RED);
                    cout << setw(2) << setfill(' ') << stoi(playgroud[i][j]) << setw(2) << setfill(' ');
                    setTextColor(LIGHT_WHITE);
                }
                else if (copy_map[i + 1][j + 1] == 0 && stoi(playgroud[i][j]) != 0 && (i != x - 1 || j != y - 1)) {
                    setTextColor(LIGHT_BLUE);
                    cout << setw(2) << setfill(' ') << stoi(playgroud[i][j]) << setw(2) << setfill(' ');
                    setTextColor(LIGHT_WHITE);
                } else if (copy_map[i + 1][j + 1] != 0 && stoi(playgroud[i][j]) == 0) {
                    setTextColor(LIGHT_YELLOW);
                    cout << setw(2) << setfill(' ') << string(1, 2) << setw(2) << setfill(' ');
                    setTextColor(LIGHT_WHITE);

                } else if (i == x - 1 && j == y - 1) {
                    setTextColor(LIGHT_YELLOW);
                    cout << setw(2) << setfill(' ') << stoi(playgroud[i][j]) << setw(2) << setfill(' ');
                    setTextColor(LIGHT_WHITE);
                } else {
                    setTextColor(GRAY);
                    cout << setw(2) << setfill(' ') << stoi(playgroud[i][j]) << setw(2) << setfill(' ');
                    setTextColor(LIGHT_WHITE);
                }
            }
            cout << setw(2) << setfill(' ') << "|" << endl;



        }
    }
    else{
        setTextColor(LIGHT_RED);
        cout<<"!!GAME OVER!!";
        setTextColor(LIGHT_WHITE);
        result="!!GAME OVER!!";
        Solve(map_read,length_map,x_map,y_map);
    }
    /*Then we enter the duration of the game, the date, the name of the player, the name of the map and the result of the game in the history maker function.*/
    history_maker(to_string((double )(finish-start)/(double )(CLOCKS_PER_SEC)),date,player_name,map_name,result);

}


//----------------------------------------------------------------------------------------------------------------------


void path (int x, int y, int length, int**& copy_maze, int target_x , int target_y) {
    if(target_x-x+target_y-y>length){
        return;
    }

    if (length < 0) {
        return;
    }

    if ((length - 1  == 0) && (copy_maze[x + 1][y] == 2 || copy_maze[x][y + 1] == 2)) {
        check = true;
       copy_maze[x][y]=0;
        return;
    }


    // Use the <random> header to generate random numbers
    random_device rd;
    mt19937 gen(rd());
    shuffle(order.begin(), order.end(), gen);

    for (int i = 0; i < 4; i++) {
        if (order[i] == 1 && copy_maze[x + 1][y] == 1) {
            copy_maze[x][y] = 0;
            path(x + 1, y, length - 1, copy_maze,  target_x ,  target_y);
            if (check) {
                return;
            } else {
                copy_maze[x][y] = 1;
            }
        } else if (order[i] == 2 && copy_maze[x - 1][y] == 1) {
            copy_maze[x][y] = 0;
            path(x - 1, y, length - 1, copy_maze,  target_x ,  target_y);
            if (check) {
                return;
            } else {
                copy_maze[x][y] = 1;
            }
        } else if (order[i] == 3 && copy_maze[x][y + 1] == 1) {
            copy_maze[x][y] = 0;
            path(x, y + 1, length - 1, copy_maze,  target_x ,  target_y);
            if (check) {
                return;
            } else {
                copy_maze[x][y] = 1;
            }
        } else if (order[i] == 4 && copy_maze[x][y - 1] == 1) {
            copy_maze[x][y] = 0;
            path(x, y - 1, length - 1, copy_maze,  target_x ,  target_y);
            if (check) {
                return;
            } else {
                copy_maze[x][y] = 1;
            }
        }
    }
   copy_maze[x][y]=1;

}


//----------------------------------------------------------------------------------------------------------------------

void EasyMap(int command) {
    /*
     First, in this part, we get (number of rows = x) and (number of columns = y).
    [moves] is a 1D array of how the track moves and [playground] is a 2D array of the game map.
    */
    int x, y;
    cout << "Enter the number of rows :";
    cin >> x;
    cout << "\nEnter the number of columns :";
    cin >> y;
    int moves[x + y - 2];
    int length = x + y - 2;
    int playground[x][y];
    string name;
    system("cls");

    srand(time(0));

    /*
    Here we determine the number of zero blocks using the rand function.
    */

    int blocks = rand() % 4 + 2;
    while (x*y-blocks<x+y-1){
         blocks = rand() % 4 + 2;
    }

    /*
     Now it's time to create a motion display. First, in this step, we set all the members of the array (movements) equal to two.
     Then, using the (rand) function, we select (x-1) random positions and set them equal to one (to avoid repeating the selected positions,
     we consider that the position is not already filled with the number one).
     Then we set the rest of the members that are not equal to 0
    */


    for (int i = 0; i < length; ++i) {
        moves[i] = 2;
    }

    for (int i = 0; i < x - 1; ++i) {

        int randmove = rand() % length, a = randmove;
        if (moves[randmove] != 1) {
            moves[randmove] = 1;

        } else {
            while (moves[randmove] == 1) {
                randmove = rand() % (length);
            }
            moves[randmove] = 1;

        }
    }

    for (int i = 0; i < length; ++i) {
        if (moves[i] == 2) {
            moves[i] = 0;
        }
    }

    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            playground[i][j] = 9;
        }
    }

    /*
    Now is the time to build the track. First, we set all the members of the array equal to 9, which is not in the range of numbers.
        Then we take an (int=sum) and set it to zero.Now we consider that we are at the point (i=0, j=0).
        Then this house using the rand function We number
    Now we move between array[playground] using a loop and array[Moves]. In this way, if [i]moves is equal to one,
        we move one house to the right and if it is equal to 0, we move one house down.
        And we assign random values to each of the places we skipped.
        And finally, when we reach the last house, we make it equal to (sum), which is the sum of the path numbers.
    */

    int ipath = 0;
    int jpath = 0;
    int sum = 0;

    for (int k = 0; k < length; ++k) {

        int path = rand() % 7 - 3;

        while (path == 0) {
            path = rand() % 7 - 3;
        }
        playground[ipath][jpath] = path;

        if (moves[k] == 1) {
            ipath++;
        }

        if (moves[k] == 0) {
            jpath++;
        }

        sum += path;
    }
    playground[x - 1][y - 1] = sum;

    /*
     In this step, select 0 blocks We randomly select (i,j) and place 0 in the desired house.
     */

    for (int k = 0; k < blocks; ++k) {
        int i = rand() % x - 1;
        int j = rand() % y - 1;

        if (playground[i][j] == 9) {
            playground[i][j] = 0;
        } else {

            while (playground[i][j] != 9) {
                i = rand() % x - 1;
                j = rand() % y - 1;
            }

            playground[i][j] = 0;

        }

    }
    /*
         In the last step, we get the name of the map from the user and after assigning values to all the houses
     whose values are equal to 9, we print them in the desired file.
    */
    cout << "\nEnter the name of the map (without the file extension) :";
    cin >> name;
    fstream map("Maps/" + name + ".txt", ios::app);
    fstream names("Maps/names.txt",ios::app);
    names<<name<<endl;
    names.close();


    for (int i = 0; i < x; ++i) {
        map << "!";
        for (int j = 0; j < y; ++j) {

            if (playground[i][j] == 9 && !(i == x - 1 && j == y - 1)) {
                playground[i][j] = rand() % 7 - 3;

                if (playground[i][j] == 0) {

                    int playrand = rand() % 7 - 3;

                    while (playrand == 0) {
                        playrand = rand() % 7 - 3;

                    }

                    playground[i][j] = playrand;
                }

            }
            map << "#" << playground[i][j];
        }
        map << endl;
    }
    map<<"$"<<length<<"%";

    map.close();

}



//----------------------------------------------------------------------------------------------------------------------


void HardMap(int command){
        srand(time(0));
    int x, y;
    cout << "Enter the number of rows :";
    cin >> x;
    cout << "\nEnter the number of columns :";
    cin >> y;
    cout<<"\nEnter the length of the path :";
    cin>>tool;

    while ((tool-(x+y-2))%2!=0||tool>x*y||tool<x+y-2){
        cerr<<"The desired path length dose not exist!!!\nEnter the length of the path again :";
        cin>>tool;
    }

    int** copymap;
    int al,au,bl,bu;
    cout<<"\nEnter the range of numbers in the table : ";
    cin>>al>>au;
    cout<<"\nEnter a range of zero blocks : ";
    cin>>bl>>bu;
    copymap=new int *[x+2];



    while (bl>(x*y)-tool-1){
        cerr<<"There are to many zero blocks!!!\nEnter a range of zero blocks again :";
        cin>>bl>>bu;

    }
    system("cls");

/*Determining the number of zero blocks randomly*/
    int blocks=rand()%(bu-bl+1)+bl;

    while (blocks>(x*y)-tool-1){
        blocks=rand()%(bu-bl+1)+bl;
    }
/*We take a copy of the map and consider its length and width plus 2 and set the box houses equal to zero,
 * the middle houses equal to one and the last house equal to two.*/
    for (int i = 0; i < x+2 ; ++i) {
        copymap[i]=new int [y+2];
        for (int j = 0; j < y+2 ; ++j) {
                copymap[i][j]=0;
        }
    }

    for (int i = 1; i < x+2 ; ++i) {
        for (int j = 1; j < y+1 ; ++j) {
            copymap[i][j]=1;
        }
    }
    copymap[x][y]=2;

/*Now, using the path function, we take a random path of arbitrary length inside the copy of the map.
 * After completing the desired path, the houses covered by the function are set to zero*/

    path(1,1,tool,copymap,x,y);

    check= false;



        string playground [x][y];
        int random_number,sum=0;

/*Now we place all the blocks of the copy map and the original map facing each other.
 * And we place the blocks that are filled with zero in the copy map in the main map equal to a random number. and add it in the last block.*/

    for (int i = 0; i < x ; ++i) {
        for (int j = 0; j < y ; ++j) {
            playground[i][j]=to_string(copymap[i+1][j+1]);
            if (playground[i][j]=="0"){
                random_number=rand()%(au-al+1)+al;
                while (random_number==0){
                    random_number=rand()%(au-al+1)+al;
                }
                sum+=random_number;
                playground[i][j]= to_string(random_number);
            }
            else if (playground[i][j]=="1"){
                playground[i][j]="#";
            }
        }
    }

    playground[x-1][y-1]=to_string(sum);
/*Then we place zero blocks. And we place the rest of the blocks with a random number.*/
    for (int k = 0; k < blocks ; ++k) {
        int i=rand()%x;
        int j=rand()%y;
        while (playground[i][j]!="#"){
            i=rand()%x;
            j=rand()%y;
        }
        playground[i][j]="0";
    }
    string name;
    cout<<"Enter the name of the map :";
    cin>>name;
    fstream map ("Maps/"+name+".txt",ios::app);
    fstream maps ("Maps/names.txt",ios::app);
    maps<<name<<endl;


    for (int i = 0; i < x ; ++i) {
        map<<"!";
        for (int j = 0; j < y; ++j) {
            if (playground[i][j]=="#"){
                random_number=rand()%(au-al+1)+al;
                while (random_number==0){
                    random_number=rand()%(au-al+1)+al;
                }
                playground[i][j]= to_string(random_number);
            }
            map<<"#"<<playground[i][j];
        }
        map<<endl;
    }
    map<<"$"<<tool<<"%";
    map.close();
    delete(copymap);

}


//-----------------------------------------------------------------------------------------------------------------------

int main(){
    int choose,command;

    cout<<"1. Create a New Map\n2. Playground\n3. Solve a Maze\n4. History\n5. exit\n";
    cout<<"Enter your command :";
    cin>>choose;
    cout<<"\n";
    system("cls");
    while (choose!=5) {

        if (choose == 1) {
            setTextColor(PURPLE);
            cout << "/Create a New Map :\n";
            setTextColor(LIGHT_WHITE);
            cout<<"1. Easy\n2. Hard\n";
            cout << "Enter your command :";
            cin >> command;
            system("cls");

            if (command==1){
                EasyMap(command);
            }

            else if (command==2){
                HardMap(command);
            }

            else{
                cerr << "This Command is not Valid\n";
                cout << "Enter your command again :";
                cin >> command;
            }

        }

        else if (choose == 2) {
            setTextColor(PURPLE);
            cout << "/Playground :\n";
            setTextColor(LIGHT_WHITE);
            cout<<"1. Choose from Existing Maps\n2. Import a Custom Map\n";
            cout << "Enter your command :";
            cin>>command;
            system("cls");
            map_reader(command);
            play(map_read,length_map,x_map,y_map);
            cout<<endl<<endl;

        }

        else if (choose == 3) {
            setTextColor(PURPLE);
            cout << "/Solve a Maze :\n";
            setTextColor(LIGHT_WHITE);
            cout<<"1. Choose from Existing Maps\n2. Import a Custom Map\n";
            cout << "Enter your command :";
            cin>>command;
            system("cls");
            map_reader(command);
            Solve(map_read,length_map,x_map,y_map);
            cout<<endl<<endl;

        }

        else if (choose == 4) {
            setTextColor(PURPLE);
            cout << "The Last ten Games :";
            setTextColor(LIGHT_WHITE);
            history_reader(choose);
            cout<<endl<<endl;
        }

        else {
            cerr << "This Command is not Valid\n";
            cout << "Enter your command again :";
            cin >> choose;
        }

        cout<<"1. Create a New Map\n2. Playground\n3. Solve a Maze\n4. History\n5. exit\n";
        cout<<"Enter your command :";
        cin>>choose;
        cout<<"\n";
        system("cls");


    }

    return 0;
}
