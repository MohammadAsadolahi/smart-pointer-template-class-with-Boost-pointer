/*
 * SmartVector.cpp
 *
 *      Author: mohammad asadolahi
 *      https://github.com/mohammadAsadolahi
 *	Mohammad.E.Asadolahi@gmail.com
 */
#include <memory>
#include <iostream>
#include <ctime>
using namespace std;
#ifndef SMARTVECTOR_H_
#define SMARTVECTOR_H_
class Exception
	{
		string description;
	public:
		Exception (string description = "unknown reason") :
				description(description)
			{
			}
		auto getDescription ( )->string
			{
				return description;
			}
		auto operator << (ostream& outputStream) const ->ostream&
			{
				outputStream << "an error occured! description:\n"
						<< description << endl;
				return outputStream;
			}
	};

template<class Type> class SmartVector
	{
		class Node
			{
			public:
				shared_ptr<Type >data;
				shared_ptr<Node >nextNode;
				Node (Type data)
					{
						this->data = shared_ptr<Type >(new Type(data));
						nextNode = nullptr;
					}
			};
		shared_ptr<Node >root;
		int count = 0;
	public:
		auto add (Type data) throw (unique_ptr<Exception >)->void;
		auto remove (int index) throw (unique_ptr<Exception >)->void;
		auto getCount ( ) throw (unique_ptr<Exception >)->int;
		auto operator[] (int index) throw (unique_ptr<Exception >)->Type&;
	};
#endif /* SMARTVECTOR_H_ */
