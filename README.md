flat-tree.c
===========

A series of functions to map a binary tree to a list ported from
[flat-tree](https://github.com/mafintosh/flat-tree).

## Installation

With [clibs](https://github.com/clibs/clib) for a local install do

```sh
$ clib install helloume/flat-tree.c --save
```

or from source:

```sh
$ git clone git@github.com:helloume/flat-tree.c.git
$ cd flat-tree.c
$ make
$ make install ## you may need sudo
```

or even with [ghi](https://github.com/stephenmathieson/ghi):

```sh
$ ghi helloume/flat-tree.c
```

which simply invokes `make install`

## Building

### Static library

Build the static library by running:

```sh
$ make static
```

## Usage

```c
#include <flat-tree/flat-tree.h>
```

## API

### `ft_ulong ft_two_pow(ft_ulong n);`

TODO

### `ft_ulong ft_right_shift(ft_ulong n);`

TODO

### `ft_ulong ft_index(ft_ulong depth, ft_ulong offset);`

Returns an array index for the tree element at the given depth and offset

### `ft_ulong ft_parent(ft_ulong index, ft_ulong depth);`

Returns the index of the parent element in tree

### `ft_ulong ft_sibling(ft_ulong index, ft_ulong depth);`

Returns the index of this elements sibling

### `ft_long ft_left_child(ft_ulong index, ft_ulong depth);`

TODO

### `ft_long ft_right_child(ft_ulong index, ft_ulong depth);`

TODO

### `bool ft_children(ft_ulong children[2], ft_ulong index, ft_ulong depth);`

 Returns true if the array children[leftChild, rightChild] was set with the
indices of this element's children. Otherwise it returns false;

### `void ft_spans(ft_ulong range[2], ft_ulong index, ft_ulong depth);`

Returns the range (inclusive) the tree root at index spans. For example,
tree.spans(3) would return [0, 6]

### `ft_ulong ft_left_span(ft_ulong index, ft_ulong depth);`

Returns the left spanning in index in the tree index spans

### `ft_ulong ft_right_span(ft_ulong index, ft_ulong depth);`

Returns the right spanning in index in the tree index spans.

### `ft_ulong ft_count(ft_ulong index, ft_ulong depth);`

Returns how many nodes (including parent nodes) a tree contains

### `ft_ulong ft_depth(ft_ulong index);`

Returns the depth of an element

### `ft_ulong ft_offset(ft_ulong index, ft_ulong depth);`

Returns the relative offset of an element

### `ft_long ft_full_roots(ft_ulong** roots, ft_ulong index);`

Returns the number of rull roots. Sets roots[] with all the full
roots (subtrees where all nodes have either 2 or 0 children) < index.
For example, fullRoots(8) returns [3] since the subtree rooted at 3
spans 0 -> 6 and the tree rooted at 7 has a child located at 9
which is >= 8

### `ft_iterator_t* ft_iterator_new(ft_ulong index);`

Create a stateful tree iterator starting at a given index.

### `ft_ulong ft_iterator_next(ft_iterator_t* iterator);`

Move the iterator to the next item in the tree. This will
increment the iterator offset and increment the index by the
iterator factor.

### `ft_ulong ft_iterator_prev(ft_iterator_t* iterator);`

Move the iterator to the previous item in the tree. This will
decrement the iterator offset and decrement the index by the
iterator factor.

### `void ft_iterator_seek(ft_iterator_t* iterator, ft_ulong index);`

Move the iterator the this specific tree index.

### `ft_ulong ft_iterator_parent(ft_iterator_t* iterator);`

Move the iterator to the current parent index

### `ft_long ft_iterator_left_child(ft_iterator_t* iterator);`

Move the iterator to the current left child index.

### `ft_long ft_iterator_right_child(ft_iterator_t* iterator);`

Move the iterator to the current right child index.

### `ft_ulong ft_iterator_left_span(ft_iterator_t* iterator);`

Move the iterator to the current left span index.

### `ft_ulong ft_iterator_right_span(ft_iterator_t* iterator);`

Move the iterator to the current right span index

### `bool ft_iterator_is_left(ft_iterator_t* iterator);`

Is the iterator at a left sibling?

### `bool ft_iterator_is_right(ft_iterator_t* iterator);`

Is the iterator at a right sibling?

### `ft_ulong ft_iterator_sibling(ft_iterator_t* iterator);`

Move the iterator to the current sibling

## License

MIT
