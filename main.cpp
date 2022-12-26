#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "stack.h"
#include "node.h"
#include "imageProcessing.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

string post_exp(string);
string pre_exp(string);
string sol_exp(string);
int GalaxyImageProcessing(string);
bool ValidExpressionCheck(string exp);
int prec(char);



class checknode
{
public:
    char val;
    checknode* next;
    checknode(char ch)
    {
        val = ch;
        next = NULL;
    }
    checknode()
    {
        next = NULL;
        val = '\0';
    }

};
class check
{
public:
    checknode* head;
    check()
    {
        head = NULL;
    }
    void push(char ch)
    {
        checknode* n = new checknode(ch);
        n->next = head;
        head = n;
    }
    bool pop()
    {
        if (head == NULL)
        {
            cout << "ERROR" << endl;
            return false;
        }
        else
        {

            checknode* n = new checknode('\0');
            n = head;
            head = head->next;
            delete n;
            return true;
        }
    }

};


int main()
{
    
    stack obj;
  
    fstream file;
    fstream resultantFile;
    file.open("C:/Users/muham/source/repos/DataAssignment2/DataAssignment2/Test_files/Test-1.txt", ios::in);//read
    resultantFile.open("C:/Users/muham/source/repos/DataAssignment2/DataAssignment2/Output_files/ResultantFile.txt", ios::app);
    bool error = false;
    bool emptyline = false;
    int check = 0;
    if (file.is_open())
    {
        char letter;
        while (!file.eof())
        {
            string word;
            string imageFile;
            string expression;
            //file >> word;
            getline(file, word);
            for (int i = 0; i < word.length();i++)
            {
                string tag;
                string imageFile;
                if (int(word[i]) == 124)
                {
                    tag += word[i];
                    
                    ++i;
                    while (int(word[i]) != 124)
                    {
                        tag += word[i];
                        i++;
                    }
                    tag += word[i];
                    
                    //cout << tag << endl;

                    if (tag == "|tab|")
                    {
                        resultantFile << "\t";
                    }
                    if (tag == "|src|")
                    {
                        ++i;
                        while (int(word[i]) != 124)
                        {
                            if (int(word[i]) != 32)
                            {
                                imageFile += word[i];
                            }
                            i++;
                        }
                        i--;

                        int num = GalaxyImageProcessing(imageFile+".png");

                        resultantFile << num;
                    }
                    if (tag == "|post_exp|")
                    {
                        ++i;
                        while (int(word[i]) != 124)
                        {
                            if (int(word[i]) != 32)
                            {
                                expression += word[i];
                            }
                            i++;
                        }
                        i--;
                        string result = post_exp(expression);
                        resultantFile << result;

                    }
                    if (tag == "|pre_exp|")
                    {
                        ++i;
                        while (int(word[i]) != 124)
                        {
                            if (int(word[i]) != 32)
                            {
                                expression += word[i];
                            }
                            i++;
                        }
                        i--;
                        string result = pre_exp(expression);
                        resultantFile << result;
                    }
                    if (tag == "|function|")
                    {
                        cout << "IT HAS NO PURPOSE!!!" << endl;
                    }
                    if (tag == "|sol_exp|")
                    {
                        ++i;
                        while (int(word[i]) != 124)
                        {
                            if (int(word[i]) != 32)
                            {
                                expression += word[i];
                            }
                            i++;
                        }
                        i--;
                        string result = sol_exp(expression);
                        resultantFile << result;
                    }
                    if (tag == "  ")
                    {
                        resultantFile << " ";
                    }
//********************************************************************************************************************

                    if (tag[1] != 92)
                    {
                        obj.push(tag);
                    }
                    else
                    {
                        if (obj.head != NULL)
                        {

                            string temp = obj.head->tag;
                            for (int x = 1; x < temp.length(); x++)
                            {
                                if (temp[x] != tag[x + 1])
                                {
                                    error = true;
                                    //cout << "ERROR TAG = " << tag << endl;
                                    break;
                                }
                            }

                            if (error == false)
                            {
                                obj.pop();
                            }
                        }
                        else
                        {
                            error = true;
                            resultantFile << "*****SYNTAX ERROR";
                        }
                        
                    }
                }
                else if(int(word[i]) != 9 && int(word[i]) != 10)
                {
                    resultantFile << word[i];
                    emptyline = true;
                }


            

            }
            if (emptyline == true)
            {
                resultantFile << "\n";
                emptyline = false;
            }

            

            





            



        }
    }
    file.close();

    if (obj.head != NULL)
    {
        error = true;
    }


    if (error == false) 
    {
        cout << endl << "No Errors" << endl;
    }
    else
    {
        /*node* temp = obj.head;
        while (temp != NULL) 
        {
            cout << temp->tag << endl;
            temp = temp->next;  
        }*/
        cout << endl << "Sytanx Errors" << endl;
    }


    return 0;
}

