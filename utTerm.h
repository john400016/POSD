#ifndef UTTERM_H
#define UTTERM_H
#include "atom.h"
#include "number.h"
#include "variable.h"

using namespace std;

//test Number.value()
TEST (Number,ctor) {

	Number num1("number", 25);
	ASSERT_EQ( "25", num1.value());

}

//test Number.symbol()
TEST (Number, symbol) {

	Number num2("number", 25);
	ASSERT_EQ( "number", num2.symbol());

}

//?- 25=25.
//true.
TEST (Number, matchSuccess) {

	Number num3("number", 25);
	Number num4("number", 25);
	ASSERT_TRUE( num3.match(num4));

}

//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {

	Number num5("number", 25);
	Number num6("number", 0);
	ASSERT_FALSE( num5.match(num6));

}

//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {

	Number num7("number", 25);
	Atom tom("tom");
	ASSERT_FALSE( num7.match(tom));

}


//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {

	Number num8("number", 25);
	Variable X("X");
	ASSERT_TRUE( num8.match(X) );
}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {

	Number num8("number", 25);
	Atom tom("tom");
	ASSERT_FALSE( tom.match(num8) );

}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {

	Variable X("X");
	Atom tom("tom");
	ASSERT_TRUE(tom.match(X));
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {

	Atom tom("tom");
	Variable X("X");
	ASSERT_TRUE(X.match(tom));
	ASSERT_TRUE(tom.match(X));

}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {

	Atom tom("tom");
	Atom jerry("jerry");
	Variable X("X");
	ASSERT_TRUE(X.match(jerry));
	ASSERT_FALSE(tom.match(X));

}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
	Number num9( "number", 5 );
 	Variable X("X");
	ASSERT_TRUE(X.match(num9));
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
	Number num10( "number", 25 );
	Number num11( "number", 100 );
 	Variable X("X");

	ASSERT_TRUE(X.match(num10));
	ASSERT_FALSE(X.match(num11));
}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
	Atom tom("tom");
	Number num12( "number", 25 );
 	Variable X("X");

 	ASSERT_TRUE(X.match(tom));
	ASSERT_FALSE(X.match(num12));

}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {

	Atom tom("tom");
	Number num13( "number", 25 );
 	Variable X("X");

 	ASSERT_TRUE(tom.match(X));
	ASSERT_FALSE(num13.match(X));

}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){

	Atom tom("tom");
 	Variable X("X");
 	ASSERT_TRUE(X.match(tom));
 	ASSERT_TRUE(X.match(tom));
}


#endif
