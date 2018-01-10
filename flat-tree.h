#ifndef FLAT_TREE_H
#define FLAT_TREE_H

typedef unsigned int uint;

typedef struct {
	uint index;
	uint offset;
	uint factor;
} Iterator;

/*
* Returns an array index for the tree element at the given depth and offset
*/
uint 
index(uint depth, uint offset);

/*
* Returns the index of the parent element in tree
*/
uint 
parent(uint index);

/* 
* Returns the index of this elements sibling
*/
uint 
sibling(uint index);

/*
* Returns an array [leftChild, rightChild] with the indices of this element's children.
* If this element does not have any children it returns null;
*/
uint* 
children(uint index);

/*
* Returns the range (inclusive) the tree root at index spans. For example, tree.spans(3)
* would return [0, 6]
*/
uint* 
spans(uint index);

/*
* Returns the left spanning in index in the tree index spans
*/
uint* 
leftSpan(uint index);

/*
* Returns how many nodes (including parent nodes) a tree contains
*/
uint 
count(uint index);

/*
* Returns the depth of an element
*/
uint 
depth(uint index);

/*
* Returns the relative offset of an element
*/
uint 
offset(uint index, uint depth);

/*
* Returns a list of all the full roots (subtrees where all nodes have either 2 or 0 children) < index.
* For example, fullRoots(8) returns [3] since the subtree rooted at 3 spans 0 -> 6
* and the tree rooted at 7 has a child located at 9 which is >= 8
*/
uint* 
fullRoots(uint index);

/*
* Move the iterator the next item in the tree.
*/
uint
next(Iterator* iterator);

/*
* Move the iterator the prev item in the tree.
*/
uint
prev(Iterator* iterator);

/*
* Move the iterator the this specific tree index.
*/
void
seek(Iterator* iterator, uint index);

/*
* Move the iterator to the current parent index
*/
uint
parent(Iterator* iterator);

/*
* Move the iterator to the current left child index.
*/
uint
leftChild(Iterator* iterator);

/*
* Move the iterator to the current right child index.
*/
uint
rightChild(Iterator* iterator);

/*
* Move the iterator to the current left span index.
*/
uint
leftSpan(Iterator* iterator);

/*
* Move the iterator to the current right span index
*/
uint
rightSpan(Iterator* iterator);

/*
* Is the iterator at a left sibling?
*/
bool
isLeft(Iterator* iterator);

/*
* Is the iterator at a right sibling?
*/
bool
isRight(Iterator* iterator);

/*
*Move the iterator to the current sibling
*/
uint
sibling(Iterator* iterator);

