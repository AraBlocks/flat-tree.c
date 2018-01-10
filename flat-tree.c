#include "flat-tree.h"

uint
twoPow(uint n)
{
	return n < 31 ? 1 << n : ((1 << 30) * (1 << (n - 30)));
}

uint
rightShift(uint n)
{
	return (n - (n & 1)) / 2;
}

/*
* Returns the depth of an element
*/
uint 
treeDepth(uint index)
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
treeOffset(uint index, uint depth)
{
	if (!(index & 1)) return index / 2;
	if (!depth) depth = treeDepth(index);

	return ((index + 1) / twoPow(depth) - 1) / 2;
}

/*
* Returns an array index for the tree element at the given depth and offset
*/
uint 
treeIndex(uint depth, uint offset)
{
	return (1 + 2 * offset) * twoPow(depth) - 1;
}

/*
* Returns the index of the parent element in tree
*/
uint 
treeParent(uint index, uint depth)
{
	if (!depth) depth = treeDepth(index);
	uint offset = treeOffset(index, depth);

	return treeIndex(depth + 1, rightShift(offset));
}

/* 
* Returns the index of this elements sibling
*/
uint 
treeSibling(uint index, uint depth)
{
	if (!depth) depth = treeDepth(index);
	uint offset = treeOffset(index, depth);

	return treeIndex(depth, offset & 1 ? offset - 1 : offset + 1);
}

/*
* Returns an array [leftChild, rightChild] with the indices of this element's children.
* If this element does not have any children it returns null;
*/
void
children(uint children[2], uint index, uint depth)
{
	if (!(index & 1)) return;

	if (!depth) depth = treeDepth(index);
	uint offset = treeOffset(index, depth) * 2;

	children[0] = treeIndex(depth - 1, offset);
	children[1] = treeIndex(depth - 1, offset + 1);
}

/*
* Returns the range (inclusive) the tree root at index spans. For example, tree.spans(3)
* would return [0, 6]
*/
void
spans(uint range[2], uint index, uint depth)
{
	if (!(index & 1))
	{
		range[0] = index;
		range[1] = depth;
	}
	if (!depth) depth = treeDepth(index);

	uint offset = treeOffset(index, depth);
	uint width = twoPow(depth + 1);

	range[0] = offset * width;
	range[1] = (offset + 1) * width - 2;
}

/*
* Returns the left spanning in index in the tree index spans
*/
uint
treeLeftSpan(uint index, uint depth)
{
	if (!(index & 1)) return index;
	if (!depth) depth = treeDepth(index);
	return treeOffset(index, depth) * twoPow(depth + 1);
}

/*
* Returns the right spanning in index in the tree index spans.
*/
uint
treeRightSpan(uint index, uint depth)
{
	if (!(index & 1)) return index;
	if (!depth) depth = treeDepth(index);
	return (treeOffset(index, depth) + 1) * twoPow(depth + 1) - 2;
}

/*
* Returns how many nodes (including parent nodes) a tree contains
*/
uint 
count(uint index, uint depth)
{
	if (!(index & 1)) return 1;
	if (!depth) depth = treeDepth(index);
	return twoPow(depth + 1) - 1;
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
* Create a stateful tree iterator starting at a given index. The iterator exposes the following methods.
*/
void
iterator(Iterator* iterator, uint index)
{
	iterator->index = 0;
	iterator->offset = 0;
	iterator->factor = 0;
	seek(iterator, index || 0);
}

/*
* Move the iterator the next item in the tree.
*/
uint
next(Iterator* iterator)
{
	iterator->offset++;
	iterator->index += iterator->factor;
	return iterator->index;
}

/*
* Move the iterator the prev item in the tree.
*/
uint
prev(Iterator* iterator)
{
	if (!iterator->offset) return iterator->index;
	iterator->offset--;
	iterator->index -= iterator->factor;
	return iterator->index;
}

/*
* Move the iterator the this specific tree index.
*/
void
seek(Iterator* iterator, uint index)
{
	iterator->index = index;
	if (iterator->index & 1) 
	{
		iterator->offset = treeOffset(index, 0);
		iterator->factor = twoPow(treeDepth(index) + 1);
	}
	else
	{
		iterator->offset = index / 2;
		iterator->offset = 2;
	}
}

/*
* Move the iterator to the current parent index
*/
uint
parent(Iterator* iterator)
{
	if (iterator->offset & 1)
	{
		iterator->index -= iterator->factor / 2;
		iterator->offset = (iterator->offset - 1) / 2;
	}
	else
	{
		iterator->index += iterator->factor / 2;
		iterator->offset /= 2;
	}
	iterator->factor *= 2;
	return iterator->index;
}

/*
* Move the iterator to the current left child index.
*/
uint
leftChild(Iterator* iterator)
{
	if (iterator->factor == 2) return iterator->index;
	iterator->factor /= 2;
	iterator->index -= iterator->factor / 2;
	iterator->offset *= 2;
	return iterator->index;
}

/*
* Move the iterator to the current right child index.
*/
uint
rightChild(Iterator* iterator)
{
	if (iterator->factor == 2) return iterator->index;
	iterator->factor /= 2;
	iterator->index += iterator->factor / 2;
	iterator->offset = 2 * iterator->offset + 1;
	return iterator->index;
}

/*
* Move the iterator to the current left span index.
*/
uint
leftSpan(Iterator* iterator)
{
	iterator->index = iterator->index - iterator->factor / 2 + 1;
	iterator->offset = iterator->index / 2;
	iterator->factor = 2;
	return iterator->index;
}

/*
* Move the iterator to the current right span index
*/
uint
rightSpan(Iterator* iterator)
{
	iterator->index = iterator->index + iterator->factor / 2 - 1;
	iterator->offset = iterator->index / 2;
	iterator->factor = 2;
	return iterator->index;
}

/*
* Is the iterator at a left sibling?
*/
bool
isLeft(Iterator* iterator)
{
	return !(iterator->offset & 1);
}

/*
* Is the iterator at a right sibling?
*/
bool
isRight(Iterator* iterator)
{
	return !isLeft(iterator);
}

/*
*Move the iterator to the current sibling
*/
uint
sibling(Iterator* iterator)
{
	return isLeft(iterator) ? next(iterator) : prev(iterator);
}