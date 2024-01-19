#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

int tool;
bool check= false;

vector<int> order = {1, 2, 3, 4};

void path (int x, int y, int length, int**& copy_maze) {

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
            path(x + 1, y, length - 1, copy_maze);
            if (check) {
                return;
            } else {
                copy_maze[x][y] = 1;
            }
        } else if (order[i] == 2 && copy_maze[x - 1][y] == 1) {
            copy_maze[x][y] = 0;
            path(x - 1, y, length - 1, copy_maze);
            if (check) {
                return;
            } else {
                copy_maze[x][y] = 1;
            }
        } else if (order[i] == 3 && copy_maze[x][y + 1] == 1) {
            copy_maze[x][y] = 0;
            path(x, y + 1, length - 1, copy_maze);
            if (check) {
                return;
            } else {
                copy_maze[x][y] = 1;
            }
        } else if (order[i] == 4 && copy_maze[x][y - 1] == 1) {
            copy_maze[x][y] = 0;
            path(x, y - 1, length - 1, copy_maze);
            if (check) {
                return;
            } else {
                copy_maze[x][y] = 1;
            }
        }
    }
   copy_maze[x][y]=1;

}


void EasyMap(int command){
    /*
     First, in this part, we get (number of rows = x) and (number of columns = y).
    [moves] is a 1D array of how the track moves and [playground] is a 2D array of the game map.
    */
    int x , y ;
    cout<<"Enter the number of rows :";
    cin>> x ;
    cout<<"\nEnter the number of columns :";
    cin>> y ;
    int moves[x+y-2];
    int length = x + y - 2;
    int playground[x][y];
    string name;

    srand(time(0));

    /*
    Here we determine the number of zero blocks using the rand function.
    */

    int blocks =rand()%4+2;

    /*
     Now it's time to create a motion display. First, in this step, we set all the members of the array (movements) equal to two.
     Then, using the (rand) function, we select (x-1) random positions and set them equal to one (to avoid repeating the selected positions,
     we consider that the position is not already filled with the number one).
     Then we set the rest of the members that are not equal to 0
    */


    for (int i = 0; i < length; ++i) {
        moves[i]=2;
    }

    for (int i = 0; i < x-1; ++i) {

        int randmove=rand()% length ,a=randmove;
        if (moves[randmove]!=1){
            moves[randmove]=1;

        }
        else {
            while (randmove==a){
                randmove=rand()%(length);
            }
            moves[randmove]=1;

        }
    }

    for (int i = 0; i < length; ++i) {
        if (moves[i]==2) {
            moves[i] = 0;
        }
    }

    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            playground[i][j]=9;
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

    int ipath=0;
    int jpath=0;
    int sum =0;

    for (int k = 0; k < length; ++k) {

        int path=rand()%7-3;

        while (path == 0) {
            path = rand() % 7 - 3;
        }
        playground[ipath][jpath]=path;

        if (moves[k]==1){
            ipath++;
        }

        if (moves[k]==0){
            jpath++;
        }

        sum+=path;
    }
    playground[x-1][y-1]=sum;

    /*
     In this step, select 0 blocks We randomly select (i,j) and place 0 in the desired house.
     */

    for (int k = 0; k < blocks; ++k) {
        int i=rand()%x-1;
        int j=rand()%y-1;

        if (playground[i][j]==9){
            playground[i][j]=0;
        }

        else {

            while (playground[i][j]!=9){
                i=rand()%x-1;
                j=rand()%y-1;
            }

            playground[i][j]=0;

        }

    }
    /*
         In the last step, we get the name of the map from the user and after assigning values to all the houses
     whose values are equal to 9, we print them in the desired file.
    */
    cout<<"\nEnter the name of the map (without the file extension) :";
    cin>>name;
    fstream map("Maps/"+name+".txt",ios::app);


    for (int i = 0 ; i < x ; ++i) {

        for (int j = 0; j < y ; ++j) {

            if (playground[i][j]==9 && !(i==x-1&&j==y-1)){
                playground[i][j]=rand()%7-3;

                if (playground[i][j]==0){

                    int playrand=rand()%7-3;

                    while (playrand==0){
                        playrand=rand()%7-3;

                    }

                    playground[i][j]=playrand;
                }

            }
            map<<playground[i][j]<<" ";
        }
        map<<endl;
    }

map.close().
}

void HardMap(int command){
        srand(time(0));
    int x,y;
    cin>>x>>y;cout<<"Enter the length of the path :";cin>>tool;

    while ((tool-(x+y-2))%2!=0||tool>x*y||tool<x+y-2){
        cerr<<"The desired path length dose not exist!!!\nEnter the length of the path again :";
        cin>>tool;
    }

    int** copymap;
    int al,au,bl,bu;
    cout<<"\nEnter the range of numbers in the table : (";
    cin>>al;cout<<",";cin>>au;cout<<")\n";
    cout<<"Enter a range of zero blocks : (";cin>>bl;cout<<",";cin>>bu;cout<<") \n";
    copymap=new int *[x+2];



    while (bl>(x*y)-tool-1){
        cerr<<"There are to many zero blocks!!!\nEnter a range of zero blocks again :";
        cin>>bl>>bu;

    }


    int blocks=rand()%(bu-bl+1)+bl;

    while (blocks>(x*y)-tool-1){
        blocks=rand()%(bu-bl+1)+bl;
    }

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

    path(1,1,tool,copymap);


        cout<<endl<<endl;

        string playground [x][y];
        int random_number,sum=0;

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


    for (int i = 0; i < x ; ++i) {
        for (int j = 0; j < y; ++j) {
            if (playground[i][j]=="#"){
                random_number=rand()%(au-al+1)+al;
                while (random_number==0){
                    random_number=rand()%(au-al+1)+al;
                }
                playground[i][j]= to_string(random_number);
            }
            map<<playground[i][j]<<" ";
        }
        map<<endl;
    }

    map.close();
}

int main(){
    int choose,command;
    cout<<"1. Create a New Map\n2. Playground\n3. Solve a Maze\n4. History\n5. exit\n";
    cout<<"Enter your command :";
    cin>>choose;
    cout<<"\n";
    while (choose!=5) {

        if (choose == 1) {
            cout << "/Create a New Map :\n1. Easy\n2. Hard\n";
            cout << "Enter your command :";
            cin >> command;

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
            cout << "/Playground :\n1. Choose from Existing Maps\n2. Import a Custom Map\n";
            cout << "Enter your command :";
            cin >> command;
        }

        else if (choose == 3) {
            cout << "/Solve a Maze :\n1. Choose from Existing Maps\n2. Import a Custom Map\n";
            cout << "Enter your command :";
            cin >> command;
        }

        else if (choose == 4) {
            cout << "/History :\n";
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

    }

    return 0;
}
