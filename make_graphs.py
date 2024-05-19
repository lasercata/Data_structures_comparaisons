#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# vim:foldnestmax=1

#--------------------------------
#
# Author            : Lasercata
# Last modification : 2024.05.19
# Version           : v1.0.0
#
#--------------------------------


##-Imports
from sys import argv
from sys import exit as sysexit

import matplotlib.pyplot as plt

from copy import deepcopy


##-Init
base_dict = {
    'T': {'fill': {}, 'search': {}},
    'O': {'fill': {}, 'search': {}},
    'M': {'fill': {}, 'search': {}}
}

# arr = dict(base_dict)
arr = deepcopy(base_dict)
arr['label'] = 'arr'

htbl = {} # {size: {'T': {...}, 'O': {...}, 'M': {...}, 'I': {...}}, ...}

bst = deepcopy(base_dict)
bst['I'] = {}
bst['height'] = {}
bst['label'] = 'bst'

avl = deepcopy(base_dict)
avl['I'] = {}
avl['height'] = {}
avl['label'] = 'avl'

structs = {'arr': arr, 'bst': bst, 'avl': avl}

nb_films_lst = [10, 1000, 2000, 4000, 10000, 20000, 40000, 100000, 200000, 400000, 1000000]

##-Parse functions
def get_line_infos(line):
    '''
    Return (struct, measuring, operation, key, value, size), where :
        - struct    : in ('arr', 'htbl', 'bst', 'avl') ;
        - measuring : in ('T', 'O', 'M', 'I') ;
        - operation : in ('fill', 'search', None) ;
        - key       : either the number of films, or the key (if measuring == 'I') ;
        - value     : the value associated with key ;
        - size      : if struct == 'htbl', it is the hbtl size. None otherwise.
    '''

    struct = line[:line.index(' ')] # arr, htbl, bst, or avl.
    measuring = line[line.index(' ') + 1:][0] # T, O, M, or I.
    size = None

    if measuring == 'I':
        operation = None
        key, val = line[line.index(measuring) + 2 :].split('=') # is_avl, is_bst, avl_height, or bst_height.
        # val = int(val)

    else:
        operation = line[line.index(measuring) + 2 : line.index('[')] # fill or search.

        params = [k.split('=') for k in line[line.index('[') + 1 : line.index(']')].split(' ')] #[[param, val], ...]
        params_d = {}

        for l in params:
            params_d[l[0]] = int(l[1])

        key = params_d['nb_films']
        val = int(line[line.index('\t') + 1 :].split(' ')[0]) # result of the measure

        if 'nb_search' in params_d:
            val /= params_d['nb_search']

        if 'size' in params_d:
            size = params_d['size']


    return (struct, measuring, operation, key, val, size)

def parse(fn):
    '''Parse the file fn and fill the corresponding dictionaries.'''

    with open(fn, 'r') as f:
        for line in f:
            line = line.strip('\n')
            struct, measuring, operation, key, val, size = get_line_infos(line)

            if struct == 'htbl':
                if size not in htbl:
                    htbl[size] = deepcopy(base_dict)
                    htbl[size]['label'] = f'htbl[{size}]'

                htbl[size][measuring][operation][key] = val

            else:
                if measuring == 'I' and key in ('avl_height', 'bst_height'):
                    h, nb_films = val.split(',')
                    structs[struct]['height'][int(nb_films)] = int(h)

                elif operation == None:
                    structs[struct][measuring][key] = val

                else:
                    structs[struct][measuring][operation][key] = val


##-Plot functions
def get_lists_from_dict(d):
    '''Return two lists (keys, values) with keys sorted.'''

    keys = sorted(d.keys())
    values = [d[k] for k in keys]

    return keys, values

#---single
def plot_subplot(d, lb, title, xlabel, ylabel):
    '''Plot a subplot'''

    plt.plot(*get_lists_from_dict(d), label=lb)
    plt.plot(*get_lists_from_dict(d), '+')
    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.legend()

def plot_base_dict(d: dict, title):
    plt.figure()

    plt.title(title)

    #------Time
    #---Fill
    plt.subplot(3, 2, 1)
    plot_subplot(d['T']['fill'], d['label'], 'fill time', 'nb films', 'time (µs)')

    #---Search
    plt.subplot(3, 2, 2)
    plot_subplot(d['T']['search'], d['label'], 'search time', 'nb films', 'time (µs)')

    #------Operations
    #---Fill
    plt.subplot(3, 2, 3)
    plot_subplot(d['O']['fill'], d['label'], 'fill nb operations', 'nb films', 'nb operations')

    #---Search
    plt.subplot(3, 2, 4)
    plot_subplot(d['O']['search'], d['label'], 'search nb operations', 'nb films', 'nb operations')

    #------Memory
    plt.subplot(3, 2, 5)
    plot_subplot(d['M']['fill'], d['label'], 'fill memory', 'nb films', 'memory (o)')

    #------Height
    if 'height' in d:
        plt.subplot(3, 2, 6)
        plot_subplot(d['height'], d['label'], 'tree height', 'nb films', 'height')

    plt.subplots_adjust(top=0.949, bottom=0.075, left=0.057, right=0.986, hspace=0.297, wspace=0.078)
    plt.show()

