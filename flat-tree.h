#include <stdbool.h>
#include <stdlib.h>

#ifndef FLAT_TREE_H
#define FLAT_TREE_H

typedef unsigned long long FTulong;
typedef long long FTlong;

typedef struct {
	FTulong index;
	FTulong offset;
	FTulong factor;
} ft_iterator_t;

FTulong
ft_two_pow(FTulong n);

FTulong
ft_right_shift(FTulong n);

/*
* Returns an array index for the tree element at the given depth and offset
*/
FTulong 
ft_index(FTulong depth, FTulong offset);

/*
* Returns the index of the parent element in tree
*/
FTulong 
ft_parent(FTulong index, FTulong depth);

/* 
* Returns the index of this elements sibling
*/
FTulong 
ft_sibling(FTulong index, FTulong depth);

FTlong
ft_left_child(FTulong index, FTulong depth);

FTlong
ft_right_child(FTulong index, FTulong depth);

/*
* Returns an array [leftChild, rightChild] with the indices of this element's children.
* If this element does not have any children it returns null;
*/
bool 
ft_children(FTulong children[2], FTulong index, FTulong depth);

/*
* Returns the range (inclusive) the tree root at index spans. For example, tree.spans(3)
* would return [0, 6]
*/
void
ft_spans(FTulong range[2], FTulong index, FTulong depth);

/*
* Returns the left spanning in index in the tree index spans
*/
FTulong
ft_left_span(FTulong index, FTulong depth);

/*
* Returns the right spanning in index in the tree index spans.
*/
FTulong
ft_right_span(FTulong index, FTulong depth);
/*
* Returns how many nodes (including parent nodes) a tree contains
*/
FTulong 
ft_count(FTulong index, FTulong depth);

/*
* Returns the depth of an element
*/
FTulong 
ft_depth(FTulong index);

/*
* Returns the relative offset of an element
*/
FTulong 
ft_offset(FTulong index, FTulong depth);

/*
* Returns a list of all the full roots (subtrees where all nodes have either 2 or 0 children) < index.
* For example, fullRoots(8) returns [3] since the subtree rooted at 3 spans 0 -> 6
* and the tree rooted at 7 has a child located at 9 which is >= 8
*/
void 
ft_full_roots(FTulong roots[], FTulong index);

////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Create a stateful tree iterator starting at a given index. The iterator exposes the following methods.
*/
ft_iterator_t*
ft_iterator_new(FTulong index);

/*
* Move the iterator the next item in the tree.
*/
FTulong
ft_iterator_next(ft_iterator_t* iterator);

/*
* Move the iterator the prev item in the tree.
*/
FTulong
ft_iterator_prev(ft_iterator_t* iterator);

/*
* Move the iterator the this specific tree index.
*/
void
ft_iterator_seek(ft_iterator_t* iterator, FTulong index);

/*
* Move the iterator to the current parent index
*/
FTulong
ft_iterator_parent(ft_iterator_t* iterator);

/*
* Move the iterator to the current left child index.
*/
FTlong
ft_iterator_left_child(ft_iterator_t* iterator);

/*
* Move the iterator to the current right child index.
*/
FTlong
ft_iterator_right_child(ft_iterator_t* iterator);

/*
* Move the iterator to the current left span index.
*/
FTulong
ft_iterator_left_span(ft_iterator_t* iterator);

/*
* Move the iterator to the current right span index
*/
FTulong
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
FTulong
ft_iterator_sibling(ft_iterator_t* iterator);

#endif