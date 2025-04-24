#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2024/2025
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond � toutes les d�pendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'�dition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = main test_image test_geometrie test_contour test_postscript test_mult_contours test_geometrie_distance test_simplification test_simplification_bezier test_postscript_bezier2 test_postscript_bezier3


#############################################################################
# definition des regles
#############################################################################

########################################################
# la r�gle par d�faut
all : $(EXECUTABLES)

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules
image.o : image.c image.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

geometrie.o : geometrie.c geometrie.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module geometrie"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

contour.o : contour.c contour.h geometrie.h image.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

bezier.o : bezier.c bezier.h geometrie.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module bezier"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

postscript.o : postscript.c postscript.h contour.h image.h geometrie.h simplification_bezier.h bezier.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module postscript"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

simplification_contours.o : simplification_contours.c simplification_contours.h contour.h image.h geometrie.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module simplification_contours"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

simplification_bezier.o : simplification_bezier.c simplification_bezier.h geometrie.h bezier.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module simplification_bezier"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_image.o : tests/test_image.c image.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<
		
test_geometrie.o : tests/test_geometrie.c geometrie.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_geometrie"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_contour.o : tests/test_contour.c contour.h image.h geometrie.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_postscript.o : tests/test_postscript.c contour.h image.h geometrie.h simplification_bezier.h bezier.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_postscript"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_mult_contours.o : tests/test_mult_contours.c contour.h image.h geometrie.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_mult_contours"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_geometrie_distance.o : tests/test_geometrie_distance.c geometrie.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_geometrie_distance"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_simplification.o : tests/test_simplification.c simplification_contours.h postscript.h contour.h image.h geometrie.h simplification_bezier.h bezier.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_simplification"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_simplification_bezier.o : tests/test_simplification_bezier.c simplification_bezier.h geometrie.h contour.h image.h bezier.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_simplification_bezier"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_postscript_bezier2.o : tests/test_postscript_bezier2.c simplification_bezier.h postscript.h geometrie.h contour.h image.h bezier.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_postscript_bezier2"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_postscript_bezier3.o : tests/test_postscript_bezier3.c simplification_bezier.h postscript.h geometrie.h contour.h image.h bezier.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_postscript_bezier3"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

main.o: main.c image.o contour.o postscript.o simplification_bezier.o simplification_contours.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module main"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de creation des executables

test_image : test_image.o image.o 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_geometrie : test_geometrie.o geometrie.o 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_contour : test_contour.o contour.o geometrie.o image.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_postscript : test_postscript.o postscript.o contour.o geometrie.o image.o simplification_bezier.o bezier.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_mult_contours : test_mult_contours.o contour.o geometrie.o image.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_geometrie_distance : test_geometrie_distance.o geometrie.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_simplification : test_simplification.o simplification_contours.o postscript.o contour.o image.o geometrie.o simplification_bezier.o bezier.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_simplification_bezier : test_simplification_bezier.o simplification_bezier.o geometrie.o contour.o image.o bezier.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_postscript_bezier2 : test_postscript_bezier2.o simplification_bezier.o postscript.o geometrie.o contour.o image.o bezier.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_postscript_bezier3 : test_postscript_bezier3.o simplification_bezier.o postscript.o geometrie.o contour.o image.o bezier.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

main: main.o image.o contour.o postscript.o simplification_bezier.o simplification_contours.o postscript.o geometrie.o contour.o image.o bezier.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@


# regle pour "nettoyer" le r�pertoire
clean:
	rm -fR $(EXECUTABLES) *.o 
