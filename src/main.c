//---------Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/init_random.h"
#include "../include/film.h"
#include "../include/complexite.h"

#include "../include/htbl.h"
#include "../include/bst.h"
#include "../include/avl.h"


//---------Constants
#define LINE_LEN 4096
#define NB_KEYS 100000
#define MIN_NB_KEYS 32
// #define MIN_NB_KEYS NB_KEYS


//---------Structures
struct arr_s { // Used for dynamically growing array. O(1) amortized complexity (real_size *= 2)
    // int* arr;      // the array
    t_film* arr;   // the array
    int len;       // the meaningful values range from 0 to len - 1.
    int real_size; // the size of the array (real_size >= len)
};
typedef struct arr_s* arr;


//---------Signatures
htbl* fill_htbl(char* filename, int size);
void search_in_htbl(htbl* t_ptr, arr keys, int nb_search);
void test_htbl(char* filename, int n, int nb_search);

bst_tree fill_bst(char* filename);
void search_in_bst(bst_tree t, arr keys, int nb_search);
void test_bst(char* filename, int nb_search);

avl_tree fill_avl(char* filename);
void search_in_avl(avl_tree t, arr keys, int nb_search);
void test_avl(char* filename, int nb_search);

arr get_keys(char* filename);
void free_arr(arr* a);

int main(int argc, char* argv[]);


