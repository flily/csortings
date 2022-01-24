CC=cc
CFLAGS=-Wall -std=c89 -g
ALGOS=selection.o
OBJS=main.o data.o
PROJ=csortings

$(PROJ): $(OBJS) $(ALGOS)
	$(CC) -o $@ $(OBJS) $(ALGOS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -f $(OBJS) $(PROJ)