string post_exp(string exp)
{
   // cout << exp << endl;
    string h = exp;
    bool error = ValidExpressionCheck(h);
    if (error == true)
    {
        return "Invalid Expression";
    }
    else
    {
        //string res;
        //int c = 0;
        //check obj;
        ////string temp = exp;
        //string temp = "(" + exp + ")";
        //for (int i = 0; temp[i] != '\0';i++)
        //{
        //    if (temp[i] == '(')
        //    {
        //        obj.push('(');
        //    }
        //    else if ((temp[i] >= 'a' && temp[i] <= 'z') || (temp[i] >= 'A' && temp[i] <= 'Z'))
        //    {
        //        res += temp[i];
        //        c++;
        //    }
        //    else if (temp[i] == '+' || temp[i] == '-' || temp[i] == '*' || temp[i] == '/' || temp[i] == '^' || temp[i] == '$')
        //    {
        //        if (prec(temp[i]) >= prec(obj.head->val))
        //        {
        //            char ch = obj.head->val;
        //            obj.pop();
        //            res += ch;
        //            obj.push(temp[i]);
        //            c++;
        //        }
        //    }
        //    else
        //    {
        //        obj.pop();
        //        char ch = obj.head->val;
        //        res += ch;
        //        c++;
        //        obj.pop();
        //        obj.pop();
        //    }
        //}
        //cout << "Result === " << res << endl;
        string temp;
        string res;

        check obj;
        int x = 0;
        for (int i = 0; temp[i] != '\0';i++)
        {
            if (temp[i] == '(')
            {
                obj.push('(');
            }
            else if ((temp[i] >= 'a' && temp[i] <= 'z') || (temp[i] >= 'A' && temp[i] <= 'Z'))
            {
                res[x] = temp[i];
                x++;
            }
            else if (temp[i] == '+' || temp[i] == '-' || temp[i] == '*' || temp[i] == '/' || temp[i] == '^' || temp[i] == '$')
            {
                if (prec(temp[i]) >= prec(obj.head->val))
                {
                    char ch = obj.head->val;
                    obj.pop();
                    res[x] = ch;
                    x++;
                    obj.push(temp[i]);

                }
            }
            else if(temp[i] == ')')
            {

                res[x] = obj.head->val;

                while (obj.head->val != '(')
                {
                    obj.pop();
                }

            }

        }


        int r = 0;
        while (res[r] != '\0')
        {
            cout << res[r] << "  ";
            r++;
        }

        string result = exp;
        return result;



    }
}

string pre_exp(string exp)
{
    // cout << exp << endl;
    string h = exp;
    bool error = ValidExpressionCheck(h);
    if (error == true)
    {
        return "Invalid Expression";
    }
    else
    {
        //string res;
        //int c = 0;
        //check obj;
        ////string temp = exp;
        //string temp = "(" + exp + ")";
        //for (int i = 0; temp[i] != '\0';i++)
        //{
        //    if (temp[i] == '(')
        //    {
        //        obj.push('(');
        //    }
        //    else if ((temp[i] >= 'a' && temp[i] <= 'z') || (temp[i] >= 'A' && temp[i] <= 'Z'))
        //    {
        //        res += temp[i];
        //        c++;
        //    }
        //    else if (temp[i] == '+' || temp[i] == '-' || temp[i] == '*' || temp[i] == '/' || temp[i] == '^' || temp[i] == '$')
        //    {
        //        if (prec(temp[i]) >= prec(obj.head->val))
        //        {
        //            char ch = obj.head->val;
        //            obj.pop();
        //            res += ch;
        //            obj.push(temp[i]);
        //            c++;
        //        }
        //    }
        //    else
        //    {
        //        obj.pop();
        //        char ch = obj.head->val;
        //        res += ch;
        //        c++;
        //        obj.pop();
        //        obj.pop();
        //    }
        //}
        //cout << "Result === " << res << endl;
        string temp;
        string res;

        check obj;
        int x = 0;
        for (int i = 0; temp[i] != '\0';i++)
        {
            if (temp[i] == '(')
            {
                obj.push('(');
            }
            else if ((temp[i] >= 'a' && temp[i] <= 'z') || (temp[i] >= 'A' && temp[i] <= 'Z'))
            {
                res[x] = temp[i];
                x++;
            }
            else if (temp[i] == '+' || temp[i] == '-' || temp[i] == '*' || temp[i] == '/' || temp[i] == '^' || temp[i] == '$')
            {
                if (prec(temp[i]) >= prec(obj.head->val))
                {
                    char ch = obj.head->val;
                    obj.pop();
                    res[x] = ch;
                    x++;
                    obj.push(temp[i]);

                }
            }
            else if (temp[i] == ')')
            {

                res[x] = obj.head->val;

                while (obj.head->val != '(')
                {
                    obj.pop();
                }

            }

        }


        int r = 0;
        while (res[r] != '\0')
        {
            cout << res[r] << "  ";
            r++;
        }

        string result = exp;
        return result;



    }
}

