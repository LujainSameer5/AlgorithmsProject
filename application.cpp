//========================== INFO OF GROUPS MEMBERS ============================

/*----------------------------------
 * Author: لجين سمير سالم باطوق
 * ID: 439006070
 * Section : 2
 * ---------------------------------
 * Author: نداءعاطف مهدي الجزار
 * ID: 439014419
 * Section : 1
 *  ---------------------------------
 * Author: أفراح إبراهيم بخيت الصاعدي
 * ID: 439008815
 * Section : 2
 * ---------------------------------
 * Author: عنود عبيد هليل المطرفي
 * ID: 439007307
 * Section : 1
 */

//=====================  String Matching algorithms Project ====================

/*
 
 algorithm KMP:
	input:  
		an array of characters, S (the text to be searched)
		an array of characters, W (the word sought)
	output:
		an array of integers, P (positions in S at which W is found)
		an integer, nP (number of positions)

	define variables:
		an integer, j ← 0 (the position of the current character in S)
		an integer, k ← 0 (the position of the current character in W)
		an array of integers, T (the table, computed elsewhere)

	let nP ← 0

	while j < length(S) do
		if W[k] = S[j] then
			let j ← j + 1
			let k ← k + 1
			if k = length(W) then
				(occurrence found, if only first occurrence is needed, m ← j - k  may be returned here)
				let P[nP] ← j - k, nP ← nP + 1
				let k ← T[k] (T[length(W)] can't be -1)
		else
			let k ← T[k]
			if k < 0 then
				let j ← j + 1
				let k ← k + 1
 
 
 */


 /*The time complexity of KMP is O(n), O(m*(n-m+1))*/

 //=====================implement the KMP algorithm in C++=======================


 //LIBRARIES OF US CODE
#define _CRT_SECURE_NO_WARNINGS
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include<cstdio>
#include<conio.h>
#include <Windows.h>
#include <MMSystem.h>
#include <chrono>
#include <fstream>
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

using namespace std;
int choice = 1;       //VAR TO SWITCH OF
int counter = 0;      //counterER OF DEGREE "CORRECT ASNWER" FOR PLAYER
string txt;           //VAR TO TEXT OF ALGO
string pat;           //VAR TO PATTERN OF TEXT
string name, allName; //


 //Declare Method to implement the KMP algorithm
void KMP(string X, string Y)
{                      
	const int m = X.length(); //VAR OF LENGYH OF TEXT
	const int n = Y.length(); //VAR OF LENGYH OF PATTERN
	const int nextNumber = n + 1;
	
	if (m < n)
	{ // if X's length is less than that of Y's
		cout << "\nWrong Choice\n\n";
		return;
	}

	int* next = new int[nextNumber]; // `next[i]` stores the index of the next best partial match

	for (int i = 0; i < n + 1; i++)
	{
		next[i] = 0;
	}

	for (int i = 1; i < n; i++)
	{
		int j = next[i + 1];

		while (j > 0 && Y[j] != Y[i])
		{
			j = next[j];
		}

		if (j > 0 || Y[j] == Y[i])
		{
			next[i + 1] = j + 1;
		}
	}
	
	for (int i = 0, j = 0; i < m; i++)  { //FOR LOOP TO PASSING CHAR BY CHAR IN TEXT
		
		if (X[i] == Y[j] || n == 0){ //COMPAR IF CHAR IN 'TEXT' IS SAME IN 'PATTREN' THEN,

			if (++j == n){  //COMPAR VAR '++j' IF PATTREN SAME TEXT THEN,
				cout << "\nCorrect Choice\n\n"; // SHOW MASSGE REPORT OF CHOOSING TO PLAYER
				counter++; // cout << "\n\nThe pattern occurs with shift " << i - j + 1 << "\n\n"<<endl;
				PlaySound(TEXT("success.wav"), NULL, SND_ASYNC | SND_FILENAME);
				return;

			}
		}
		else if (j > 0)//OTHERWISE, COMPAR VAR 'j' IF GREATER THAN ZERO THEN,
		{                
			j = next[j]; //INITIALISE OF VAR 'j'
			i--;         // since `i` will be incremented in the next iteration
			if (i == 0){  // IF VAR 'i' IS EQUAL ZERO THEN,
				cout << "\nWrong Choice\n\n"; // SHOW MASSGE REPORT OF CHOOSING TO PLAYER

				PlaySound(TEXT("fail.wav"), NULL, SND_ASYNC | SND_FILENAME);
				return;
			}
		}

	}

	delete[] next;
	cout << "\nWrong Choice\n\n"; // SHOW MASSGE REPORT OF CHOOSING TO PLAYER
	PlaySound(TEXT("fail.wav"), NULL, SND_ASYNC | SND_FILENAME);
}


