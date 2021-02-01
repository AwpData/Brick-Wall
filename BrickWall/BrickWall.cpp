// PROG 111 Trevor Tang 1/31/2021 

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

#define M_PI   3.14159265358979323846264338327950288
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)

char wndname[] = "Bricks and More Bricks";
Mat image = Mat::zeros(500, 500, CV_8UC3);
Scalar WHITE(255, 255, 255); // Colors are (B, G, R)
Scalar BRICK_RED(34, 34, 178); // I made this color for the bricks 
const int DELAY = 1;
Point _curPosition(250, 250);
int _direction = 0;

// ----------- FUNCTION PROTOTYPES ---------- //

void drawBrick(int&, int);
void drawHalfBrick(int&, int);
void drawRow(int);
void drawMultipleRows(int rows = 18);

void pointRight();
void pointLeft();
void pointUp();
void pointDown();

// 
// Must be called in main() before any other drawing function
//
void init()
{
	imshow(wndname, image); // Note: This updates the window display 
	waitKey(DELAY);
}

//
// Move the pen to the given coordinates without leaving a mark
// 
// Note (0,0)     refers to the upper left corner
//      (500,500) refers to the bottom right corner  
//
void changePosition(int x, int y)
{
	_curPosition.x = x;
	_curPosition.y = y;
}

// Changes direction according to numerical value direction 
void changeDirection(int direction)
{
	_direction = direction;
}

//
// Moves the pen forward the given number of pixels
// Note leaves a mark creating a line from the previous point
// to the new point
//
void moveForward(int nPixels)
{
	int x = static_cast<int>(round(nPixels * cos(degToRad(_direction))));
	int y = static_cast<int>(round(nPixels * sin(degToRad(_direction))));

	Point newPoint = Point(x + _curPosition.x, y + _curPosition.y);
	line(image, _curPosition, newPoint, WHITE, 4); // (image, first point, second point, color, thickness)
	_curPosition = newPoint;
	// cout << "moved to " << newPoint.x << "," << newPoint.y << endl;
	imshow(wndname, image);
	waitKey(DELAY);
}

// X-position and Y-position of the first brick 
int xpos = 25;
int ypos = 25;

// -------------- MAIN ------------- // 
int main()
{
	init();
	cout << "Building brick wall..." << endl;
	drawMultipleRows(); // Put a number into the parameters (must be less than or equal to 18 to fit) to change number of brick rows 
	system("cls");
	cout << "Brick wall complete!" << endl;
	waitKey();
}

// ------ HELPER FUNCTIONS -------- //

// Draws a brick at (xpos, ypos)
void drawBrick(int& xpos, int ypos) {
	changePosition(xpos, ypos);

	// Code to fill in bricks with red 
	Point p1 = Point(xpos, ypos); // Top-left point of brick
	Point p2 = Point(xpos + 50, ypos + 25); // Bottom-right point of brick
	rectangle(image, p1, p2, BRICK_RED, FILLED); // Makes a rectangle filled with Red at the defined points above 

	moveForward(50);
	pointDown();
	moveForward(25);
	pointLeft();
	moveForward(50);
	pointUp();
	moveForward(25);
	pointRight();
	xpos += 50; // Adjust x-pos for next brick
}

// Draws a half-brick at (xpos, ypos)
void drawHalfBrick(int& xpos, int ypos) {
	changePosition(xpos, ypos);

	// Code to fill in half-bricks with red
	Point p1 = Point(xpos, ypos);
	Point p2 = Point(xpos + 25, ypos + 25);
	rectangle(image, p1, p2, BRICK_RED, FILLED);

	moveForward(25);
	pointDown();
	moveForward(25);
	pointLeft();
	moveForward(25);
	pointUp();
	moveForward(25);
	pointRight();
	xpos += 25; // Adjust x-pos for next brick 
}

// Draws a row of bricks with the length specified by numOfBricks
void drawRow(int numOfBricks) {
	for (int i = 0; i < numOfBricks; i++) {
		drawBrick(xpos, ypos);
	}
}

// Default Arguments (or empty parameters on function call) will draw 18 rows 
void drawMultipleRows(int rows) {

	for (int i = 1; i <= rows; i++) {
		// Just some funny messages that will print while the brick wall is building
		if (i == (int)(rows * 0.25)) {
			system("cls");
			cout << "Did you know these bricks are made of bytes instead of clay?" << endl;
		}
		if (i == (int)(rows / 2)) {
			system("cls");
			cout << "I'm halfway done, I'm only one computer!" << endl;
		} if (i == (int)(rows * 0.75)) {
			system("cls");
			cout << "Almost there, I'm starting to get tired..." << endl;
		}

		// This is how I decide what which row should draw (if 'i' is even, then don't draw a wall with half bricks and vice versa for else) 
		if (i % 2 == 0) {
			drawRow(9);
		}
		else {
			drawHalfBrick(xpos, ypos);
			drawRow(8);
			drawHalfBrick(xpos, ypos);
		}

		// We are done building a row, so we must reset the xpos and increase the ypos to build another row if needed 
		ypos += 25;
		xpos = 25;
	}
}

//
// The functions help simplify change direction to point in the direction given in degrees
// 0   ==> point right
// 90  ==> point down
// 180 ==> point left
// 270 ==> point up
//

void pointRight() {
	changeDirection(0);
}

void pointLeft() {
	changeDirection(180);
}

void pointUp() {
	changeDirection(270);
}

void pointDown() {
	changeDirection(90);
}
