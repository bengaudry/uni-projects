#!/bin/bash

# On quitte le programme avec une erreur si aucun argument ou trop d'arguments
if [ $# -ne 1 ] 
then 
    echo "Exactement un argument attendu"
    exit
fi

# On définit les premiers termes de la suite
u0=1
u1=1

# On regroupe certaines instructions répétitives dans
# une fonction say
say () {
    cowsay $1
    sleep 1
    clear
}  

# On affiche les deux premiers termes de la suite
say $u0
say $u1

# On affiche tous les termes de la suite (jusqu'à n-1)
for (( i=1; i<=$(($1-1)); i++ ))
do
    un=$(($u1+$u0))
    say $un
    u0=$u1
    u1=$un
done