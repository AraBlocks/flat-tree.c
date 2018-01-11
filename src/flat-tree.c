#include <flat-tree/flat-tree.h>

ft_ulong
ft_two_pow(ft_ulong n) {
  return n < 31LLU
    ? 1LLU << n
    : ((1LLU << 30LLU) * (1LLU << (n - 30LLU)));
}

ft_ulong
ft_right_shift(ft_ulong n) {
  return (n - (n & 1LLU)) / 2LLU;
}

ft_ulong
ft_depth(ft_ulong index) {
  ft_ulong depth = 0LLU;
  index += 1LLU;
  while (0 == (index & 1LLU)) {
    depth++;
    index = ft_right_shift(index);
  }
  return depth;
}

ft_ulong
ft_offset(ft_ulong index, ft_ulong depth) {
  if (0 == (index & 1LLU)) { return index / 2LLU; }
  if (0 == depth) { depth = ft_depth(index); }
  return ((index + 1LLU) / ft_two_pow(depth) - 1LLU) / 2LLU;
}

ft_ulong
ft_index(ft_ulong depth, ft_ulong offset) {
  return (1LLU + 2LLU * offset) * ft_two_pow(depth) - 1LLU;
}

ft_ulong
ft_parent(ft_ulong index, ft_ulong depth) {
  if (0 == depth) { depth = ft_depth(index); }
  ft_ulong offset = ft_offset(index, depth);
  return ft_index(depth + 1LLU, ft_right_shift(offset));
}

ft_ulong
ft_sibling(ft_ulong index, ft_ulong depth) {
  if (0 == depth) { depth = ft_depth(index); }
  ft_ulong offset = ft_offset(index, depth);
  return ft_index(depth, offset & 1LLU ? offset - 1LLU : offset + 1LLU);
}

ft_long
ft_left_child(ft_ulong index, ft_ulong depth) {
  if (0 == (index & 1)) { return -1; }
  if (0 == depth) { depth = ft_depth(index); }
  return ft_index(depth - 1LLU, ft_offset(index, depth) * 2LLU);
}

ft_long
ft_right_child(ft_ulong index, ft_ulong depth) {
  if (0 == (index & 1)) { return -1; }
  if (0 == depth) { depth = ft_depth(index); }
  return ft_index(depth - 1LLU, 1LLU + ft_offset(index, depth) * 2LLU);
}

bool
ft_children(ft_ulong children[2], ft_ulong index, ft_ulong depth) {
  if (0 == (index & 1)) { return false; }
  if (0 == depth) { depth = ft_depth(index); }
  ft_ulong offset = ft_offset(index, depth) * 2LLU;
  children[0] = ft_index(depth - 1LLU, offset);
  children[1] = ft_index(depth - 1LLU, offset + 1LLU);
  return true;
}

void
ft_spans(ft_ulong range[2], ft_ulong index, ft_ulong depth) {
  if (0 ==(index & 1)) {
    range[0] = index;
    range[1] = depth;
  }

  if (0 == depth) { depth = ft_depth(index); }

  ft_ulong offset = ft_offset(index, depth);
  ft_ulong width = ft_two_pow(depth + 1LLU);

  range[0] = offset * width;
  range[1] = (offset + 1LLU) * width - 2LLU;
}

ft_ulong
ft_left_span(ft_ulong index, ft_ulong depth) {
  if (0 == (index & 1)) { return index; }
  if (0 == depth) { depth = ft_depth(index); }
  return ft_offset(index, depth) * ft_two_pow(depth + 1LLU);
}

ft_ulong
ft_right_span(ft_ulong index, ft_ulong depth) {
  if (0 == (index & 1)) { return index; }
  if (0 == depth) { depth = ft_depth(index); }
  return (ft_offset(index, depth) + 1LLU) * ft_two_pow(depth + 1LLU) - 2LLU;
}

ft_ulong
ft_count(ft_ulong index, ft_ulong depth) {
  if (0 == (index & 1)) { return 1; }
  if (0 == depth) { depth = ft_depth(index); }
  return ft_two_pow(depth + 1LLU) - 1LLU;
}

ft_long
ft_full_roots(ft_ulong** roots, ft_ulong index) {
  if (index & 1) { return 0; }
  ft_ulong factor = 1LLU;
  ft_ulong offset = 0LLU;
  int length = 2;
  int count = 0;

  (*roots) = malloc(length * sizeof(ft_ulong));

  index /= 2LLU;

  while (true) {
    if (0 == index) { return count; }

    while (factor * 2LLU <= index) {
      factor *= 2LLU;
    }

    if (count == length) {
      length += 2;
      (*roots) = realloc(*roots, length);
    }

    (*roots)[count] = offset + factor - 1LLU;

    offset = offset + 2LLU * factor;
    index -= factor;
    factor = 1;

    (void) count++;
  }
}