float* glVertex_pixels(const double x, const double y) {
	float vertexPosition[2] = { (x * 2.0 / (float)WINDOW_WIDTH) - 1.0, 1.0 - (y * 2.0 / (float)WINDOW_HEIGHT) };
	return vertexPosition;
}

float rangeConvert(float x) {
	return (x * 2) - 1;
}

float normalizeWidth(float x) {
	return rangeConvert(x / WINDOW_WIDTH);
}

float normalizeHeight(float x) {
	x = WINDOW_HEIGHT - x;
	return rangeConvert(x / WINDOW_HEIGHT);
}

GLuint LoadTexture(const char* filename)
{
	GLuint texture;
	int width, height;
	unsigned char* data;

	FILE* file;
	file = fopen(filename, "rb");

	if (file == NULL) {
		printf("file not found");
		return 0;
	}
	width = 200;
	height = 50;
	data = (unsigned char*)malloc(width * height * 3);
	//int size = fseek(file,);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i < width * height; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_RECTANGLE,
		0,
		GL_RGB,
		width,
		height,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		data);


	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);

	return texture;
}

enum Action {
	EXIT,
	FILE_MATCHING,
	ENTER_GAME,
	EASY,
	MEDIUM,
	HARD,
	BACK,
	SELECT,
};

enum ActiveMode {
	MAIN_MENU,
	LEVEL_SELECT
};

ActiveMode mode = MAIN_MENU;
class Button {
public:
	GLuint id;
	float xPos;
	float yPos;
	float width;
	float height;
	float* topLeft;
	float* topRight;
	float* bottomLeft;
	float* bottomRight;
	const char* txtName;
	Action act;
	GLuint texture;

	Button(float x, float y, float w, float h, const char* txt, Action action) {
		xPos = x;
		yPos = y;
		width = w;
		height = h;
		txtName = txt;
		act = action;
		generateBorder();
		id = ++count;
	}

	void draw() {

		GLuint texture;
		texture = LoadTexture(txtName);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_POLYGON);

		glTexCoord2f(0.0, 0.0); glVertex2f(bottomRight[0], bottomRight[1]);
		glTexCoord2f(1.0, 0.0); glVertex2f(bottomLeft[0], bottomLeft[1]);
		glTexCoord2f(1.0, 1.0); glVertex2f(topRight[0], topRight[1]);
		glTexCoord2f(0.0, 1.0); glVertex2f(topLeft[0], topLeft[1]);
		glEnd();

		glDisable(GL_TEXTURE_2D);
	}
private:

	static int count;
	void generateBorder() {
		topLeft = new float[2]{ normalizeWidth(xPos) , normalizeHeight(yPos) };
		topRight = new float[2]{ normalizeWidth(xPos + width) , normalizeHeight(yPos) };
		bottomLeft = new float[2]{ normalizeWidth(xPos + width) , normalizeHeight(yPos + height) };
		bottomRight = new float[2]{ normalizeWidth(xPos) , normalizeHeight(yPos + height) };
		draw();
	}

};

