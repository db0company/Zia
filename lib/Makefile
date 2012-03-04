
## name

NAME_NETWORK	= SNetwork
NAME_THREAD	= Thread

## directories
DIR_NETWORK	= SNetwork
DIR_THREAD	= Thread

DIR_SRC		= src/
DIR_INC		= include/

## srcs
SRC_NETWORK	= $(NAME_NETWORK)/$(DIR_SRC)/ATCPClientSocket.cpp	\
		  $(NAME_NETWORK)/$(DIR_SRC)/ATCPServerSocket.cpp	\
		  $(NAME_NETWORK)/$(DIR_SRC)/TCPClientSocketUnix.cpp	\
		  $(NAME_NETWORK)/$(DIR_SRC)/TCPServerSocketUnix.cpp	\
		  $(NAME_NETWORK)/$(DIR_SRC)/UDPServerSocketUnix.cpp	\
		  $(NAME_NETWORK)/$(DIR_SRC)/UDPClientSocketUnix.cpp

SRC_THREAD	= $(NAME_THREAD)/$(DIR_SRC)/MutexUnix.cpp		\
		  $(NAME_THREAD)/$(DIR_SRC)/ThreadUnix.cpp		\
		  $(NAME_THREAD)/$(DIR_SRC)/CondVarUnix.cpp		\
		  $(NAME_THREAD)/$(DIR_SRC)/ScopedLock.cpp


## objects
OBJS_NETWORK	= $(SRC_NETWORK:.cpp=.o)
OBJS_THREAD	= $(SRC_THREAD:.cpp=.o)

## bin
RM		= rm -f
MV		= mv
CXX		= g++
CFLAGS		+= -Wextra -Wall -Werror -I$(DIR_NETWORK)/$(DIR_INC) -I$(DIR_THREAD)/$(DIR_INC)
AR		= ar r

## the game

all		: $(NAME_NETWORK) $(NAME_THREAD)

$(NAME_NETWORK) : $(OBJS_NETWORK)
		  $(AR) lib$(NAME_NETWORK).a $(OBJS_NETWORK)
		  ranlib lib$(NAME_NETWORK).a

$(NAME_THREAD)	: $(OBJS_THREAD)
		  $(AR) lib$(NAME_THREAD).a $(OBJS_THREAD)
		  ranlib lib$(NAME_THREAD).a
clean		:
		$(RM) $(OBJS_THREAD)
		$(RM) $(OBJS_NETWORK)

fclean		: clean
		$(RM) lib$(NAME_NETWORK).a
		$(RM) lib$(NAME_THREAD).a

re		: fclean all

.cpp.o		:
		$(CXX) -c $(CFLAGS) $< -o $(<:.cpp=.o) -I$(DIR_NETWORK)/$(DIR_INC) -I$(DIR_THREAD)/$(DIR_INC)