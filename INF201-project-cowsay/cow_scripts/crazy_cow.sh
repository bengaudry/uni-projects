#!/bin/bash

# Ce script attend trois arguments a, b, c représentant une équation de la forme "ax^2+bx+c=0"

# On quitte avec une erreur si le nombre d'arguments est différent de 3
if [ "$#" -ne 3 ]; then
  echo "Trois arguments requis (a, b, c -> ax^2+bx+c=0)"
  exit 1
fi

a="$1"
b="$2"
c="$3"

# On calcule le discriminant de l'équation
if [ $a -eq 0 -a $b -ne 0 ]
then
  # Si a = 0, on a une équation du type bx+c = 0 donc x = -c/b
  # (on fait ce cas à part pour éviter une division par 0)
  x=$(echo "-$c/$b" | bc -l)
  cowsay "x=$x"
elif [ $a -eq 0 -a $b -eq 0 ]
  # Si a = b = 0, on a une équation du type c = 0 donc pas possible
  then cowsay "a ou b doit être différent de 0"
else
  delta=$((b*b-4*a*c))
  if [ "$delta" -gt 0 ]
  then
    # On calcule sqrt(delta) et les solutions puis on les affiche
    rac=$(echo "sqrt($delta)" | bc -l)
    x1=$(echo "(-$b-$rac)/(2*$a)" | bc -l)
    x2=$(echo "(-$b+$rac)/(2*$a)" | bc -l)
    cowsay "x=$x1 ou x=$x2"
  elif [ "$delta" -eq 0 ]
  then
    # On calcule puis on affiche l'unique solution
    sol=$(echo "-$b/(2*$a)" | bc -l)
    cowsay "x = $sol"
  else
    cowsay "Pas de solutions réelles"
  fi
fi
