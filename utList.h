#ifndef UTLIST_H
#define UTLIST_H

#include <string>
#include <exception>
using std::string;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) 
{
    List mylist;
    ASSERT_EQ("[]", mylist.symbol());
}

// Given there are two perfect numbers: 8128
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[8128]"
TEST(List, Numbers) 
{
    Number num(8128);
    std::vector<Term*> v = {&num};
    List mylist(v);
    ASSERT_EQ("[8128]", mylist.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) 
{
    Atom a1("terence_tao"),a2("alan_mathison_turing");
    std::vector<Term*> v = {&a1, &a2};
    List mylist(v);
    ASSERT_EQ("[terence_tao, alan_mathison_turing]", mylist.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) 
{
    Variable var1("X");
    Variable var2("Y");
    std::vector<Term*> v = {&var1, &var2};
    List mylist(v);
    ASSERT_EQ("[X, Y]", mylist.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) 
{
    Atom tom("tom");
    Number num(496);
    Variable var("X");
    Atom a("terence_tao");
    std::vector<Term*> v = {&num, &var, &a};
    List mylist(v);
    ASSERT_FALSE(tom.match(mylist));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) 
{
    Number num1(8128);
    Number num2(496);
    Variable var("X");
    Atom a("terence_tao");
    std::vector<Term*> v = {&num2, &var, &a};
    List mylist(v);
    ASSERT_FALSE(num1.match(mylist));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) 
{
    Variable var("X");
    std::vector<Term*> v1 = {&var};
    Struct s(Atom("X"), v1);
    Number num(496);
    Atom a("terence_tao");
    std::vector<Term*> v2 = {&num, &var, &a};
    List mylist(v2);
    ASSERT_FALSE(s.match(mylist));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) 
{
    Variable Y("Y");
    Number num(496);
    Variable var("X");
    Atom a("terence_tao");
    std::vector<Term*> v = {&num, &var, &a};
    List mylist(v);
    ASSERT_TRUE(Y.match(mylist));
    ASSERT_EQ("[496, X, terence_tao]", Y.value());
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) 
{
    Variable X("X");
    Number num(496);
    Atom a("terence_tao");
    std::vector<Term*> v = {&num, &X, &a};
    List mylist(v);
    ASSERT_FALSE(X.match(mylist));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) 
{
    Variable X("X");
    Number num(496);
    Atom a("terence_tao");
    std::vector<Term*> v = {&num, &X, &a};
    List mylist(v);
    ASSERT_TRUE(mylist.match(mylist));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) 
{
    Variable Y("Y");
    Variable X("X");
    Number num(496);
    Atom a("terence_tao");
    std::vector<Term*> v1 = {&num, &X, &a};
    std::vector<Term*> v2 = {&num, &Y, &a};
    List list1(v1), list2(v2);
    ASSERT_TRUE(list1.match(list2));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) 
{
    Number num1(496),num2(8128);
    Variable X("X");
    Atom a("terence_tao");
    std::vector<Term*> v1 = {&num1, &X, &a};
    std::vector<Term*> v2 = {&num1, &num2, &a};
    List list1(v1), list2(v2);
    ASSERT_TRUE(list1.match(list2));
    ASSERT_TRUE(list2.match(list1));
    ASSERT_EQ("8128", X.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) 
{
    Number num1(496);
    Variable Y("Y");
    Variable X("X");
    Atom a1("terence_tao"), a2("alan_mathison_turing"); 
    std::vector<Term*> v1 = {&num1, &X, &a1};
    List list1(v1);
    ASSERT_TRUE(Y.match(list1));
    ASSERT_TRUE(X.match(a2));
    ASSERT_EQ("[496, alan_mathison_turing, terence_tao]", Y.value());
    ASSERT_EQ("alan_mathison_turing", X.value());
}
// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) 
{
    Atom f("first"), s("second"), t("third");
    vector<Term *> args = {&f, &s, &t};
    List l(args);
    
    EXPECT_EQ(string("first"), l.head()->symbol());
    EXPECT_EQ(string("[second, third]"), l.tail()->value());
}


// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) 
{
    Atom f("first"), s("second"), t("third");
    vector<Term *> args ={&f, &s, &t};
    List l(args);
    
    EXPECT_EQ(string("second"),  l.tail()->head()->value());
    EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) 
{
    Atom f("first"), s("second"), t("third");
    vector<Term *> args1 = {&f};
    List lf(args1);
    vector<Term *> args2 ={&lf, &s, &t};
    List l(args2);
    
    EXPECT_EQ(string("[first]"), l.head()->symbol());
    EXPECT_EQ(string("[second, third]"), l.tail()->value());
}


// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) 
{
    Atom f("first"), s("second"), t("third");
    vector<Term *> args ={&f, &s, &t};
    List l(args);
    
    EXPECT_EQ(string("third"), l.tail()->tail()->head()->symbol());
    EXPECT_EQ(string("[]"), l.tail()->tail()->tail()->value());
}


// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) 
{
    Atom f("first"), s("second"), t("third");
    vector<Term *> args ={&f, &s, &t};
    List l(args);
//  ASSERT_THROW(l.head(), std::string("Accessing head in an empty list"));
    ASSERT_THROW(l.head(), std::string);
}


// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) 
{
    List l;
    ASSERT_THROW(l.head(), std::string);
//  ASSERT_THROW(l.tail(), std::string("Accessing tail in an empty list"));
}
#endif
