CC = gcc
CFLAGS = -Wall -Wextra
SRCDIR = source
INCDIR = include

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=%.o)
TARGET = Mini-Project

APISRCS = $(filter-out $(SRCDIR)/main.c, $(SRCS))
APIOBJS = $(APISRCS:$(SRCDIR)/%.c=%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)
	rm -f $(OBJS)

%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR)

api_s: $(APIOBJS)
	ar r libstudent_s.a $(APIOBJS)
	rm -f $(APIOBJS)

api_d: $(APIOBJS)
	gcc -shared -o libstudent_d.so $(APIOBJS)
	rm -f $(APIOBJS)

clean:
	rm -f $(OBJS)
	rm -f $(TARGET)
	rm -rf Docs/html Docs/latex

run: all
	rm -rf Docs/html Docs/latex
	doxygen Doxyfile
	./$(TARGET)
