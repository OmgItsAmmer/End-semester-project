#include <iostream>
#include <windows.h>
#include <conio.h>


using namespace std;

const int width = 76;
const int length = 26;
const int s1width = 52;
const int s1length = 20;


struct Position
{
    int x;
    int y;
};

//gotoxy fnction
void gotoxy(int x, int y)
{ // gotoxy code
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//Dialogue box function
void dialogueBox()
{
    gotoxy(width + 16, 3);
    cout << "<<<<DIALOGUE BOX>>>>";
    for (int i = 0; i < length-2; i++)
    {
        gotoxy(width + 7, 2+i);
		cout << "<";
        gotoxy(width + 43, 2+i);
        cout << ">";
    }
	for (int i = 0; i < length + 11; i++) //iteration range depends on size you want
    {
        gotoxy(width+7+i,2);
        cout << "*";
        gotoxy(width + 7 + i, length-1); //To match with game border
        cout << "*";
    }
}
// Function to get the character at a specific position
char getCharacterAtPosition(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        // Handle error
        return '\0';
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        // Handle error
        return '\0';
    }

    COORD coord;
    coord.X = x;
    coord.Y = y;

    DWORD dwRead;
    CHAR_INFO chi;
    if (!ReadConsoleOutputCharacter(hConsole, &chi.Char.UnicodeChar, 1, coord, &dwRead)) {
        // Handle error
        return '\0';
    }
    //cout << chi.Char.UnicodeChar;
    return chi.Char.UnicodeChar;
}
//hiding cursor
void cursorhide() {
    
}   //not working 
//levelblocker
void doorblocker()
{
    for (int i = 0; i < 5; i++) //4
    {
        gotoxy((width / 2) - 2 + i, 4);
        cout << "*";
    }   
    //vertical walls
    for (int j = 0; j < 2; j++)
    {
        gotoxy((width / 2)-2, 4-j);
        cout << "*";
        gotoxy((width / 2) + 3, 4 -j);
        cout << "*";
    }

}
void border()
{
    for (int i = 2; i < length; i++) //starting from 2 to  escape starting line (C:/ammer etc)
    {
        gotoxy(0, i);
        cout << "#";
        gotoxy(width, i);
        cout << "#";
    }

    for (int i = 0; i < width; i++)
    {
        gotoxy(i, 2);
        cout << "#";
        gotoxy(i, length - 1);
        cout << "#";
    }
} // border
//shop inner border(shop walls)
void shopinnerborder() {
    //horizontal
    for (int i = 0; i < s1width; i++)
    {
        gotoxy(i,0);
		cout << "*";
        gotoxy(i,s1length);
		cout << "*";
    }
    //vertical
    for (int i = 0; i < s1length; i++)
    {
        gotoxy(0, i);
		cout << "*";
        gotoxy(s1width-1, i);
		cout << "*";
    }
}
/// shop outerborder
void shopexterior1()
{
    // vertical walls
    for (int i = 1; i < (4); i++)
    {
        gotoxy(width - 8, (length / 2) - 3 + i);
        cout << "**";
        gotoxy(width - 8, (length / 2) + 1 + i);
        cout << "**";
    }
    // horizontal walls
    for (int i = 1; i < (9); i++)
    {
        gotoxy(width - 9 + i, (length / 2) - 3);
        cout << "*";
    }
    for (int i = 1; i < (9); i++)
    {
        gotoxy(width - 9 + i, (length / 2) + 5);
        cout << "*";
    }
    // door
    gotoxy(width - 8, (length / 2) + 1);
    cout << "OO";

} // shopexterior1
/////Player and destination position////
void drawposition(Position& playerpos, Position& destpos)
{
    gotoxy(playerpos.x, playerpos.y);
    cout << "@";

    gotoxy(destpos.x, destpos.y);
    cout << "()";
} // drawposition
/////drawshopposition
void drawshopthings(Position& playerpos, Position& destpos, Position& doorpos)
{
    gotoxy(playerpos.x, playerpos.y);
    cout << "@";

    gotoxy(destpos.x, destpos.y);
    cout << "AI";

    gotoxy(doorpos.x, doorpos.y);
    cout << "8";

}
// move function(not using)
void move(int preY, int preX, Position& newPos)
{
   
} 
/// collison&movement///
bool checkcollision(Position& newpos)
{
    if (newpos.x < 1 || newpos.x >= 75 || newpos.y < 3 || newpos.y >= 25)
    {
        return true;
    }
    else
        return false;
} // collsiom

bool checkshopcollision(Position& newpos)
{
    if (newpos.x < 1 || newpos.x >= s1width-1 || newpos.y < 1 || newpos.y >= s1length) //s1width-1 is adjusting border in square in upper function so we need -1 in this too 
    {
        return true;
    }
    else
        return false;
} // collsiom

//check door collision function
bool checkdoorcollision(Position& newpos)
{
    if (newpos.x == width - 8 && newpos.y == (length / 2) + 1)
    {
        return false;
    }
    else
        return true;

} // checkdoorcollision

bool portal(Position& playerpos, Position& destpos)
{
    if (playerpos.x == destpos.x && playerpos.y == destpos.y)
    {
        return true;
    }
    else
        return false;
}
//shop1doorcollision function
bool door1(Position& playerpos, Position& doorpos)
{
    if (playerpos.x == doorpos.x && playerpos.y == doorpos.y)
    {
        return true;
    }
    else
        return false;
 }
//Hintman collision function
bool hintman(Position& playerpos, Position& destpos)
{
    if (playerpos.x == destpos.x && playerpos.y == destpos.y)
    {
        return true;
    }
    else
        return false;
}

