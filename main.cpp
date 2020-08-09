#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<stdlib.h>

using namespace std;

int menu();
string getkey();
string keyboardinput();
string Create_Matrix(string);
string encrypt(string, string);
string decrypt(string, string);
string format(string);
int outputmethod();
void Print_Matrix(string);


int main()
{
    /******* Variable Declarations *****************/
    int choice = 0;
    string key;
    int method = 0;
    string plaintext = "";
    string ciphertext = "";
    string matrix = "";

    while (choice != 4)
    {
        choice = menu();
        switch(choice)
        {
        case 1:
            key = getkey();
            matrix = Create_Matrix(key);
            plaintext = keyboardinput();
            plaintext = format(plaintext);
            ciphertext = encrypt(plaintext, matrix);
            method = outputmethod();
            if (method == 1)
            {
                cout<<"Ciphertext: "<<ciphertext<<endl;
            }

            else
                cout<<"invalid choice"<<endl;
            break;
            /**** Decrypt from the Keyboard ****************/
        case 2:
            key = getkey();
            matrix = Create_Matrix(key);
            ciphertext = keyboardinput();
            plaintext = decrypt(ciphertext, matrix);
            method = outputmethod();
            if (method == 1)
            {
                cout<<"The original message: "<<plaintext<<endl;
            }
            else
                cout<<"invalid choice"<<endl;
            break;
            /**** Print the 7x7 Matrix ****************/
        case 3:
            Print_Matrix(matrix);
            break;
            /**** Exit Program *****/
        case 4:
            exit (0);
        default:
            cout<<"Your choice is invalid, please try again"<<endl;
        }
    }
    return 0;
}

/************ getkey Function *****************
Purpose: Gets a key from the user
return: String containining the key
*************************************************/
string getkey()
{
    string tempkey;
    cout<<"PLEASE INPUT THE KEY IN UPPERCASE"<<endl;
    cin>> tempkey;
    return tempkey;
}

/************ Keyboardinput Function *****************
Purpose: Gets input from the Keyboard
return: String containing keyboard input
*************************************************/
string keyboardinput()
{
    string temptext;
    cout<<"ENTER THE MESSAGE IN UPPERCASE"<<endl;
    cin.ignore(); //bug fix for getline function
    getline(cin,temptext); //Get text from user
    return temptext;
}


/************ Create_Matrix Function *****************/
string Create_Matrix(string keyword)
{
    char array[49];
    int i = 0;
    int k = 0;
    int value = 0;
    int count = 0;
    bool unique = true;
    int len = keyword.length();
    int run = 1;

    for (run = 0; run < len; run++) //run loop once for each letter of key
    {
        for (k = 0; k < run; k++)
        {
            if (keyword[run] == keyword[k])
            {
                unique = false;
            }
        }
        if (unique == true) //Letter has not been used in table
        {
            array[i] = keyword[run]; //give the location the correct ascii value
            i++;//increment matrix since it has been filled
        }
        unique = true;
    }
    /*** put the rest of the characters in **/
    while (count < 50)
    {
        for (k = 0; k < len; k++)
        {
            if (value == keyword[k] - 42)
            {
                unique = false;
            }
        }
        if (unique == true) //Letter has not been used in table
        {
            if (value != 10)
            {
                array[i] = 42+ value; //give the location the correct ascii value
                i++;//increment matrix since it has been filled
            }
        }
        value++;
        count++;
        k = 0;
        unique = true;
    }
    return array;
}

/************ Print_Matrix Function *****************/

void Print_Matrix(string matrix)
{

    cout<<"\t\tThe Current Matrix"<<endl;
    cout<<"\t\t------------------"<<endl;
    cout<<" "<<endl;
    for (int j = 0; j < 49; j++)
    {
        cout<<"\t"<<matrix[j]<<"\t"<<matrix[j + 1]<<"\t"<< matrix[j + 2]<<"\t" <<matrix[j + 3]<<"\t"<< matrix[j + 4]<<"\t"<< matrix[j + 5]<<"\t"<< matrix[j + 6]<< endl;
        j = j + 6;
    }
}

/************ Encrypt Function *****************/

