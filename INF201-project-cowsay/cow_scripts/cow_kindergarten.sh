#!/bin/bash

# On affiche les 10 premiers entiers
for i in {1..10}
do
    clear
    cowsay $i
    sleep 1
done

# On efface la console
clear
cowsay -d " "
