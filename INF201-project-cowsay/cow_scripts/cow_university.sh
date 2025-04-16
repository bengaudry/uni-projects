#!/bin/bash

# On quitte le programme avec une erreur si aucun argument n'est donné
if [ $# -ne 1 ]
then
  echo "Un argument requis"
  exit 1
fi

# Cette fonction détermine si un nombre est premier
is_prime() {
    if [ $1 -lt 1 ] 
    then
        return 1
    elif [ $1 -eq 1 ]
    then 
      return 0
    fi
    for (( i=2; i<$1; i++ ))
    do
        if [ $(($1 % $i)) -eq 0 ]
        then
            return 1
        fi
    done
    return 0
}

# On renomme la variable pour plus de clarté
n=$1
# On parcourt tous les nombres de 1 à n et on les affiche
# seulement si ils sont premiers
echo "Nombres premiers inférieurs à $n :"
for (( j=1; j<n; j++ ))
do
    if is_prime $j
    then
        clear
        cowsay $j
        sleep 1
    fi
done
