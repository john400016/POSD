#include "include/Sort.h"

#include <list>
using namespace std;

void Sort::sortByIncreasingPerimeter(std::list<Shape *> * shapeList){

    Shape *temp;
    
    list<Shape *>::iterator shape1 = shapeList->begin();
    list<Shape *>::iterator shape2 = next(shape1,1);
    
    for(int i = 0; i < shapeList->size() -1;i++){
	for(int j = 0; j < shapeList->size() -1 -i;j++){
	    while(shape2 != shapeList->end()){
		if((*shape1)->perimeter() > (*shape2)->perimeter()){
		    temp = *shape1;
		    *shape1 = *shape2;
		    *shape2 = temp;
	        }
		shape1 = next(shape1,1);
		shape2 = next(shape2,1);
	   }
		shape1 = shapeList->begin();
		shape2 = next(shape1,1);
	}
    }
}

void Sort::sortByDecreasingPerimeter(std::list<Shape *> * shapeList){
    
    Shape *temp;
    
    list<Shape *>::iterator shape1 = shapeList->begin();
    list<Shape *>::iterator shape2 = next(shape1,1);
    
    for(int i = 0; i < shapeList->size() -1;i++){
	for(int j = 0; j < shapeList->size() -1 -i;j++){
	    while(shape2 != shapeList->end()){
		if((*shape1)->perimeter() < (*shape2)->perimeter()){
		    temp = *shape1;
		    *shape1 = *shape2;
		    *shape2 = temp;
	        }
		shape1 = next(shape1,1);
		shape2 = next(shape2,1);
	   }
		shape1 = shapeList->begin();
		shape2 = next(shape1,1);
	}
    }
}

void Sort::sortByIncreasingArea(std::list<Shape *> * shapeList){

    Shape *temp;
    
    list<Shape *>::iterator shape1 = shapeList->begin();
    list<Shape *>::iterator shape2 = next(shape1,1);
    
    for(int i = 0; i < shapeList->size() -1;i++){
	for(int j = 0; j < shapeList->size() -1 -i;j++){
	    while(shape2 != shapeList->end()){
		if((*shape1)->area() > (*shape2)->area()){
		    temp = *shape1;
		    *shape1 = *shape2;
		    *shape2 = temp;
	        }
		shape1 = next(shape1,1);
		shape2 = next(shape2,1);
	   }
		shape1 = shapeList->begin();
		shape2 = next(shape1,1);
	}
    }
}

void Sort::sortByDecreasingArea(std::list<Shape *> * shapeList){
    //Bubble sorting
    Shape *temp;
    
    list<Shape *>::iterator shape1 = shapeList->begin();
    list<Shape *>::iterator shape2 = next(shape1,1);
    
    for(int i = 0; i < shapeList->size() -1;i++){
	for(int j = 0; j < shapeList->size() -1 -i;j++){
	    while(shape2 != shapeList->end()){
		if((*shape1)->area() < (*shape2)->area()){
		    temp = *shape1;
		    *shape1 = *shape2;
		    *shape2 = temp;
	        }
		shape1 = next(shape1,1);
		shape2 = next(shape2,1);
	   }
		shape1 = shapeList->begin();
		shape2 = next(shape1,1);
	}
    }
}
  
void Sort::sortByIncreasingCompactness(std::list<Shape *> * shapeList){

    Shape *temp;
    
    list<Shape *>::iterator shape1 = shapeList->begin();
    list<Shape *>::iterator shape2 = next(shape1,1);
    
    for(int i = 0; i < shapeList->size() -1;i++){
	for(int j = 0; j < shapeList->size() -1 -i;j++){
	    while(shape2 != shapeList->end()){
		if((*shape1)->area() > (*shape2)->area()){
		    temp = *shape1;
		    *shape1 = *shape2;
		    *shape2 = temp;
	        }
		shape1 = next(shape1,1);
		shape2 = next(shape2,1);
	   }
	}
	    
    }
}

