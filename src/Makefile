CC = g++ -g --std=c++17 -Wall -Werror -Wextra
# -fsanitize=address
GCOV=-fprofile-arcs -ftest-coverage
OS=$(shell uname)
DIR=./build/
ifeq ($(OS), Linux)
  LIBS=-lgtest -lpthread -lrt -lm -lsubunit
else
  LIBS=-lgtest
endif

all: clean tests

tests:	
	$(CC) s21_test.cpp mymodel.cpp $(LIBS) -o model_test.out
	./model_test.out

build: clean
	mkdir $(DIR); cd $(DIR); qmake ../; make; rm -rf *.cpp *.h *.ui *.o

install: build
	mkdir $(HOME)/Desktop/SmartCalc_Torell/
	cp -rf $(DIR)SmartCalc.app $(HOME)/Desktop/SmartCalc_Torell/
	make clean

uninstall:
	rm -rf $(HOME)/Desktop/SmartCalc_Torell/

dvi:
	makeinfo --html Documentation.texi
	open ./Documentation/index.html

dist:
	rm -rf SmartCalc_archive
	mkdir SmartCalc_archive
	cp Makefile *.h *.pro Documentation.texi *.cpp *.ui *.user SmartCalc_archive/
	tar -cvzf $(HOME)/Desktop/SmartCalc_archive.tgz SmartCalc_archive/
	rm -rf SmartCalc_archive/

clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.out
	rm -rf ./report
	rm -rf ./Documentation
	rm -rf ./build
	rm -rf $(HOME)/Desktop/SmartCalc_archive.tgz
	rm -rf ./model_test.out.dSYM

leaks:
	make tests
	CK_FORK=no leaks --atExit -- ./model_test.out
	make clean
	
check: 
	@cp ../materials/linters/.clang-format .clang-format
	@clang-format -i *.cpp *.h
	@rm -rf .clang-format


gcov_report:
	$(CC) $(GCOV) s21_test.cpp mymodel.cpp $(LIBS) -o GCOV_test.out 
	./GCOV_test.out
	lcov -t "GCOV_test" -o GCOV_test.info -c -d . --no-external
	genhtml -o report GCOV_test.info
	open -a "Google Chrome" report/index.html

cppcheck:
	cppcheck graph.cpp mymodel.cpp s21_test.cpp controller.cpp