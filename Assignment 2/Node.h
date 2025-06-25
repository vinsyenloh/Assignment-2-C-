#ifndef Node_type
#define Node_type

#include "BTNode.h"

#pragma warning(push);
#pragma warning(disable: 4996);

using type2 = BTNode *;

struct Node {
	
		type2		item;
		Node	*next;
		Node(type2);
};


#endif