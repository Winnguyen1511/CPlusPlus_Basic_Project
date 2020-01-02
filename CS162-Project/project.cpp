#include "project.h"
//MAIN FUNCTION://
int main()
{
    Opening();
    clearConsole();
    srand(time(0));
    ifstream inputData;
    inputData.open("database.txt");
    create_allQuest(inputData);
    Choose_to_play();
    Ending();
}
//****************************************************//
// SUBFUNCTION://
void Opening()
{
    string enter;
    cout<<"***\tWELLCOME TO QUIZME\t***\n";
    cout<<"Press Enter to go to the menu.....";
    getline(cin,enter);
}
void Ending()
{
    cout<<"**\tTHANKS FOR USING QUIZME\t**";
}
void see_result()
{
    string sR;
    cout<<"\tQUIZ FINISHED !!!\n";
    cout<<"Press Enter to see your result....";
    getline(cin,sR);
}
void post_result()
{
    string ch;
    getline(cin,ch);
}
void removeSpaces(string& s)
{
    size_t p = s.find_first_not_of(" \t");
    s.erase(0, p);
    p = s.find_last_not_of(" \t");
    if (string::npos != p)
    s.erase(p+1);
}
string lowcase(string s)
{
    for (int i=0 ;i < s.length();i++)
    {
        s[i]=tolower(s[i]);
    }
    return s;
}
string normalize(string s)
{
    removeSpaces(s);
    s=lowcase(s);
    return s;
}
void playGame()
{
    while (true)
    {
        create_testingQuest();
        Ask_and_Answer();
        see_result();
        clearConsole();
        result();
        post_result();
        clearConsole();
        ASK=YorN();
        if ( ASK==1 ) continue;
        else break;
    }
}
QuestionInfo splitInfo (string input)
{
    string tag, category, level;
    QuestionInfo sI;
    istringstream iss(input);
    getline(iss,tag,'#');
    getline(iss,category,'#');
    getline(iss,level,'#');
    sI.tag=tag;
    sI.category=convertCategory(category);
    sI.level=convertLevel(level);
    return sI;
}
int convertCategory(string category)
{
    if (category == "general") return 1;
    else if (category == "science") return 2;
    else if (category == "geography" ) return 3;
    else if (category == "sport" ) return 4;
}
int convertLevel(string level)
{
    if (level == "easy") return 1;
    else if (level == "medium") return 2;
    else if (level == "hard" ) return 3;
}
void splitQuest(ifstream &in)
{
    while (getline(in,input))
        {
            if (input == "#") break;
            sQ.question.push_back(input);
        }
}
void create_allQuest (ifstream&inputData)
{
    while (inputData>>input)
    {
        sI=splitInfo(input);
        sQ.info=sI;
        splitQuest(inputData);
        getline(inputData,input);
        sQ.answer=normalize(input);
        allQuest.push_back(sQ);
        sQ.question.clear();
    }
}
int choose_category ()
{
    int c;
    cout <<"**** Please choose the category ****"<<endl;
    cout<<" 0) All category.\n 1) General.\n 2) Science.\n 3) Geography.\n 4) Sport."<<endl;
    cout<<"Your choice : ";
    cin>>c;
    clearConsole();
    return c;
}
int choose_level ()
{
    int c;
    cout <<"**** Please choose the level **** "<<endl;
    cout<<" 0) All level.\n 1) Easy.\n 2) Medium.\n 3) Hard."<<endl;
    cout<<"Your choice : ";
    cin>>c;
    cin.ignore();
    clearConsole();
    return c;
}
void create_vec_category(int cate)
{
    string userCategory;
    if (cate != 0)
    {
        for (int i=0 ; i<allQuest.size();i++)
        {
            if ( allQuest[i].info.category == cate ) vec_category.push_back(allQuest[i]);
        }
    }
    else
    {
        for (int i=0 ; i<allQuest.size();i++)
        {
            vec_category.push_back(allQuest[i]);
        }
    }
}
void create_vec_level(int lev)
{
    string userLevel;
    if (lev != 0 )
    {
        for (int i=0;i<vec_category.size();i++)
        {
            if (vec_category[i].info.level == lev ) vec_level.push_back(vec_category[i]);
        }
    }
    else
    {
        for (int i=0;i<vec_category.size();i++)
        {
            vec_level.push_back(vec_category[i]);
        }
    }
}
int gatherSIZE(int a[])
{
    a[0]=pick1i();
    for (int i=1;i<SIZE ;i++)
    {
        a[i]=pick1i();
        if (a[i] == a[i-1] ) continue;
    }
}
int pick1i ()
{
    const int Max=vec_level.size(),Min=0;
    int num = (rand()%(Max-Min))+Min;
    return num;
}
void create_testingQuest()
{
    int cate,lev;
    cate=choose_category();
    lev=choose_level();
    create_vec_category(cate);
    create_vec_level(lev);
    vec_category.clear();
    gatherSIZE(GatherSIZE);
    for (int i=0;i<SIZE;i++)
    {
        testingQuest[i] = vec_level[GatherSIZE[i]];
    }
    vec_level.clear();
}
void displayQuest(int num)
{
    for (int i=0;i<testingQuest[num].question.size();i++)
    {
        cout<<testingQuest[num].question[i]<<endl;
    }
}
void Ask_and_Answer()
{
    string a;
    for (int i=0;i<SIZE;i++)
    {
        displayInfo(i);
        displayQuest(i);
        cout<<endl;
        getline(cin,a);
        userAnswer[i]=normalize(a);
        clearConsole();
    }
}
void displayInfo(int num)
{
    cout<<"#"<<testingQuest[num].info.tag
    <<" // Category: "<<changeCategory(testingQuest[num].info.category)
    <<" // Level: "<<changeLevel(testingQuest[num].info.level);
    cout<<endl;
}
string changeCategory(int category)
{
    if (category == 1) return "general";
    else if (category == 2) return "science";
    else if (category == 3 ) return "geography";
    else if (category == 4 ) return "sport";
}
string changeLevel(int level)
{
    if (level == 1) return "easy";
    else if (level == 2) return "medium";
    else if (level == 3 ) return "hard";
}
int checking()
{
    int numof_correct=0;
    for (int i=0;i<SIZE;i++)
    {
        if (testingQuest[i].answer == userAnswer[i]) numof_correct++;
        else urA.push_back(i);
    }
    return numof_correct;
}
void result()
{
    cout<<"***************RESULT***************\n";
    cout<<"Your score :"<<checking()<<"/"<<SIZE<<endl;
    cout<<"You failed in : "<<endl;
    for (int i=0;i<urA.size();i++)
    {
        cout<<"#"<<testingQuest[urA[i]].info.tag;
        displayQuest(urA[i]);
        cout<<"your answer is :"<<userAnswer[urA[i]]<<endl;
        cout<<"Correct answer is :"<<testingQuest[urA[i]].answer;
        cout<<endl<<endl;
    }
    cout<<"************************************"<<endl;
    urA.clear();
}
void clearConsole()
{
    if (system("CLS"))
        system("clear");
}
int YorN()
{
    char ask;
    while (true)
    {
        cout<<"Do you want to do Quiz again ? (Y/N) ";
        cin>>ask;
        clearConsole();
        if (ask == 'Y' || ask == 'y')
        {
            return 1;
            break;
        }
        else if (ask == 'N' || ask == 'n')
        {
            return 0;
            break;
        }
        else continue;
    }
}
void Create_ADQ()
{
    ofstream addQuest;
    addQuest.open("database.txt",ios::in | ios::out| ios::app | ios::out | ios::ate);
    cout<<"Enter the #tag: ";
    cin>>sI.tag;
    Category();
    cin>>sI.category;
    Level();
    cin>>sI.level;
    string Tagvalue = sI.tag.c_str();
    addQuest<<Tagvalue<<"#"<<changeCategory(sI.category)
    <<"#"<<changeLevel(sI.level)<<endl;
    cin.ignore();
    cout<<"Enter your Question: "<<endl;
    while (true)
    {
        cout<<">";
        getline(cin,input);
        if(input == "") break;
        sQ.question.push_back(input);
    }
    for (int i=0;i<sQ.question.size();i++)
    {
        addQuest<<sQ.question[i]<<endl;
    }
    sQ.question.clear();
    addQuest<<"#"<<endl;
    cout<<"Enter the answer: ";
    getline(cin,input);
    addQuest<<input;
    addQuest<<"\n";
    clearConsole();
}
void Choose_to_play()
{
    while (true)
    {
        int a=User_Choice();
        clearConsole();
        if (a == 1) playGame();
        else if( a == 2) Create_ADQ();
        else if (a == 3) DellQuest();
        else break;
    }
}
int User_Choice()
{
    int c;
    cout<<"QUIZME MENU"<<endl;
    cout<<"1)Do a Quiz"<<endl;
    cout<<"2)Add a question to the database"<<endl;
    cout<<"3)Delete a question from the database "<<endl;
    cout<<"0)Quit the program"<<endl;
    cout<<"Enter your choice: ";
    while (true)
    {
        cin>>c;
        if (c !=0&& c !=1&& c !=2&& c !=3) continue;
        else break;
    }
    return c;
}
void Category()
{
    cout<<"Choose the category : 1) general 2)science 3)geography 4)sport ."<<endl;
    cout<<">";
}
void Level()
{
    cout<<"Choose the level : 1) easy 2)medium 3)hard ."<<endl;
    cout<<">";
}
void DellQuest()
{
    ifstream inputData;
    inputData.open("database.txt");
    get_delQuest(inputData);
    del_process();
    inputData.clear();
    inputData.close();
    ofstream outputData;
    outputData.open("database.txt");
    print_process(outputData);
    outputData.close();
    clearConsole();
    delQuest.clear();
}
void get_delQuest(ifstream&inputData)
{
    while (inputData>>input)
    {
        sI=splitInfo(input);
        sQ.info=sI;
        splitQuest(inputData);
        getline(inputData,input);
        sQ.answer=input;
        delQuest.push_back(sQ);
        sQ.question.clear();
    }
}
void del_process()
{
    string t;
    cout<<"enter #tag to delete : ";
    cin>>t;
    cin.ignore();
    for (int i=0;i<delQuest.size();i++)
    {
        if (t == delQuest[i].info.tag)
        {
            cout<<delQuest[i].info.tag<<"#"
            <<changeCategory(delQuest[i].info.category)<<"#"
            <<changeLevel(delQuest[i].info.level)<<endl;
            for (int a=0;a<delQuest[i].question.size();a++)
            {
                cout<<delQuest[i].question[a]<<endl;
            }
            cout<<"#"<<endl;
            cout<<delQuest[i].answer<<endl;
            cout<<"Press Enter to delete... ";
            getline(cin,input);
            delQuest.erase(delQuest.begin()+i);
        }
    }
}
void print_process(ofstream&outputData)
{
    for(int a=0;a<delQuest.size();a++)
    {
        string tagValue=delQuest[a].info.tag.c_str();
        outputData<<tagValue<<"#"
        <<changeCategory(delQuest[a].info.category)<<"#"
        <<changeLevel(delQuest[a].info.level);
        for (int b =0;b<delQuest[a].question.size();b++)
        {
            outputData<<delQuest[a].question[b]<<endl;
        }
        outputData<<"#"<<endl;
        outputData<<delQuest[a].answer<<endl;
    }
}
