
## Made by		db0
## Contact		db0company@gmail.com
## Website		http://db0.fr/
##

NAME		=	zia

## Directories
LIB_DIR		=	lib/
BIN_DIR		=	bin/

SRC_DIR		=	src/

MAIN_DIR	=	$(SRC_DIR)$(NAME)/

NTWK_DIR	=	$(SRC_DIR)network/
HTTP_DIR	=	$(SRC_DIR)http/

TOOL_DIR	=	$(SRC_DIR)tools/
ERR_DIR		=	$(SRC_DIR)error/

BREF_DIR	=	libBref/src/

INCLUDE		=	-Iinclude/				\
			-Isrc/					\
			-Iapi/					\
			-I$(LIB_DIR)Thread/include/		\
			-I$(LIB_DIR)SNetwork/include/		\
			-Ibref-api/include/bref/		\
			\

## Sources
SRCS		=	$(MAIN_DIR)main.cpp			\
			$(MAIN_DIR)$(NAME)_main.cpp		\
			\
			$(MAIN_DIR)Zia.cpp			\
			\
			$(NTWK_DIR)ZiaNetwork.cpp		\
			\
			$(HTTP_DIR)HttpParser.cpp		\
			$(HTTP_DIR)HttpRequestParser.cpp	\
			$(HTTP_DIR)HttpLiterals.cpp		\
			$(HTTP_DIR)HttpRequest.cpp		\
			$(HTTP_DIR)HttpResponse.cpp		\
			\
			$(TOOL_DIR)InChannel.cpp		\
			$(TOOL_DIR)OutChannel.cpp		\
			\
			$(BREF_DIR)config/BrefValue.cpp		\
			$(BREF_DIR)config/Configuration.cpp	\
			# $(BREF_DIR)http/HttpLiterals.cpp	\
			# $(BREF_DIR)http/HttpParser.cpp		\
			# $(BREF_DIR)http/HttpRequest.cpp		\
			# $(BREF_DIR)http/HttpRequestParser.cpp	\
			# $(BREF_DIR)http/HttpResponse.cpp	\
			$(BREF_DIR)module/AModule.cpp		\
			\

## Libraries
LIB		=	-L$(LIB_DIR) -lSNetwork -lThread -ldl

# Objects
OBJS		=	$(SRCS:.cpp=.o)

# functions
RM		=	rm -f
CXX		=	g++
CFLAGS		=	-ldl -fPIC -W -Wall
LDFLAGS		=	-export-dynamic

## RULES

all		:	$(NAME)

$(NAME)		:	lib $(OBJS)
			$(CXX) $(CFLAGS) $(OBJS) -o $(BIN_DIR)$(NAME) $(LIB) $(LDFLAGS)

# libs
lib		:
			@(cd $(LIB_DIR) && make)

libre		:
			@(cd $(LIB_DIR) && make re)

libclean	:
			@(cd $(LIB_DIR) && make clean)

libfclean	:
			@(cd $(LIB_DIR) && make fclean)

libdistclean	:	libfclean

## clean
clean		:	libclean
			$(RM) $(OBJS)

fclean		:	libfclean clean
			$(RM) $(BIN_DIR)$(NAME)

distclean	:	fclean

## re
re		:	fclean libre all

.cpp.o		:
			$(CXX) -c $(CFLAGS) $(INCLUDE) $< -o $(<:.cpp=.o)

