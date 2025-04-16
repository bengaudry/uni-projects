#!/bin/bash

# On quitte avec une erreur si aucun argument n'est donné
if [ $# -ne 1 ]
then
  echo "Un argument requis"
  exit 1
fi

# On calcule le résultat avec la commande bc et on le stocke dans une variable
result=$(echo "$1" | bc)

# puis on l'affiche
cowsay -e $result $1 