/*
Part of Catfish
(c) 2017 by  Mingfu Shao, Carl Kingsford, and Carnegie Mellon University.
See LICENSE for licensing.
*/

#ifndef __GTF_H__
#define __GTF_H__

#include <fstream>

#include "path.h"
#include "gene.h"
#include "interval_map.h"
#include "splice_graph.h"

using namespace std;

class gtf : public gene
{
public:
	gtf(const gene &g);

public:
	split_interval_map imap;
	vector<path> tpaths;

public:
	int build_splice_graph(splice_graph &gr);
	int write_transcript_paths(ofstream &fout);
	int output_gtf(ofstream &fout, const vector<path> &paths, const string &prefix) const;	
	int output_gtf(ofstream &fout) const;	

private:
	int build_split_interval_map();
	int build_transcript_paths();
	double compute_sum_expression();
	int add_vertices(splice_graph &gr);
	int add_edges(splice_graph &gr);
	int add_single_edge(int s, int t, double w, splice_graph &gr);
};

#endif
