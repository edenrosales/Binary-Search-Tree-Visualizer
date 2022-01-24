#pragma once
#include <SFML/Graphics.hpp>
#include <string> 
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include "Node.h"

using namespace std;

class Tree {
public:
	Node* root; 
	void LNR(Node* r,string&);
	void NLR(Node* r, string&);
	void LRN(Node* r,string& str1);
	Node* insert(int key, Node* r);
	Tree();
	Node* deletenode(int key, Node* r);
	Node* nextValueNode(Node* node);
	bool isEmpty();
	void readFromFile();
	void displayTree(sf::RenderWindow &theWindow, Node* r, float xloc, float yloc);
	void displayString(sf::RenderWindow& theWindow, float xloc, float yloc, string info);
};

