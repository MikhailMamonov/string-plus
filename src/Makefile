CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
GCOV_FLAGS = --coverage

# Исходники библиотеки (укажите все ваши 5 файлов)
SRCS = memchr.c
OBJS = $(SRCS:.c=.o)
NAME = s21_string.a

# Исходники тестов (например, ваш тестовый main с использованием библиотеки check)
TEST_SRCS = tests/test_main.c tests/test_memchr.c
# Флаги линковки для библиотеки check
# На Linux обычно достаточно -lcheck -lsubunit -lm -lrt -lpthread
# На macOS (Homebrew) может потребоваться: -L/opt/homebrew/lib -lcheck
TEST_FLAGS = -lcheck -lsubunit -lm -lrt -lpthread

test:
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(SRCS) $(TEST_SRCS) $(TEST_FLAGS) -o test_exec
	./test_exec

gcov_report: clean test
	lcov -t "s21_string_report" -o s21_string.info -c -d .
	genhtml -o report s21_string.info
	rm -f test_exec *.gcno *.gcda
# Флаги для подключения библиотеки check (стандарт Школы 21)
# На macOS может потребоваться дополнительно указать пути к Homebrew

all: $(NAME)

# Сборка обычной библиотеки
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	ranlib $(NAME)

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

.PHONY: all clean fclean re gcov_report

