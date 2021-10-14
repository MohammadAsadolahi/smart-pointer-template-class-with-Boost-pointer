/*
 * SmartVector.cpp
 *
 *      Author: mohammad asadolahi 
 *      https://github.com/mohammadAsadolahi
 *	Mohammad.E.Asadolahi@gmail.com
 */

#include "SmartVector.h"
template<class Type>
inline auto SmartVector<Type >::add (Type data) throw (unique_ptr<Exception >)->void
	{
		if (count == 0)
			{
				root = shared_ptr<Node >
					{ new Node(data) };
			}
		else
			{
				auto temp = root;
				while (temp->nextNode)
					temp = temp->nextNode;
				temp->nextNode = shared_ptr<Node >
					{ new Node(data) };
			}
		count++;
	}
template<class Type>
auto SmartVector<Type >::remove (int index) throw (unique_ptr<Exception >)->void
	{
		if (count < 1 || index >= count)
			throw unique_ptr<Exception >
				{ new Exception("can't remove object, index out of vector") };
		auto tempRoot = root;
		for (register int counter = 0 ;counter < index - 1 ;counter++)
			tempRoot = tempRoot->nextNode;
		tempRoot->nextNode = tempRoot->nextNode->nextNode;
		count--;
	}

template<class Type>
auto SmartVector<Type >::getCount ( ) throw (unique_ptr<Exception >)->int
	{
		return count;
	}

template<class Type>
auto SmartVector<Type >::operator [] (int index) throw (unique_ptr<Exception >)->Type&
	{
		if (index < 0 || index >= count)
			throw unique_ptr<Exception >
				{ new Exception("can't access object, index out of vector") };
		auto tempRoot = root;
		for (register int counter = 0 ;counter < index ;counter++)
			tempRoot = tempRoot->nextNode;
		return (*tempRoot->data);
	}
