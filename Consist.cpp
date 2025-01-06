// "data.txt" stores long term tasks, "dailydata.txt" stores daily tasks.
// "metadata.txt" stores the information required to run this code (1. previous date 2. Task complition status 3. Score)
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime> 
//ctime is used to retrieve date.
//fstream for file handling.
//cstdlib for clearing terminal after each iteration.
using namespace std;

//add() adds the task in local storage (data.txt or dailydata.txt) file.
void add(string filename, bool &status){
    
    fstream file(filename, ios::app); //ios::app and fstream for specifically appending the data inserted to file to avoid rewriting
    cout<<"Enter task: ";
    string task;
    getline(cin, task);
    file<<task<<"\n";
    file.close();

    if(filename == "dailydata.txt"){
        string line;
        vector <string> history;
        ifstream temp("metadata.txt");
        while(getline(temp, line)){
            history.push_back(line);
        }
        temp.close();
        ofstream temp2("metadata.txt");
        for(int i = 0; i < history.size(); i++){
            if(i == 1){
                temp2<<0<<"\n";
            }
            else{
                temp2<<history[i]<<"\n";
            }
        }
        status = false;
    }

    if(filename == "data.txt"){
        int day;
        cout<<"\nEnter number of days for deadline: ";
        cin>>day;
        while(day <= 0){
            cout<<"Enter valid input: ";
            cin>>day;
        }
        fstream temp("metadata.txt", ios::app);
        temp<<day<<"\n";
        temp.close();
    }

    system("cls"); //clears the terminal after each iteration or successful function call
}

//delete() function deletes any task within list with task number as input;
void Delete(string filename){
    ifstream file(filename); //ifstream for only reading the file and not writing anything
    cout<<"Enter task number to delete: ";
    int target; // Target is task's number (example: task number 3 or task number 8)
    cin>>target;
    while(target<=0){
        cout<<"Wrong input, enter valid input"<<endl<<": ";
        cin>>target;
    }
    vector <string> history;
    string line;
    
    if(filename == "data.txt"){
        vector <string> history2;
        ifstream temp("metadata.txt");
        while(getline(temp, line)){
            history2.push_back(line);
        }
        temp.close();
        ofstream temp2("metadata.txt"); //ofstream for writing (overwriting) task into file

        //second loop refills the metadata.txt with required update and changes
        for(int i = 0; i < history2.size() ; i++){
            if(i+1 != target + 3){
                temp2<<history2[i]<<"\n";
            }
        }
        temp2.close();
    }

    //First loop fills up vector
    while(getline(file, line)){
        history.push_back(line);
    }
    file.close();
    ofstream file2(filename); //ofstream for writing (overwriting) task into file
    //second loop refills the data.txt with required update and changes
    for(int i = 0; i < history.size() ; i++){
        if(i+1 != target){
            file2<<history[i]<<"\n";
        }
    }
    file2.close();
    system("cls");
}

//Modify() function modifies any task, we have to enter updated or completely new task as input;
//acts similar to delete() function with smaller chnages;
void edit(string filename){
    ifstream file(filename);
    int target;
    if(filename == "data.txt"){
        cout<<"Edit task - 1    Edit deadline - 2"<<endl;
        cin >> target;
    }
    else{
        target = 1;
    }
    
    if(target == 1){
        cout<<"Enter task number to edit: ";
        cin>>target;
        while(target<=0){
            cout<<"Wrong input, enter valid input"<<endl<<": ";
            cin>>target;
        }

        cout<<"Enter new task: ";
        string NewTask;
        cin.ignore(10, '\n'); //added cin.ignore() to remove cin's new line buffer
        getline(cin, NewTask); //this acts as primary getLine function for NewTask
        
        vector <string> history;
        string line;

        while(getline(file, line)){
            history.push_back(line); // Stores vector with file data
        }

        file.close();
        ofstream file2(filename);

        for(int i = 0; i < history.size() ; i++){
            if(i+1 != target){
                file2<<history[i]<<"\n";
            }
            else{
                file2<<NewTask<<"\n";
            }
        }
        file2.close();
        system("cls");
    }
    else{
        if(target == 2){
            cout<<"Enter task number: ";
            cin >> target;
            while(target <= 0){
                cout<<"Wrong input, enter valid input"<<endl<<": ";
                cin>>target;
            }
            int newdeadline;
            cout<<"Enter new deadline: ";
            cin>>newdeadline;
            cin.ignore(10, '\n');
            vector <string> history2;
            string line;
            ifstream filee("metadata.txt");
            while(getline(filee, line)){
                history2.push_back(line);
            }
            filee.close();
            ofstream temp("metadata.txt");

            for(int i = 0; i<history2.size(); i++){
                if(i+1 != target+3){
                    temp<<history2[i]<<"\n";
                }
                else{
                    temp<<newdeadline<<"\n";
                }
            }
        }
        else{
            cout<<"invalid input, enter valid input\n";
            edit(filename);
        }
    }
}

