# CC = gcc
# CFLAGS = -O3 -std=c99

# OBJS = morton.o 

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# compile: $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) driver.c  -o transpose.x -march=native

# run:
# 	./transpose.x
# 	./transpose.x 1000  4 4

# clean:
# 	rm -f *.x *~ *.o

CC = gcc
CFLAGS = -O3 -std=c99 -Wall -Wextra
AVX2FLAGS = -mavx2 -mavx

OBJS = morton.o driver.o

# morton.c uses AVX2 intrinsics
morton.o: CFLAGS += $(AVX2FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

transpose.x: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

compile: transpose.x

run:
	./transpose.x
	./transpose.x 1000 4 4

clean:
	rm -f *.x *~ *.o
