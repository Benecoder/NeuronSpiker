g++ -o $1.out $1.cpp
rm $1.csv
./$1.out >> $1.csv
python3 plotting.py $1.csv $2
