#include "stdafx.h"
#include "Cable.h"


CCable::CCable()
{
}

CCable::CCable(double d, double l, CString m, double t, int n, double s, double p, double al, double tl, CString tm, double sd, double sl, CString sm)
{
	diameter = d;
	length = l;
	material = m;
	tailing = t;
	number = n;
	space = s;
	pitch = p;
	aLength = al;
	trayLength = tl;
	trayMaterial = tm;
	shuLength = sl;
	shuDiameter = sd;
	shuMaterial = sm;
}


CCable::~CCable()
{
}
