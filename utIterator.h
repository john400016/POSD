#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "list.h"
#include "iterator.h"
#include "number.h"

TEST(iterator, first) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    Iterator <Term*> *itStruct = s.createIterator();
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
    ASSERT_TRUE(itStruct->isDone());
}

TEST(iterator, nested_iterator) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });
  Iterator <Term*> *it = s.createIterator();
  it->first();
  it->next();
  Struct *s2 = dynamic_cast<Struct *>(it->currentItem());

  Iterator <Term*> *it2 = s2->createIterator();
  it2->first();
  ASSERT_EQ("X", it2->currentItem()->symbol());
  ASSERT_FALSE(it2->isDone());
  it2->next();
  ASSERT_EQ("2", it2->currentItem()->symbol());
  ASSERT_FALSE(it2->isDone());
  it2->next();
  ASSERT_TRUE(it2->isDone());
}

TEST(iterator, firstList) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
    ListIterator <Term*> it(&l);
    Iterator <Term*> * itList = &it;
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    ASSERT_TRUE(itList->isDone());
}

TEST(iterator, NullIterator){
  Number one(1);
  NullIterator <Term*> nullIterator(&one);
  nullIterator.first();
  ASSERT_TRUE(nullIterator.isDone());
  Iterator <Term *> * it = one.createIterator();
  it->first();
  ASSERT_TRUE(it->isDone());
}


TEST(iterator,DfsStruct){
  Number num(1) , num2(2);
  Variable X("X") , Y("Y");
  Struct t(Atom("t"), {&X,&num2});
  Struct s(Atom("s"),  {&num,&t,&Y});
  Iterator<Term*> *it = s.createDFSIterator();
  it->first();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("t(X, 2)", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}


TEST(iterator,DfsStructOfList){
  Number num(1) , num2(2);
  Variable X("X") , Y("Y");
  List l({&X,&num});
  Struct s(Atom("s"), {&num2,&l,&Y});
  Iterator<Term*> *it = s.createDFSIterator();
  it->first();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("[X, 1]", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}


TEST(iterator, BfsStruct) {
  Number num(1) , num2(2);
  Variable X("X") , Y("Y");
  Struct t(Atom("t"), {&X,&num2});
  Struct s(Atom("s"), {&num,&t,&Y});
  Iterator<Term*>*it = s.createBFSIterator();
  it->first();
  ASSERT_EQ("1",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("t(X, 2)",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2",it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}


TEST(iterator, BfsStructOfList) {
  Number num(1) , num2(2);
  Variable X("X") , Y("Y");
  List l({&X,&num});
  Struct s(Atom("s"), {&num2,&l,&Y});
  Iterator<Term*>*it = s.createBFSIterator();
  it->first();
  ASSERT_EQ("2",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("[X, 1]",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1",it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}


TEST (iterator, DfsList) {
  Number num(1) , num2(2);
  Variable X("X") , Y("Y");
  List l({&X,&num});
  List l2({&num2,&l,&Y});
  Iterator<Term*>*it = l2.createDFSIterator();
  it->first();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("[X, 1]", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}


TEST (iterator, DfsListOfStruct) {
    Number num(1) , num2(2);
    Variable X("X") , Y("Y");
  Struct s(Atom("s"), {&X,&num});
  List l({&num2,&s,&Y});
  Iterator<Term*>*it = l.createDFSIterator();
  it->first();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("s(X, 1)", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}



TEST (iterator, BfsList) {
  Number num(1) , num2(2);
  Variable X("X") , Y("Y");
  List l({&X,&num2});
  List l2({&num,&l,&Y});
  Iterator<Term*> *it = l2.createBFSIterator();
  it->first();
  ASSERT_EQ("1",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("[X, 2]",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2",it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}


TEST (iterator, BfsListOfStruct) {
  Number num(1) , num2(2);
  Variable X("X") , Y("Y");
  Struct s(Atom("s"), {&X,&num});
  List l({&num2,&s,&Y});
  Iterator<Term*> *it = l.createBFSIterator();
  it->first();
  ASSERT_EQ("2",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("s(X, 1)",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1",it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}



#endif