//---------Implementations
//------Hash table
htbl* fill_htbl(char* filename, int size) {
    // Creates a hash table and fill it with film data from filename

    initialiser_comp_op_elementaire();
    init_memory();

    htbl* h = init_htbl(size);
    FILE* fd = fopen(filename, "r");
    if (fd == NULL) {
        fprintf(stderr, "Error while opening file '%s'.\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[LINE_LEN];
    t_film* pfilm;
    int nb = 0;

    demarrer_chrono();

    while (fgets(line, sizeof(line), fd) != NULL) {
        pfilm = creer_film(line);

        if (pfilm != NULL) {
            add_elem_htbl(h, pfilm);
            ++nb;
        }
    }

    printf("htbl T fill[nb_films=%d size=%d] :\t", nb, size);
    stop_chrono_and_print_time(nb);

    printf("htbl O fill[nb_films=%d size=%d] :\t", nb, size);
    afficher_op_elem();

    printf("htbl M fill[nb_films=%d size=%d] :\t", nb, size);
    show_memory();

    fclose(fd);
    return h;
}

void search_in_htbl(htbl* t_ptr, arr keys, int nb_search) {
    /*
     * Randomly select elements from the array, and search for them in the hash table.
     *
     * - htbl* t_ptr   : a pointer to the hash table ;
     * - arr keys      : the array containing all films ;
     * - int nb_search : the number of search to perform.
     */

    initialiser_comp_op_elementaire();
    // init_memory();
    demarrer_chrono();

    for (int k = 0; k < nb_search; ++k) {
        int i = rand() % keys->len;
        t_film to_find = keys->arr[i];

        if (!is_in_htbl(*t_ptr, &to_find)) {
            printf("search_in_htbl: incorrect: not in ! (%d)\n", to_find.num);
        }
    }

    printf("htbl T search[nb_films=%d nb_search=%d size=%d] :\t", keys->len, nb_search, t_ptr->n);
    stop_chrono_and_print_time(nb_search);

    printf("htbl O search[nb_films=%d nb_search=%d size=%d] :\t", keys->len, nb_search, t_ptr->n);
    afficher_op_elem();

    // printf("htbl M search[nb_search=%d] :\t", nb_search);
    // show_memory();
}

void test_htbl(char* filename, int size, int nb_search) {
    arr keys = get_keys(filename);

    htbl* t = fill_htbl(filename, size);

    // print_htbl(*t);
    search_in_htbl(t, keys, nb_search);

    free_htbl(&t);
    free_arr(&keys);
}

//------BST
bst_tree fill_bst(char* filename) {
    // Creates a bst and fill it with film data from filename

    initialiser_comp_op_elementaire();
    init_memory();

    bst_tree t = create_empty_bst_tree();
    FILE* fd = fopen(filename, "r");
    if (fd == NULL) {
        fprintf(stderr, "Error while opening file '%s'.\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[LINE_LEN];
    t_film* pfilm;
    int nb = 0;

    demarrer_chrono();

    while (fgets(line, sizeof(line), fd) != NULL) {
        pfilm = creer_film(line);

        if (pfilm != NULL) {
            add_to_bst_tree(&t, pfilm);
            ++nb;
        }
    }

    printf("bst T fill[nb_films=%d] :\t", nb);
    stop_chrono_and_print_time(nb);

    printf("bst O fill[nb_films=%d] :\t", nb);
    afficher_op_elem();

    printf("bst M fill[nb_films=%d] :\t", nb);
    show_memory();

    fclose(fd);
    return t;
}

void search_in_bst(bst_tree t, arr keys, int nb_search) {
    /*
     * Randomly select elements from the array, and search for them in the bst.
     *
     * - bst_tree t    : the bst to search in ;
     * - arr keys      : the array containing all films ;
     * - int nb_search : the number of search to perform.
     */

    initialiser_comp_op_elementaire();
    // init_memory();
    demarrer_chrono();

    for (int k = 0; k < nb_search; ++k) {
        int i = rand() % keys->len;
        t_film to_find = keys->arr[i];

        if (!in_bst_tree(t, &to_find)) {
            printf("search_in_bst: incorrect: not in ! (%d)\n", to_find.num);
        }
    }

    printf("bst T search[nb_films=%d nb_search=%d] :\t", keys->len, nb_search);
    stop_chrono_and_print_time(nb_search);

    printf("bst O search[nb_films=%d nb_search=%d] :\t", keys->len, nb_search);
    afficher_op_elem();

    // printf("bst M search[nb_search=%d] :\t", nb_search);
    // show_memory();
}

void test_bst(char* filename, int nb_search) {
    (void) nb_search;

    arr keys = get_keys(filename);
    bst_tree t = fill_bst(filename);

    // print_bst_tree_infix(t);
    search_in_bst(t, keys, nb_search);

    printf("bst I is_bst=%d\n", is_bst(t));
    printf("bst I bst_height=%d,%d\n", get_bst_height(t), keys->len);

    free_bst_tree(&t);
    free_arr(&keys);
}

//------AVL
avl_tree fill_avl(char* filename) {
    // Creates an avl and fill it with film data from filename

    initialiser_comp_op_elementaire();
    init_memory();

    avl_tree t = init_avl_tree();
    FILE* fd = fopen(filename, "r");
    if (fd == NULL) {
        fprintf(stderr, "Error while opening file '%s'.\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[LINE_LEN];
    t_film* pfilm;
    int nb = 0;

    demarrer_chrono();

    while (fgets(line, sizeof(line), fd) != NULL) {
        pfilm = creer_film(line);

        if (pfilm != NULL) {
            avl_leaf_insertion(&t, pfilm);
            ++nb;
        }
    }

    printf("avl T fill[nb_films=%d] :\t", nb);
    stop_chrono_and_print_time(nb);

    printf("avl O fill[nb_films=%d] :\t", nb);
    afficher_op_elem();

    printf("avl M fill[nb_films=%d] :\t", nb);
    show_memory();

    fclose(fd);
    return t;
}

void search_in_avl(avl_tree t, arr keys, int nb_search) {
    /*
     * Randomly select elements from the array, and search for them in the avl.
     *
     * - avl_tree t    : the avl to search in ;
     * - arr keys      : the array containing all films ;
     * - int nb_search : the number of search to perform.
     */

    initialiser_comp_op_elementaire();
    // init_memory();
    demarrer_chrono();

    for (int k = 0; k < nb_search; ++k) {
        int i = rand() % keys->len;
        t_film to_find = keys->arr[i];

        if (!in_avl_tree(t, &to_find)) {
            printf("search_in_avl: incorrect: not in ! (%d)\n", to_find.num);
        }
    }

    printf("avl T search[nb_films=%d nb_search=%d] :\t", keys->len, nb_search);
    stop_chrono_and_print_time(nb_search);

    printf("avl O search[nb_films=%d nb_search=%d] :\t", keys->len, nb_search);
    afficher_op_elem();

    // printf("avl M search[nb_search=%d] :\t", nb_search);
    // show_memory();
}

void test_avl(char* filename, int nb_search) {
    (void) nb_search;

    arr keys = get_keys(filename);
    avl_tree t = fill_avl(filename);

    // print_avl_tree(t);
    search_in_avl(t, keys, nb_search);

    // printf("I is_avl_a_bst=%d\n", is_avl_a_bst(t));
    printf("avl I is_avl=%d\n", is_avl(t));
    printf("avl I avl_height=%d,%d\n", get_avl_height(t), keys->len);

    free_avl_tree(&t);
    free_arr(&keys);
}

//------Array
arr get_keys(char* filename) {
    // return an array of keys

    initialiser_comp_op_elementaire();
    init_memory();

    FILE* fd = fopen(filename, "r");
    if (fd == NULL) {
        fprintf(stderr, "Error while opening file '%s'.\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[LINE_LEN];
    t_film* pfilm;

    // arr keys = (arr) malloc(sizeof(struct arr_s));
    arr keys = (arr) allouer(sizeof(struct arr_s));
    keys->real_size = MIN_NB_KEYS;
    keys->len = 0;
    operation_elementaire();

    // keys->arr = (t_film*) malloc(((size_t) keys->real_size) * sizeof(t_film));
    keys->arr = (t_film*) allouer(((size_t) keys->real_size) * sizeof(t_film));
    operation_elementaire();

    demarrer_chrono();

    while (fgets(line, sizeof(line), fd) != NULL) {
        pfilm = creer_film(line);
        operation_elementaire();

        if (pfilm != NULL) {
            operation_elementaire();
            // keys->arr[keys->len] = pfilm->num;
            keys->arr[keys->len] = *pfilm;
            ++keys->len;

            if (keys->len >= keys->real_size) {
                operation_elementaire();

                keys->real_size *= 2;
                t_film* tmp = realloc(keys->arr, ((size_t) keys->real_size) * sizeof(t_film));

                if (tmp == NULL) {
                    fprintf(stderr, "Error with realloc\n");
                    free(keys->arr);
                    exit(EXIT_FAILURE);
                }
                else
                    keys->arr = tmp;
            }
        }
    }

    printf("arr T fill[nb_films=%d] :\t", keys->len);
    stop_chrono_and_print_time(keys->len);

    printf("arr O fill[nb_films=%d] :\t", keys->len);
    afficher_op_elem();

    printf("arr M fill[nb_films=%d] :\t", keys->len);
    show_memory();

    fclose(fd);
    return keys;
}

void free_arr(arr* a) {
    free((*a)->arr);
    free(*a);
    *a = NULL;
}


//---------Main
int main(int argc, char* argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage : %s filename NB_SEARCH structure\n", argv[0]);

        fprintf(stderr, "\nfilename  : the file name (.tsv file) containing films ;");
        fprintf(stderr, "\nNB_SEARCH : the number of search to perform ;");
        fprintf(stderr, "\nstructure : the name of the structure to test : 'htbl', 'bst', or 'avl'.\n");

        fprintf(stderr, "\nOutput format :\n");
        fprintf(stderr, "\t<struct> T <operation_name>[<param>=<val>] :\t <time> (<readable time>) Average (<readable average>)\n");
        fprintf(stderr, "\t<struct> O <operation_name>[<param>=<val>] :\t <operation number>\n");
        fprintf(stderr, "\t<struct> M <operation_name>[<param>=<val>] :\t <memory usage> (<readable usage>)\n");
        fprintf(stderr, "\t<struct> I <var>=<value>\n");
        exit(EXIT_FAILURE);
    }

    init_random();

    char* filename = argv[1];
    int nb_search = atoi(argv[2]);
    char* data_s = argv[3];

    if (strcmp(data_s, "htbl") == 0) { // Hash table
        if (argc < 5) {
            fprintf(stderr, "Usage : %s filename NB_SEARCH htbl N\n", argv[0]);
            fprintf(stderr, "\nfilename  : the file name (.tsv file) containing films ;");
            fprintf(stderr, "\nNB_SEARCH : the number of search to perform ;");
            fprintf(stderr, "\nstructure : the name of the structure to test : 'htbl', 'bst', or 'avl'. Here it is 'htbl' ;");
            fprintf(stderr, "\nN         : the size of the hash table.\n");
            exit(EXIT_FAILURE);

        }

        int size = atoi(argv[4]);

        test_htbl(filename, size, nb_search);
    }
    else if (strcmp(data_s, "bst") == 0) { // Binary search tree
        test_bst(filename, nb_search);
    }
    else if (strcmp(data_s, "avl") == 0) { // AVL
        test_avl(filename, nb_search);
    }
    else {
        fprintf(stderr, "error: structure should be 'htbl', 'bst', or 'avl', but '%s' found !\n", data_s);
    }

    return EXIT_SUCCESS;
}
