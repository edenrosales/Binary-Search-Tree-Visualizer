#include <SFML/Graphics.hpp>
#include "Tree.h"
#include "Node.h"
#include <conio.h>
#include <iostream>
#include <Windows.h>
//this is a function that will check if the input value is all numbers or not 
bool check_number(string str) {//this wil take the string that will be user input and checks if all the values are 
	for (int i = 0; i < str.length(); i++) {//goes through the length of the string 
		if (isdigit(str[i]) == false) {//if any of the chars in the string are not digits, will return false 
			return false;
		}
	}
	return true;//otherwise return true
}
void gotoxy(int x, int y)//places the cursor at the (x,y) coordinate 
{
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}
int main()
{
    Tree newtree;//new tree object 
    //text that prompts useer what to do 
    cout << "1 will be to get a user input for a character " << endl << "2 will be to get a uset input to remove a character " << endl << "3 will be to read the values from a file " << endl;
    sf::RenderWindow window(sf::VideoMode(1200, 1000), "Binary Serach Tree");//creates an SFML window
   /* sf::CircleShape shape(45.f);*/
    //shape.setFillColor(sf::Color::Green);
    window.clear(sf::Color::Black);//clears the screen and turns it black 
    window.display();//prints the black screen 
    window.clear(sf::Color::Black);//clears the screen again (both frames)
    //this block here will print LNR, NLR, and RNL to hold nothing, and represent that 
    string blankLNR = "LNR: EMPTY";
    newtree.displayString(window, 50.f, 800.f, blankLNR);
    string blankNLR = "NLR: EMPTY";
    newtree.displayString(window, 50.f, 820.f, blankNLR);
    string blankRNL = "RNL: EMPTY";
    newtree.displayString(window, 50.f, 840.f, blankRNL);
    window.display();
    //the main body of the project 
    while (window.isOpen())//project will close if the SFML window is closed 
    {
        sf::Event event;
        //makes sure that the window will close if the close button is clicked 
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (_kbhit()) {//checks for a keyboard input 
            			//1 will be to get a user input for a character 
            			//2 will be to get a uset input to remove a character 
            			//3 will be to get information from a file 
            			//4 will be to exit (or another button that i choose) 
           char ch = _getch();
            if (ch == '1') {//if 1 is pressed 
                //will clear the terminal screen, and prompt user to input a value 
            	std::system("cls");
            	cout << "input the value to add"<<endl;
                //creates a string 
           		string userinput;
                //will input the user input to the string 
         		cin >> userinput;
                //will make sure that the string is a valid input (that all the values are numbers, for example 123a3 would not work, 1233 would though)
            		while (!check_number(userinput) && (stoi(userinput)<0)) {//if the user input is not valid, will continue to prompt the user until a vald input is recieved 
            			std::system("cls");
            			cout << "invaled number, try again"<<endl;
            			cin >> userinput;
            		}
                    //if the tree is emtpy, it will set the input node to be the root node 
                    if (newtree.isEmpty())
                        newtree.root = newtree.insert(stoi(userinput), newtree.root);
                    else //else, simply adds the node to the tree normally 
            			newtree.insert(stoi(userinput), newtree.root);
            		std::system("cls");//clears the screen and will input the information that will prompt the user to take another action 
            		cout << "1 will be to get a user input for a character " << endl << "2 will be to get a uset input to remove a character " << endl << "3 will be to read the values from a file " << endl;
                    //this part of the function will clear both frames in SFML and set them the black, then it will completely redisplay the updated tree along with the LNR NLR RNL info 
                    if (!newtree.isEmpty()) {
                        window.clear(sf::Color::Black);
                        window.display();
                        Sleep(200);
                        window.clear(sf::Color::Black);
                        newtree.displayTree(window, newtree.root, 600.f, 50.f);
                        string toprintLNR = "LNR: ";
                        newtree.LNR(newtree.root, toprintLNR);
                        newtree.displayString(window, 50.f, 800.f, toprintLNR);
                        string toprintNLR = "NLR: ";
                        newtree.NLR(newtree.root, toprintNLR);
                        newtree.displayString(window, 50.f, 820.f, toprintNLR);
                        string toprintRNL = "LRN: ";
                        newtree.LRN(newtree.root, toprintRNL);
                        newtree.displayString(window, 50.f, 840.f, toprintRNL);
                        window.display();
                    }
            }
            else if (ch == '2') {//deleting nodes 
                /*window.clear(sf::Color::Black);
                window.display();
                Sleep(200);
                window.clear(sf::Color::Black);
                newtree.deletenode(50, newtree.root);
                cout << "this works";
                newtree.displayTree(window, newtree.root, 600.f, 50.f);
                window.display();*/
                std::system("cls");
                cout << "input the value to delete" << endl;//promps the user to input a value 
                string userinput; 
                cin >> userinput;//inputs value to a created string varable 
                while (!check_number(userinput) && stoi(userinput) < 0) {//verifies that this value is valid, if not, will continue to prompt the user until a valid number is input 
                    std::system("cls");
                    cout << "invalid number, try again" << endl;
                    Sleep(200);
                    cin >> userinput;
                }
                if (newtree.isEmpty()) {//if the tree is empty, there is nothing to delte 

                }
                else {
                    newtree.deletenode(stoi(userinput), newtree.root);//if the tree is not empty, will delete like normal
                }
                std::system("cls");//will reprompt the user to do another action
                cout << "1 will be to get a user input for a character " << endl << "2 will be to get a uset input to remove a character " << endl << "3 will be to read the values from a file " << endl;
                //this part of the function will clear both frames in SFML and set them the black, then it will completely redisplay the updated tree along with the LNR NLR RNL info 
                if (!newtree.isEmpty()) {//however, if the tree is empty due to the deletion, it must display an empty tree along with the LNR NLR RNL values that will show that there is nothing in the tree 
                    window.clear(sf::Color::Black);
                    window.display();
                    Sleep(200);
                    window.clear(sf::Color::Black);
                    newtree.displayTree(window, newtree.root, 600.f, 50.f);
                    string toprintLNR = "LNR: ";
                    newtree.LNR(newtree.root, toprintLNR);
                    newtree.displayString(window, 50.f, 800.f, toprintLNR);
                    string toprintNLR = "NLR: ";
                    newtree.NLR(newtree.root, toprintNLR);
                    newtree.displayString(window, 50.f, 820.f, toprintNLR);
                    string toprintRNL = "RNL: ";
                    newtree.LRN(newtree.root, toprintRNL);
                    newtree.displayString(window, 50.f, 840.f, toprintRNL);
                    window.display();
                }
                else {//if the tree is not empty, it will redisplay all the tree and the number display like normal 
                    window.clear(sf::Color::Black);
                    window.display();
                    window.clear(sf::Color::Black);
                    string blankLNR = "LNR: EMPTY";
                    newtree.displayString(window, 50.f, 800.f, blankLNR);
                    string blankNLR = "NLR: EMPTY";
                    newtree.displayString(window, 50.f, 820.f, blankNLR);
                    string blankRNL = "RNL: EMPTY";
                    newtree.displayString(window, 50.f, 840.f, blankRNL);
                    window.display();
                }

           	}
          	else if (ch == '3') {//reads from file and inputs to screen 
            	newtree.readFromFile();//calls the readfromfile function 
                //after the function, all the values will be added to the tree and the rest of this section is used to just display the updated tree
                window.clear(sf::Color::Black);
                window.display();
                Sleep(200);
                window.clear(sf::Color::Black);
                newtree.displayTree(window, newtree.root, 600.f, 50.f);
                string toprintLNR = "LNR: ";
                newtree.LNR(newtree.root, toprintLNR);
                newtree.displayString(window, 50.f, 800.f, toprintLNR);
                string toprintNLR = "NLR: ";
                newtree.NLR(newtree.root, toprintNLR);
                newtree.displayString(window, 50.f, 820.f, toprintNLR);
                string toprintRNL = "RNL: ";
                newtree.LRN(newtree.root, toprintRNL);
                newtree.displayString(window, 50.f, 840.f, toprintRNL);
                window.display();
            }
            else if (ch == '4') {//breaks the function and ends the program
            	break;
            }
            else if (ch == '5') {//added for testing reasons 
            cout << "hi";
               /* window.clear(sf::Color::Black);
                window.display();*/
               /* newtree.displayTree(window, newtree.root, 600.f, 20.f);
                window.display();*/
            }
         }

       /* window.clear();
        shape.setPosition(600.f, 50.f);
        window.draw(shape);*/
       /* newtree.displayTree(window, newtree.root, 600.f, 20.f);
        window.display();*/
    }//clears the screen at the end of the program
    std::system("cls");
    Sleep(20);
    gotoxy(50, 50);
    /*if(newtree.isEmpty()){}
    else {
        string input = "";
        string toprint=newtree.LNR(newtree.root,input);
        newtree.displayString(window, 20.f, 800.f,"jenna is really retarded and she has no life");
    }*/
    return 0;
}

