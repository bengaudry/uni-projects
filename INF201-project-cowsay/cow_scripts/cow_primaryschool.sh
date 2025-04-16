#!/bin/bash

# On quitte le programme avec une erreur si aucun argument ou trop d'arguments
if [ $# -ne 1 ] 
then 
    echo "Exactement un argument attendu"
    exit
fi

if [$1 -le 0 ]
then
  echo "n doit être supérieur ou égal à 1"
  exit
fi

# On affiche les n premiers entiers
for (( i=1; i<=$1; i++ ))
do
    clear
    cowsay $i
    sleep 1
done

# On efface la console
clear
cowsay -d " "