string sol_exp(string exp)
{
    // cout << exp << endl;
    string h = exp;
    bool error = ValidExpressionCheck(h);
    if (error == true)
    {
        return "Invalid Expression";
    }
    else
    {
        //string res;
        //int c = 0;
        //check obj;
        ////string temp = exp;
        //string temp = "(" + exp + ")";
        //for (int i = 0; temp[i] != '\0';i++)
        //{
        //    if (temp[i] == '(')
        //    {
        //        obj.push('(');
        //    }
        //    else if ((temp[i] >= 'a' && temp[i] <= 'z') || (temp[i] >= 'A' && temp[i] <= 'Z'))
        //    {
        //        res += temp[i];
        //        c++;
        //    }
        //    else if (temp[i] == '+' || temp[i] == '-' || temp[i] == '*' || temp[i] == '/' || temp[i] == '^' || temp[i] == '$')
        //    {
        //        if (prec(temp[i]) >= prec(obj.head->val))
        //        {
        //            char ch = obj.head->val;
        //            obj.pop();
        //            res += ch;
        //            obj.push(temp[i]);
        //            c++;
        //        }
        //    }
        //    else
        //    {
        //        obj.pop();
        //        char ch = obj.head->val;
        //        res += ch;
        //        c++;
        //        obj.pop();
        //        obj.pop();
        //    }
        //}
        //cout << "Result === " << res << endl;
        string temp;
        string res;

        check obj;
        int x = 0;
        for (int i = 0; temp[i] != '\0';i++)
        {
            if (temp[i] == '(')
            {
                obj.push('(');
            }
            else if ((temp[i] >= 'a' && temp[i] <= 'z') || (temp[i] >= 'A' && temp[i] <= 'Z'))
            {
                res[x] = temp[i];
                x++;
            }
            else if (temp[i] == '+' || temp[i] == '-' || temp[i] == '*' || temp[i] == '/' || temp[i] == '^' || temp[i] == '$')
            {
                if (prec(temp[i]) >= prec(obj.head->val))
                {
                    char ch = obj.head->val;
                    obj.pop();
                    res[x] = ch;
                    x++;
                    obj.push(temp[i]);

                }
            }
            else if (temp[i] == ')')
            {

                res[x] = obj.head->val;

                while (obj.head->val != '(')
                {
                    obj.pop();
                }

            }

        }


        int r = 0;
        while (res[r] != '\0')
        {
            cout << res[r] << "  ";
            r++;
        }

        string result = exp;
        return result;



    }
}

bool ValidExpressionCheck(string exp)
{
    check obj;
    bool error = false;
    for (int i = 0; i < exp.length();i++)
    {
        if (int(exp[i]) == 40 || int(exp[i]) == 41)
        {

            if (exp[i] == '(')
            {
                obj.push(exp[i]);
            }
            else
            {
                if (obj.head != NULL)
                {
                    char temp = obj.head->val;
                    if (temp != 40)
                    {
                        error = true;
                        break;
                    }
                    if (error == false)
                    {
                        obj.pop();

                    }
                }
                else
                {
                    error = true;
                }
            }




        }
    }

    if (obj.head != NULL)
    {
        error = true;
    }

    return error;
}


int prec(char ch)
{
    if (ch == '^' || ch == '$')
    {
        return 3;
    }
    else if (ch == '*' || ch == '/')
    {
        return 2;
    }
    else if (ch == '+' || ch == '-')
    {
        return 1;
    }
    else
    {
        return -1;
    }
}