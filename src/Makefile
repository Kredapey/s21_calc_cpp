CPP=g++
CPP_FLAGS=-std=c++17 -Wall -Werror -Wextra
TEST_LIBS = -lgtest

all: tests install dvi open uninstall clean

s21_calculator.o:
	$(CPP) $(CPP_FLAGS) -c ./model/Calculator_model.cc ./controller/Calculator_controller.cc -g $(TEST_LIBS)

s21_calculator_tests.o:
	$(CPP) $(CPP_FLAGS) -c ./tests/Calculator_tests.cc -g $(TEST_LIBS)

s21_calculator.a: s21_calculator.o
	ar rcs s21_calculator.a Calculator_controller.o Calculator_model.o

tests: s21_calculator_tests.o s21_calculator.a
	$(CPP) Calculator_controller.o Calculator_model.o Calculator_tests.o -o test s21_calculator.a $(TEST_LIBS)
	./test

gcov_report: s21_calculator.a
	$(CPP) $(CPP_FLAGS) --coverage ./tests/Calculator_tests.cc ./model/Calculator_model.cc ./controller/Calculator_controller.cc -o gcov_report s21_calculator.a $(TEST_LIBS)
	chmod +x *
	./gcov_report
	lcov -t "gcov_report" -o gcov_report.info --no-external --ignore-errors mismatch -c -d .
	genhtml -o report/ gcov_report.info
	open ./report/index.html

valgrind: tests
	CK_FORK=no valgrind --track-origins=yes --leak-check=full --leak-resolution=med --show-leak-kinds=all -s ./test

install: uninstall clean
	mkdir -p build
	cd build && qmake6 .. && make && rm Makefile

uninstall:
	rm -rf ./build*

open:
	./build/Calculator.app/Contents/MacOS/Calculator

dist: install
	rm -rf ../Calc_arch/
	mkdir ../Calc_arch/
	cp -a Makefile ./controller ./model ./QCustomLib ./view ./brief ./tests ./*.pro ./*.user ./*.cpp ./build/Calculator.app ../Calc_arch
	cd ../ && tar -cvzf Calc_arch.tar.gz Calc_arch

dvi:
	open ./brief/index.html

style:
	clang-format -n ./view/*.cc ./view/*.h ./controller/*.cc ./controller/*.h ./model/*.cc ./model/*.h ./*.cpp ./QCustomLib/*.cpp ./QCustomLib/*.h ./tests/*.cc

clean:
	rm -rf *.{a,o,dSYM,out,info,gcda,gcno,txt,log} test gcov_report ../Calc_arch.tar.gz ../Calc_arch ./report
