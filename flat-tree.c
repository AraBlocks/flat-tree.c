#include "flat-tree.h"

FTulong
ft_two_pow(FTulong n) {
	return n < 31LLU ? 1LLU << n : ((1LLU << 30LLU) * (1LLU << (n - 30LLU)));
}

FTulong
ft_right_shift(FTulong n) {
	return (n - (n & 1LLU)) / 2LLU;
}

/*
* Returns the depth of an element
*/
FTulong 
ft_depth(FTulong index) {
	FTulong depth = 0LLU;

	index += 1LLU;
	while (!(index & 1LLU)) 
	{
		depth++;
		index = ft_right_shift(index);
	}
	return depth;
}

/*
* Returns the relative offset of an element
*/
FTulong 
ft_offset(FTulong index, FTulong depth) {
	if (!(index & 1LLU)) return index / 2LLU;
	if (!depth) depth = ft_depth(index);

	return ((index + 1LLU) / ft_two_pow(depth) - 1LLU) / 2LLU;
}

/*
* Returns an array index for the tree element at the given depth and offset
*/
FTulong 
ft_index(FTulong depth, FTulong offset) {
	return (1LLU + 2LLU * offset) * ft_two_pow(depth) - 1LLU;
}

/*
* Returns the index of the parent element in tree
*/
FTulong 
ft_parent(FTulong index, FTulong depth) {
	if (!depth) depth = ft_depth(index);
	FTulong offset = ft_offset(index, depth);

	return ft_index(depth + 1LLU, ft_right_shift(offset));
}

/* 
* Returns the index of this elements sibling
*/
FTulong 
ft_sibling(FTulong index, FTulong depth) {
	if (!depth) depth = ft_depth(index);
	FTulong offset = ft_offset(index, depth);

	return ft_index(depth, offset & 1LLU ? offset - 1LLU : offset + 1LLU);
}

FTlong
ft_left_child(FTulong index, FTulong depth)
{
	if (!(index & 1)) return -1;
	if (!depth) depth = ft_depth(index);
	return ft_index(depth - 1LLU, ft_offset(index, depth) * 2LLU);
}

FTlong
ft_right_child(FTulong index, FTulong depth)
{
	if (!(index & 1)) return -1;
	if (!depth) depth = ft_depth(index);
	return ft_index(depth - 1LLU, 1LLU + ft_offset(index, depth) * 2LLU);
}

/*
* Returns an array [leftChild, rightChild] with the indices of this element's children.
* If this element does not have any children it returns null;
*/
bool
ft_children(FTulong children[2], FTulong index, FTulong depth) {
	if (!(index & 1)) return false;

	if (!depth) depth = ft_depth(index);
	FTulong offset = ft_offset(index, depth) * 2LLU;

	children[0] = ft_index(depth - 1LLU, offset);
	children[1] = ft_index(depth - 1LLU, offset + 1LLU);
	return true;
}

/*
* Returns the range (inclusive) the tree root at index spans. For example, tree.spans(3)
* would return [0, 6]
*/
void
ft_spans(FTulong range[2], FTulong index, FTulong depth) {
	if (!(index & 1))
	{
		range[0] = index;
		range[1] = depth;
	}
	if (!depth) depth = ft_depth(index);

	FTulong offset = ft_offset(index, depth);
	FTulong width = ft_two_pow(depth + 1LLU);

	range[0] = offset * width;
	range[1] = (offset + 1LLU) * width - 2LLU;
}

/*
* Returns the left spanning in index in the tree index spans
*/
FTulong
ft_left_span(FTulong index, FTulong depth) {
	if (!(index & 1)) return index;
	if (!depth) depth = ft_depth(index);
	return ft_offset(index, depth) * ft_two_pow(depth + 1LLU);
}

/*
* Returns the right spanning in index in the tree index spans.
*/
FTulong
ft_right_span(FTulong index, FTulong depth) {
	if (!(index & 1)) return index;
	if (!depth) depth = ft_depth(index);
	return (ft_offset(index, depth) + 1LLU) * ft_two_pow(depth + 1LLU) - 2LLU;
}

