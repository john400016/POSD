#ifndef utSort_H
#define utSort_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"
#include <list>
using namespace std;

TEST (Sort, sortByIncreasingPerimeter) {
	
	/*Triangle tri1({0,0},{0,1},{1,0});
	Triangle tri2({0,0},{0,2},{2,0});
	Triangle tri3({0,0},{0,3},{3,0});
	
	Rectangle rec1(0,0,10,9);
	Rectangle rec2(0,0,11,9);
	Rectangle rec3(0,0,9,9);
	Rectangle rec4(0,0,1,1);*/
	
	Circle cir1(0,0,35);
	Circle cir2(0,0,15);
	Circle cir3(0,0,45);
	Circle cir4(0,0,25);
	Circle cir5(0,0,55);

	list<Shape *>myshape;

	/*myshape.push_back(&tri1);
	myshape.push_back(&tri2);
	myshape.push_back(&tri3);

	myshape.push_back(&rec1);
	myshape.push_back(&rec2);
	myshape.push_back(&rec3);
	myshape.push_back(&rec4);*/

	myshape.push_back(&cir1);
	myshape.push_back(&cir2);
	myshape.push_back(&cir3);
	myshape.push_back(&cir4);
	myshape.push_back(&cir5);

	Sort sort;
	sort.sortByIncreasingPerimeter(&myshape);
	
	EXPECT_EQ(cir5 .perimeter(),(*myshape.back()).perimeter());
}

TEST (Sort, sortByDecreasingPerimeter) {

	/*Triangle tri1({0,0},{0,1},{1,0});
	Triangle tri2({0,0},{0,2},{2,0});
	Triangle tri3({0,0},{0,3},{3,0});
	
	Rectangle rec1(0,0,10,9);
	Rectangle rec2(0,0,11,9);
	Rectangle rec3(0,0,9,9);
	Rectangle rec4(0,0,1,1);*/
	
	Circle cir1(0,0,35);
	Circle cir2(0,0,15);
	Circle cir3(0,0,45);
	Circle cir4(0,0,25);

	list<Shape *>myshape;

	/*myshape.push_back(&tri1);
	myshape.push_back(&tri2);
	myshape.push_back(&tri3);

	myshape.push_back(&rec1);
	myshape.push_back(&rec2);
	myshape.push_back(&rec3);
	myshape.push_back(&rec4);*/

	myshape.push_back(&cir1);
	myshape.push_back(&cir2);
	myshape.push_back(&cir3);
	myshape.push_back(&cir4);

	Sort sort;
	sort.sortByDecreasingPerimeter(&myshape);
	
	EXPECT_EQ(cir2 .perimeter(),(*myshape.back()).perimeter());
}

TEST (Sort, sortByIncreasingArea) {

	/*Triangle tri1({0,0},{0,1},{1,0});
	Triangle tri2({0,0},{0,2},{2,0});
	Triangle tri3({0,0},{0,3},{3,0});
	
	Rectangle rec1(0,0,10,9);
	Rectangle rec2(0,0,11,9);
	Rectangle rec3(0,0,9,9);
	Rectangle rec4(0,0,1,1);*/
	
	Circle cir1(0,0,35);
	Circle cir2(0,0,15);
	Circle cir3(0,0,45);
	Circle cir4(0,0,25);

	list<Shape *>myshape;

	/*myshape.push_back(&tri1);
	myshape.push_back(&tri2);
	myshape.push_back(&tri3);

	myshape.push_back(&rec1);
	myshape.push_back(&rec2);
	myshape.push_back(&rec3);
	myshape.push_back(&rec4);*/

	myshape.push_back(&cir1);
	myshape.push_back(&cir2);
	myshape.push_back(&cir3);
	myshape.push_back(&cir4);

	Sort sort;
	sort.sortByIncreasingArea(&myshape);
	
	EXPECT_EQ(cir3 .area(),(*myshape.back()).area());
}

TEST (Sort, sortByDecreasingArea) {

	/*Triangle tri1({0,0},{0,1},{1,0});
	Triangle tri2({0,0},{0,2},{2,0});
	Triangle tri3({0,0},{0,3},{3,0});*/
	
	Rectangle rec1(0,0,12,9);
	Rectangle rec2(0,0,11,9);
	Rectangle rec3(0,0,10,1);
	Rectangle rec4(0,0,1,1);
	
	/*Circle cir1(0,0,35);
	Circle cir2(0,0,15);
	Circle cir3(0,0,45);
	Circle cir4(0,0,25);*/

	list<Shape *>myshape;

	/*myshape.push_back(&tri1);
	myshape.push_back(&tri2);
	myshape.push_back(&tri3);*/

	myshape.push_back(&rec1);
	myshape.push_back(&rec2);
	myshape.push_back(&rec3);
	myshape.push_back(&rec4);

	/*myshape.push_back(&cir1);
	myshape.push_back(&cir2);
	myshape.push_back(&cir3);
	myshape.push_back(&cir4);*/

	Sort sort;
	sort.sortByDecreasingArea(&myshape);
	
	EXPECT_EQ(rec4.area(),(*myshape.back()).area());
}

TEST (Sort, sortByIncreasingCompactness) {

	/*Triangle tri1({0,0},{0,3},{4,0});
	Triangle tri2({0,0},{0,5},{12,0});
	Triangle tri3({0,0},{0,3},{3,0});*/
	
	/*Rectangle rec1(0,0,10,9);
	Rectangle rec2(0,0,11,9);
	Rectangle rec3(0,0,9,9);
	Rectangle rec4(0,0,1,1);*/
	
	Circle cir1(0,0,35);
	Circle cir2(0,0,15);
	Circle cir3(0,0,45);
	Circle cir4(0,0,55);
	Circle cir5(0,0,25);

	list<Shape *>myshape;

	/*myshape.push_back(&tri1);
	myshape.push_back(&tri2);
	myshape.push_back(&tri3);*/

	/*myshape.push_back(&rec1);
	myshape.push_back(&rec2);
	myshape.push_back(&rec3);
	myshape.push_back(&rec4);*/

	myshape.push_back(&cir1);
	myshape.push_back(&cir2);
	myshape.push_back(&cir3);
	myshape.push_back(&cir4);
	myshape.push_back(&cir5);
	
	Sort sort;
	sort.sortByIncreasingCompactness(&myshape);
	 
	
	EXPECT_EQ( cir4 .area()/cir4.perimeter() , (*myshape.back()).area()/(*myshape.back()).perimeter());
	
}

#endif
