CC = gcc
UNAME_S := $(shell uname -s)
CFLAGS = -Wall -Werror -Wextra -std=c11
GCOV_FLAGS = --coverage

# Исходники библиотеки
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
NAME = s21_string.a

# Исходники тестов (например, ваш тестовый main с использованием библиотеки check)
TEST_LIB = tests
TEST_SRCS = $(wildcard $(TEST_LIB)/*.c)
# Флаги линковки для библиотеки check
# На Linux обычно достаточно -lcheck -lsubunit -lm -lrt -lpthread
# На macOS (Homebrew) может потребоваться: -L/opt/homebrew/lib -lcheck
TEST_FLAGS = -lcheck -lm -lpthread

# Только для Linux добавляем специфичные библиотеки
ifeq ($(UNAME_S),Linux)
    TEST_FLAGS += -lsubunit -lrt
endif

test:
	# Добавляем флаг -fsanitize=address для поиска утечек памяти
	$(CC) $(CFLAGS) -fsanitize=address $(SRCS) $(TEST_SRCS) $(TEST_FLAGS) -o test_exec
	# Переменная окружения отключает ложные срабатывания внутри самой библиотеки Check
	ASAN_OPTIONS=detect_leaks=1 ./test_exec

	rm -f test_exec *.gcno *.gcda

all: $(NAME)

# Сборка обычной библиотеки
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	ranlib $(NAME)
	rm -f $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Цель для генерации GCOV отчета
gcov_report: clean
	# 1. Компилируем исходники вместе с тестами и флагами покрытия
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(SRCS) $(TEST_SRCS) $(TEST_FLAGS) -o test_exec
	# 2. Запускаем тесты, чтобы собралась статистика (.gcda файлы)
	./test_exec
	# 3. Собираем данные покрытия через lcov
	lcov -t "s21_string_report" -o s21_string.info -c -d .
	lcov --remove s21_string.info '*/$(TEST_LIB)/*' -o s21_string.info
	# 4. Формируем красивую HTML папку
	genhtml -o report s21_string.info
	# 5. Очищаем исполняемый файл и промежуточные файлы покрытия
	rm -f test_exec *.gcno *.gcda

clean:
	rm -f $(OBJS) *.gcno *.gcda *.info
	rm -rf report test_exec

fclean: clean
	rm -f $(NAME)

re: fclean all


# Проверка стиля (опционально)
check-style:
	clang-format -n $(SRCS) $(TEST_SRCS)

fix-style:
	clang-format -i $(SRCS) $(TEST_SRCS)

.PHONY: all clean fclean re gcov_report

