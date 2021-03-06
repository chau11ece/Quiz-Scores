/******************************************************************************

    Author: tchau@esilicon.com

*******************************************************************************/

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

void clear_input()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

class Contest
{
public:
    Contest() : m_scores(0)
    {

    }

    void init();
    void define();
    void display();

    //friend std::istream& operator >>(std::istream& ins, Contest &c);
    //friend std::ostream& operator <<(std::ostream& outs, const Contest &c);
    void processQuizFile(std::ifstream& in_stream);
    bool doAgain();

private:
    //int m_roll;
    float m_scores;
    char m_name[200];
    char m_oneline[500];
    char m_ans;
};

/*
std::istream& operator >>(std::istream& ins, Contest &c)
{
    return ins;
}

std::ostream& operator <<(std::ostream& outs, const Contest &c)
{
    return outs;
}
*/

void  Contest::define()
{

    ifstream fin;
    //ofstream fout;

    fin.open("ques.txt");

    if (fin.fail())
    {
        cout << "Input file opening failed.\n";
        exit(1);
    }

    processQuizFile(fin);

    fin.close();
}

void Contest::processQuizFile(std::ifstream& in_stream)
{
    char next;
    //in_stream.get(next);
    int line = 0;

    while(!in_stream.eof())
    {

        /// Check correct ans

        if (line == 5)
        {
            in_stream.get(next);
            in_stream.ignore(256,'\n');   // ignore until space
            //cout << "test get ->" << next << endl;     // answer

            do
            {
                cout << "\nans:";
                cin >> m_ans;
                clear_input();
                cout << "'a', 'b', 'c' or 'd' silly!";
            } while (m_ans != 'a' && m_ans != 'b' && m_ans != 'c' && m_ans != 'd');

            if(m_ans == next)
            {
                m_scores += 5;
                cout<<" * Correct ans.\n\n";
            }
            else
            {
                (m_scores > 0) ? m_scores -= 2.5 : m_scores = 0;
                cout<<" # Wrong ans.\n\n";
            }

            line = -1;
        }
        else
        {
            in_stream.getline(m_oneline,500);
            cout << m_oneline << endl;
            //cout << "test getline ->" << m_oneline << endl;
        }

        line++;
    }
}

void Contest::init()
{
    std::string stdName;
    cout << "\t\t   Examinee Name:\t";
    getline(cin, stdName);
    std::cin.ignore(32767, '\n');
}

void Contest::display()
{
    cout << "\n **Result:\n";
    cout << "\t" << m_name << " you got total " << m_scores << " marks,out of 50.\n";
}

char getPlayerChoice()
{
    std::cout << "\t*5 marks per Ques(half negative marking for wrong ans)";
    std::cout << "\n\n\tselect your choice:\n";
    std::cout << "(s) for start exam, or (q) for quit the exam: ";
    char choice;
    do
    {
        std::cin >> choice;
    }
    while (choice != 's' && choice != 'q');

    return choice;
}

bool Contest::doAgain()
{
    char ch;
    do
    {
        cout << "Would u like to take the exam again? (y/n)";
        cin >> ch;
    } while ((ch != 'y' && ch != 'n'));

    /// True if ans =  'y'
    return (ch == 'y');
}

int main()
{
    Contest test;

    do
    {
        system("CLS");
        cout<<"      \t\t~~~*** QUIZ Contest***~~~\t      Total Marks:50\n\n";
        test.init();

        char c = getPlayerChoice();
        switch(c)
        {
        case 's':
            test.define();
            test.display();
            break;
        case 'q':
            cout << "Thanks for taking the quiz.\n";
            exit(1);
        default:
            cout<<"invalid choice!";
        }

    } while (test.doAgain());


    return 0;
}
