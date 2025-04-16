echo "TEST 1 - cow_kindergarten.sh"
sleep 2
./cow_kindergarten.sh

echo "TEST 2 - cow_primaryschool.sh (doit fonctionner normalement)"
sleep 2
./cow_primaryschool.sh 4

echo "TEST 3 - cow_primaryschool.sh (doit renvoyer une erreur)"
sleep 2
./cow_primaryschool.sh 0

echo "TEST 4 - cow_highschool.sh (doit afficher 1, 4, 9, 16)"
sleep 2
./cow_highscool.sh 4

echo "TEST 5 - cow_college.sh (doit afficher 1, 1, 2, 3, 5, 8, 13)"
sleep 2
./cow_college 6

echo "TEST 6 - cow_university.sh (doit afficher 1, 2, 3, 5, 7, 11)"
sleep 2
./cow_university.sh 12

echo "TEST 7 - smart_cow.sh (doit afficher (3+11) et 14"
sleep 2
./smart_cow.sh "3+11"

echo "TEST 8 - crazy_cow.sh (doit afficher x = -0.5 ou x = 0)"
sleep 2
./crazy_cow.sh 4 2 0

echo "TEST 9 - crazy_cow.sh (doit afficher une erreur (a=b=0)"
sleep 2
./crazy_cow.sh 0 0 1

echo "TEST 9 - crazy_cow.sh (doit afficher \"pas de solutions réelles\")"
sleep 2
./crazy_cow.sh 2 4 4
