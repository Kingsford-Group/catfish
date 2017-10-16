bin_PROGRAMS=catfish

GTFDIR = ../lib/gtf
UTILDIR = ../lib/util
GRAPHDIR = ../lib/graph

catfish_CPPFLAGS = -std=c++11 -I$(GTFDIR) -I$(GRAPHDIR) -I$(UTILDIR)
catfish_LDFLAGS = -L$(GTFDIR) -L$(GRAPHDIR) -L$(UTILDIR) -pthread
catfish_LDADD = -lgtf -lgraph -lutil

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
				  main.cc
