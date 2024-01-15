#include <iostream>
using namespace std;

void EasyMap(int command);
void HardMap(int command);

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
