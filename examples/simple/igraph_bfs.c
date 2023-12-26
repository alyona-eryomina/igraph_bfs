/* -*- mode: C -*-  */
/*
   IGraph library.
   Copyright (C) 2009-2021  The igraph development team

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc.,  51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301 USA

*/

#include <igraph.h>

int main(void) {

    igraph_t graph, ring;
    igraph_vector_int_t order, rank, father_td, pred, succ, dist;
    igraph_vector_int_t father_bu, dist_bu, father_td_common, dist_td_common, father_bu_common, dist_bu_common;
    igraph_vector_int_t father_comb, dist_comb;
    igraph_vector_int_t father_comb_common, dist_comb_common;

    /* Create a disjoint union of two rings */
    igraph_ring(&ring, 10, /*directed=*/ 0, /*mutual=*/ 0, /*circular=*/ 1);
    igraph_disjoint_union(&graph, &ring, &ring);
    igraph_destroy(&ring);

    /* Initialize the vectors where the result will be stored. Any of these
     * can be omitted and replaced with a null pointer when calling
     * igraph_bfs() */
    igraph_vector_int_init(&order, 0);
    igraph_vector_int_init(&rank, 0);
    igraph_vector_int_init(&father_td, 0);
    igraph_vector_int_init(&father_bu, 0);
    igraph_vector_int_init(&father_td_common, 0);
    igraph_vector_int_init(&father_bu_common, 0);
    igraph_vector_int_init(&father_comb, 0);
    igraph_vector_int_init(&father_comb_common, 0);
    igraph_vector_int_init(&pred, 0);
    igraph_vector_int_init(&succ, 0);
    igraph_vector_int_init(&dist, 0);
    igraph_vector_int_init(&dist_bu, 0);
    igraph_vector_int_init(&dist_td_common, 0);
    igraph_vector_int_init(&dist_bu_common, 0);
    igraph_vector_int_init(&dist_comb, 0);
    igraph_vector_int_init(&dist_comb_common, 0);

    /* Now call the BFS function */
    igraph_bfs(&graph, /*root=*/0, /*roots=*/ NULL, /*neimode=*/ IGRAPH_OUT,
               /*unreachable=*/ 1, /*restricted=*/ NULL,
               &order, &rank, &father_td, &pred, &succ, &dist,
               /*callback=*/ NULL, /*extra=*/ NULL);
    
    igraph_bfs_bottom_up(&graph, /*root=*/0, /*roots=*/ NULL, /*neimode=*/ IGRAPH_OUT,
               /*unreachable=*/ 1, /*restricted=*/ NULL, &father_bu, &dist_bu);

    igraph_bfs_td_common_memory(&graph, /*root=*/0, /*roots=*/ NULL, /*neimode=*/ IGRAPH_OUT,
               /*unreachable=*/ 1, /*restricted=*/ NULL, &father_td_common, &dist_td_common);
    
    igraph_bfs_bu_common_memory(&graph, /*root=*/0, /*roots=*/ NULL, /*neimode=*/ IGRAPH_OUT,
               /*unreachable=*/ 1, /*restricted=*/ NULL, &father_bu_common, &dist_bu_common);
    
    igraph_bfs_combine(&graph, /*root=*/0, /*roots=*/ NULL, /*neimode=*/ IGRAPH_OUT,
               /*unreachable=*/ 1, /*restricted=*/ NULL, &father_comb, &dist_comb);
    
    igraph_bfs_combine_common(&graph, /*root=*/0, /*roots=*/ NULL, /*neimode=*/ IGRAPH_OUT,
               /*unreachable=*/ 1, /*restricted=*/ NULL, &father_comb_common, &dist_comb_common);
    
    if (igraph_vector_int_all_e(&father_td, &father_bu)) {
        printf("bottom-up vector is correct\n");
    } else {
        printf("bottom-up vector is incorrect!\n");
    }

    if (igraph_vector_int_all_e(&father_td, &father_td_common)) {
        printf("top-down-common-memory vector is correct\n");
    } else {
        printf("top-down-common-memory vector is incorrect!\n");
    }

    if (igraph_vector_int_all_e(&father_td, &father_bu_common)) {
        printf("bottom-up-common-memory vector is correct\n");
    } else {
        printf("bottom-up-common-memory vector is incorrect!\n");
    }

    if (igraph_vector_int_all_e(&father_td, &father_comb)) {
        printf("combine vector is correct\n");
    } else {
        printf("combine vector is incorrect!\n");
    }

    if (igraph_vector_int_all_e(&father_td, &father_comb_common)) {
        printf("combine vector is correct\n");
    } else {
        printf("combine vector is incorrect!\n");
    }

    /* Print the results */
    igraph_vector_int_print(&order);
    igraph_vector_int_print(&rank);
    igraph_vector_int_print(&father_td);
    igraph_vector_int_print(&father_bu);
    igraph_vector_int_print(&father_td_common);
    igraph_vector_int_print(&father_bu_common);
    igraph_vector_int_print(&father_comb);
    igraph_vector_int_print(&father_comb_common);
    igraph_vector_int_print(&pred);
    igraph_vector_int_print(&succ);
    igraph_vector_int_print(&dist);
    igraph_vector_int_print(&dist_bu);
    igraph_vector_int_print(&dist_td_common);
    igraph_vector_int_print(&dist_bu_common);
    igraph_vector_int_print(&dist_comb);
    igraph_vector_int_print(&dist_comb_common);

    /* Cleam up after ourselves */
    igraph_vector_int_destroy(&order);
    igraph_vector_int_destroy(&rank);
    igraph_vector_int_destroy(&father_td);
    igraph_vector_int_destroy(&father_bu);
    igraph_vector_int_destroy(&father_td_common);
    igraph_vector_int_destroy(&father_bu_common);
    igraph_vector_int_destroy(&father_comb);
    igraph_vector_int_destroy(&father_comb_common);
    igraph_vector_int_destroy(&pred);
    igraph_vector_int_destroy(&succ);
    igraph_vector_int_destroy(&dist);
    igraph_vector_int_destroy(&dist_bu);
    igraph_vector_int_destroy(&dist_td_common);
    igraph_vector_int_destroy(&dist_bu_common);
    igraph_vector_int_destroy(&dist_comb);
    igraph_vector_int_destroy(&dist_comb_common);

    igraph_destroy(&graph);

    return 0;
}
