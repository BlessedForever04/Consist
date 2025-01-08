// "data.txt" stores long term tasks, "dailydata.txt" stores daily tasks.
// "metadata.txt" stores the information required to run this code (1. previous date 2. Task complition status 3. Score)
#include <iostream> // cin/cout and basic tasks
#include <fstream>  // <fstream> for file handling
#include <vector>   // just for using vectors
#include <cstdlib>  // For clearing terminal after each iteration
#include <ctime>    // <ctime> retrieves date information

//add() adds the task in local storage (data.txt or dailydata.txt) file, changes the task status to 0/false when new daily task is added and also inputs the deadline for normal tasks.
void add(std::string filename, bool &status){
    
    std::fstream file(filename, std::ios::app); //ios::app and fstream for specifically appending the data inserted to file to avoid rewriting
    std::cout<<"Enter task: ";
    std::string task;
    std::getline(std::cin, task);
    file<<task<<"\n";
    file.close();

    // If add() function is called for daily list purpose then this changes the task status after addition of task.
    if(filename == "dailydata.txt"){
        std::string line;
        std::vector <std::string> history;
        std::ifstream temp("metadata.txt");
        while(std::getline(temp, line)){
            history.push_back(line);
        }
        temp.close();
        std::ofstream temp2("metadata.txt");
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

    // if add() function is called for normal list puropose then it asks for user input for deadline for added task.
    if(filename == "data.txt"){
        int day;
        std::cout<<"\nEnter number of days for deadline: ";
        std::cin>>day;
        while(day <= 0){
            std::cout<<"Enter valid input: ";
            std::cin>>day;
        }
        std::fstream temp("metadata.txt", std::ios::app);
        temp<<day<<"\n";
        temp.close();
    }
    system("cls"); //clears the terminal after each iteration or successful function call
}

//delete() function deletes any task within list with task number as input.
void Delete(std::string filename){
    std::ifstream file(filename); //ifstream for only reading the file and not writing anything
    std::cout<<"Enter task number to delete: ";
    int target; // Target is tasks number (example: task number 3 or task number 8)
    std::cin>>target;
    while(target<=0){ // Just normal validation as target cannot be 0 or less than it.
        std::cout<<"Wrong input, enter valid input"<<std::endl<<": ";
        std::cin>>target;
    }
    std::vector <std::string> history; // vector History stores the all information in required file
    std::string line; // string line for storing each line at a time.
    
    // if Delete() function is called for normal list then it also deletes the associated deadline to the task.
    if(filename == "data.txt"){
        std::vector <std::string> history2;
        std::ifstream temp("metadata.txt");
        while(std::getline(temp, line)){
            history2.push_back(line);
        }
        temp.close();
        std::ofstream temp2("metadata.txt"); //ofstream for writing (overwriting) task into file

        //second loop refills the metadata.txt with required update and changes
        for(int i = 0; i < history2.size() ; i++){
            if(i+1 != target + 3){
                temp2<<history2[i]<<"\n";
            }
        }
        temp2.close();
    }

    //First loop fills up vector
    while(std::getline(file, line)){
        history.push_back(line);
    }
    file.close();
    std::ofstream file2(filename); //ofstream for writing (overwriting) task into file
    //second loop refills the data.txt with required update and changes
    for(int i = 0; i < history.size() ; i++){
        if(i+1 != target){
            file2<<history[i]<<"\n";
        }
    }
    file2.close();
    system("cls");
}

//edit() function modifies any task. We have to enter updated or completely new task as input also allows chaning deadline
//acts similar to delete() function with smaller chnages.
void edit(std::string filename){
    std::ifstream file(filename);
    int target;
    if(filename == "data.txt"){
        std::cout<<"Edit task - 1    Edit deadline - 2"<<std::endl;
        std::cin >> target;
    }
    else{
        target = 1;
    }
    // target = 1 signifies edit of tasks
    if(target == 1){
        std::cout<<"Enter task number to edit: ";
        std::cin>>target;
        while(target<=0){
            std::cout<<"Wrong input, enter valid input"<<std::endl<<": ";
            std::cin>>target;
        }

        std::cout<<"Enter new task: ";
        std::string NewTask;
        std::cin.ignore(10, '\n'); //added cin.ignore() to remove cin's new line buffer
        std::getline(std::cin, NewTask); //this acts as primary getLine function for NewTask
        
        std::vector <std::string> history;
        std::string line;

        while(std::getline(file, line)){
            history.push_back(line); // Stores vector with file data
        }

        file.close();
        std::ofstream file2(filename);

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
        // target = 1 signifies edit of deadlines.
        if(target == 2){
            std::cout<<"Enter task number: ";
            std::cin >> target;
            while(target <= 0){
                std::cout<<"Wrong input, enter valid input"<<std::endl<<": ";
                std::cin>>target;
            }
            int newdeadline;
            std::cout<<"Enter new deadline: ";
            std::cin>>newdeadline;
            std::cin.ignore(10, '\n');
            std::vector <std::string> history2;
            std::string line;
            std::ifstream filee("metadata.txt");
            while(std::getline(filee, line)){
                history2.push_back(line);
            }
            filee.close();
            std::ofstream temp("metadata.txt");

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
            std::cout<<"invalid input, enter valid input\n";
            edit(filename);
        }
    }
}

//Clearall() function clears the whole to-do list, just deletes all tasks along with deadlines allocated to tasks.
void clearall(std::string filename){
    int confirm;
    int history[3];
    std::cout<<"1 - Yes / 0 - No"<<std::endl<<": ";
    std::cin>>confirm;
    if(confirm == 0){
        system("cls");
    }
    else{
        if(confirm == 1){
            std::ofstream file(filename);
            file << "";
            file.close();
            system("cls");

            // Deleting all deadlines.
            if(filename == "data.txt"){
                std::ifstream temp("metadata.txt");
                for(int i = 0; i < 3; i++){
                    temp >> history[i];
                }
                temp.close();
                std::ofstream temp2("metadata.txt");
                for(int i = 0; i< 3; i++){
                    temp2 << history[i]<<"\n";
                }
            }
        }
        else{
            std::cout<<"Enter valid input";
            clearall(filename);
        }
    }
}

int totalCount(){
    std::string line, deadLine;
    std::ifstream task("data.txt"), deadlines("metadata.txt");
    deadlines >> line >> line >> line;// storing previous date, task status and score.

    int stored = 0; // just stores the previous used space to compare the next one
    int used; 
    while(std::getline(task, line) && std::getline(deadlines, deadLine)){
        used = 4 + line.length() + 10;// 2 (counter) + 2 (. ) + lineLength + 10("deadline: ") + deadlineLength;
        if(used > stored){
            stored = used;
        }
    }
    task.close();
    deadlines.close();
    if(stored == 0){
        return 50;
    }
    else{
        return stored + 10;
    }
}

//print() function prints all the tasks in the list and their deadlines.
void print(std::string filename){
    std::ifstream file(filename);
    int counter = 1; //simple counter to print task number
    std::string line, deadline;
    int totalWidth = totalCount();
    if(filename == "data.txt"){
        for(int i = 1; i <= totalWidth/2-2; i++){
            std::cout<<" ";
        }
        std::cout<<"Tasks\n";

        for(int i = 1; i != totalWidth+8; i++){
            std::cout<<"-";
        }
        std::cout<<"\n";
    }
    else{
        std::cout<<"         Tasks"<<std::endl;
        std::cout<<"-------------------------"<<std::endl;
    }

    std::ifstream temp("metadata.txt");
    temp >> deadline >> deadline >> deadline; // storing date, status and score in deadline.
    while(std::getline(file, line)){
        if(counter != 0){
            if(filename == "data.txt"){
                temp >> deadline;
                int usedSpace = std::to_string(counter).length() + 2 + line.length() + 10; // Counter + ". " + line length + "Deadline: "
                int freespace = totalWidth - usedSpace;

                if (freespace < 0) freespace = 0; // Avoid negative spacing

                // Adjust formatting
                printf("%d. %s%*sDeadline: %s Days\n", counter, line.c_str(), freespace, "", deadline.c_str());
                // cout<<counter<<". "<<line<<"\t\tDeadline: "<<deadline<<endl;
            }
            else{
                std::cout<<counter<<". "<<line<<std::endl;
            }
        }
        counter++;
    }

    if(filename == "data.txt"){
        if(counter == 0 || counter == 1){
            std::cout<<"                                 --- No tasks ---"<<std::endl;
        }
        for(int i = 1; i != totalWidth+8; i++){
            std::cout<<"-";
        }
        std::cout<<"\n";
    }
    else{
        if(counter == 0 || counter == 1){
            std::cout<<"    --- No tasks ---"<<std::endl;
        }
        std::cout<<"-------------------------"<<std::endl;
    }
    file.close();
}

//Swapping() functions swaps 2 tasks (their position) and their deadlines, 2 inputs are required (their task number);
void swapping(std::string filename){
    int t1, t2; //target 1 and target 2
    std::string line;
    std::cout<<"Enter task to swap: ";
    std::cin>>t1;
    while(t1<=0){
        std::cout<<"Wrong input, enter valid input"<<std::endl<<": ";
        std::cin>>t1;
    }
    std::cout<<"Enter task to swap with: ";
    std::cin>>t2;
    while(t2<=0 || t1 == t2){
        std::cout<<"Wrong input, enter valid input"<<std::endl<<": ";
        std::cin>>t2;
    }
    
    std::cin.ignore(10,'\n');

    std::ifstream file(filename);
    std::vector <std::string> history;

    while(std::getline(file, line)){
        history.push_back(line);
    }
    file.close();
    swap(history[t1-1], history[t2-1]);
    std::ofstream filee(filename);
    for(int i = 0; i< history.size(); i++){
        filee<<history[i]<<"\n";
    }
    filee.close();

    if(filename == "data.txt"){
        std::vector <std::string> history2;
        std::ifstream temp("metadata.txt");
        while(std::getline(temp, line)){
            history2.push_back(line);
        }
        temp.close();
        swap(history2[t1-1+3], history2[t2-1+3]);
        std::ofstream temp2("metadata.txt");
        for(int i = 0; i < history2.size(); i++){
            temp2 << history2[i]<<"\n";
        }
        temp2.close();
        std::cout<<"Everything works here"<<std::endl;
    }
    system("cls");
}
//Checks if files are present in the local directory of our code, if not then it creates them.
//Sets up the required files
void setup(int Currentdate){
    std::ifstream file("data.txt"); 
    if(!file.is_open()){
        std::ofstream temp1("data.txt");
        temp1.close();
    }
    file.close();

    std::ifstream file3("dailydata.txt");
    if(!file3.is_open()){
        std::ofstream temp2("dailydata.txt");
        temp2.close();
    }
    file3.close();

    std::ifstream file2("metadata.txt");
    // consider it as constructor for files which works when file is not present in desired directory XD
    if(!file2.is_open()){
        std::ofstream NewFile("metadata.txt"); 
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
        std::cout<<"Task status: Not completed\n"<<std::endl;
    }else{
        std::cout<<"Task status: Completed\n"<<std::endl;
    }
}

// UpdateDeadline() function updates deadlines everyday when code is run daily, it's like bootup process which occures as you run the code.
// making shortcut keeping it as startup app will make it automatic for exe to run everyday (obviously only if you open laptop/pc everyday).
void UpdateDeadline(int currentdate){
    std::ifstream temp("metadata.txt");
    std::ifstream temp5("metadata.txt");
    std::vector <int> history;
    std::string line;
    int number;
    while(std::getline(temp5, line)){
        temp>>number;
        history.push_back(number);
    }
    temp5.close();
    temp.close();
    //number stores amount of days to be substracted
    number = currentdate - history[0];//history of 0 stores previous date
    if(number < 0){

    }
    std::ofstream temp2("metadata.txt");
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
    int Currentdate = localTime->tm_mday;
    int previousdate;
    int input = 0;
    std::string line;

    setup(Currentdate); // Check if the required files are available within the required directory or not, creates itself is not present.
    std::ifstream temp("metadata.txt");
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
                std::ofstream temp("metadata.txt");
                temp << Currentdate <<"\n"; //stores present date in file
                temp << 0 <<"\n"; // sets task status as 0 in file
                temp << score <<"\n"; // store score back in
                status = false;
                temp.close();
            }
            else{
                // This part executes when there's negative difference between current and previous date
                std::ofstream temp("metadata.txt");
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
            std::ofstream temp("metadata.txt");
            temp << Currentdate<<"\n"; //stores present date in file
            temp << 0 <<"\n"; // sets task status as 0 in file
            temp << 0 <<"\n"; // sets score back to zero as day gap is more than 1, losing all score.
            score = 0;
            status = false;
            temp.close();
        }
    }
    else{
        std::ifstream temp("metadata.txt");
        temp >> line >> line; // line variable stores second data i.e status (0/1);
        if(line == "1"){
            status = true;
        }
        temp.close();
    }

    while(true){
        system("cls");
        std::cout<<" - Select mode - \n"<<std::endl;
        std::cout<<"1 - Daily tasks\n2 - Normal tasks\n3 - Exit\n: ";
        std::cin>>input;

        // daily todo list
        if(input == 1){
            while(true){
                system("cls");
                std::cout<<"\nMiss a single and your score will be zero\n";
                std::cout<<"Your points: "<<score;
                std::cout<<"\n\nYour daily To-Do list:\n\n";

                print("dailydata.txt");

                taskStatus(status);

                std::cout<<"1 - Mark as done\n2 - Modify\n3 - Exit\n: ";
                std::cin>>input;

                // case 1 for sub branch 1
                if(input == 1){
                    if(status != true){
                        status = true;

                        std::vector <std::string> historyy;
                        std::string dm;
                        std::ifstream demp("metadata.txt");

                        while(std::getline(demp, dm)){
                            historyy.push_back(dm);
                        }
                        demp.close();

                        std::ifstream temp("metadata.txt");
                        temp >> line; // line stores current date;
                        temp.close();
                        std::ofstream temp2("metadata.txt");
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
                        std::cout<<"All tasks are already marked as done!"<<std::endl;
                    }
                }
                if(input == 2){
                    while(input!=11){
                        system("cls");
                        std::cout<<"\nYour daily To-Do list:\n\n\n";
                        print("dailydata.txt");
                        taskStatus(status);
                        std::cout<<std::endl;
                        std::cout<<"1: Add task\n";
                        std::cout<<"2: Delete task\n";
                        std::cout<<"3: Edit task\n";
                        std::cout<<"4: Swap tasks\n";
                        std::cout<<"5: Clear all tasks\n";
                        std::cout<<"6: Exit\n";
                        std::cout<<": ";
                        std::cin>>input;
                        std::cin.ignore(10,'\n');

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
                            std::cout<<"1 - Yes / 0 - No"<<std::endl<<": ";
                            std::cin>>input;
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
                                    std::cout<<"Wrong input, cant perform task";
                                }
                            }

                            default:
                            system("cls");
                            std::cout<<"Enter valid input"<<std::endl;
                            break;
                        }
                    }
                }
                if(input == 3){
                    std::cout<<"Confirmation"<<std::endl;
                    std::cout<<"1 - Yes      0 - No"<<std::endl;
                    std::cin>>input;
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
                    std::cout<<"Enter valid input!"<<std::endl;
                }
            }
        }
        else{
            // Taste case 2 main
            if(input == 2){
                while(input!=11){
                system("cls");
                std::cout<<"\nYour friendly To-Do list:\n\n";
                print("data.txt");
                std::cout<<std::endl;
                std::cout<<"1: Add task\n";
                std::cout<<"2: Delete task\n";
                std::cout<<"3: Edit task\n";
                std::cout<<"4: Swap tasks\n";
                std::cout<<"5: Clear all tasks\n";
                std::cout<<"6: Exit\n";
                std::cout<<": ";
                std::cin>>input;
                std::cin.ignore(10,'\n');

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
                    std::cout<<"1 - Yes / 0 - No"<<std::endl<<": ";
                    std::cin>>input;
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
                            std::cout<<"Wrong input, cant perform task";
                        }
                    }

                    default:
                    system("cls");
                    std::cout<<"Enter valid input"<<std::endl;
                    break;
                    }
                }
                //--------------------------  
            }
            else{
                // Case 3 for main branch
                if(input == 3){
                    std::cout<<"Confirmation"<<std::endl;
                    std::cout<<"1 - Yes      0 - No"<<std::endl;
                    std::cin>>input;
                    if(input == 1){
                        return 0;
                    }
                    else{
                        input == 10;
                        system("cls");
                    }
                }
                else{
                    system("cls");
                    std::cout<<"Enter valid input!"<<std::endl;
                }
            }
        }
    }
}
//ignore the switch case complixity, I might work on it later to make it more simplified but not now :)
//Thanks for reading the code,
//This code can be more optimized and object oriented using classes and their instances i.e class ToDo, class Task etc