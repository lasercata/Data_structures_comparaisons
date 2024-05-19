#!/bin/bash

nb_search=10000

for len in 10 1000 2000 4000 10000 20000 40000 100000 200000 400000 1000000; do
    echo "len: $len"
    ./bin/main data/title_$len.tsv $nb_search bst > logs/bst_"$len"_$nb_search.log &
    ./bin/main data/title_$len.tsv $nb_search avl > logs/avl_"$len"_$nb_search.log &

    for size in 10 100 1000 10000 100000; do
        echo "htbl size: $size"
        ./bin/main data/title_$len.tsv $nb_search htbl $size > logs/htbl_"$len"_"$nb_search"_"$size".log &
    done
done
wait
