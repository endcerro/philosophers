#!/bin/bash
VAR="50 410 200 200 20"
cd ./philo_one 
make re
cd ../philo_two
make re
cd ../philo_three
make re
cd ..

./philo_one/philo_one $VAR > f1
./philo_two/philo_two $VAR > f2
./philo_three/philo_three $VAR > f3