string encrypt(string plain, string matrix)
{
    string ciphertxt = plain;
    int loc[2];
    int row[2];
    int col[2];
    int shift = 0;
    int original_row = 0;
    int n = 0;
    cout<<"Plaintext arrival: " <<plain<<endl;
    int textlen = plain.length();
    for (n = 0; n < textlen; n = n + 2) //run half the length (diagrams)
    {
        //Assign letters to their locations in matrix
        for (int temp = 0; temp < 49; temp++)
        {
            if (plain[n] == matrix[temp])
            {
                loc[0] = temp; //location of the first letter in pair
            }
            if (plain[n+1] == matrix[temp])
            {
                loc[1] = temp; //location of the second letter in pair
            }
        }

        /* Find Row and Column Numbers */
        for (int m = 0; m < 2; m++)
        {
            if (loc[m] < 7 ) // Location first row
            {
                row[m] = 1;
            }
            else if (loc[m] > 6 && loc[m] < 14) // Location second row
            {
                row[m] = 2;
            }
            else if (loc[m] > 13 && loc[m] < 21 ) // Location third row
            {
                row[m] = 3;
            }
            else if (loc[m] > 20 && loc[m] < 28) // Location fourth row
            {
                row[m] = 4;
            }
             else if (loc[m] > 27 && loc[m] < 35) // Location fifth row
            {
                row[m] = 5;
            }
             else if (loc[m] > 34 && loc[m] < 42) // Location sixth row
            {
                row[m] = 6;
            }
            else // Location seventh row
            {
                row[m] = 7;
            }
            if (loc[m] == 0 || loc[m] == 7 || loc[m] == 14 || loc[m] == 21 || loc[m] == 28 || loc[m] == 35 || loc[m] == 42)
            {
                // Location first column
                col[m] = 1;
            }
            else if (loc[m] == 1 || loc[m] == 8 || loc[m] == 15 || loc[m] == 22 || loc[m] == 29 || loc[m] == 36 || loc[m] == 43)
            {
                // Location second column
                col[m] = 2;
            }
            else if (loc[m] == 2 || loc[m] == 9 || loc[m] == 16 || loc[m] == 23 || loc[m] == 30 || loc[m] == 37 || loc[m] == 44)
            {
                // Location third column
                col[m] = 3;
            }
            else if (loc[m] == 3 || loc[m] == 10 || loc[m] == 17 || loc[m] == 24 || loc[m] == 31 || loc[m] == 38 || loc[m] == 45)
            {
                // Location fourth column
                col[m] = 4;
            }
            else if (loc[m] == 4 || loc[m] == 11 || loc[m] == 18 || loc[m] == 25 || loc[m] == 32 || loc[m] == 39|| loc[m] == 46)
            {
                // Location fifth column
                col[m] = 5;
            }
            else if (loc[m] == 5 || loc[m] == 12 || loc[m] == 19 || loc[m] == 26 || loc[m] == 33 || loc[m] == 40|| loc[m] == 47)
            {
                // Location sixth column
                col[m] = 6;
            }
            else
            {
                // Location seventh column
                col[m] = 7;
            }
        }
        //Start that encryption and shifting :-)
        if (row[0] == row[1] || col[0] == col[1]) //same row or same column: special case
        {
            if (row[0] == row[1]) //same row
            {
                original_row = row[0]; //sets a baseline for starting row
                loc[0] = (loc[0] + 1);
                loc[1] = (loc[1] + 1);
                /* Find Row after shift */
                for (int m = 0; m < 2; m++)
                {
                    if (loc[m] < 7 )
                    {
                        row[m] = 1;
                    }
                    else if (loc[m] > 6 && loc[m] < 14)
                    {
                        row[m] = 2;
                    }
                    else if (loc[m] > 13 && loc[m] < 21 )
                    {
                        row[m] = 3;
                    }
                    else if (loc[m] > 20 && loc[m] < 28)
                    {
                        row[m] = 4;
                    }
                    else if (loc[m] > 27 && loc[m] < 35)
                    {
                        row[m] = 5;
                    }
                    else if (loc[m] > 34 && loc[m] < 42)
                    {
                        row[m] = 6;
                    }
                    else
                    {
                        row[m] = 7;
                    }
                }
                if (row[0] != original_row)
                {
                    loc[0] = loc[0] - 7;
                }
                if (row[1] != original_row)
                {
                    loc[1] = loc[1] - 7;
                }
                ciphertxt[n] = matrix[loc[0]]; //assign the resultant location to be cipher char
                ciphertxt[n+1] = matrix[loc[1]];

            }
            if (col[0] == col[1]) //same column
            {
                loc[0] = (loc[0] + 7) ;
                loc[1] = (loc[1] + 7) ;
                if (loc[0] > 48)
                {
                    loc[0] = loc[0] - 49;
                }
                if (loc[1] > 48)
                {
                    loc[1] = loc[1] - 49;
                }
                ciphertxt[n] = matrix[loc[0]]; //assign the result location to be cipher char
                ciphertxt[n+1] = matrix[loc[1]];

            }
        }
        else if (col[0] < col[1]) //if the second letter has a higher column
        {
            shift = abs(col[0] - col[1]); //col difference between char 1 - char 2
            loc[0] = loc[0] + shift;//location point right after shift
            loc[1] = loc[1] - shift;
            ciphertxt[n] = matrix[loc[0]]; //assign the result location to be cipher char
            ciphertxt[n+1] = matrix[loc[1]];

        }
        else if (col[0] > col[1]) //if the first letter has a higher column
        {
            shift = (col[0] - col[1]); //col difference between char 1 - char 2
            loc[0] = loc[0] - shift;//location point right after shift
            loc[1] = loc[1] + shift;
            ciphertxt[n] = matrix[loc[0]];
            ciphertxt[n+1] = matrix[loc[1]];

        }
}

    return ciphertxt;
}


