bin_PROGRAMS=catfish

GTFDIR = ../../lib/gtf/src
UTILDIR = ../../lib/util/src
GRAPHDIR = ../../lib/graph/src

catfish_CPPFLAGS = -std=c++11 -I$(HTSLIB) -I$(GUROBI_HOME)/include -I$(BOOST_HOME) -I$(GTFDIR) -I$(GRAPHDIR) -I$(UTILDIR)
catfish_LDFLAGS = -L$(HTSLIB) -L$(GUROBI_HOME)/lib -L$(GTFDIR) -L$(GRAPHDIR) -L$(UTILDIR) -pthread
catfish_LDADD = -lhts -lz -lgurobi_c++ -lgurobi -lgtf -lgraph -lutil

catfish_SOURCES = splice_graph.h splice_graph.cc \
				  sgraph_compare.h sgraph_compare.cc \
				  vertex_info.h vertex_info.cc \
				  edge_info.h edge_info.cc \
				  nested_graph.h nested_graph.cc \
				  interval_map.h interval_map.cc \
				  subsetsum.h subsetsum.cc \
				  config.h config.cc \
				  path.h path.cc \
				  equation.h equation.cc \
				  gtf.h gtf.cc \
				  catfish.h catfish.cc \
				  assembler.h assembler.cc \
				  main.cc
