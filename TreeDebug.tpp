#include <iostream>
#include "Print.hpp"

template <typename T>
Tree<T>::TreeDebug::TreeDebug(void){
	this->success=false;
}

template <typename T>
bool Tree<T>::TreeDebug::run(void){
	this->success=(this->debugObjectMethods());//this->debugClassMethods()
	Print::objectDebug(std::cout,"Tree",this->success);
	return this->success;
}

template <typename T>
bool Tree<T>::TreeDebug::debugObjectMethods(void){
	return (this->debugConstructor() &&
		this->debugEmplace() &&
		this->debugEmplaceBelow() &&
		this->debugIterator() &&
		this->debugEraseBelow() &&
		this->debugErase() &&
		this->debugClear() &&
		this->debugCopyConstructor() &&
		this->debugFind() &&
		this->debugCount());
}

template <typename T>
bool Tree<T>::TreeDebug::debugConstructor(void){
	Tree<int> test;
	Tree<int> test2(1);
	return (test.size()==0 && test2.size()==1);
}

template <typename T>
bool Tree<T>::TreeDebug::debugEmplace(void){
	bool rv=true;
	Tree<int> test(1);
	Tree<int>::iterator iter=test.begin();
	test.emplace(2);
	rv&=(*iter==1);
	iter++;
	rv&=(*iter==2);
	rv&=(test.size()==2);

	Tree<int> test2;
	test2.emplace(1);
	test2.emplace(2);
	Tree<int>::iterator iter2=test2.begin();
	rv&=(*iter2==1);
	iter2++;
	rv&=(*iter2==2);
	rv&=(test2.size()==2);
	return rv;
}

template <typename T>
bool Tree<T>::TreeDebug::debugEmplaceBelow(void){
	bool rv=true;
	std::vector<int> correct={ 1,3,4,2 };
	Tree<int> test(1);
	Tree<int>::iterator iter=test.begin();
	test.emplace(2);
	test.emplaceBelow(iter,3);
	test.emplaceBelow(iter,4);
	for (int i=0; i<4; i++, iter++){
		rv&=(*iter==correct[i]);
	}
	rv&=(test.size()==4);
	return rv;
}

template <typename T>
bool Tree<T>::TreeDebug::debugIterator(void){
	bool rv=true;
	std::vector<int> correct={ 0,5,15,16,17,18,19,6,7,8,9,1,10,11,12,13,14,2,3,4 };
	std::vector<int> correctRepeat={ 0,5,15,16,17,18,19,5,6,7,8,9,0,1,10,11,12,13,14,1,2,3,4 };
	Tree<int> test=this->createDebugTestTree();
	rv&=(test.size()==20);
	int i=0;
	for (Tree<int>::iterator iter3=test.begin(); iter3!=test.end(); iter3++, i++){
		rv&=(*iter3==correct[i]);
	}
	i=0;
	for (Tree<int>::iterator iter4=test.begin(true); iter4!=test.end(); iter4++, i++){
		rv&=(*iter4==correctRepeat[i]);
	}
	return rv;
}

template <typename T>
bool Tree<T>::TreeDebug::debugEraseBelow(void){
	bool rv=true;
	std::vector<int> correct={ 0,5,6,7,8,9,1,10,11,12,13,14,2,3,4 };
	Tree<int> test=this->createDebugTestTree();
	rv&=(test.size()==20);

	Tree<int>::iterator iter=test.begin();
	iter++;
	rv&=(*iter==5);
	//std::cout << "iter: " << *iter << std::endl;
	test.eraseBelow(iter);
	int i=0;
	for (Tree<int>::iterator iter2=test.begin(); iter2!=test.end(); iter2++, i++){
		rv&=(*iter2==correct[i]);
		//std::cout << "iter: " << *iter2 << " corr: " << correct[i] << std::endl;
	}
	return rv;
}

template <typename T>
bool Tree<T>::TreeDebug::debugErase(void){
	bool rv=true;
	std::vector<int> correct={ 0,6,7,8,9,1,10,11,12,13,14,2,3,4 };
	std::vector<int> correct2={ 0,6,7,8,9,2,3,4 };
	std::vector<int> correct3={ 0,6,8,9,2,3,4 };
	std::vector<int> correct4={ 2,3,4 };
	Tree<int> test=this->createDebugTestTree();
	rv&=this->debugEraseHelp(test,correct,5,6);
	rv&=this->debugEraseHelp(test,correct2,1,2);
	rv&=this->debugEraseHelp(test,correct3,7,8);
	rv&=this->debugEraseHelp(test,correct4,0,2);
	return rv;
}

template <typename T>
bool Tree<T>::TreeDebug::debugClear(void){
	bool rv=true;
	Tree<int> test=this->createDebugTestTree();
	test.clear();
	Tree<int>::iterator iter=test.begin();
	rv&=(iter==test.end());
	rv&=(test.size()==0);
	return rv;
}

template <typename T>
bool Tree<T>::TreeDebug::debugCopyConstructor(void){
	bool rv=true;
	Tree<int> other=this->createDebugTestTree();
	Tree<int> test=other;
	Tree<int>::iterator otherIter=other.begin();
	Tree<int>::iterator testIter=test.begin();
	for (; otherIter!=other.end() && testIter!=test.end(); otherIter++, testIter++){
		rv&=(*testIter==*otherIter);
		rv&=(testIter.operator->()!=otherIter.operator->());
		//Pointers to nodes should not equal, would imply shallow copy
	}
	return rv;
}

template <typename T>
bool Tree<T>::TreeDebug::debugFind(void){
	bool rv=true;
	Tree<int> test=this->createDebugTestTree();
	Tree<int>::iterator iter=test.begin();
	for (int i=0; i<7; i++, iter++);
	Tree<int>::iterator iter2=test.find(iter,12);
	rv&=(*iter2==12);
	Tree<int>::iterator iter3=test.find(iter2,5);
	rv&=(iter3==test.end());

	Tree<int>::iterator iter4=test.find(14);
	rv&=(*iter4==14);
	Tree<int>::iterator iter5=test.find(100);
	rv&=(iter5==test.end());
	return rv;
}

template <typename T>
bool Tree<T>::TreeDebug::debugCount(void){
	bool rv=true;
	Tree<int> test=this->createDebugTestTree();
	test.emplace(12);
	rv&=(test.count(5)==1);
	rv&=(test.count(12)==2);
	return rv;
}

template <typename T>
Tree<int> Tree<T>::TreeDebug::createDebugTestTree(void) const {
	Tree<int> rv(0);
	Tree<int>::iterator iter=rv.begin();
	for (int i=1; i<5; rv.emplace(i), i++);
	Tree<int>::iterator iter2=rv.begin();
	iter2++;
	for (int i=5; i<10; rv.emplaceBelow(iter,i), i++);
	for (int i=10; i<15; rv.emplaceBelow(iter2,i), i++);
	iter++;
	for (int i=15; i<20; rv.emplaceBelow(iter,i), i++);
	return rv;
}

template <typename T>
bool Tree<T>::TreeDebug::debugEraseHelp(Tree<int> &test, std::vector<int> &correct, int delNum, int next){
	bool rv=true;
	Tree<int>::iterator iter=test.begin();
	for(; *iter!=delNum; iter++);
	Tree<int>::iterator nextIter=test.erase(iter);
	rv&=((unsigned int)test.size()==correct.size());
	int i=0;
	for (Tree<int>::iterator iter2=test.begin(); 
		rv && iter2!=test.end(); iter2++, i++){
		rv&=(*iter2==correct[i]);
	}
	rv&=(*nextIter==next);
	return rv;
}
