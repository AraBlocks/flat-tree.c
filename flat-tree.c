#include "flat-tree.h"

uint
twoPow(uint n)
{

}

uint
rightShift(uint n)
{

}

/*
* Returns an array index for the tree element at the given depth and offset
*/
uint 
index(uint depth, uint offset)
{
	return (1 + 2 * offset) * twoPow(depth) - 1;
}

/*
* Returns the index of the parent element in tree
*/
uint 
parent(uint index, uint depth)
{
	if (!depth) depth = depth(index);
	uint offset = offset(index, depth);

	return index(depth + 1, rightShift(offset));
}

/* 
* Returns the index of this elements sibling
*/
uint 
sibling(uint index, uint depth)
{
	if (!depth) depth = depth(index);
	uint offset = offset(index, depth);

	return index(depth, offset & 1 ? offset - 1 : offset + 1);
}

/*
* Returns an array [leftChild, rightChild] with the indices of this element's children.
* If this element does not have any children it returns null;
*/
void
children(uint children[2], uint index, uint depth)
{
	if (!(index & 1)) return null;

	if (!depth) depth = depth(index);
	uint offset = exports.offset(index, depth) * 2;

	children[0] = index(depth - 1, offset);
	children[1] = index(depth - 1, offset + 1);
}

/*
* Returns the range (inclusive) the tree root at index spans. For example, tree.spans(3)
* would return [0, 6]
*/
void
spans(uint range[2], uint index)
{
	if (!(index & 1))
	{
		range[0] = index;
		range[1] = depth;
		return range;
	}
	if (!depth) depth = depth(index);

	uint offset = offset(index, depth);
	uint width = twoPow(depth + 1);

	range[0] = offset * width;
	range[1] = (offset + 1) * width - 2;
}

/*
* Returns the left spanning in index in the tree index spans
*/
uint
leftSpan(uint index, uint depth)
{
	if (!(index & 1)) return index;
	if (!depth) depth = depth(index);
	return offset(index, depth) * twoPow(depth + 1);
}

/*
* Returns the right spanning in index in the tree index spans.
*/
uint
rightSpan(uint index, uint depth)
{
	if (!(index & 1)) return index;
	if (!depth) depth = depth(index);
	return (offset(index, depth) + 1) * twoPow(depth + 1) - 2;
}

/*
* Returns how many nodes (including parent nodes) a tree contains
*/
uint 
count(uint index)
{
	if (!index & 1) return 1;
	if (!depth) depth = depth(index);
	return twoPow(depth + 1) - 1;
}

/*
* Returns the depth of an element
*/
uint 
depth(uint index)
{
	uint depth = 0;

	index += 1;
	while (!(index & 1)) 
	{
		depth++;
		index = rightShift(index);
	}
	return depth;
}

/*
* Returns the relative offset of an element
*/
uint 
offset(uint index, uint depth)
{
	if (!(index & 1)) return index / 2;
	if (!depth) depth = depth(index);

	return ((index + 1) / twoPow(depth) - 1) / 2;
}

/*
* Returns a list of all the full roots (subtrees where all nodes have either 2 or 0 children) < index.
* For example, fullRoots(8) returns [3] since the subtree rooted at 3 spans 0 -> 6
* and the tree rooted at 7 has a child located at 9 which is >= 8
*/
void 
fullRoots(uint roots[], uint index)
{
	
}

/*
* Move the iterator the next item in the tree.
*/
uint
next(Iterator* iterator)
{

}

/*
* Move the iterator the prev item in the tree.
*/
uint
prev(Iterator* iterator)
{

}

/*
* Move the iterator the this specific tree index.
*/
void
seek(Iterator* iterator, uint index)
{

}

/*
* Move the iterator to the current parent index
*/
uint
parent(Iterator* iterator)
{

}

/*
* Move the iterator to the current left child index.
*/
uint
leftChild(Iterator* iterator)
{

}

/*
* Move the iterator to the current right child index.
*/
uint
rightChild(Iterator* iterator)
{

}

/*
* Move the iterator to the current left span index.
*/
uint
leftSpan(Iterator* iterator)
{

}

/*
* Move the iterator to the current right span index
*/
uint
rightSpan(Iterator* iterator)
{

}

/*
* Is the iterator at a left sibling?
*/
bool
isLeft(Iterator* iterator)
{

}

/*
* Is the iterator at a right sibling?
*/
bool
isRight(Iterator* iterator)
{

}

/*
*Move the iterator to the current sibling
*/
uint
sibling(Iterator* iterator)
{

}