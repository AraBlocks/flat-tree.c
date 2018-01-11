#ifndef FLAT_TREE_ITERATOR_H
#define FLAT_TREE_ITERATOR_H
#if defined(__cplusplus)
extern "C" {
#endif

#include <stdbool.h>
#include "common.h"

/**
 * The `ft_iterator_t' type defines a stateful iterator with an index,
 * offset, and growth factor.
 */
typedef struct ft_iterator ft_iterator_t;
struct ft_iterator {
  ft_ulong index;
  ft_ulong offset;
  ft_ulong factor;
};

/**
 * Create a stateful tree iterator starting at a given index.
 */
ft_iterator_t*
ft_iterator_new(ft_ulong index);

/**
 * Move the iterator to the next item in the tree. This will
 * increment the iterator offset and increment the index by the
 * iterator factor.
 */
ft_ulong
ft_iterator_next(ft_iterator_t* iterator);

/**
 * Move the iterator to the previous item in the tree. This will
 * decrement the iterator offset and decrement the index by the
 * iterator factor.
 */
ft_ulong
ft_iterator_prev(ft_iterator_t* iterator);

/**
 * Move the iterator the this specific tree index.
 */
void
ft_iterator_seek(ft_iterator_t* iterator, ft_ulong index);

/**
 * Move the iterator to the current parent index
 */
ft_ulong
ft_iterator_parent(ft_iterator_t* iterator);

/**
 * Move the iterator to the current left child index.
 */
ft_long
ft_iterator_left_child(ft_iterator_t* iterator);

/**
 * Move the iterator to the current right child index.
 */
ft_long
ft_iterator_right_child(ft_iterator_t* iterator);

/**
 * Move the iterator to the current left span index.
 */
ft_ulong
ft_iterator_left_span(ft_iterator_t* iterator);

/**
 * Move the iterator to the current right span index
 */
ft_ulong
ft_iterator_right_span(ft_iterator_t* iterator);

/**
 * Is the iterator at a left sibling?
 */
bool
ft_iterator_is_left(ft_iterator_t* iterator);

/**
 * Is the iterator at a right sibling?
 */
bool
ft_iterator_is_right(ft_iterator_t* iterator);

/**
 *Move the iterator to the current sibling
 */
ft_ulong
ft_iterator_sibling(ft_iterator_t* iterator);

#if defined(__cplusplus)
}
#endif
#endif
