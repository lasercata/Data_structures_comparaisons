#!/bin/bash

nb_search=500000

for len in 10 1000 2000 4000 10000 20000 40000 100000 200000 400000 1000000; do
    (./bin/main data/title_$len.tsv $nb_search bst > logs/bst_"$len"_$nb_search.log && echo bst len: $len done)
    (./bin/main data/title_$len.tsv $nb_search avl > logs/avl_"$len"_$nb_search.log && echo avl len: $len done)

    for size in 10 100 1000 10000 100000; do
        (./bin/main data/title_$len.tsv $nb_search htbl $size > logs/htbl_"$len"_"$nb_search"_"$size".log && echo "htbl len: "$len", size: $size" done)
    done
done
wait