/*
* Returns how many nodes (including parent nodes) a tree contains
*/
FTulong 
ft_count(FTulong index, FTulong depth) {
	if (!(index & 1)) return 1;
	if (!depth) depth = ft_depth(index);
	return ft_two_pow(depth + 1LLU) - 1LLU;
}

/*
* Returns a list of all the full roots (subtrees where all nodes have either 2 or 0 children) < index.
* For example, fullRoots(8) returns [3] since the subtree rooted at 3 spans 0 -> 6
* and the tree rooted at 7 has a child located at 9 which is >= 8
*/
void 
ft_full_roots(FTulong roots[], FTulong index) {

}

/*
* Create a stateful tree iterator starting at a given index. The iterator exposes the following methods.
*/
ft_iterator_t*
ft_iterator_new(FTulong index) {
	ft_iterator_t* iterator = malloc(sizeof(ft_iterator_t));
	iterator->index = 0LLU;
	iterator->offset = 0LLU;
	iterator->factor = 0LLU;
	ft_iterator_seek(iterator, index || 0);
	return iterator;
}

/*
* Move the iterator the next item in the tree.
*/
FTulong
ft_iterator_next(ft_iterator_t* iterator) {
	iterator->offset++;
	iterator->index += iterator->factor;
	return iterator->index;
}

/*
* Move the iterator the prev item in the tree.
*/
FTulong
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
ft_iterator_seek(ft_iterator_t* iterator, FTulong index) {
	iterator->index = index;
	if (iterator->index & 1) 
	{
		iterator->offset = ft_offset(index, 0);
		iterator->factor = ft_two_pow(ft_depth(index) + 1LLU);
	}
	else
	{
		iterator->offset = index / 2LLU;
		iterator->factor = 2LLU;
	}
}

/*
* Move the iterator to the current parent index
*/
FTulong
ft_iterator_parent(ft_iterator_t* iterator) {
	if (iterator->offset & 1)
	{
		iterator->index -= iterator->factor / 2LLU;
		iterator->offset = (iterator->offset - 1LLU) / 2LLU;
	}
	else
	{
		iterator->index += iterator->factor / 2LLU;
		iterator->offset /= 2LLU;
	}
	iterator->factor *= 2LLU;
	return iterator->index;
}

/*
* Move the iterator to the current left child index.
*/
FTlong
ft_iterator_left_child(ft_iterator_t* iterator) {
	if (iterator->factor == 2LLU) return iterator->index;
	iterator->factor /= 2LLU;
	iterator->index -= iterator->factor / 2LLU;
	iterator->offset *= 2LLU;
	return iterator->index;
}

/*
* Move the iterator to the current right child index.
*/
FTlong
ft_iterator_right_child(ft_iterator_t* iterator) {
	if (iterator->factor == 2LLU) return iterator->index;
	iterator->factor /= 2LLU;
	iterator->index += iterator->factor / 2LLU;
	iterator->offset = 2LLU * iterator->offset + 1LLU;
	return iterator->index;
}

/*
* Move the iterator to the current left span index.
*/
FTulong
ft_iterator_left_span(ft_iterator_t* iterator) {
	iterator->index = iterator->index - iterator->factor / 2LLU + 1LLU;
	iterator->offset = iterator->index / 2LLU;
	iterator->factor = 2LLU;
	return iterator->index;
}

/*
* Move the iterator to the current right span index
*/
FTulong
ft_iterator_right_span(ft_iterator_t* iterator) {
	iterator->index = iterator->index + iterator->factor / 2LLU - 1LLU;
	iterator->offset = iterator->index / 2LLU;
	iterator->factor = 2LLU;
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
FTulong
ft_iterator_sibling(ft_iterator_t* iterator) {
	return ft_iterator_is_left(iterator) ? ft_iterator_next(iterator) : ft_iterator_prev(iterator);
}