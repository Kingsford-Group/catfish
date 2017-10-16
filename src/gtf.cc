/*
Part of Catfish
(c) 2017 by  Mingfu Shao, Carl Kingsford, and Carnegie Mellon University.
See LICENSE for licensing.
*/

#include <algorithm>
#include "gtf.h"
#include "util.h"

gtf::gtf(const gene &g)
	:gene(g)
{
}

int gtf::build_splice_graph(splice_graph &gr)
{
	build_split_interval_map();
	build_transcript_paths();
	add_vertices(gr);
	add_edges(gr);
	return 0;
}

int gtf::build_split_interval_map()
{
	imap.clear();
	for(int i = 0; i < transcripts.size(); i++)
	{
		transcript &t = transcripts[i];
		for(int j = 0; j < t.exons.size(); j++)
		{
			PI32 p = t.exons[j];
			imap += make_pair(ROI(p.first, p.second), (int32_t)(t.coverage));
		}
	}
	return 0;
}

int gtf::add_vertices(splice_graph &gr)
{
	PI32 pi = get_bounds();
	double sum = compute_sum_expression();
	gr.add_vertex();
	vertex_info vi0;
	vi0.lpos = pi.first;
	vi0.rpos = pi.first;
	gr.set_vertex_weight(0, sum);
	gr.set_vertex_info(0, vi0);

	SIMI it;
	for(it = imap.begin(); it != imap.end(); it++)
	{
		gr.add_vertex();
		vertex_info vi;
		vi.length = upper(it->first) - lower(it->first);
		vi.lpos = lower(it->first);
		vi.rpos = upper(it->first);
		gr.set_vertex_weight(gr.num_vertices() - 1, it->second);
		gr.set_vertex_info(gr.num_vertices() - 1, vi);
	}

	gr.add_vertex();
	vertex_info vin;
	vin.lpos = pi.second;
	vin.rpos = pi.second;
	gr.set_vertex_weight(gr.num_vertices() - 1, sum);
	gr.set_vertex_info(gr.num_vertices() - 1, vin);
	return 0;
}

int gtf::build_transcript_paths()
{
	tpaths.clear();
	int n = distance((SIMI)(imap.begin()), (SIMI)(imap.end())) + 2;
	for(int i = 0; i < transcripts.size(); i++)
	{
		path p;
		transcript &tt = transcripts[i];
		assert(tt.exons.size() >= 1);
		p.abd = tt.coverage;
		p.v.push_back(0);
		for(int k = 0; k < tt.exons.size(); k++)
		{
			PI32 &ge = tt.exons[k];
			SIMI it = imap.find(ge.first);
			assert(it != imap.end());		// make sure all input transcripts with >= 1 expression
			while(true)
			{
				int uu = distance((SIMI)(imap.begin()), it) + 1;
				p.v.push_back(uu);
				if(upper(it->first) >= ge.second) break;
				it++;
			}
		}
		p.v.push_back(n - 1);
		tpaths.push_back(p);
	}
	return 0;
}

int gtf::add_edges(splice_graph &gr)
{
	for(int i = 0; i < tpaths.size(); i++)
	{
		int32_t expr = tpaths[i].abd;
		vector<int> &v = tpaths[i].v;
		assert(v[0] == 0);
		assert(v[v.size() - 1] == gr.num_vertices() - 1);
		for(int k = 0; k < v.size() - 1; k++)
		{
			add_single_edge(v[k], v[k + 1], expr, gr);
		}
	}
	return 0;
}

int gtf::add_single_edge(int s, int t, double w, splice_graph &gr)
{
	PEB p = gr.edge(s, t);
	if(p.second == true)
	{
		double w0 = gr.get_edge_weight(p.first);	
		gr.set_edge_weight(p.first, w + w0);
	}
	else
	{
		edge_descriptor p = gr.add_edge(s, t);
		gr.set_edge_weight(p, w);
		gr.set_edge_info(p, edge_info());
	}
	return 0;
}

double gtf::compute_sum_expression()
{
	double s = 0;
	for(int i = 0; i < transcripts.size(); i++)
	{
		s += transcripts[i].coverage;
	}
	return s;
}

int gtf::output_gtf(ofstream &fout, const vector<path> &paths, const string &prefix) const
{
	fout.precision(2);
	fout<<fixed;

	if(transcripts.size() == 0) return 0;

	string chrm = transcripts[0].seqname;
	string gene = transcripts[0].gene_id;

	for(int i = 0; i < paths.size(); i++)
	{
		const vector<int> &v = paths[i].v;
		double abd = paths[i].abd;
		if(v.size() < 2) continue;

		SIMI si = imap.begin();
		SIMI ti = imap.end();
		ti--;

		fout<<chrm.c_str()<<"\t";					// chromosome name
		fout<<prefix.c_str()<<"\t";					// source
		fout<<"transcript\t";						// feature
		fout<<lower(si->first) + 1<<"\t";			// left position
		fout<<upper(ti->first)<<"\t";				// right position
		fout<<1000<<"\t";							// score
		fout<<"+\t";								// strand
		fout<<".\t";								// frame
		fout<<"gene_id \""<<gene.c_str()<<"\"; ";
		fout<<"transcript_id \""<<gene.c_str()<<"."<<i + 1<<"\"; ";
		fout<<"expression \""<<abd<<"\";"<<endl;

		assert(v[0] == 0);
		join_interval_map jmap;
		for(int k = 1; k < v.size() - 1; k++)
		{
			SIMI it = imap.begin();
			advance(it, v[k] - 1);
			jmap += make_pair(ROI(lower(it->first), upper(it->first)), 1);
		}

		int cnt = 0;
		for(JIMI it = jmap.begin(); it != jmap.end(); it++)
		{
			fout<<chrm.c_str()<<"\t";			// chromosome name
			fout<<prefix.c_str()<<"\t";			// source
			fout<<"exon\t";						// feature
			fout<<lower(it->first) + 1<<"\t";	// left position
			fout<<upper(it->first)<<"\t";		// right position
			fout<<1000<<"\t";					// score
			fout<<"+\t";						// strand
			fout<<".\t";						// frame
			fout<<"gene_id \""<<gene.c_str()<<"\"; ";
			fout<<"transcript_id \""<<gene.c_str()<<"."<<i + 1<<"\"; ";
			fout<<"exon \""<<++cnt<<"\"; ";
			fout<<"expression \""<<abd<<"\";"<<endl;
		}
	}
	return 0;
}

int gtf::output_gtf(ofstream &fout) const
{
	write(fout);
	return 0;
}

int gtf::write_transcript_paths(ofstream &fout) 
{
	//fout << tpaths.size() << endl;
	for(int i = 0; i < tpaths.size(); i++)
	{
		int32_t abd = tpaths[i].abd;
		vector<int> &v = tpaths[i].v;
		fout<< abd << " ";
		for(int k = 0; k < v.size(); k++) fout<< v[k] << " ";
		fout<<endl;
	}
	return 0;
}