//#include "Tree.h"
//#include "Node.h"
//#include <conio.h>
//#include <iostream>
//#include <Windows.h>
//
//bool check_number(string str) {//this wil take the string that will be user input and checks if all the values are 
//	for (int i = 0; i < str.length(); i++) {//goes through the length of the string 
//		if (isdigit(str[i]) == false) {//if any of the chars in the string are not digits, will return false 
//			return false;
//		}
//	}
//	return true;//otherwise return true
//}
//void gotoxy(int x, int y)//places the cursor at the (x,y) coordinate 
//{
//	COORD pos = { x, y };
//	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
//	SetConsoleCursorPosition(output, pos);
//}
//
//int main() {
//	Tree newtree;
//	cout << "1 will be to get a user input for a character " << endl << "2 will be to get a uset input to remove a character " <<endl<<"3 will be to read the values from a file " <<endl;
//	while (1) {
//		if (_kbhit()) {
//			//1 will be to get a user input for a character 
//			//2 will be to get a uset input to remove a character 
//			//3 will be to get information from a file 
//			//4 will be to exit (or another button that i choose) 
//			char ch = _getch();
//			if (ch == '1') {
//				std::system("cls");
//				cout << "input the value to add"<<endl;
//				string userinput;
//				cin >> userinput;
//				while (!check_number(userinput) && (stoi(userinput)<0)) {
//					std::system("cls");
//					cout << "invaled number, try again"<<endl;
//					cin >> userinput;
//				}
//				if (newtree.isEmpty())
//					newtree.root = newtree.insert(stoi(userinput), newtree.root);
//				else
//					newtree.insert(stoi(userinput), newtree.root);
//				std::system("cls");
//				cout << "1 will be to get a user input for a character " << endl << "2 will be to get a uset input to remove a character " << endl << "3 will be to read the values from a file " << endl;
//			}
//			else if (ch == '2') {
//				
//			}
//			else if (ch == '3') {
//				newtree.readFromFile();
//			}
//			else if (ch == '4') {
//				break;
//			}
//		}
//	}
//
//	/*if (newtree.isEmpty())
//		newtree.root = newtree.insert(50, newtree.root);
//	newtree.insert(30, newtree.root);
//	newtree.insert(20, newtree.root);
//	newtree.insert(40, newtree.root);
//	newtree.insert(70, newtree.root);
//	newtree.insert(60, newtree.root);
//	newtree.insert(80, newtree.root);
//	newtree.LNR(newtree.root);
//	newtree.deletenode(80, newtree.root);
//	cout << endl;*/
//	std::system("cls");
//	Sleep(20);
//	gotoxy(50, 50);
//	newtree.LNR(newtree.root);
//}
//
//
//
