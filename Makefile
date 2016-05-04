APP     = hovercraft

SRCDIR  = src
OBJDIR  = obj

SRCS    := $(shell find $(SRCDIR) -name '*.c')
SRCDIRS := $(shell find . -name '*.c' -exec dirname {} \; | uniq)
OBJS    := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

CC       =  gcc
CFLAGS   = -Wall -O2 -std=c99 -g
LDFLAGS  = -lSDL -lSDL_image -lGLU -lGL -lglut -lm


all: $(APP)

$(APP) : buildrepo $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(APP)

buildrepo:
		@$(call make-repo)

define make-repo
   for dir in $(SRCDIRS); \
   do \
	mkdir -p $(OBJDIR)/$$dir; \
   done
endef
