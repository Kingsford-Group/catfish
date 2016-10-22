#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "util.h"
#include <stdint.h>
#include <map>
#include <sstream>

using namespace std;

// constants
#define TRIVIAL 0
#define NORMAL 1

// user-defined parameters
extern int max_dp_table_size;
extern int max_num_subsetsum_solutions;
extern int max_equations_each_iteration;

extern int simulation_num_vertices;
extern int simulation_num_edges;
extern int simulation_max_edge_weight;

extern string algo;
extern string input_file;
extern string output_file;
extern string ref_file;
extern string fixed_gene_name;

extern bool fast_mode;
extern bool output_tex_files;
extern int min_gtf_transcripts_num;

// parse arguments
bool parse_arguments(int argc, const char ** argv);
int print_parameters();

// load parameters
int load_config(const char * conf_file);

#endif
