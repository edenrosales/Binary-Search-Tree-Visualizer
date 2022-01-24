#include "Tree.h"
#include <SFML/Graphics.hpp>


//modifies a reference to a string, in LNR order
void Tree::LNR(Node* r, string& str1)
{
	//if there is a left node, call this funciton again but with the left node
	if (r->left != nullptr) {
		LNR(r->left,str1);
	}
	str1 += to_string(r->num) + " "; //concatenate the information of this node into the string
	//if there is a right node, call this funciton again but with the right node 
	if (r->right != nullptr) {
		LNR(r->right, str1);
	}
}
//modified a refernce to a string, in RNL order
void Tree::LRN(Node* r, string& str1)
{
	//if there is a left node, call this funciton again but with the left node
	if (r->left != nullptr) {
		LRN(r->left, str1);
	}
	//if there is a right node, call this funciton again but with the right node 
	if (r->right != nullptr) {
		LRN(r->right, str1);
	}
	str1 += to_string(r->num) + " ";//concatenate the information of this node into the string
}

Node* Tree::insert(int key, Node* r)
{
	//creates a new node with the informatin that was input for the function 
    Node* newnode = new Node;
    newnode->num = key;
	newnode->left = NULL;
	newnode->right = NULL;
    Node* x = r;
    Node* y = NULL;
	//traverses the tree until we get to the end of the tree (the location that we are giong to put our new node)
	//since x is the leading variable that will alawys be one step ahead of y, x might be at a leaf node while y might not be 
	//the only time that y will be NULL is when we are adding a root to our tree 
    while (x != NULL) {
        y = x;
        if (key < x->num)
            x = x->left;
        else
            x = x->right;
    }
	//this is the case where the tree is empty
    if (y == NULL) {
        y = newnode;
    }
	//these two if statements are making sure that we input the new node in the correct position, y will be lagging behind x by one node
	//so we must move to the final node by traversing one more step to input the new node 
    else if (key < y->num)
        y->left = newnode;
    else
        y->right = newnode;
    return y;
}
//constructor for the tree 
Tree::Tree()
{
	root = NULL;
}
//deletes node from the tree 
Node* Tree::deletenode(int key, Node* r)
{
	//sets a new node called leftnode to the r
	Node* leftnode = new Node; 
	leftnode = r;
	//when we are deleting from an empty tree 
	if (r == NULL)
		return r; 
	//if the node we need to delete is smaller thn the current node, we call the functoin again with the left node 
	if (key < r->num) {
		r->left = deletenode(key, r->left);
	}
	//if the node we need to delete is larger than the current node, we call the function again with the right node
	else if (key > r->num) {
		r->right = deletenode(key, r->right);
	}
	//if the root node is the node that we need to delete 
	//this case is needed because the root node acts a little different than non-root nodes in the program
	//this is because the root node is stored as a variable in tree objects, so it needs to be directly modified here, and will not react well if it is normally mofidied like other nodes are 
	else if (key == root->num) {
		//case for when the node has one child or no children
		if (root->left == NULL)
		{
			root = root->right;
			return root;
		}
		//case for when the node has one child
		else if (root->right == NULL)
		{
			root = root->left;
			return root;
		}
		//this is the case where the node has two children 
		else {
			//we will create a new node called temp that contains the next highest value node 
			Node* temp = nextValueNode(root->right);//returns the next higher value node 
			int tempnum = temp->num;//creates a variable to store the information of the next highest value node 
			root->right = deletenode(temp->num, root->right);//deletes the next highest value node 
			root->num = tempnum;//sets the original node that we were going to delete to store the informatoin of the next higest value node 
			//that was also the node that was just deleted, effectively replacing the node that we were going to delete with the next highest value node.


			//another way to write this
			/*
			* 
			* Node* temp = nextValueNode(r->right);
			* temp->right = deletenode(temp->num, temp->right);
			* temp->left = r->left;
			* r = temp;
			*/
		}
	}
	//if a non-root node is the node that we need to delete, and the info of this node matched the info of the node we are deleting 
	else {
		//case for when the node has one child or no children
		if (r->left == NULL)
		{
			//simply returns the node to the right of this one, so that it can be reconnected to the tree, if the node has no parents, it will work, just will attach NULL
			Node* temp = r->right;
			free(r);
			return temp;
		}
		//case for when the node has one child 
		else if (r->right == NULL)
		{
			//returns the node to the left of this one, so that it can be reconnected to the tree
			Node* temp = r->left;
			free(r);
			return temp;
		}
		//case when the node has two children 
		else {//we will createa a new node called temp that holds the info of the next highest value node 
			Node* temp = nextValueNode(r->right);
			r->num = temp->num;//converting the node that we are deleting into the next highest value node
			r->right= deletenode(temp->num, r->right);//we are deleting the next highest value node, to convert the node that we are deleting, and then getting rid of the other instande of this copied node
		}
	}
	return r;//to reconnect different parts of the tree if they are deleted, this is why a return value is needed 
}
// returns the node that is all the way to the left of this node...or in other words, returns the next highest node of the node that is the parent of the node that is input 
Node* Tree::nextValueNode(Node* node)
{
	//set up a temp node that holds the input node
	Node* current = new Node;
	current = node; 
	//while there are nodes to the left, continue to change this temp node to the left node
	while (current->left != NULL || current->left !=nullptr) {
		current = node->left; 
	}
	//return the leftmost node, that will be stored in current after the loop is finished. will be the next hightest value node of the parent that is input into the original iteration of the function
	return current;
}