int main()
{


    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    // Hide the cursor
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
    //////////////
    bool blocker = true;
    Position playerpos = { width / 2, length - 2 }; // x and y
    mainmap: //line 380
    system("cls");
    Position destpos = { width / 2, 3 };
    Position newPos = playerpos;
    int preY = 0, preX = 0;
    dialogueBox();
    cursorhide();
    border();
    shopexterior1();
    drawposition(playerpos, destpos);
    if(blocker==true)
    {
        doorblocker();
    }
    
    while (true)
    {
        if (_kbhit())
        { 

            char key = _getch();

            if (key == 80)
            {
                preY = newPos.y;
                newPos.y++;
            }
            else if (key == 72)
            {
                preY = newPos.y;
                newPos.y--;
            }

            else if (key == 77)
            {
                preX = newPos.x;
                newPos.x++;
            }

            else if (key == 75)
            {
                preX = newPos.x;
                newPos.x--;
            }
        }
        if (getCharacterAtPosition(newPos.x, newPos.y) == '*') //position matters
        {
            newPos.x = preX;
            newPos.y = preY;
        }
        if (getCharacterAtPosition(newPos.x, newPos.y) == '#') //position matters
        {
            newPos.x = preX;
            newPos.y = preY;
        }
        if (!checkcollision(newPos)) // colliosn function is working oposite bcz its easy to code area of map
        {
            gotoxy(playerpos.x, playerpos.y);
            cout << " ";                      // it will empty the previous position
            playerpos = newPos;               // default playerpos is the when u give in start but its also kep updating
            drawposition(playerpos, destpos); // we didnt require destpos bcz we need final desiton once
        }
        if (portal(newPos, destpos))
        {
            system("cls");
            gotoxy(width / 2, length / 2);
            cout << "Welcome back king";
            break;
        }
        if (!checkdoorcollision(newPos))
        {
            system("cls");
            break;
        }
    } // while1
    
    if (checkdoorcollision(newPos) == false)
    {
    
    
        Position playerpos2 = { (s1width / 2),(s1length/2) +7 }; 
     shopnearAI:
        Position hintmanstandingpos =   {1,1}; // write in width form later
        Position hintmaninteractingpos = {2||1,2||2}; //Or not working sadly :(
        Position doorpos = { 2 , (s1length / 2) };
        gotoxy(width + 10, 3);
        dialogueBox();
		Position newPos2 = playerpos2;
        
        shopinnerborder();
        drawshopthings(playerpos2, hintmanstandingpos,doorpos);
        while (true)
        {       
            if (_kbhit())
            {

                char key = _getch();

                if (key == 80)
                {
                    preY = newPos2.y;
                    newPos2.y++;
                }
                else if (key == 72)
                {
                    preY = newPos2.y;
                    newPos2.y--;
                }

                else if (key == 77)
                {
                    preX = newPos2.x;
                    newPos2.x++;
                }

                else if (key == 75)
                {
                    preX = newPos2.x;
                    newPos2.x--;
                }
            }
            if (getCharacterAtPosition(newPos.x, newPos.y) == '*') //position matters
            {
                newPos.x = preX;
                newPos.y = preY;
            }
            if (!checkshopcollision(newPos2)) // colliosn function is working oposite bcz its easy to code area of map
            {   
                gotoxy(playerpos2.x, playerpos2.y);
                cout << " ";                      // it will empty the previous position
                playerpos2 = newPos2;               // default playerpos is the when u give in start but its also kep updating
                drawshopthings(playerpos2, hintmanstandingpos,doorpos); // we didnt require destpos bcz we need final desiton once
            }
            if (hintman(newPos2, hintmaninteractingpos))
            {
                string answer, answer2, answer3;
                gotoxy(width + 10, 6); 
                cout << "AI: You need help witcher?(yes/no)" << endl;
                gotoxy(width + 10, 7);
                cout << "Witcher: ";
                gotoxy(width + 10, 8);
                cin >> answer; 
                
                if (answer == "yes" || answer == "YES" || answer== "Yes")
                {   
                    gotoxy(width + 10, 9);
                    cout << "Yes,I am looking for the portal";
                    gotoxy(width + 10, 10);
                    cout << "AI: Oh portal, its to the north" << endl;
					gotoxy(width + 10, 11);
                    cout << "ok Thanks,AI";
                    blocker = false;
                    //tryagain:
                    gotoxy(width + 10, 12);
                    cout << "Say \"bye\" to continue joruney";
                    gotoxy(width + 10, 13);
                    cin >> answer2;
                    if (answer2 == "bye")
                    {

                        gotoxy(width + 10, 9);
                        system("cls");
                        playerpos2 = { 2 ,2 };
                        blocker = false;
                        goto shopnearAI; //line 294  
                    }
                    else 
                    {
                        cout << "AI: Sorry what you said?";
                       // goto tryagain; can use as handler
                    }
                }
                else if(answer == "no" || answer == "NO" || answer == "No")
                    {
                    gotoxy(width + 10, 9);
                    cout << "As you say witcher";
                    Sleep(2000);
                    gotoxy(width + 10, 9);
                    system("cls");
                    playerpos2 = { 2 ,2 };
                    goto shopnearAI; //line 294 
                }
                else 
                {
                    gotoxy(width + 10, 9);
                    cout << "enter valid option, thanks";
                }
                
            }   
            if (door1(newPos2, doorpos))
            {
                playerpos = { (width - 8)-1, (length / 2) + 1 };
                goto mainmap; // 221
            }
        }//while2
    }//if for shop1 entry
    

     
    return 0;
} // main
