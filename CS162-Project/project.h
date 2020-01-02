#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED
#include <iostream>
#include <fstream> // file processing
#include <vector>
#include <cstdlib> //for random and clear console
#include <iomanip> // format result
#include <sstream> // split the information
#include <ctime>
#include <locale>
#include <cstdio>
using namespace std;
struct QuestionInfo
    {
        string tag;
        int category;
        int level;
    };
struct Question
{
    QuestionInfo info;
    vector <string> question;
    string answer;
};
string input;
QuestionInfo sI;
Question sQ;
int ASK;
//FUNCTIONS AND VECTORS AND INITIALIZE :
//1)Opening :
void Opening();
//2)Ending :
void Ending();
//3)play game:
void playGame();
//4)Clear console :
void clearConsole();
//5)Normalize answer :
void removeSpaces(string&);
string lowcase(string);
string normalize (string);
//6) Pick up 1 random number "i" in [1;100]
int pick1i ();
//7) Initialize size of the test question array in main() SIZE=10 ;
const int SIZE =5 ;
int GatherSIZE[SIZE];
int gatherSIZE(int a[]);
//8) Split and return info  :
QuestionInfo splitInfo (string);
//9) Split and return question :
void splitQuest(ifstream&);
//10) Create a vector with all questions :
vector <Question> allQuest;
void create_allQuest (ifstream&);
//11) Create a array with SIZE questions :
Question testingQuest[SIZE];
int choose_category ();
vector <Question> vec_category;
void create_vec_category(int);
int choose_level();
vector <Question> vec_level;
void create_vec_level(int);
void create_testingQuest();
//12) Create an array to store the correct answers :
string correctAnswer [SIZE];
void create_correctAnswer();
//13) Create an array to store the user's answers :
string userAnswer [SIZE];
//14)asking and display the question ,return the answer as string data :
void Ask_and_Answer ();
//15) checking functions (pass 2 array in and compare as string data ):
//return the numbers of correct answer ;
int checking ();
//16) convert category :
int convertCategory (string);
string changeCategory(int);
//17)convert level :
int convertLevel(string);
string changeLevel(int);
//18)display the question:
void displayQuest(int);
//19)display the info of the question:
void displayInfo(int);
//20)print result of the test :
vector<int>urA;
void see_result();
void result();
void post_result();
//21) ask for playing again ?
int YorN();
//25)) Create additional Question
void Create_ADQ();
void Category();
void Level();
//26)) delete question
void DellQuest();
vector<Question> delQuest;
void get_delQuest(ifstream&);
void del_process();
void print_process(ofstream&);
//
void Choose_to_play();
int User_Choice();
//******************************************************/
//                                                      //
#endif // TEST_H_INCLUDED
