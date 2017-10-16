/*
Part of Catfish
(c) 2017 by  Mingfu Shao, Carl Kingsford, and Carnegie Mellon University.
See LICENSE for licensing.
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iostream>
#include <ctime>
#include <cassert>
#include <sstream>

#include "config.h"
#include "catfish.h"
#include "gtf.h"
#include "genome.h"
#include "nested_graph.h"
#include "sgraph_compare.h"

using namespace std;

int assemble(const string &file);
int transform(const string &file);

int main(int argc, const char **argv)
{
	if(argc == 1)
	{
		print_copyright();
		print_help();
		return 0;
	}

	srand(time(0));
	parse_arguments(argc, argv);
	//print_parameters();

	if(input_file == "" && output_file != "" && algo == "simulate")
	{
		splice_graph sg;
		sg.simulate(simulation_num_vertices, simulation_num_edges, simulation_max_edge_weight);
		sg.write(output_file);
		return 0;
	}

	if(input_file != "" && output_file != "" && algo == "transform")
	{
		string s = input_file.substr(input_file.size() - 3, 3);
		if(s != "gtf") return 0;
		transform(input_file);
		return 0;
	}

	if(input_file != "")
	{
		assemble(input_file);
	}
	return 0;
}

int assemble(const string &file)
{
	ifstream fin(file);
	if(fin.fail()) return 0;

	ofstream fout;
	if(output_file != "") fout.open(output_file);

	char buf[10240];
	string header;
	stringstream sstr;
	while(fin.getline(buf, 10240, '\n'))
	{
		string s(buf);
		if(s.size() == 0) continue;
		if(s[0] == '#')
		{
			if(header != "")
			{
				splice_graph sg;
				sg.build(sstr);

				catfish sc("catfish", sg);
				sc.assemble();
				if(output_file != "") fout << header.c_str() << " paths = " << sc.paths.size() << endl;
				if(output_file != "") sc.write(fout);
			}

			sstr.clear();
			header = s;
		}
		else
		{
			sstr << s << "\n";
		}
	}

	if(header != "")
	{
		splice_graph sg;
		sg.build(sstr);

		catfish sc("catfish", sg);
		sc.assemble();
		if(output_file != "") fout << header.c_str() << " paths = " << sc.paths.size() << endl;
		if(output_file != "") sc.write(fout);
	}

	fin.close();
	if(output_file != "") fout.close();

	return 0;
}

int transform(const string &file)
{
	genome g(file);

	ofstream fout1(output_file + ".graph");
	ofstream fout2(output_file + ".truth");

	for(int i = 0; i < g.genes.size(); i++)
	{
		gtf gg(g.genes[i]);

		string name = gg.get_gene_id();

		fout1 << "# graph number = " << i << " name = " << name.c_str() << endl;
		fout2 << "# graph number = " << i << " name = " << name.c_str() << endl;

		splice_graph gr;
		gg.build_splice_graph(gr);

		gr.write(fout1);
		gg.write_transcript_paths(fout2);
	}

	fout1.close();
	fout2.close();
	return 0;
}
