CC=cc
CFLAGS=-Wall -std=c89 -g
OBJS=main.o data.o
PROJ=csortings

$(PROJ): $(OBJS)
	$(CC) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -f $(OBJS) $(PROJ)
