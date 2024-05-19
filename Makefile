SRCS = main.c achtung.c term_manip.c
EXEC = achtung

buildrun: $(SRCS)
	gcc -o $(EXEC) $(SRCS)
	./$(EXEC)

build: $(SRCS)
	gcc -o $(EXEC) $(SRCS)

run: $(EXEC)
	./$(EXEC)
