#!/usr/bin/env python3
# -*- coding: utf-8 -*-

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


##-Init
base_dict = {
    'T': {'fill': {}, 'search': {}},
    'O': {'fill': {}, 'search': {}},
    'M': {'fill': {}, 'search': {}}
}

arr = dict(base_dict)

htbl = {} # {size: {'T': {...}, 'O': {...}, 'M': {...}, 'I': {...}}, ...}

bst = dict(base_dict)
bst['I'] = {}
bst['height'] = {}

avl = dict(base_dict)
avl['I'] = {}
avl['height'] = {}

structs = {'arr': arr, 'bst': bst, 'avl': avl}


##-Functions
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

    if measuring == 'I':
        operation = None
        key, val = line[line.index(measuring) + 2 :].split('=') # is_avl, is_bst, avl_height, or bst_height.
        # val = int(val)

    else:
        operation = line[line.index(measuring) + 2 : line.index('[')] # fill or search.
        key = int(line[line.index('[') : line.index(']')].split(' ')[0].split('=')[1]) # number of films
        val = int(line[line.index('\t') + 1 :].split(' ')[0]) # result of the measure

    if struct == 'htbl':
        size = int(line[line.index('[') : line.index(']')].split(' ')[1].split('=')[1]) # htbl size

    else:
        size = None

    return (struct, measuring, operation, key, val, size)


def parse(fn):
    '''Parse the file fn and fill the corresponding dictionaries.'''

    with open(fn, 'r') as f:
        for line in f:
            line = line.strip('\n')
            struct, measuring, operation, key, val, size = get_line_infos(line)

            if struct == 'htbl':
                if size not in htbl.keys():
                    htbl[size] = dict(base_dict)
                    htbl[size][measuring][operation][key] = val

            else:
                if measuring == 'I' and key in ('avl_height', 'bst_height'):
                    nb, h = val.split(',')
                    structs[struct]['height'][int(nb)] = int(h)

                elif operation == None:
                    structs[struct][measuring][key] = val

                else:
                    structs[struct][measuring][operation][key] = val


def plot_base_dict(d: dict, title):
    plt.figure()

    plt.title(title)

    #------Time
    #---Fill
    plt.subplot(3, 2, 1)
    plt.plot(d['T']['fill'].keys(), d['T']['fill'].values(), '+')
    plt.title('fill time')
    plt.xlabel('nb films')
    plt.ylabel('time (µs)')

    #---Search
    plt.subplot(3, 2, 2)
    plt.plot(d['T']['search'].keys(), d['T']['search'].values(), '+')
    plt.title('search time')
    plt.xlabel('nb films')
    plt.ylabel('time (µs)')

    #------Operations
    #---Fill
    plt.subplot(3, 2, 3)
    plt.plot(d['O']['fill'].keys(), d['O']['fill'].values(), '+')
    plt.title('fill nb operations')
    plt.xlabel('nb films')
    plt.ylabel('nb operations')

    #---Search
    plt.subplot(3, 2, 4)
    plt.plot(d['O']['search'].keys(), d['O']['search'].values(), '+')
    plt.title('search time')
    plt.xlabel('nb films')
    plt.ylabel('time (µs)')

    #TODO: continue this

    # #------Memory
    # plt.subplot()
    # plt.plot(d['M'].keys(), d['M'].values())

    plt.show()


##-Run
if __name__ == '__main__':
    if len(argv) < 2:
        print(f'Usage: {argv[0]} filenames ...')
        sysexit()

    for k in argv[1:]:
        parse(k)

    print(structs)

    # plot_base_dict(avl, 'avl test')

