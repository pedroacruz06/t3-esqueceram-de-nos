install:
	sudo apt-get install -f flex
	sudo apt-get install -f bison

compile:
	bison --defines=token.h t3.y
	flex t3.l
	cc -o compl t3.tab.c lex.yy.c main.c expr.c decl.c stmt.c type.c param_list.c lbn.c

test:
	./run_tests.sh

all:
	make install
	make compile
	make test

clean:
	rm lex.yy.c
	rm t3.tab.c
	rm token.h
	rm compl