void exit_callback(GLFWwindow* window) {
	std::cout << "Entered exit callback" << std::endl;
	//glfwWindowShouldClose(window);
	glfwSetWindowShouldClose(window, 1);
}

void file_matching_callback() {

	cout << "Enter name: ";
	cin >> pat;
	KMP(allName, pat);
}

void enter_game_callback(Action choice1) {
	cout << "\n\t********************************************"
		"\n\t********************************************"
		"\n\t********************************************"
		"\n\t******GAME STRING MATCHING ALGHORITHM.******"
		"\n\t********************************************"
		"\n\t********************************************"
		"\n\t********************************************\n\n";

	//int choice1;

	do
	{
		switch (choice1)
		{

		case EASY:
			cout << "\n\t****************** FIRST LEVEL ******************\n\n";
			{
				switch (choice)
				{
				case 1:
					cout << "Which path is maching this String --> ABABDABACDABABCABAB" << endl;
					txt = "ABABDABACDABABCABAB";
					cout << "1.ABABCABAB\n2.ACCA\n3.AAAB" << endl;
					cout << "Enter Your Choice: ";
					cin >> choice;
					if (choice == 1)
					{
						pat = "ABABCABAB";
						KMP(txt, pat);

					}
					else if (choice == 2)
					{
						pat = "ACCA";
						KMP(txt, pat);
					}
					else if (choice == 3)
					{
						pat = "AAAB";
						KMP(txt, pat);
					}
					else
						cout << "Invalid choice" << endl;

				case 2:
					cout << "Which path is maching this String --> ABBAB" << endl;
					txt = "ABBAB";
					cout << "1.ABB\n2.ACA\n3.AAB" << endl;
					cout << "Enter Your Choice: ";
					cin >> choice;
					if (choice == 1)
					{
						pat = "ABB";
						KMP(txt, pat);

					}
					else if (choice == 2)
					{
						pat = "ACA";
						KMP(txt, pat);
					}
					else if (choice == 3)
					{
						pat = "AAB";
						KMP(txt, pat);
					}
					else
						cout << "Invalid choice" << endl;

				case 3:
					cout << "Which path is maching this String --> CDABA" << endl;
					txt = "CDABA";
					cout << "1.BAB\n2.CDA\n3.CCA" << endl;
					cout << "Enter Your Choice: ";
					cin >> choice;
					if (choice == 1)
					{
						pat = "BAB";
						KMP(txt, pat);
					}
					else if (choice == 2)
					{
						pat = "CDA";
						KMP(txt, pat);
					}
					else if (choice == 3)
					{
						pat = "CCA";
						KMP(txt, pat);
					}
					else
						cout << "Invalid choice" << endl;

				case 4:
					cout << "Which path is maching this String --> DSEDSEDRDESDD" << endl;
					txt = "DSEDSEDRDESDD";
					cout << "1.DESS\n2.EDRD\n3.SSSB" << endl;
					cout << "Enter Your Choice: ";
					cin >> choice;
					if (choice == 1)
					{
						pat = "DESS";
						KMP(txt, pat);
					}
					else if (choice == 2)
					{
						pat = "EDRD";
						KMP(txt, pat);
					}
					else if (choice == 3)
					{
						pat = "SSSB";
						KMP(txt, pat);
					}
					else
						cout << "Invalid choice" << endl;

				case 5:
					cout << "Which path is maching this String --> FGHJKLABACDAXCVBNM" << endl;
					txt = "FGHJKLABACDAXCVBNM";
					cout << "1.XCVB\n2.CVBN\n3.AYUI" << endl;
					cout << "Enter Your Choice: ";
					cin >> choice;
					if (choice == 1)
					{
						pat = "XCVB";
						KMP(txt, pat);
					}
					else if (choice == 2)
					{
						pat = "CVBN";
						KMP(txt, pat);
					}
					else if (choice == 3)
					{
						pat = "AYUI";
						KMP(txt, pat);
					}
					else
						cout << "Invalid choice" << endl;
				}
			}
			cout << "\n\n\tYOUR DEGREE FROM 5 MARKS IS: " << counter;
			if (counter <= 3)
			{
				cout << "\n\nGOOD LUCK,But You won't be able to proceed to the Second level"
					<< "Becaues Your Degree Is Less Than 4.\n\n";
				break;
			}

			counter = 0;
			break;
		case MEDIUM:
			cout << "\n\t****************** SECOND LEVEL ******************\n\n";
			{
				switch (choice = 1)
				{
				case 1:
					cout << "Which path is maching this String --> 1628657376545678766" << endl;
					txt = "1628657376545678766";
					cout << "1.7376545\n2.7316542\n3.7377545" << endl;
					cout << "Enter Your Choice: ";
					cin >> choice;
					if (choice == 1)
					{
						pat = "7376545";
						KMP(txt, pat);
					}
					else if (choice == 2)
					{
						pat = "7316542";
						KMP(txt, pat);
					}
					else if (choice == 3)
					{
						pat = "7377545";
						KMP(txt, pat);
					}
					else
						cout << "Invalid choice" << endl;

				case 2:
					cout << "Which path is maching this String --> 765432345654321234" << endl;
					txt = "765432345654321234";
					cout << "1.6541212\n2.6543211\n3.6543212" << endl;
					cout << "Enter Your Choice: ";
					cin >> choice;
					if (choice == 1)
					{
						pat = "6541212";
						KMP(txt, pat);
					}
					else if (choice == 2)
					{
						pat = "6543211";
						KMP(txt, pat);
					}
					else if (choice == 3)
					{
						pat = "6543212";
						KMP(txt, pat);
					}
					else
						cout << "Invalid choice" << endl;

				case 3:
					cout << "Which path is maching this String --> 9843456374837526738823" << endl;
					txt = "9843456374837526738823";
					cout << "1.6738833\n2.6738823\n3.6718823" << endl;
					cout << "Enter Your Choice: ";
					cin >> choice;
					if (choice == 1)
					{
						pat = "6738833";
						KMP(txt, pat);
					}
					else if (choice == 2)
					{
						pat = "6738823";
						KMP(txt, pat);
					}
					else if (choice == 3)
					{
						pat = "6718823";
						KMP(txt, pat);
					}
					else
						cout << "Invalid choice" << endl;

				case 4:
					cout << "Which path is maching this String --> 9876543569875623432" << endl;
					txt = "9876543569875623432";
					cout << "1.76543539875\n2.76547569875\n3.76543569875" << endl;
					cout << "Enter Your Choice: ";
					cin >> choice;
					if (choice == 1)
					{
						pat = "76543539875";
						KMP(txt, pat);
					}
					else if (choice == 2)
					{
						pat = "76547569875";
						KMP(txt, pat);
					}
					else if (choice == 3)
					{
						pat = "76543569875";
						KMP(txt, pat);
					}
					else
						cout << "Invalid choice" << endl;

				case 5:
					cout << "Which path is maching this String --> 876543234567654323456543234543" << endl;
					txt = "876543234567654323456543234543";
					cout << "1.54323456\n2.59323456\n3.54323556" << endl;
					cout << "Enter Your Choice: ";
					cin >> choice;
					if (choice == 1)
					{
						pat = "54323456";
						KMP(txt, pat);
					}
					else if (choice == 2)
					{
						pat = "59323456";
						KMP(txt, pat);
					}
					else if (choice == 3)
					{
						pat = "54323556";
						KMP(txt, pat);
					}
					else
						cout << "Invalid choice" << endl;
				}
			}
			cout << "\n\n\tYOUR DEGREE FROM 5 MARKS IS: " << counter;
			if (counter <= 3)
			{
				cout << "\n\nGOOD LUCK,But You won't be able to proceed to the Second level"
					<< "Becaues Your Degree Is Less Than 4.\n\n";
				break;
			}

			counter = 0;
			break;
		case HARD:
			cout << "\n\t****************** THIRD LEVEL ******************\n\n";

			{
				switch (choice = 1)
				{
				case 1:
					cout << "Which path is maching this String --> 56SDFGFD78FG6GFD7S8DF6F7DF" << endl;
					txt = "56SDFGFD78FG6GFD7S8DF6F7DF";
					cout << "1.FD7S8DF6F\n2.FD7E8DF6F\n3.FD7S8DF2F" << endl;
					cout << "Enter Your Choice: ";
					cin >> choice;
					if (choice == 1)
					{
						pat = "FD7S8DF6F";
						KMP(txt, pat);
					}
					else if (choice == 2)
					{
						pat = "FD7E8DF6F";
						KMP(txt, pat);
					}
					else if (choice == 3)
					{
						pat = "FD7S8DF2F";
						KMP(txt, pat);
					}
					else
						cout << "Invalid choice" << endl;
				case 2:
					cout << "Which path is maching this String --> 4W5ER6FE5RF5RE6D7FGFE67RF8FG7F" << endl;
					txt = "4W5ER6FE5RF5RE6D7FGFE67RF8FG7F";
					cout << "1.RE6D7FGEE67RF8\n2.RE6D7FGFE67RF8\n3.RE6D7FGFE67UF8" << endl;
					cout << "Enter Your Choice: ";
					cin >> choice;
					if (choice == 1)
					{
						pat = "RE6D7FGEE67RF8";
						KMP(txt, pat);
					}
					else if (choice == 2)
					{
						pat = "RE6D7FGFE67RF8";
						KMP(txt, pat);
					}
					else if (choice == 3)
					{
						pat = "RE6D7FGFE67UF8";
						KMP(txt, pat);
					}
					else
						cout << "Invalid choice" << endl;

				case 3:
					cout << "Which path is maching this String --> D7F6D67S8DF76D78F76D7FG6FD78F78F7FF8" << endl;
					txt = "D7F6D67S8DF76D78F76D7FG6FD78F78F7FF8";
					cout << "1.7F6D37S8DF7\n2.7F6D67S8DF7\n3.7F3D67S8DF7" << endl;
					cout << "Enter Your Choice: ";
					cin >> choice;
					if (choice == 1)
					{
						pat = "7F6D32S8DF7";
						KMP(txt, pat);
					}
					else if (choice == 2)
					{
						pat = "7FG6FD78F7";
						KMP(txt, pat);
					}
					else if (choice == 3)
					{
						pat = "7F3D67S8DF7";
						KMP(txt, pat);
					}
					else
						cout << "Invalid choice" << endl;
					if (counter < 2)
					{
						cout << "\n\nGOOD LUCK,But You won't be able to proceed to the Second level"
							<< "Becaues Your Degree Is Less Than 4.\n\n";
						break;
					}
				case 4:
					cout << "Which path is maching this String --> RTYUJ4587643546578VBGHNJHBGVFCH4343" << endl;
					txt = "RTYUJ4587643546578VBGHNJHBGVFCH4343";
					cout << "1.7643546578VBGH\n2.7643546548VBGH\n3.7243546578VBGH" << endl;
					cout << "Enter Your Choice: ";
					cin >> choice;
					if (choice == 1)
					{
						pat = "7643546578VBGH";
						KMP(txt, pat);
					}
					else if (choice == 2)
					{
						pat = "7643546548VBGH";
						KMP(txt, pat);
					}
					else if (choice == 3)
					{
						pat = "7243546578VBGH";
						KMP(txt, pat);
					}
					else
						cout << "Invalid choice" << endl;

				case 5:
					cout << "Which path is maching this String --> 234JNK5434N54M3K45N4M3454JHGFDBNM" << endl;
					txt = "234JNK5434N54M3K45N4M3454JHGFDBNM";
					cout << "1.N4M3454JH\n2.N4M3654JH\n3.N4M3454JK" << endl;
					cout << "Enter Your Choice: ";
					cin >> choice;
					if (choice == 1)
					{
						pat = "N4M3454JH";
						KMP(txt, pat);
					}
					else if (choice == 2)
					{
						pat = "N4M3654JH";
						KMP(txt, pat);
					}
					else if (choice == 3)
					{
						pat = "N4M3454JK";
						KMP(txt, pat);
					}
					else
						cout << "Invalid choice" << endl;
				}

				if (counter == 3 || counter == 4 || counter == 5)
				{
					cout << "\n\n\tCONGRATULATIONS, YOU WON.";
				}
				cout << "\n\n\tYOUR DEGREE FROM 5 MARKS IS: " << counter;
				break;
			}
			break;
		}
	} while (choice1 != 4);
}
void nothing_callback() {};
int Button::count;
Button btn1(220, 40, 200, 50, "filematching.bmp", FILE_MATCHING);
Button btn2(220, 100, 200, 50, "entergame.bmp", ENTER_GAME);
Button btn3(220, 160, 200, 50, "exit.bmp", EXIT);
Button btns[3] = { btn1,btn2,btn3 };
Button btnEasy(220, 240, 200, 50, "easy.bmp", EASY);
Button btnMedium(220, 300, 200, 50, "medium.bmp", MEDIUM);
Button btnHard(220, 360, 200, 50, "hard.bmp", HARD);
Button levelSelectBtns[3] = { btnEasy,btnMedium,btnHard };
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		//&& && (float) xpos < btn.xPos + btn.width, (float)ypos < btn.yPos + btn.height
		for (Button btn : btns)
		{
			if ((float)xpos < btn.xPos + btn.width && (float)ypos < btn.yPos + btn.height && (float)ypos > btn.yPos && (float)xpos > btn.xPos) {
				//std::cout << "button clicked: " << btn.id << std::endl;

				switch (btn.act)
				{
				case EXIT:
					exit_callback(window);
					break;
				case FILE_MATCHING:

					file_matching_callback();

					break;
				case ENTER_GAME:
					mode = LEVEL_SELECT;
					//enter_game_callback();
					break;
				default:
					break;
				}
			}
		}
		for (Button btn : levelSelectBtns) {
			if ((float)xpos < btn.xPos + btn.width && (float)ypos < btn.yPos + btn.height && (float)ypos > btn.yPos && (float)xpos > btn.xPos) {
				switch (btn.act)
				{
				case EASY:
					enter_game_callback(EASY);
					break;
				case MEDIUM:
					enter_game_callback(MEDIUM);
					break;
				case HARD:
					enter_game_callback(HARD);
					break;
				}
			}
		}

	}
}

