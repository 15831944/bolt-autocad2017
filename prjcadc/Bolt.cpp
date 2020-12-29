#include "stdafx.h"
#include "Bolt.h"


CBolt::CBolt()
{
}

CBolt::CBolt(double d, double l, CString m, double t, int n, double s, double p, double al, double bw, CString bm, CString tl, CString tm)
{
	diameter = d;
	length = l;
	material = m;
	tailing = t;
	number = n;
	space = s;
	pitch = p;
	aLength = al;
	beamWidth = bw;
	beamMaterial = bm;
	trayLength = tl;
	trayMaterial = tm;
}



CBolt::~CBolt()
{
}
