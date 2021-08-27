SRCS := cond.c
APP :=$(patsubst %.c,%,$(firstword $(SRCS)))
OBJS := $(SRCS:.c=.o)
DEPS := $(SRCS:.c=.dep)
CC := gcc

all: $(APP)


$(APP): $(OBJS)
	$(CC) -g $^ -o $@ -pthread

$(OBJS):%.o:%.c
	$(CC) -g -c $< -o $@

include $(DEPS)

%.dep: %.c
	$(CC) -M $(CPPFLAGS) $< > $@.$$$$;                  \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

clean:
	rm -rf $(OBJS) $(APP) $(DEPS)
