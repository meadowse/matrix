all: clean s21_matrix.a test gcov_report

s21_matrix.a: clean
	gcc -Wall -Werror -Wextra -c s21_matrix.c
	ar rc s21_matrix.a s21_matrix.o
	ranlib s21_matrix.a
	cp s21_matrix.a libs21_matrix.a
	rm *.o

clean:
	rm -rf *.o *.a *.so *.g* *.i* *.ht* *.css test r* *.t* *.d*

test:
	checkmk clean_mode=1 test.check > test.c
	gcc --coverage -Wall -Werror -Wextra test.c s21_matrix.c -lcheck -o test
	./test

gcov_report: test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

install lcov:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

check: test
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.c *.h
	cp ../materials/linters/.clang-format .
	clang-format -i *.c *.h
	clang-format -n *.c *.h
	make test