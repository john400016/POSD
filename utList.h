#ifndef UTLIST_H
#define UTLIST_H

#include <vector>
#include <string>
using namespace std;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
	List list;
	ASSERT_EQ( "[]" , list.symbol());
}

// Given there are two perfect numbers: 8128
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[8128]"
TEST(List, Numbers) {
	Number num(8128), num2(496);
	std::vector <Term * > v = {&num, &num2};
	List list(v);
	ASSERT_EQ( "[8128, 496]" , list.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
	Atom atom1("terence_tao") , atom2("alan_mathison_turing");
	std::vector <Term * > v = {&atom1 , &atom2};
	List list(v);
	ASSERT_EQ( "[terence_tao, alan_mathison_turing]" , list.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
	Variable X("X"), Y("Y");
	std::vector <Term * > v = {&X , &Y};
	List list(v);
	ASSERT_EQ( "[X, Y]" , list.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
	Number num(496);
	Variable X("X");
	Atom atom("terence_tao"), tom("tom");
	std::vector <Term * > v = {&tom};
	List list(v);
	ASSERT_FALSE(tom.match(list));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
	Number num(496), num2(8128);
	Variable X("X");
	Atom atom("terence_tao");
	std::vector <Term * > v = {&num, &X , &atom};
	List list(v);
	ASSERT_FALSE(num2.match(list));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
	Number num(496);
	Variable X("X");
	Atom atom("terence_tao");
	std::vector <Term * > v = {&num, &X , &atom};
	std::vector <Term * > v2 = {&X};
	List list(v);
	Struct s(Atom("s"), v2);
	ASSERT_FALSE(s.match(list));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
	Number num(496);
	Variable X("X"),Y("Y");
	Atom atom("terence_tao");
	std::vector <Term * > v = {&num, &X , &atom};
	List list(v);
	Y.match(list);
	ASSERT_EQ("[496, X, terence_tao]",Y.value());
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
	Number num(496);
	Variable X("X");
	Atom atom("terence_tao");
	std::vector <Term * > v = {&num, &X , &atom};
	List list(v);
	ASSERT_FALSE(X.match(list));

}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
	Number num(496);
	Variable X("X");
	Atom atom("terence_tao");
	std::vector <Term * > v = {&num, &X , &atom};
	List list(v);
	ASSERT_TRUE(list.match(list));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
	Number num(496);
	Variable X("X"), Y("Y");
	Atom atom("terence_tao");
	std::vector <Term * > v = {&num, &X , &atom};
	std::vector <Term * > v2 = {&num, &Y , &atom};
	List list(v);
	List list2(v2);
	ASSERT_TRUE(list.match(list2));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
	Number num(496), num2(8128);
	Variable X("X");
	Atom atom("terence_tao");
	std::vector <Term * > v = {&num, &X , &atom};
	std::vector <Term * > v2 = {&num, &num2 , &atom};
	List list(v);
	List list2(v2);
	list.match(list2);
	ASSERT_EQ("8128", X.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
	Number num(496);
	Variable X("X"), Y("Y");
	Atom atom("terence_tao"),atom2("alan_mathison_turing");
	std::vector <Term * > v = {&num, &X , &atom};
	List list(v);
	Y.match(list);
	X.match(atom2);
	ASSERT_EQ("[496, alan_mathison_turing, terence_tao]", Y.value());
	ASSERT_EQ("alan_mathison_turing", X.value());
}

// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("first"), l.head()->symbol());
  EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);
  
  EXPECT_EQ(string("second"), l.tail()->head()->value());
  EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
	Atom f("first"), s("second"), t("third");
	vector<Term *> args2 = {&f};
	List l2(args2);
	vector<Term *> args = {&l2, &s, &t};
	List l(args);
	
	EXPECT_EQ(string("[first]"), l.head()->value());
	EXPECT_EQ(string("[second, third]"), l.tail()->value());
  
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
	Atom f("first"), s("second"), t("third");
	vector<Term *> args = {&f, &s, &t};
	List l(args);
	
	EXPECT_EQ(string("third"), l.tail()->tail()->head()->value());
	EXPECT_EQ(string("[]"), l.tail()->tail()->tail()->value());
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
	List l;
	try{
		l.head();
	}catch(string s){
		EXPECT_EQ("Accessing tail in an empty list",s);
	}
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
	List l;
	try{
		l.tail();
	}catch(string s){
		EXPECT_EQ("Accessing tail in an empty list",s);
	}
}




#endif
