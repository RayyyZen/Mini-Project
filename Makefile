CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCDIR = source
INCDIR = include

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=%.o)
TARGET = Mini-Project

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)
	rm -f $(OBJS)

%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR)

clean:
	rm -f $(OBJS)
	rm -f $(TARGET)
	rm -rf Docs/html Docs/latex

run: all
	rm -rf Docs/html Docs/latex
	doxygen Doxyfile
	./$(TARGET)
