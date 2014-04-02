#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

const int NODEERROR = -1;
const int NEWERROR = -2;
const int SUCCESS = 1;
const int DONOTHING = 0;

//----------------------------------------------
template <class T>
struct bTreeType
{
	T	data;
	struct bTreeType *leftChild;
	struct bTreeType *rightChild;
};
//----------------------------------------------

template <class T>
class binTree
{
public:
	binTree();
	binTree(const binTree<T> &btree);
	binTree& operator=(const binTree &btree);
	virtual ~binTree();

	void travel();
	int buildByArray(T *array,int len)	;
	int addData(T data);
//	binTree* find(T data,binTree& *pFather);
	bool del(T data);
	int initNode(struct bTreeType<T>** btreeNode);
	int destory(struct bTreeType<T>* btreenode);
	void copyBTree(struct bTreeType<T> **dstHead,struct bTreeType<T> **srcHead);

private:
	void  _travel(struct bTreeType<T>* pNode);
	int _add(T data,struct bTreeType<T>* btreeNode);
private:
	struct bTreeType<T> * head;
};






//Filename:BinTree.cpp
//Author:Ryan
//Date:Mon Mar 24 09:06:25 CST 2014

template <class T>
binTree<T>::binTree():head(NULL)
{
/*
	head = new struct bTreeType<T>;
	memset(head,'/0',sizeof(struct bTreeType<T>));	
	head->leftChild = NULL;
	head->rightChild = NULL;	
*/
}
//------------------------------------------------------
template <class T>
binTree<T>::binTree(const binTree<T> &btree)
	: head(NULL)
{
	copyBTree(&(this->head),&(btree.head) );	
	
}
//------------------------------------------------------
template<class T>
void binTree<T>::copyBTree(struct bTreeType<T> **dstHead,struct bTreeType<T> **srcHead)
{
	if(*srcHead == NULL)
	{
		*dstHead = NULL;
		return;
	}	

	*dstHead = new struct bTreeType<T>;
	if(*dstHead == NULL)

	(*dstHead)->data = (*srcHead)->data;
	copyBTree(&(dstHead->leftChild),&(srcHead->leftChild) );
	copyBTree(&(dstHead->rightChild),&(srcHead->rightChild) );
}
//------------------------------------------------------
template <class T>
binTree<T>::~binTree()
{
	this->destory(this->head);	
}
//------------------------------------------------------
template <class T>
int binTree<T>::addData(T data)
{
	_add(data,this->head);
}
//------------------------------------------------------
template <class T>
int binTree<T>::buildByArray(T *array,int len)
{
	
	int i = 0;
	for(i=0;i<len;++i)
	{
		this->addData(array[i]);
	}
}
//------------------------------------------------------
template <class T>
int binTree<T>::_add(T data,struct bTreeType<T>* btreeNode)
{
	if(this->head == NULL)
	{	
		this->initNode(&(this->head));
		if(head == NULL)
			return NEWERROR;
		this->head->data = data;
		return SUCCESS;
	}
	if(btreeNode==NULL)	
		return NODEERROR;

	if(btreeNode->data <= data)		
	{
		if(btreeNode->rightChild != NULL)
			_add(data,btreeNode->rightChild);
		else
		{
			this->initNode(&(btreeNode->rightChild));
			btreeNode->rightChild->data = data;	
		}
	}	
	else if(btreeNode->data > data)
	{
		if(btreeNode->leftChild != NULL)
			_add(data,btreeNode->leftChild);
		else
		{
			this->initNode(&(btreeNode->leftChild));
			btreeNode->leftChild->data = data; 
		} 
	} 
	return SUCCESS; 
} 
//------------------------------------------------------
template <class T>
int binTree<T>::initNode(struct bTreeType<T>** btreeNode)
{
	if(*btreeNode == NULL)	
	{	
		*btreeNode = new struct bTreeType<T>;
		if(*btreeNode == NULL)
			return NEWERROR;
		memset((*btreeNode),0,sizeof(struct bTreeType<T>));	
		
		(*btreeNode)->rightChild = NULL;
		(*btreeNode)->leftChild = NULL;
		
		return SUCCESS;
	}
	else
		return DONOTHING;	
}
//------------------------------------------------------
//------------------------------------------------------
template<class T>
void binTree<T>::_travel(struct bTreeType<T>* pNode)
{
	if(pNode == NULL)
		return ;
	else
	{
	//deal with
	cout<<pNode->data<<endl;
	
	_travel(pNode->leftChild);
	_travel(pNode->rightChild);
	}
}
//------------------------------------------------------
template <class T>
int binTree<T>::destory(struct bTreeType<T>* btreenode)
{
	if(btreenode != NULL)
	{
		destory(btreenode->leftChild);
		destory(btreenode->rightChild);
		delete(btreenode);
		btreenode = NULL;
	}
}
//------------------------------------------------------
template <class T>
void binTree<T>::travel()
{
	this->_travel(this->head);
}
