CC=cc
CFLAGS=-Wall -std=c89 -g
OBJS=main.o data.o
ALGOS=selection.o insertion.o bubble.o
PROJ=csortings

$(PROJ): $(OBJS) $(ALGOS)
	$(CC) -g -o $@ $(OBJS) $(ALGOS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -f $(PROJ) $(OBJS) $(ALGOS)
