g++ -o $1.out $1.cpp
rm $1.csv
./$1.out >> $1.csv
python $1.py $1.csv
