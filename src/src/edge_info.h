#ifndef __EDGE_INFO__
#define __EDGE_INFO__

class edge_info
{
public:
	edge_info();
	edge_info(int l);
	edge_info(const edge_info &ei);

public:
	int length;
	int type;
};

#endif
