#include <flat-tree/flat-tree.h>
#include <flat-tree/iterator.h>
#include <stdlib.h>

ft_iterator_t*
ft_iterator_new(ft_ulong index) {
  ft_iterator_t* iterator = malloc(sizeof(ft_iterator_t));
  iterator->index = 0LLU;
  iterator->offset = 0LLU;
  iterator->factor = 0LLU;
  ft_iterator_seek(iterator, index || 0);
  return iterator;
}

ft_ulong
ft_iterator_next(ft_iterator_t* iterator) {
  (void) iterator->offset++;
  iterator->index += iterator->factor;
  return iterator->index;
}

ft_ulong
ft_iterator_prev(ft_iterator_t* iterator) {
  if (0 == iterator->offset) { return iterator->index; }
  (void) iterator->offset--;
  iterator->index -= iterator->factor;
  return iterator->index;
}

void
ft_iterator_seek(ft_iterator_t* iterator, ft_ulong index) {
  iterator->index = index;
  if (iterator->index & 1) {
    iterator->offset = ft_offset(index, 0);
    iterator->factor = ft_two_pow(ft_depth(index) + 1LLU);
  } else {
    iterator->offset = index / 2LLU;
    iterator->factor = 2LLU;
  }
}

ft_ulong
ft_iterator_parent(ft_iterator_t* iterator) {
  if (iterator->offset & 1) {
    iterator->index -= iterator->factor / 2LLU;
    iterator->offset = (iterator->offset - 1LLU) / 2LLU;
  } else {
    iterator->index += iterator->factor / 2LLU;
    iterator->offset /= 2LLU;
  }
  iterator->factor *= 2LLU;
  return iterator->index;
}

ft_long
ft_iterator_left_child(ft_iterator_t* iterator) {
  if (iterator->factor == 2LLU) { return iterator->index; }
  iterator->factor /= 2LLU;
  iterator->index -= iterator->factor / 2LLU;
  iterator->offset *= 2LLU;
  return iterator->index;
}

ft_long
ft_iterator_right_child(ft_iterator_t* iterator) {
  if (iterator->factor == 2LLU) { return iterator->index; }
  iterator->factor /= 2LLU;
  iterator->index += iterator->factor / 2LLU;
  iterator->offset = 2LLU * iterator->offset + 1LLU;
  return iterator->index;
}

ft_ulong
ft_iterator_left_span(ft_iterator_t* iterator) {
  iterator->index = iterator->index - iterator->factor / 2LLU + 1LLU;
  iterator->offset = iterator->index / 2LLU;
  iterator->factor = 2LLU;
  return iterator->index;
}

ft_ulong
ft_iterator_right_span(ft_iterator_t* iterator) {
  iterator->index = iterator->index + iterator->factor / 2LLU - 1LLU;
  iterator->offset = iterator->index / 2LLU;
  iterator->factor = 2LLU;
  return iterator->index;
}

bool
ft_iterator_is_left(ft_iterator_t* iterator) {
  return 0 == (iterator->offset & 1);
}

bool
ft_iterator_is_right(ft_iterator_t* iterator) {
  return false == ft_iterator_is_left(iterator);
}

ft_ulong
ft_iterator_sibling(ft_iterator_t* iterator) {
  return ft_iterator_is_left(iterator)
    ? ft_iterator_next(iterator)
    : ft_iterator_prev(iterator);
}
