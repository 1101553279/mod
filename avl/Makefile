
SRCS := avl.c main.c
OBJS := $(SRCS:.c=.o)
TGT := $(patsubst %.c,%,$(word 1,$(SRCS)))
#TGT := $(patsubst %.c,%,$(firstword $(SRCS)))
#TGT := cond
#$(info "--TGT = $(TGT)")

$(TGT):$(OBJS)
	gcc  -g $^ -o $@

$(OBJS):%.o:%.c
	gcc -g -c $< -o $@

clean:
	rm $(TGT) $(OBJS)

.PHONY: $(TGT) clean