//checks if the tree is empty or not 
bool Tree::isEmpty()
{
	if (root == NULL)
		return true;
	return false;
}
//reads information from a file and inputs all the numbers into the tree, stops at -1 
void Tree::readFromFile()
{
	string input; //string input variable
	ifstream infile("C:/temp/input.txt");//takes the file that is at this location and opens it 
	while (getline(infile, input)) {//will get lines from the input file 
		if (input.length()>0) {//while the input is larger than 0
			if ((stoi(input) >= 0)) {//while it input is greater then -1 
				if (isEmpty())//if the tree is empty, will input the first node as the root node
					root = insert(stoi(input), root);
				else//otherwise will simply input the node into the tree
					insert(stoi(input), root);
			}
			else //if the input is -1 or lower, will not input it into the file, and breaks out of the loop, and consequently, the function
				break;
		}
	}

}

//displays the tree using SFML 
void Tree::displayTree(sf::RenderWindow& theWindow, Node* r, float xloc,  float yloc)
{
	//the function works very similarly to LNR, just instead of traversing, it will also add arrows, and instead of printing, it will print inside the nodes (circles)

	//the part of the function that draws arrows between the nodes (circles) 
	if (r->left != NULL && r->left!=nullptr) {
		sf::RectangleShape arrow;//creates arrow shape 
		arrow.setSize(sf::Vector2f(140, 5));//sets the size of the arrow 
		arrow.setRotation(135);//rotates the arrow so that its compatible with the other nodes 
		arrow.setPosition(xloc, yloc);//sets the position of the arrow 
		theWindow.draw(arrow);//draws the arrow onto the screen
		displayTree(theWindow,r->left, xloc-100.f, yloc+ 100.f);//calls the function again with the left node 
	}
	//creates a new circle that is white, with its origin in the middle of the circle, draws it into the frame 
	sf::CircleShape newcircle; 
	newcircle.setRadius(45.f);
	newcircle.setOrigin(newcircle.getRadius(), newcircle.getRadius());
	newcircle.setPosition(xloc, yloc);
	theWindow.draw(newcircle);

	/*if (!(r->right == NULL)) {
		sf::RectangleShape arrow;
		arrow.setSize(sf::Vector2f(140, 5));
		arrow.setRotation(45);
		arrow.setPosition(xloc, yloc);
		theWindow.draw(arrow);
	}
	else if (!(r->left == NULL)) {
		sf::RectangleShape arrow;
		arrow.setSize(sf::Vector2f(140, 5));
		arrow.setRotation(135);
		arrow.setPosition(xloc, yloc);
		theWindow.draw(arrow);
	}
	else {}*/
	//the part of the function that draws arrows between the nodes (circles) 
	if (r->right != NULL && r->right != nullptr) {
		sf::RectangleShape arrow; //creats an arrow shape 
		arrow.setSize(sf::Vector2f(140, 5));//sets the size of the arrow 
		arrow.setRotation(45);//stes the rotation of the arrow 
		arrow.setPosition(xloc, yloc);//sets the position of the arrow 
		theWindow.draw(arrow);//draws the arrow to the board 
		displayTree(theWindow, r->right, xloc +100.f, yloc +100.f);//iterates the function again with the node to the right 
	}
	//this section will print the numbers that are associated with each node inside of their circle (node) 
	sf::Font fonts;
	fonts.loadFromFile("arial.ttf");//obtains the arial font that is in the project files 
	sf::Text text(to_string(r->num), fonts);//convers the int value of the num property of nodes to string 
	text.setCharacterSize(30);//sets the size 
	text.setFillColor(sf::Color::Red);//sets the color 
	text.setPosition(xloc, yloc);//sets the position 
	theWindow.draw(text);//draws it to the board 
}

//this function will print the string that you ask it to, where you ask it to (onto the SFML window)
void Tree::displayString(sf::RenderWindow& theWindow, float xloc, float yloc, string info)
{
	sf::Font font;//creates font class
	font.loadFromFile("arial.ttf");//sets the font 
	sf::Text str(info, font);//makes text object 
	str.setPosition(xloc, yloc);//sets location 
	str.setCharacterSize(15);//sets font size 
	str.setFillColor(sf::Color::White);//sets the character color 
	theWindow.draw(str);//inputs the text that is going to be printed 
}

//char c;
//for (int n = 0; n < 6; n++) { //we are going to read the file 6 times over
//	ifstream infile(mazePathway1);//takes the file that is at this location and opens it 
//	for (int i = 0; i <= MAZEROWS - 1; i++) {//the loop for the rows 
//		for (int j = 0; j <= MAZECOLS - 1; j++) {//the loop for the columns 
//			infile >> c;
//			if (c == '1') {//reads ones and inputs the integer value into the array (the mouse will not be able to move here)
//				board[n][i][j] = 1;
//			}
//			else if (c == '0') {//reads 0's and inputs the integer value in the array (the mouse can move here)
//				board[n][i][j] = 0;
//			}
//			else if (c == '4')//reads 4's and intputs the integer value in the array (the mouse will not be able to move here, but when adjacent, finishes the game) 
//				board[n][i][j] = 4;
//			else//if it is none of these values, it will input a 2 integer value (mouse cannot move here)
//				board[n][i][j] = 2;
//		}
//	}
//	infile.close();//closes the file 
//}


//modifies a reference to a string, in NLR order
void Tree::NLR(Node* r, string& str1)
{
	//concatenates the string to the end of the rest of the string 
	str1 += to_string(r->num) + " ";
	//if there is a left node, travels there 
	if (r->left != nullptr) {
		NLR(r->left, str1);
	}
	if (r->right != nullptr) {//if there is a right node, travels there
		NLR(r->right, str1);
	}
	
}
