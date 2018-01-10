#include "flat-tree.h"

uint
ft_two_pow(uint n) {
	return n < 31 ? 1 << n : ((1 << 30) * (1 << (n - 30)));
}

uint
ft_right_shift(uint n) {
	return (n - (n & 1)) / 2;
}

/*
* Returns the depth of an element
*/
uint 
ft_depth(uint index) {
	uint depth = 0;

	index += 1;
	while (!(index & 1)) 
	{
		depth++;
		index = ft_right_shift(index);
	}
	return depth;
}

/*
* Returns the relative offset of an element
*/
uint 
ft_offset(uint index, uint depth) {
	if (!(index & 1)) return index / 2;
	if (!depth) depth = ft_depth(index);

	return ((index + 1) / ft_two_pow(depth) - 1) / 2;
}

/*
* Returns an array index for the tree element at the given depth and offset
*/
uint 
ft_index(uint depth, uint offset) {
	return (1 + 2 * offset) * ft_two_pow(depth) - 1;
}

/*
* Returns the index of the parent element in tree
*/
uint 
ft_parent(uint index, uint depth) {
	if (!depth) depth = ft_depth(index);
	uint offset = ft_offset(index, depth);

	return ft_index(depth + 1, ft_right_shift(offset));
}

/* 
* Returns the index of this elements sibling
*/
uint 
ft_sibling(uint index, uint depth) {
	if (!depth) depth = ft_depth(index);
	uint offset = ft_offset(index, depth);

	return ft_index(depth, offset & 1 ? offset - 1 : offset + 1);
}

int
ft_left_child(uint index, uint depth)
{
	if (!(index & 1)) return -1;
	if (!depth) depth = ft_depth(index);
	return ft_index(depth - 1, ft_offset(index, depth) * 2);
}

int
ft_right_child(uint index, uint depth)
{
	if (!(index & 1)) return -1;
	if (!depth) depth = ft_depth(index);
	return ft_index(depth - 1, 1 + ft_offset(index, depth) * 2);
}

/*
* Returns an array [leftChild, rightChild] with the indices of this element's children.
* If this element does not have any children it returns null;
*/
bool
ft_children(uint children[2], uint index, uint depth) {
	if (!(index & 1)) return false;

	if (!depth) depth = ft_depth(index);
	uint offset = ft_offset(index, depth) * 2;

	children[0] = ft_index(depth - 1, offset);
	children[1] = ft_index(depth - 1, offset + 1);
	return true;
}

/*
* Returns the range (inclusive) the tree root at index spans. For example, tree.spans(3)
* would return [0, 6]
*/
void
ft_spans(uint range[2], uint index, uint depth) {
	if (!(index & 1))
	{
		range[0] = index;
		range[1] = depth;
	}
	if (!depth) depth = ft_depth(index);

	uint offset = ft_offset(index, depth);
	uint width = ft_two_pow(depth + 1);

	range[0] = offset * width;
	range[1] = (offset + 1) * width - 2;
}

/*
* Returns the left spanning in index in the tree index spans
*/
uint
ft_left_span(uint index, uint depth) {
	if (!(index & 1)) return index;
	if (!depth) depth = ft_depth(index);
	return ft_offset(index, depth) * ft_two_pow(depth + 1);
}

/*
* Returns the right spanning in index in the tree index spans.
*/
uint
ft_right_span(uint index, uint depth) {
	if (!(index & 1)) return index;
	if (!depth) depth = ft_depth(index);
	return (ft_offset(index, depth) + 1) * ft_two_pow(depth + 1) - 2;
}

/*
* Returns how many nodes (including parent nodes) a tree contains
*/
uint 
ft_count(uint index, uint depth) {
	if (!(index & 1)) return 1;
	if (!depth) depth = ft_depth(index);
	return ft_two_pow(depth + 1) - 1;
}

/*
* Returns a list of all the full roots (subtrees where all nodes have either 2 or 0 children) < index.
* For example, fullRoots(8) returns [3] since the subtree rooted at 3 spans 0 -> 6
* and the tree rooted at 7 has a child located at 9 which is >= 8
*/
void 
ft_full_roots(uint roots[], uint index) {

}

/*
* Create a stateful tree iterator starting at a given index. The iterator exposes the following methods.
*/
ft_iterator_t*
ft_iterator_new(uint index) {
	ft_iterator_t* iterator = malloc(sizeof(ft_iterator_t));
	iterator->index = 0;
	iterator->offset = 0;
	iterator->factor = 0;
	ft_iterator_seek(iterator, index || 0);
	return iterator;
}

/*
* Move the iterator the next item in the tree.
*/
uint
ft_iterator_next(ft_iterator_t* iterator) {
	iterator->offset++;
	iterator->index += iterator->factor;
	return iterator->index;
}

/*
* Move the iterator the prev item in the tree.
*/
uint
ft_iterator_prev(ft_iterator_t* iterator) {
	if (!iterator->offset) return iterator->index;
	iterator->offset--;
	iterator->index -= iterator->factor;
	return iterator->index;
}

/*
* Move the iterator the this specific tree index.
*/
void
ft_iterator_seek(ft_iterator_t* iterator, uint index) {
	iterator->index = index;
	if (iterator->index & 1) 
	{
		iterator->offset = ft_offset(index, 0);
		iterator->factor = ft_two_pow(ft_depth(index) + 1);
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
ft_iterator_parent(ft_iterator_t* iterator) {
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
int
ft_iterator_left_child(ft_iterator_t* iterator) {
	if (iterator->factor == 2) return iterator->index;
	iterator->factor /= 2;
	iterator->index -= iterator->factor / 2;
	iterator->offset *= 2;
	return iterator->index;
}

/*
* Move the iterator to the current right child index.
*/
int
ft_iterator_right_child(ft_iterator_t* iterator) {
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
ft_iterator_left_span(ft_iterator_t* iterator) {
	iterator->index = iterator->index - iterator->factor / 2 + 1;
	iterator->offset = iterator->index / 2;
	iterator->factor = 2;
	return iterator->index;
}

/*
* Move the iterator to the current right span index
*/
uint
ft_iterator_right_span(ft_iterator_t* iterator) {
	iterator->index = iterator->index + iterator->factor / 2 - 1;
	iterator->offset = iterator->index / 2;
	iterator->factor = 2;
	return iterator->index;
}

/*
* Is the iterator at a left sibling?
*/
bool
ft_iterator_is_left(ft_iterator_t* iterator) {
	return !(iterator->offset & 1);
}

/*
* Is the iterator at a right sibling?
*/
bool
ft_iterator_is_right(ft_iterator_t* iterator) {
	return !ft_iterator_is_left(iterator);
}

/*
*Move the iterator to the current sibling
*/
uint
ft_iterator_sibling(ft_iterator_t* iterator) {
	return ft_iterator_is_left(iterator) ? ft_iterator_next(iterator) : ft_iterator_prev(iterator);
}