//Clearall() function clears the whole to-do list, just deletes all tasks.
void clearall(string filename){
    int confirm;
    int history[3];
    cout<<"1 - Yes / 0 - No"<<endl<<": ";
    cin>>confirm;
    if(confirm == 0){
        system("cls");
    }
    else{
        if(confirm == 1){
            ofstream file(filename);
            file << "";
            file.close();
            system("cls");

            if(filename == "data.txt"){
                ifstream temp("metadata.txt");
                for(int i = 0; i < 3; i++){
                    temp >> history[i];
                }
                temp.close();
                ofstream temp2("metadata.txt");
                for(int i = 0; i< 3; i++){
                    temp2 << history[i]<<"\n";
                }
            }
        }
        else{
            cout<<"Enter valid input";
            clearall(filename);
        }
    }
}

//print() function prints all the tasks in the list
void print(string filename){
    ifstream file(filename);
    int counter = 1; //simple counter to print task number
    string line, deadline;
    if(filename == "data.txt"){
        cout<<"                              Tasks\n";
        cout<<"-------------------------------------------------------------------\n";
    }
    else{
        cout<<"         Tasks"<<endl;
        cout<<"-------------------------"<<endl;
    }

    ifstream temp("metadata.txt");
    temp >> deadline >> deadline >> deadline; // storing date, status and score in deadline.
    while(getline(file, line)){
        if(counter != 0){
            if(filename == "data.txt"){
                temp >> deadline;
                int totalWidth = 60;
                int usedSpace = to_string(counter).length() + 2 + line.length() + 10; // Counter + ". " + line length + "Deadline: "
                int freespace = totalWidth - usedSpace;

                if (freespace < 0) freespace = 0; // Avoid negative spacing

                // Adjust formatting
                printf("%d. %s%*sDeadline: %s Days\n", counter, line.c_str(), freespace, "", deadline.c_str());
                // cout<<counter<<". "<<line<<"\t\tDeadline: "<<deadline<<endl;
            }
            else{
                cout<<counter<<". "<<line<<endl;
            }
        }
        counter++;
    }

    if(filename == "data.txt"){
        if(counter == 0 || counter == 1){
            cout<<"                         --- No tasks ---"<<endl;
        }
        cout<<"-------------------------------------------------------------------\n";
    }
    else{
        if(counter == 0 || counter == 1){
            cout<<"    --- No tasks ---"<<endl;
        }
        cout<<"-------------------------"<<endl;
    }
    file.close();
}

//Swapping() functions swaps 2 tasks (their position), 2 inputs are required (their task number);
void swapping(string filename){
    int t1, t2; //target 1 and target 2
    string line;
    cout<<"Enter task to swap: ";
    cin>>t1;
    while(t1<=0){
        cout<<"Wrong input, enter valid input"<<endl<<": ";
        cin>>t1;
    }
    cout<<"Enter task to swap with: ";
    cin>>t2;
    while(t2<=0 || t1 == t2){
        cout<<"Wrong input, enter valid input"<<endl<<": ";
        cin>>t2;
    }
    
    cin.ignore(10,'\n');

    ifstream file(filename);
    vector <string> history;

    while(getline(file, line)){
        history.push_back(line);
    }
    file.close();
    swap(history[t1-1], history[t2-1]);
    ofstream filee(filename);
    for(int i = 0; i< history.size(); i++){
        filee<<history[i]<<"\n";
    }
    filee.close();

    if(filename == "data.txt"){
        vector <string> history2;
        ifstream temp("metadata.txt");
        while(getline(temp, line)){
            history2.push_back(line);
        }
        temp.close();
        swap(history2[t1-1+3], history2[t2-1+3]);
        ofstream temp2("metadata.txt");
        for(int i = 0; i < history2.size(); i++){
            temp2 << history2[i]<<"\n";
        }
        temp2.close();
        cout<<"Everything works here"<<endl;
    }
    system("cls");
}
//Checks if file is present in the local directory of our code, if not then it creates it.
//Sets up the required files.
void setup(int Currentdate){
    //Cheacks if file is present in the local directory of our code
    // If "data.txt" and "dailydata.txt" is not present then it creates one for storing data
    ifstream file("data.txt"); 
    if(!file.is_open()){
        ofstream temp1("data.txt");
        temp1.close();
    }
    file.close();

    ifstream file3("dailydata.txt");
    if(!file3.is_open()){
        ofstream temp2("dailydata.txt");
        temp2.close();
    }
    file3.close();

    ifstream file2("metadata.txt");
    // consider it as constructor for files which works when file is not present in desired directory XD
    if(!file2.is_open()){
        ofstream NewFile("metadata.txt"); 
        NewFile<<Currentdate<<"\n"; // storing current date
        NewFile<<0<<"\n"; // storing task status
        NewFile<<0<<"\n"; // storing score
        NewFile.close();
    }
    file2.close();
}

