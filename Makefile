CC=cc
CFLAGS=-Wall -std=c89 -g
ALGOS=selection.o insertion.o
OBJS=main.o data.o
PROJ=csortings

$(PROJ): $(OBJS) $(ALGOS)
	$(CC) -g -o $@ $(OBJS) $(ALGOS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -f $(PROJ) $(OBJS) $(ALGOS)
