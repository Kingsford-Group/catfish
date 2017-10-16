/*
Part of Catfish
(c) 2017 by  Mingfu Shao, Carl Kingsford, and Carnegie Mellon University.
See LICENSE for licensing.
*/

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
string version = "v0.2.1";
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
		else if(string(argv[i]) == "-v")
		{
			printf("%s\n", version.c_str());
			exit(0);
		}
		else if(string(argv[i]) == "-h")
		{
			print_copyright();
			print_help();
			exit(0);
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

int print_command_line(int argc, const char ** argv)
{
	printf("command line: ");
	for(int i = 0; i < argc; i++)
	{
		printf("%s ", argv[i]);
	}
	printf("\n");
	return 0;
}


int print_help()
{
	printf("\n");
	printf("Usage: catfish -i <input.sgr|input.gtf> -o <output-file> [-a core|full|greedy] [-h] [-v]\n");
	printf("\n");
	printf(" %-28s  %s\n", "-i <input.sgr|input.gtf>",  "input file specifying graph, supporting two formats:");
	printf(" %-28s  %s\n", "",  ".sgr specifies a directed acyclic graph. The first line gives n,");
	printf(" %-28s  %s\n", "",  "indicating the number of vertices in the graph. The vertices are");
	printf(" %-28s  %s\n", "",  "named from 0 to (n - 1), where vertex 0 has to be the source vertex");
	printf(" %-28s  %s\n", "",  "and vertex (n - 1) has to be the sink vertex. Each of the following");
	printf(" %-28s  %s\n", "",  "line specifies an edge, which consists of three integers: in-vertex,");
	printf(" %-28s  %s\n", "",  "out-vertex and the weight of this edge.");
	printf(" %-28s  %s\n", "",  ".gtf is the standard GTF (General Transfer Format). For this format");
	printf(" %-28s  %s\n", "",  "Catfish will merge all transcripts for each gene into splice graph,");
	printf(" %-28s  %s\n", "",  "and then try to decompose it.");
	printf(" %-28s  %s\n", "-o <output-file>",  "output-file with decomposed paths and their weights");
	printf(" %-28s  %s\n", "-a <core|full|greedy>",  "With option of core, the program will only run the core algorithm to");
	printf(" %-28s  %s\n", "",  "(partially) decompose the given splice graph, which will predict fewer");
	printf(" %-28s  %s\n", "",  "paths but with higher accuracy. With option of full, the program will");
	printf(" %-28s  %s\n", "",  "completely decompose the given splice graph, using greedy algorithm ");
	printf(" %-28s  %s\n", "",  "following the core part of the algorithm. With option of greedy, the");
	printf(" %-28s  %s\n", "",  "program will use greedy algorithm to fully decompose the given graph. ");
	printf(" %-28s  %s\n", "",  "This parameter is optional, and its default value is full.");
	printf(" %-28s  %s\n", "-h",  "print usage of Catfish and exit");
	printf(" %-28s  %s\n", "-v",  "print current version of Catfish and exit");

	return 0;
}

int print_copyright()
{
	printf("Catfish %s (c) 2017 Mingfu Shao, Carl Kingsford, and Carnegie Mellon University\n", version.c_str());
	return 0;
}
