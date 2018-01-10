#include "flat-tree.h"
#include "deps/debug/debug.h"
#include "deps/describe/describe.h"
#include <string.h>

debug_t debugger;

int main() {
	debug_init(&debugger, "flat-tree");
	// debug(&debugger, "doing stuff");

	describe("flat-tree_test") {
		it("base blocks") {
			assert(ft_index(0, 0) == 0);
			assert(ft_index(0, 1) == 2);
			assert(ft_index(0, 2) == 4);
		}

		it("parents") {
			assert(ft_index(1, 0) == 1);
			assert(ft_index(1, 1) == 5);
			assert(ft_index(2, 0) == 3);

			assert(ft_parent(0, 0) == 1);
			assert(ft_parent(2, 0) == 1);
			assert(ft_parent(1, 0) == 3);
		}

		it("children") {
			FTulong children[2];
			assert(ft_children(children, 0, 0) == false);

			assert(ft_children(children, 1, 0) == true);
			assert(children[0] == 0);
			assert(children[1] == 2);
			memset(children, 0, sizeof(children));

			assert(ft_children(children, 3, 0) == true);
			assert(children[0] == 1);
			assert(children[1] == 5);
		}

		it("left_child") {
			assert(ft_left_child(0, 0) == -1);
			assert(ft_left_child(1, 0) == 0);
			assert(ft_left_child(3, 0) == 1);
		}

		it("right_child") {
			assert(ft_right_child(0, 0) == -1);
			assert(ft_right_child(1, 0) == 2);
			assert(ft_right_child(3, 0) == 5);
		}

		it("siblings") {
			assert(ft_sibling(0, 0) == 2);
			assert(ft_sibling(2, 0) == 0);
			assert(ft_sibling(1, 0) == 5);
			assert(ft_sibling(5, 0) == 1);
		}

		it("depths") {
			assert(ft_depth(0) == 0);
			assert(ft_depth(1) == 1);
			assert(ft_depth(2) == 0);
			assert(ft_depth(3) == 2);
			assert(ft_depth(4) == 0);
		}

		it("offsets") {
			assert(ft_offset(0, 0) == 0);
			assert(ft_offset(1, 0) == 0);
			assert(ft_offset(2, 0) == 1);
			assert(ft_offset(3, 0) == 0);
			assert(ft_offset(4, 0) == 2);
		}

		it("spans") {
			FTulong range[2];
			ft_spans(range, 0, 0);
			assert(range[0] == 0);
			assert(range[1] == 0);
			memset(range, 0, sizeof(range));

			ft_spans(range, 1, 0);
			assert(range[0] == 0);
			assert(range[1] == 2);
			memset(range, 0, sizeof(range));

			ft_spans(range, 3, 0);
			assert(range[0] == 0);
			assert(range[1] == 6);
			memset(range, 0, sizeof(range));

			ft_spans(range, 23, 0);
			assert(range[0] == 16);
			assert(range[1] == 30);
			memset(range, 0, sizeof(range));

			ft_spans(range, 27, 0);
			assert(range[0] == 24);
			assert(range[1] == 30);
		}

		it("left_span") {
			assert(ft_left_span(0, 0) == 0);
			assert(ft_left_span(1, 0) == 0);
			assert(ft_left_span(3, 0) == 0);
			assert(ft_left_span(23, 0) == 16);
			assert(ft_left_span(27, 0) == 24);
		}

		it("right_span") {
			assert(ft_right_span(0, 0) == 0);
			assert(ft_right_span(1, 0) == 2);
			assert(ft_right_span(3, 0) == 6);
			assert(ft_right_span(23, 0) == 30);
			assert(ft_right_span(27, 0) == 30);
		}

		it("count") {
			assert(ft_count(0, 0) == 1);
			assert(ft_count(1, 0) == 3);
			assert(ft_count(3, 0) == 7);
			assert(ft_count(5, 0) == 3);
			assert(ft_count(23, 0) == 15);
			assert(ft_count(27, 0) == 7);
		}

		it("parent > int32") {
			assert(ft_parent(10000000000, 0) == 10000000001);
		}

		it("child to parent to child") {
			FTulong child = 0;
			for (int i = 0; i < 50; i++) {
				child = ft_parent(child, 0);
			}
			assert(child == 1125899906842623LLU);
			for (int j = 0; j < 50; j++) {
				child = ft_left_child(child, 0);
			}
			assert(child == 0LLU);
		}

		it("iterator") {
			ft_iterator_t* iterator = ft_iterator_new(0);

			assert(iterator->index == 0);
			assert(ft_iterator_parent(iterator) == 1);
			assert(ft_iterator_parent(iterator) == 3);
			assert(ft_iterator_parent(iterator) == 7);
			assert(ft_iterator_right_child(iterator) == 11);
			assert(ft_iterator_left_child(iterator) == 9);
			assert(ft_iterator_next(iterator) == 13);
			assert(ft_iterator_left_span(iterator) == 12);
		}

		it("iterator, non-left start") {
			ft_iterator_t* iterator = ft_iterator_new(1);
			assert(iterator->index == 1);
			assert(ft_iterator_parent(iterator) == 3);
			assert(ft_iterator_parent(iterator) == 7);
			assert(ft_iterator_right_child(iterator) == 11);
			assert(ft_iterator_left_child(iterator) == 9);
			assert(ft_iterator_next(iterator) == 13);
			assert(ft_iterator_left_span(iterator) == 12);
		}
	}
	return assert_failures();
}