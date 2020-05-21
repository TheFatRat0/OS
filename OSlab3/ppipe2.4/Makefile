srcs = ppipe2.4.c 
objs = ppipe2.4.o 
opts = -g -c 
all: ppipe2.4
ppipe2.4: $(objs) 
	gcc $(objs) -o ppipe2.4 
ppipe2.4.o: $(srcs) 
	gcc $(opts) $(srcs) 
clean: 
	rm ppipe2.4 *.o