#---multiple
def plot_subplot_lst(d_lst, lb_lst, title, xlabel, ylabel, xlog=False, ylog=False):
    '''Plot a subplot'''

    for d, lb in zip(d_lst, lb_lst):
        plt.plot(*get_lists_from_dict(d), label=lb)
        plt.plot(*get_lists_from_dict(d), '+')

        if xlog:
            plt.xscale('log')
        if ylog:
            plt.yscale('log')

    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.legend()

def plot_base_dict_lst(d_lst, title):
    plt.figure()

    plt.title(title)

    #------Time
    #---Fill
    plt.subplot(3, 2, 1)
    plot_subplot_lst([d['T']['fill'] for d in d_lst], [d['label'] for d in d_lst], 'fill time', 'nb films', 'time (µs)')

    #---Search
    plt.subplot(3, 2, 2)
    plot_subplot_lst([d['T']['search'] for d in d_lst], [d['label'] for d in d_lst], 'search time', 'nb films', 'time (µs)')

    #------Operations
    #---Fill
    plt.subplot(3, 2, 3)
    plot_subplot_lst([d['O']['fill'] for d in d_lst], [d['label'] for d in d_lst], 'fill nb operations', 'nb films', 'nb operations')

    #---Search
    plt.subplot(3, 2, 4)
    plot_subplot_lst([d['O']['search'] for d in d_lst], [d['label'] for d in d_lst], 'search nb operations', 'nb films', 'nb operations')

    #------Memory
    plt.subplot(3, 2, 5)
    plot_subplot_lst([d['M']['fill'] for d in d_lst], [d['label'] for d in d_lst], 'fill memory', 'nb films', 'memory allocated (o)')

    #------Height
    if True in ['height' in d for d in d_lst]:
        plt.subplot(3, 2, 6)
        for d in d_lst:
            if 'height' in d:
                plt.plot(*get_lists_from_dict(d['height']), label=d['label'])
                plt.plot(*get_lists_from_dict(d['height']), '+')
        plt.title('tree height')
        plt.xlabel('nb films')
        plt.ylabel('height')
        plt.legend()

    plt.subplots_adjust(top=0.949, bottom=0.075, left=0.057, right=0.986, hspace=0.297, wspace=0.078)
    plt.show()


#---htbl size
def plot_htbl_size(d, nb_films):
    x = d.keys()
    y = [d[size]['O']['search'][nb_films] for size in x]

    plt.figure()
    plt.plot(x, y, label=f'htbl[nb_films={nb_films}]')
    plt.plot(x, y, '+')
    # plt.xscale('log')
    # plt.yscale('log')
    plt.title('htbl search time by size')
    plt.xlabel('size')
    plt.ylabel('nb operations')
    plt.legend()

    plt.show()

def plot_htbl_size_lst(d, nb_films_lst):
    x = d.keys()
    y_lst = [[d[size]['O']['search'][nb_films] for size in x] for nb_films in nb_films_lst]

    plt.figure()
    for y in y_lst:
        plt.plot(x, y, label=f'htbl[nb_films={nb_films_lst[y_lst.index(y)]}]')
        plt.plot(x, y, '+')

    plt.xscale('log')
    plt.yscale('log')

    plt.title('htbl search time by size')
    plt.xlabel('size')
    plt.ylabel('nb operations')
    plt.legend()

    plt.show()



##-Run
if __name__ == '__main__':
    if len(argv) < 2:
        print(f'Usage: {argv[0]} filenames ...\nExample :\n\t {argv[0]} logs/*_*')
        sysexit()

    for k in argv[1:]:
        parse(k)

    # print(structs)
    # print(json.dumps(htbl, indent=True))

    # plot_base_dict(avl, 'AVL test')
    # plot_base_dict(bst, 'BST test')
    # plot_base_dict(htbl[1000], 'htbl 1000 test')

    plot_base_dict_lst([avl, bst], 'avl + bst')
    plot_base_dict_lst([avl, bst, htbl[1000]], 'avl + bst + htbl[1000]')
    plot_base_dict_lst([htbl[10], htbl[1000], htbl[100000]], 'htbl[10, 1000, 100000]')
    plot_base_dict_lst([htbl[1000], htbl[10000], htbl[100000]], 'htbl[1000, 10000, 100000]')

    # plot_htbl_size(htbl, 100000)
    plot_htbl_size_lst(htbl, nb_films_lst)
    # plot_htbl_size(htbl, 10)

