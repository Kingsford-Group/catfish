/*
Part of Catfish
(c) 2017 by  Mingfu Shao, Carl Kingsford, and Carnegie Mellon University.
See LICENSE for licensing.
*/

#include "edge_info.h"

edge_info::edge_info()
{
	length = 0;
	type = 0;
}

edge_info::edge_info(int l)
	: length(l)
{
	type = 0;
}

edge_info::edge_info(const edge_info &ei)
{
	length = ei.length;
	type = ei.type;
}
