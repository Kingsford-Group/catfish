/*
Part of Catfish
(c) 2017 by  Mingfu Shao, Carl Kingsford, and Carnegie Mellon University.
See LICENSE for licensing.
*/

#include "vertex_info.h"

vertex_info::vertex_info()
{
	pos = 0;
	lpos = 0;
	rpos = 0;
	length = 0;
}

vertex_info::vertex_info(int l)
	: length(l)
{
	lpos = 0;
	rpos = 0;
	pos = 0;
}

vertex_info::vertex_info(const vertex_info &vi)
{
	length = vi.length;
	lpos = vi.lpos;
	rpos = vi.rpos;
	pos = vi.pos;
}
