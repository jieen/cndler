################################################################################################################
#
#														通用Makefile模板
#			自动将src目录下中的.c文件编译，生成所有.o文件保存在bin/objs下
#			修改TARGETS和CC以及CFLAGS和LDFLAG即可完成工程的配置
#										by jieen 		2013-4-27				
#
#################################################################################################################
PROJECT_TOP_DIR=$(shell cd ../; pwd)
PROJECT_BIN_DIR=$(PROJECT_TOP_DIR)/bin
PROJECT_SRC_DIR=$(PROJECT_TOP_DIR)/src
PROJECT_INC_DIR=$(PROJECT_TOP_DIR)/inc
PROJECT_LIB_DIR=$(PROJECT_TOP_DIR)/lib
PROJECT_OBJ_DIR=$(PROJECT_BIN_DIR)/objs
MKDIR := mkdir -p

CC := gcc
TARGETS = opxl

CFLAGS := -g -static -I $(PROJECT_INC_DIR)
LDFLAG := -L $(PROJECT_LIB_DIR)/libiconv.a

src :=$(wildcard $(PROJECT_SRC_DIR)/*.c)
dir := $(notdir $(src))
PROJECT_OBJ := $(patsubst %.c,%.o,$(dir) )
	
PROJECT_ALL_OBJS := $(addprefix $(PROJECT_OBJ_DIR)/, $(PROJECT_OBJ))
	
all:$(PROJECT_SRC_DIR) $(PROJECT_ALL_OBJS)
	$(CC) $(CFLAGS) $(PROJECT_ALL_OBJS) -o $(PROJECT_BIN_DIR)/$(TARGETS) $(LDFLAG)

$(PROJECT_OBJ_DIR)/%.o : $(PROJECT_SRC_DIR)/%.c
	$(MKDIR) $(PROJECT_OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	rm -fr $(PROJECT_OBJ_DIR)
	rm -fr $(PROJECT_BIN_DIR)/$(TARGETS)	