/************ Decrypt Function *****************/
string decrypt(string cipher, string matrix )
{
    string plain = cipher;
    int loc[2];
    int row[2];
    int col[2];
    int shift = 0;
    int original_row = 0;
    int n = 0;
    int m = 0;
    int textlen = cipher.length();
    for (n = 0; n < textlen; n = n + 2) //run half the length
    {
        loc[0] = 0;
        loc[1] = 0;

        //Assign letters to their locations in matrix
        for (int temp = 0; temp < 49; temp++)
        {
            if (plain[n] == matrix[temp])
            {
                loc[0] = temp; //location of the first letter in pair
            }
            if (plain[n+1] == matrix[temp])
            {
                loc[1] = temp; //location of the second letter in pair
            }
        }
        /* Find Row and Column Numbers */
        for (m = 0; m < 2; m++)
        {
            if (loc[m] < 7 ) // Location first row
            {
                row[m] = 1;
            }
            else if (loc[m] > 6 && loc[m] < 14) // Location second row
            {
                row[m] = 2;
            }
            else if (loc[m] > 13 && loc[m] < 21 ) // Location third row
            {
                row[m] = 3;
            }
            else if (loc[m] > 20 && loc[m] < 28) // Location fourth row
            {
                row[m] = 4;
            }
             else if (loc[m] > 27 && loc[m] < 35) // Location fifth row
            {
                row[m] = 5;
            }
             else if (loc[m] > 34 && loc[m] < 42) // Location sixth row
            {
                row[m] = 6;
            }
            else // Location seventh row
            {
                row[m] = 7;
            }
            //GET column Locations
            if (loc[m] == 0 || loc[m] == 7 || loc[m] == 14 || loc[m] == 21 || loc[m] == 28|| loc[m] == 35|| loc[m] == 42)
            {
                // Location first column
                col[m] = 1;
            }
            else if (loc[m] == 1 || loc[m] == 8 || loc[m] == 15 || loc[m] == 22 || loc[m] == 29|| loc[m] == 36|| loc[m] == 43)
            {
                // Location second column
                col[m] = 2;
            }
            else if (loc[m] == 2 || loc[m] == 9 || loc[m] == 16 || loc[m] == 23 || loc[m] == 30|| loc[m] == 37|| loc[m] == 44)
            {
                // Location third column
                col[m] = 3;
            }
            else if (loc[m] == 3 || loc[m] == 10 || loc[m] == 17 || loc[m] == 24 || loc[m] == 31|| loc[m] == 38|| loc[m] == 45)
            {
                // Location fourth column
                col[m] = 4;
            }
            else if (loc[m] == 4 || loc[m] == 11 || loc[m] == 18 || loc[m] == 25 || loc[m] == 32|| loc[m] == 39|| loc[m] == 46)
            {
                // Location fifth column
                col[m] = 5;
            }
            else if (loc[m] == 5 || loc[m] == 12 || loc[m] == 19 || loc[m] == 26 || loc[m] == 33|| loc[m] == 40|| loc[m] == 47)
            {
                // Location sixth column
                col[m] = 6;
            }
            else
            {
                // Location seventh column
                col[m] = 7;
            }
        }
        //Start that encryption and shifting :-)
        if (row[0] == row[1] || col[0] == col[1])
        {
            //same row or same column: special case
            if (row[0] == row[1])
            {
                //same row
                original_row = row[0]; //sets a baseline for starting row
                loc[0] = (loc[0] - 1);
                loc[1] = (loc[1] - 1);
                // Find Row after shift
                for (m = 0; m < 2; m++)
                {
                    if (loc[m] < 7 )
                    {
                        row[m] = 1;
                    }
                    else if (loc[m] > 6 && loc[m] < 14)
                    {
                        row[m] = 2;
                    }
                    else if (loc[m] >13 && loc[m] < 21 )
                    {
                        row[m] = 3;
                    }
                    else if (loc[m] > 20 && loc[m] < 28)
                    {
                        row[m] = 4;
                    }
                    else if (loc[m] > 27 && loc[m] < 35)
                    {
                        row[m] = 5;
                    }
                    else if (loc[m] > 34 && loc[m] < 42)
                    {
                        row[m] = 6;
                    }
                    else
                    {
                        row[m] = 7;
                    }
                }

                if (row[0] != original_row || loc[0] < 0)
                {
                    loc[0] = loc[0] + 7;
                }
                if (row[1] != original_row || loc[1] < 0)
                {
                    loc[1] = loc[1] + 7;
                }
                plain[n] = matrix[loc[0]]; //assign the result location to be cipher char
                plain[n+1] = matrix[loc[1]];

            } //ends if row = row...moves along to column
            else if (col[0] == col[1]) //same column
            {
                if (loc[0] > loc[1]) //account for upper rollover
                {
                    loc[0] = (loc[0] - 7) ;
                    loc[1] = (loc[1] - 7) ;
                    if (loc[1] < 0)
                    {
                        loc[1] = (loc[1] + 49) ;
                    }
                }
                else if (loc[0] < loc[1] && loc[0] < 6) //account for lower rollover
                {
                    loc[0] = (loc[0] + 7) ; //Inverse of encryption shift
                    loc[1] = (loc[1] - 7) ; //Inverse of encryption shift
                }
                else
                {
                    if (loc[1] - loc[0] == 42) //account for adjacent column special case
                    {
                        loc[0] = loc[0] + 42; //Inverse of encryption shift
                        loc[1] = (loc[1] - 7) ; //Inverse of encryption shift
                    }

                    else //normal cases
                    {
                        loc[0] = (loc[0] - 7) ; //Inverse of encryption shift
                        loc[1] = (loc[1] - 7) ; //Inverse of encryption shift
                        if (loc[0] > 48)
                        {
                            loc[0] = loc[0] - 49; //account for wraparound
                        }
                        if (loc[1] > 48)
                        {
                            loc[1] = loc[1] - 49; //account for wraparound
                        }
                    }
                }
                plain[n] = matrix[loc[0]]; //assign the result location to be cipher char
                plain[n+1] = matrix[loc[1]]; //assign the result location to be cipher char
            }
        }
        else if (col[0] < col[1]) //if the second letter has a higher column
        {
            shift = abs(col[0] - col[1]);//col difference between char 1 - char 2
            loc[0] = loc[0] + shift;//location point right after shift
            loc[1] = loc[1] - shift;//location point right after shift
            plain[n] = matrix[loc[0]]; //assign the result location to be cipher char
            plain[n+1] = matrix[loc[1]]; //assign the result location to be cipher char
        }

        else if (col[0] > col[1]) //if the first letter has a higher column
        {
            shift = (col[0] - col[1]); //col difference between char 1 - char 2
            loc[0] = loc[0] - shift;//location point right after shift
            loc[1] = loc[1] + shift;//location point right after shift
            plain[n] = matrix[loc[0]]; //assign the result location to be cipher char
            plain[n+1] = matrix[loc[1]]; //assign the result location to be cipher char
        }
    }
    return plain;
}

