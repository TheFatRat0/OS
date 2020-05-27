hdrs = ipc.h
opts = -g -c
c_src = tool1.c ipc.c
c_obj = tool1.o ipc.o
d_src = tool2.c ipc.c
d_obj = tool2.o ipc.o
e_src = tool3.c ipc.c
e_obj = tool3.o ipc.o
f_src = producer.c ipc.c
f_obj = producer.o ipc.o
all:    tool1 tool2 tool3 producer
tool1:   $(c_obj)
	gcc $(c_obj) -o tool1
tool1.o:	$(c_src) $(hdrs)
	gcc $(opts) $(c_src)
tool2:	$(d_obj)
	gcc $(d_obj) -o tool2
tool2.o:	$(p_src) $(hdrs)
	gcc $(opts) $(d_src)
tool3:	$(e_obj)
	gcc $(e_obj) -o tool3
tool3.o:      $(e_src) $(hdrs)
	gcc $(opts) $(e_src)
producer:	$(f_obj)
	gcc $(f_obj) -o producer
producer.o:     $(f_src) $(hdrs)
	gcc $(opts) $(f_src)
clean:
	rm tool1 tool2 tool3 producer *.o      