void initFile() {
	auto start = chrono::steady_clock::now(); //starting calculate the time
	ofstream f;                               //creat file for insirt
	f.open("neams.txt");                      //open file insert
	//write it in the file
	f << "Anoud";
	f << "Lujain";
	f << "Faiza";
	f << "Jomanah";
	f << "Omar";
	f << "Sameer";
	f << "Obaid";
	f << "Afrah";
	f << "Afnan";
	f << "Musa";
	f << "Amira";
	f << "Arwa";
	f << "Abeer";
	f << "Afaf";
	f << "Aliya";
	f.close(); //close file

	ifstream i("neams.txt");
	while (i >> name)
	{
		allName = name;
	}
	i.close();

}


int main(void)
{

	initFile();
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	/* Create a windowed mode window and its OpenGL context */
	
	window = glfwCreateWindow(640, 480, "ALGORTHIMS PROJECT", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "Error" << std::endl;


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//Buttons

		switch (mode)
		{
		case MAIN_MENU:
			for (Button btn : btns)
			{
				btn.draw();
			}
			break;
		case LEVEL_SELECT:
			for (Button btn : levelSelectBtns)
			{
				btn.draw();
			}
			break;
			break;
		default:
			break;
		}

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwSetMouseButtonCallback(window, mouse_button_callback);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
