all: main acte1 acte2 acte3 acte3b acte4


CC=clang
CFLAGS+= -g -Wall -Wextra -Werror -Wno-unused-parameter -gdwarf-4


tests_acte1: acte1
	@set -e; for f in $$(cat tests_acte1/liste.txt); do echo Test: $$f; ./acte1 tests_acte1/$$f; done; printf "\033[0;32mSuccès\033[0m sur l'acte I !\n"

tests_acte2: acte2
	@set -e; for f in $$(cat tests_acte2/liste.txt); do echo Test: $$f; ./acte2 tests_acte2/$$f; done; printf "\033[0;32mSuccès\033[0m sur l'acte II !\n"

tests_acte3: acte3
	@set -e; for f in $$(cat tests_acte3/liste.txt); do echo Test: $$f; ./acte3 tests_acte3/$$f; done; printf "\033[0;32mSuccès\033[0m sur l'acte III-A !\n"

tests_acte3b: acte3b
	@set -e; for f in $$(cat tests_acte3b/liste.txt); do echo Test: $$f; ./acte3b tests_acte3b/$$f; done; printf "\033[0;32mSuccès\033[0m sur l'acte III-B !\n"

tests_acte4: acte4
	@set -e; for f in $$(cat tests_acte4/liste.txt); do echo Test: $$f; ./acte4 tests_acte4/$$f; done; printf "\033[0;32mSuccès\033[0m sur l'acte IV !\n"

OBJS= arbres.o arbresphylo.o listes.o common_tests.o affichage.o file.o
acte1: acte1.o $(OBJS)
acte2: acte2.o $(OBJS)
acte3: acte3.o $(OBJS)
acte3b: acte3b.o $(OBJS)
acte4: acte4.o $(OBJS)

exercice_secret: exercice_secret.c $(OBJS) client.o

generer_affichage: affichage.o arbres.o

.PHONY: tests_acte1 tests_acte2 tests_acte3 tests_acte3b tests_acte4

# Ici, on utilise l'"intelligence" de 'make' qui saura tout seul
# comment créer les .o à partir des .c
main: main.o arbresphylo.o arbres.o listes.o affichage.o file.o

clean:
	rm -f main *.o acte1 acte2 acte3 acte3b acte4 acte5 dot generer_affichage affichage exercice_secret
