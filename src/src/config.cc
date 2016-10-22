#include "config.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

//// parameters
// for algorithm
int max_equations_each_iteration = 50;
int max_dp_table_size = 10000;
int max_num_subsetsum_solutions = 10;

// for simulation
int simulation_num_vertices = 10;
int simulation_num_edges = 10;
int simulation_max_edge_weight = 100;

//// from command line
string algo = "full";
string input_file;
string output_file;
string ref_file;
string fixed_gene_name;

bool fast_mode = true;
bool output_tex_files = false;
int min_gtf_transcripts_num = 0;

int print_parameters()
{
	// for algorithm
	printf("max_dp_table_size = %d\n", max_dp_table_size);
	printf("max_num_subsetsum_solutions = %d\n", max_num_subsetsum_solutions);
	printf("max_equations_each_iteration = %d\n", max_equations_each_iteration);

	// for simulation
	printf("simulation_num_vertices = %d\n", simulation_num_vertices);
	printf("simulation_num_edges = %d\n", simulation_num_edges);
	printf("simulation_max_edge_weight = %d\n", simulation_max_edge_weight);

	// for command
	printf("algo = %s\n", algo.c_str());
	printf("input_file = %s\n", input_file.c_str());
	printf("output_file = %s\n", output_file.c_str());
	printf("ref_file = %s\n", ref_file.c_str());
	printf("fixed_gene_name = %s\n", fixed_gene_name.c_str());
	printf("output_tex_files = %c\n", output_tex_files ? 'T' : 'F');
	printf("min_gtf_transcripts_num = %d\n", min_gtf_transcripts_num);
	printf("fast_mode = %c\n", fast_mode ? 'T' : 'F');
	printf("\n");

	return 0;
}

int parse_arguments(int argc, const char ** argv)
{
	for(int i = 1; i < argc; i++)
	{
		if(string(argv[i]) == "-a")
		{
			algo = string(argv[i + 1]);
			i++;
		}
		else if(string(argv[i]) == "-i")
		{
			input_file = string(argv[i + 1]);
			i++;
		}
		else if(string(argv[i]) == "-o")
		{
			output_file = string(argv[i + 1]);
			i++;
		}
		else if(string(argv[i]) == "-r")
		{
			ref_file = string(argv[i + 1]);
			i++;
		}
		else if(string(argv[i]) == "-g")
		{
			fixed_gene_name = string(argv[i + 1]);
			i++;
		}
		else if(string(argv[i]) == "-t")
		{
			output_tex_files = true;
		}
		else if(string(argv[i]) == "-n")
		{
			min_gtf_transcripts_num = atoi(argv[i + 1]);
			i++;
		}
	}
	return 0;
}

