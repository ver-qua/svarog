# OBJS обозначает, какой файл компелировать
OBJS = main.cpp

# CC обозначает, какой компилятор использовать
CC = g++

# COMPILER_FLAGS обозначает, какие фополнительные флаги нужно использовать
# -W показать все предупреждения
COMPILER_FLAGS = -W -pthread

# LINKER_FLAGS обозначает подключаемые библиотеки
LINKER_FLAGS = -lSDL2 -lSDL2_gfx

# OBJ_PATH обозначает директорию компиляции
OBJ_PATH = ./build

# OBJ_NAME обозначает название исполняемого файла
OBJ_NAME = out


# Запуск
run : compile
	$(OBJ_PATH)/$(OBJ_NAME)

# Компиляция?
compile : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_PATH)/$(OBJ_NAME)

# Очистка
clean : 
	rm $(OBJ_PATH)/$(OBJ_NAME)