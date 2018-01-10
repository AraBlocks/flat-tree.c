#include <stdbool.h>
#include <stdlib.h>

#ifndef FLAT_TREE_H
#define FLAT_TREE_H

typedef unsigned int uint;

typedef struct {
	int index;
	uint offset;
	uint factor;
} ft_iterator_t;

uint
ft_two_pow(uint n);

uint
ft_right_shift(uint n);

/*
* Returns an array index for the tree element at the given depth and offset
*/
uint 
ft_index(uint depth, uint offset);

/*
* Returns the index of the parent element in tree
*/
uint 
ft_parent(uint index, uint depth);

/* 
* Returns the index of this elements sibling
*/
uint 
ft_sibling(uint index, uint depth);

int
ft_left_child(uint index, uint depth);

int
ft_right_child(uint index, uint depth);

/*
* Returns an array [leftChild, rightChild] with the indices of this element's children.
* If this element does not have any children it returns null;
*/
bool 
ft_children(uint children[2], uint index, uint depth);

/*
* Returns the range (inclusive) the tree root at index spans. For example, tree.spans(3)
* would return [0, 6]
*/
void
ft_spans(uint range[2], uint index, uint depth);

/*
* Returns the left spanning in index in the tree index spans
*/
uint
ft_left_span(uint index, uint depth);

/*
* Returns the right spanning in index in the tree index spans.
*/
uint
ft_right_span(uint index, uint depth);
/*
* Returns how many nodes (including parent nodes) a tree contains
*/
uint 
ft_count(uint index, uint depth);

/*
* Returns the depth of an element
*/
uint 
ft_depth(uint index);

/*
* Returns the relative offset of an element
*/
uint 
ft_offset(uint index, uint depth);

/*
* Returns a list of all the full roots (subtrees where all nodes have either 2 or 0 children) < index.
* For example, fullRoots(8) returns [3] since the subtree rooted at 3 spans 0 -> 6
* and the tree rooted at 7 has a child located at 9 which is >= 8
*/
void 
ft_full_roots(uint roots[], uint index);

////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Create a stateful tree iterator starting at a given index. The iterator exposes the following methods.
*/
ft_iterator_t*
ft_iterator_new(uint index);

/*
* Move the iterator the next item in the tree.
*/
uint
ft_iterator_next(ft_iterator_t* iterator);

/*
* Move the iterator the prev item in the tree.
*/
uint
ft_iterator_prev(ft_iterator_t* iterator);

/*
* Move the iterator the this specific tree index.
*/
void
ft_iterator_seek(ft_iterator_t* iterator, uint index);

/*
* Move the iterator to the current parent index
*/
uint
ft_iterator_parent(ft_iterator_t* iterator);

/*
* Move the iterator to the current left child index.
*/
int
ft_iterator_left_child(ft_iterator_t* iterator);

/*
* Move the iterator to the current right child index.
*/
int
ft_iterator_right_child(ft_iterator_t* iterator);

/*
* Move the iterator to the current left span index.
*/
uint
ft_iterator_left_span(ft_iterator_t* iterator);

/*
* Move the iterator to the current right span index
*/
uint
ft_iterator_right_span(ft_iterator_t* iterator);

/*
* Is the iterator at a left sibling?
*/
bool
ft_iterator_is_left(ft_iterator_t* iterator);

/*
* Is the iterator at a right sibling?
*/
bool
ft_iterator_is_right(ft_iterator_t* iterator);

/*
*Move the iterator to the current sibling
*/
uint
ft_iterator_sibling(ft_iterator_t* iterator);

#endif