// Prints out the task status.
void taskStatus(bool status){
    if(status == false){
        cout<<"Task status: Not completed\n"<<endl;
    }else{
        cout<<"Task status: Completed\n"<<endl;
    }
}

void UpdateDeadline(int currentdate){
    ifstream temp("metadata.txt");
    ifstream temp5("metadata.txt");
    vector <int> history;
    string line;
    int number;
    while(getline(temp5, line)){
        temp>>number;
        history.push_back(number);
    }
    temp5.close();
    temp.close();
    //number stores amount of days to be substracted
    number = currentdate - history[0];//history of 0 stores previous date
    if(number < 0){

    }
    ofstream temp2("metadata.txt");
    for(int i = 0; i < history.size(); i++){
        if(i>2){
            temp2 << history[i] - number<<"\n";
        }
        else{
            temp2 << history[i]<<"\n";
        }
    }
    temp2.close();
}

int main(){
    int score = 0;
    bool status = false;
    // Get the current time
    time_t now = time(0);
    // Convert to local time structure
    tm *localTime = localtime(&now);
    // Get the current hour
    // int currentHour = localTime->tm_hour; // Time ch kam nahi ahe sadhya as date will be enough.
    int Currentdate = localTime->tm_mday;
    int previousdate;
    int input = 0;
    string line;

    setup(Currentdate); // Check if the required files are available within the required directory or not, creates itself is not present.
    ifstream temp("metadata.txt");
    temp >> previousdate;
    temp >> line; // Just storing second line which is status here;
    temp >> score; // storing actual score
    temp.close();
    
    UpdateDeadline(Currentdate);
    // Check if current date is equals saved date, if not then it updates the saved date with current date and make the status as 0
    // Currentdate = Currentdate + (-5);
    if(previousdate != Currentdate){
        int Difference = Currentdate - previousdate;

        if(Difference <= 1){
        //This following if condition part changes status to false representating new day.
            if(Difference == -27 || Difference == -30 || Difference == -29 || Difference == -28 || Difference == 1){
                ofstream temp("metadata.txt");
                temp << Currentdate <<"\n"; //stores present date in file
                temp << 0 <<"\n"; // sets task status as 0 in file
                temp << score <<"\n"; // store score back in
                status = false;
                temp.close();
            }
            else{
                // This part executes when there's negative difference between current and previous date
                ofstream temp("metadata.txt");
                temp << Currentdate<<"\n"; //stores present date in file
                temp << 0 <<"\n"; // sets task status as 0 in file
                temp << 0 <<"\n"; // sets score back to zero as day gap is more than 1, losing all score.
                score = 0;
                status = false;
                temp.close();
            }
        }
        // This is losing part where you lose you all score as you have gap more than 1
        else{
            ofstream temp("metadata.txt");
            temp << Currentdate<<"\n"; //stores present date in file
            temp << 0 <<"\n"; // sets task status as 0 in file
            temp << 0 <<"\n"; // sets score back to zero as day gap is more than 1, losing all score.
            score = 0;
            status = false;
            temp.close();
        }
    }
    else{
        ifstream temp("metadata.txt");
        temp >> line >> line; // line variable stores second data i.e status (0/1);
        if(line == "1"){
            status = true;
        }
        temp.close();
    }

    while(true){
        system("cls");
        cout<<" - Select mode - \n"<<endl;
        cout<<"1 - Daily tasks\n2 - Normal tasks\n3 - Exit\n: ";
        cin>>input;

        // daily todo list
        if(input == 1){
            while(true){
                system("cls");
                cout<<"\nMiss a single and your score will be zero\n";
                cout<<"Your points: "<<score;
                cout<<"\n\nYour daily To-Do list:\n\n";

                print("dailydata.txt");

                taskStatus(status);

                cout<<"1 - Mark as done\n2 - Modify\n3 - Exit\n: ";
                cin>>input;

                // case 1 for sub branch 1
                if(input == 1){
                    if(status != true){
                        status = true;

                        vector <string> historyy;
                        string dm;
                        ifstream demp("metadata.txt");

                        while(getline(demp, dm)){
                            historyy.push_back(dm);
                        }
                        demp.close();

                        ifstream temp("metadata.txt");
                        temp >> line; // line stores current date;
                        temp.close();
                        ofstream temp2("metadata.txt");
                        temp2 << line<<"\n"; // stores back the date
                        temp2 << 1 <<"\n"; // stores the status

                        if(score == 0){
                            temp2 << 100 <<"\n"; 
                            score = 100; 
                            for(int i = 3; i < historyy.size(); i++){
                                temp2 << historyy[i]<<"\n";
                            }
                            temp2.close();
                        }
                        else{
                        score = score+(score/10)*8;
                        temp2 << score <<"\n";
                        for(int i = 3; i < historyy.size(); i++){
                            temp2 << historyy[i]<<"\n";
                        }
                        temp2.close();
                        }
                    }
                    else{
                        cout<<"All tasks are already marked as done!"<<endl;
                    }
                }
                if(input == 2){
                    while(input!=11){
                        system("cls");
                        cout<<"\nYour daily To-Do list:\n\n\n";
                        print("dailydata.txt");
                        taskStatus(status);
                        cout<<endl;
                        cout<<"1: Add task\n";
                        cout<<"2: Delete task\n";
                        cout<<"3: Edit task\n";
                        cout<<"4: Swap tasks\n";
                        cout<<"5: Clear all tasks\n";
                        cout<<"6: Exit\n";
                        cout<<": ";
                        cin>>input;
                        cin.ignore(10,'\n');

                        switch(input){
                            case 1:
                            add("dailydata.txt",status);
                            break;

                            case 2:
                            Delete("dailydata.txt");
                            break;

                            case 3:
                            edit("dailydata.txt");
                            break;

                            case 4:
                            swapping("dailydata.txt");
                            break;

                            case 5:
                            clearall("dailydata.txt");
                            break;

                            case 6:
                            //Confirmation, just in case someone press is accidently
                            cout<<"1 - Yes / 0 - No"<<endl<<": ";
                            cin>>input;
                            if(input == 0){
                                input = 7;
                            }
                            else{
                                if(input == 1){
                                    input = 11;
                                    system("cls");
                                    break;
                                }
                                else{
                                    cout<<"Wrong input, cant perform task";
                                }
                            }

                            default:
                            system("cls");
                            cout<<"Enter valid input"<<endl;
                            break;
                        }
                    }
                }
                if(input == 3){
                    cout<<"Confirmation"<<endl;
                    cout<<"1 - Yes      0 - No"<<endl;
                    cin>>input;
                    if(input == 1){
                        break;
                        system("cls");
                    }
                    else{
                        input == 10;
                        system("cls");
                    }
                }
                else{
                    system("cls");
                    cout<<"Enter valid input!"<<endl;
                }
            }
        }
        else{
            // Taste case 2 main
            if(input == 2){
                while(input!=11){
                system("cls");
                cout<<"\nYour friendly To-Do list:\n\n";
                print("data.txt");
                cout<<endl;
                cout<<"1: Add task\n";
                cout<<"2: Delete task\n";
                cout<<"3: Edit task\n";
                cout<<"4: Swap tasks\n";
                cout<<"5: Clear all tasks\n";
                cout<<"6: Exit\n";
                cout<<": ";
                cin>>input;
                cin.ignore(10,'\n');

                switch(input){
                    case 1:
                    add("data.txt", status);
                    break;

                    case 2:
                    Delete("data.txt");
                    break;

                    case 3:
                    edit("data.txt");
                    break;

                    case 4:
                    swapping("data.txt");
                    break;

                    case 5:
                    clearall("data.txt");
                    break;

                    case 6:
                    //Confirmation, just in case someone press is accidently
                    cout<<"1 - Yes / 0 - No"<<endl<<": ";
                    cin>>input;
                    if(input == 0){
                        input = 7;
                    }
                    else{
                        if(input == 1){
                            input = 11;
                            system("cls");
                            break;
                        }
                        else{
                            cout<<"Wrong input, cant perform task";
                        }
                    }

                    default:
                    system("cls");
                    cout<<"Enter valid input"<<endl;
                    break;
                    }
                }
                //--------------------------  
            }
            else{
                // Case 3 for main branch
                if(input == 3){
                    cout<<"Confirmation"<<endl;
                    cout<<"1 - Yes      0 - No"<<endl;
                    cin>>input;
                    if(input == 1){
                        break;
                    }
                    else{
                        input == 10;
                        system("cls");
                    }
                }
                else{
                    system("cls");
                    cout<<"Enter valid input!"<<endl;
                }
            }
        }
    }
}
//ignore the switch case complixity, I might work on it later to make it more simplified but not now :)
//Thanks for reading the code,
//This code can be more optimized and object oriented using classes and their instances i.e class ToDo, class Task etc