SRC := $(wildcard src/*.c) $(wildcard deps/*/*.c)
OBJS := $(SRC:.c=.o)
NAME := ftree
TEST := $(NAME)-test
STATIC := lib$(NAME).a
PREFIX ?= /usr/local

CFLAGS += -I deps -I include

.PHONY: all lib static clean

all: $(OBJS) $(STATIC)

lib: static
static: $(STATIC)

install: $(STATIC)
	install $(STATIC) $(PREFIX)/lib
	mkdir -p $(PREFIX)/include/$(NAME)
	install *.h $(PREFIX)/include/$(NAME)

uninstall:
	rm -rf $(PREFIX)/include/$(NAME)
	rm -rf $(PREFIX)/lib/$(STATIC)

clean:
	rm -f $(TEST) $(OBJS) $(STATIC)

test: $(TEST)
	./$^

$(STATIC): $(OBJS)
	$(AR) crs $@ $^

$(TEST): $(OBJS) test.c
	$(CC) $^ $(CFLAGS) -o $@