/***************** Format ************************
Purpose: To format the plaintext for encryption
************************************************/
string format(string text)
{
    int i = 0;
    int j = 0;
    int len = 0;
    len = text.length();

    /**********************************/
    if (len % 2 == 0)
    {
        cout<<"plaintext is even"<<endl;
    }
    else
    {
        cout<< "plaintext is odd"<<endl;
        text = text + "X"; //add x as a filler to the end
    }
    len = text.length();
    /*** Assign 'x' to letters that repeat in a diagram ***/
    for (i = 0; i < len; i = i + 2) //run for half of string length
    {
        if (text[i+1] == text[i]) //if char = previous char
        {
            text = text + " ";//increase length
            len = text.length();
            for (j = len -1; j > i; j--) //j starts a top len, will run till it hits i
            {
                text[j] = text[j-1]; //last letter = previous letter
            }
            text[i + 1] = 'X';
        }
        else //not a repeat character, move along
        {}
    }
    return text;
}

/***************** outputmethod ************************
Purpose: determines how to output results
*****************************************************/
int outputmethod()
{
    int method;
    cout<<"Press 1 to continue"<<endl;
    cin >> method;
    return method;
}


//same old menu
int menu()
{
    int menuselect;
    cout<<"|--------------------------------------------------|"<<endl;
    cout<<"|*The Playfair Cipher* |"<<endl;
    cout<<"| |"<<endl;
    cout<<"---------------------------------------------------|"<<endl;
    cout<<"| Please Make a Selection |"<<endl;
    cout<<"| Encryption Functions |"<<endl;
    cout<<"| 1: Encrypt the message (Keyboard source)|"<<endl;
    cout<<"| 2: Decrypt the message (Keyboard source)|"<<endl;
    cout<<"| |"<<endl;
    cout<<"| Extras |"<<endl;
    cout<<"| 3. View Matrix|"<<endl;
    cout<<"| |"<<endl;
    cout<<"| Exit |"<<endl;
    cout<<"| 4. Quit|"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    cin>> menuselect;
    return menuselect;
}
