.PHONY: all clean fclean re
# .SILENT:

NAME	:=	fall2024

# //////////////////////////////////////////////////////////////////////////// #
#                                   ALL FILES                                  #
# //////////////////////////////////////////////////////////////////////////// #

# /////////////////////////////////// Files ////////////////////////////////// #
LST_INCS	:=	debug.hpp \
							fallchallenge.hpp \
							input_handling.hpp \
							action.hpp
LST_SRCS	:=	main.cpp \
							debug.cpp \
							input_handling.cpp \
							action.cpp
LST_TMPT	:=
LST_DEPS	:=	$(LST_SRCS:.cpp=.d)
LST_OBJS	:=	$(LST_SRCS:.cpp=.o)

# //////////////////////////////// Directories /////////////////////////////// #

P_INCS	:=	incs/
P_SRCS	:=	srcs/
P_TMPT	:=	tmpt/
P_DEPS	:=	.deps/
P_OBJS	:=	.objs/

# ///////////////////////////////// Shortcuts //////////////////////////////// #
INCS	:=	$(addprefix $(P_INCS),$(LST_INCS))
SRCS	:=	$(addprefix $(P_SRCS),$(LST_SRCS))
TMPT	:=	$(addprefix $(P_TMPT),$(LST_TMPT))
DEPS	:=	$(addprefix $(P_DEPS),$(LST_DEPS))
OBJS	:=	$(addprefix $(P_OBJS),$(LST_OBJS))

# //////////////////////////////////////////////////////////////////////////// #
#                               COMMAND SHORTCUTS                              #
# //////////////////////////////////////////////////////////////////////////// #

# ///////////////////////////////// Commands ///////////////////////////////// #
CC	:=	c++
CF	:=	-Wall -Werror -Wextra
CI	:=	-I $(P_INCS) -I $(P_TMPT)
RM	:=	rm -rf

# //////////////////////////////////////////////////////////////////////////// #
#                                     RULES                                    #
# //////////////////////////////////////////////////////////////////////////// #

all: $(NAME)

# ////////////////////////////// Binary creation ///////////////////////////// #
$(NAME): $(OBJS)
	$(CC) $(CF) $(CI) $(OBJS) -o $@

$(DEPS):	$(SRCS) | $(P_DEPS)
	$(CC) $(CF) $(CI) -MM -MF $@ -MT "$(P_OBJS)$*.o $@" $<

-include $(DEPS)

$(P_OBJS)%.o:	$(P_SRCS)%.cpp $(P_DEPS)%.d | $(P_OBJS)
	$(CC) $(CF) $(CI) -I $(P_DEPS) -c $< -o $@

# /////////////////////////// Directories Creation /////////////////////////// #
$(P_DEPS):
	mkdir -p $(P_DEPS)

$(P_OBJS):
	mkdir -p $(P_OBJS)

# ////////////////////////////// Mandatory rules ///////////////////////////// #
clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(P_OBJS)
	$(RM) $(P_DEPS)

fclean:
	$(MAKE) clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all