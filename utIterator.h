#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "list.h"
#include "iterator.h"
#include "number.h"

TEST(iterator, first)
{
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    // StructIterator it(&s);
    Iterator<Term*> *itStruct = s.createIterator();
    // Iterator& itStruct = it;
    // ASSERT_EQ(it.first()->symbol());
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

TEST(iterator, nested_iterator) 
{
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    Iterator<Term*> *it = s.createIterator();
    it->first();
    it->next();
    Struct *s2 = dynamic_cast<Struct *>(it->currentItem());

    Iterator<Term*> *it2 = s2->createIterator();
    it2->first();
    ASSERT_EQ("X", it2->currentItem()->symbol());
    ASSERT_FALSE(it2->isDone());
    it2->next();
    ASSERT_EQ("2", it2->currentItem()->symbol());
    ASSERT_FALSE(it2->isDone());
    it2->next();
    ASSERT_TRUE(it2->isDone());
}

TEST(iterator, firstList) 
{
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
    Iterator<Term*>* itList = l.createIterator();
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

TEST(iterator, NullIterator)
{
    Number one(1);
    Iterator<Term*> * it = one.createIterator();
    one.createDFSIterator();
    it->first();
    ASSERT_TRUE(it->isDone());
}

TEST(iterator,TreeDFSIteratorStruct)
{
    //s(1, t(1, 2), X) 
    Number _1(1) , _2(2);
    Variable X("X");
    vector<Term*> v = {&_1,&_2};
    Struct t(Atom("t"), v);
    vector<Term*> v2 = {&_1,&t,&X};
    Struct s(Atom("s"), v2);
    Iterator<Term*> *it = s.createDFSIterator();
    it->first();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("t(1, 2)", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}

TEST(iterator,TreeDFSIteratorStruct_2)
{
    //s(t(1, 2, [3, X, [4, 5]]), Y, 6) 
    Number _1(1), _2(2), _3(3), _4(4), _5(5), _6(6); 
    Variable X("X"), Y("Y"); 
    List list2(vector<Term*>{&_4, &_5}); 
    List list1(vector<Term*>{&_3, &X, &list2}); 
    Struct t(Atom("t"), vector<Term*>{&_1, &_2, &list1}); 
    Struct s(Atom("s"), vector<Term*>{&t , &Y, &_6});
    Iterator<Term*>* it = s.createDFSIterator();
    it->first();
    ASSERT_EQ("t(1, 2, [3, X, [4, 5]])", it->currentItem()->symbol()); 
    it->next(); 
    ASSERT_EQ("1", it->currentItem()->symbol()); 
    it->next(); 
    ASSERT_EQ("2", it->currentItem()->symbol()); 
    it->next(); 
    ASSERT_EQ("[3, X, [4, 5]]", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("3", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("[4, 5]", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("4", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("5", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("6", it->currentItem()->symbol()); 
    it->next();
    ASSERT_TRUE(it->isDone());
}

TEST(iterator, TreeBFSIteratorStruct) 
{
    //s(1, t(1, 2), X) 
    Number _1(1) , _2(2);
    Variable X("X");
    vector<Term*> v = {&_1,&_2};
    Struct t(Atom("t"), v);
    vector<Term*> v2 = {&_1,&t,&X};
    Struct s(Atom("s"), v2);
    Iterator<Term*> *it = s.createBFSIterator();
    it->first();
    ASSERT_EQ("1",it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("t(1, 2)",it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X",it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1",it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2",it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}

TEST(iterator, TreeBFSIteratorStruct_2)
{
    //s(t(1, 2, [3, X, [4, 5]]), Y, 6) 
    Number _1(1), _2(2), _3(3), _4(4), _5(5), _6(6); 
    Variable X("X"), Y("Y"); 
    List list2(vector<Term*>{&_4, &_5}); 
    List list1(vector<Term*>{&_3, &X, &list2}); 
    Struct t(Atom("t"), vector<Term*>{&_1, &_2, &list1}); 
    Struct s(Atom("s"), vector<Term*>{&t , &Y, &_6});
    Iterator<Term*>* it = s.createBFSIterator();
    it->first();
    ASSERT_EQ("t(1, 2, [3, X, [4, 5]])", it->currentItem()->symbol()); 
    it->next(); 
    ASSERT_EQ("Y", it->currentItem()->symbol()); 
    it->next(); 
    ASSERT_EQ("6", it->currentItem()->symbol()); 
    it->next(); 
    ASSERT_EQ("1", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("[3, X, [4, 5]]", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("3", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("[4, 5]", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("4", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("5", it->currentItem()->symbol()); 
    it->next();
    ASSERT_TRUE(it->isDone());

}

TEST (iterator, TreeDFSIteratorList) 
{
    //[1, t(1, 2), X]
    Number _1(1) , _2(2);
    Variable X("X");
    vector<Term*> v = {&_1,&_2};
    Struct t(Atom("t"), v);
    vector<Term*> v2 = {&_1,&t,&X};
    List l(v2);
    Iterator<Term*> *it = l.createDFSIterator();
    it->first();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("t(1, 2)", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}

TEST (iterator, TreeDFSIteratorList_2) 
{
    //[t(1, 2, [3, X, [4, 5]]), Y, 6] 
    Number _1(1), _2(2), _3(3), _4(4), _5(5), _6(6); 
    Variable X("X"), Y("Y"); 
    List list2(vector<Term*>{&_4, &_5}); 
    List list1(vector<Term*>{&_3, &X, &list2}); 
    Struct t(Atom("t"), vector<Term*>{&_1, &_2, &list1}); 
    List l(vector<Term*>{&t , &Y, &_6});
    Iterator<Term*>* it = l.createDFSIterator();
    it->first();
    ASSERT_EQ("t(1, 2, [3, X, [4, 5]])", it->currentItem()->symbol()); 
    it->next(); 
    ASSERT_EQ("1", it->currentItem()->symbol()); 
    it->next(); 
    ASSERT_EQ("2", it->currentItem()->symbol()); 
    it->next(); 
    ASSERT_EQ("[3, X, [4, 5]]", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("3", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("[4, 5]", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("4", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("5", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("6", it->currentItem()->symbol()); 
    it->next();
    ASSERT_TRUE(it->isDone());
}

TEST (iterator, TreeBFSIteratorList) 
{
    //[1, t(1, 2), X] 
    Number _1(1) , _2(2);
    Variable X("X");
    vector<Term*> v = {&_1,&_2};
    Struct t(Atom("t"), v);
    vector<Term*> v2 = {&_1,&t,&X};
    List l(v2);
    Iterator<Term*> *it = l.createBFSIterator();
    it->first();
    ASSERT_EQ("1",it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("t(1, 2)",it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X",it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1",it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2",it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}

TEST (iterator, TreeBFSIteratorList_2)
{
    //[t(1, 2, [3, X, [4, 5]]), Y, 6] 
    Number _1(1), _2(2), _3(3), _4(4), _5(5), _6(6); 
    Variable X("X"), Y("Y"); 
    List list2(vector<Term*>{&_4, &_5}); 
    List list1(vector<Term*>{&_3, &X, &list2}); 
    Struct t(Atom("t"), vector<Term*>{&_1, &_2, &list1}); 
    List l(vector<Term*>{&t , &Y, &_6});
    Iterator<Term*>* it = l.createBFSIterator();
    it->first();
    ASSERT_EQ("t(1, 2, [3, X, [4, 5]])", it->currentItem()->symbol()); 
    it->next(); 
    ASSERT_EQ("Y", it->currentItem()->symbol()); 
    it->next(); 
    ASSERT_EQ("6", it->currentItem()->symbol()); 
    it->next(); 
    ASSERT_EQ("1", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("[3, X, [4, 5]]", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("3", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("[4, 5]", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("4", it->currentItem()->symbol()); 
    it->next();
    ASSERT_EQ("5", it->currentItem()->symbol()); 
    it->next();
    ASSERT_TRUE(it->isDone());  
}
#endif
