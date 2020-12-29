#pragma once
#include "ArcTunnel.h"
#include "SimpleIni.h"
class CDrawArcProject
{
public:
	CDrawArcProject();
	~CDrawArcProject();
	static void DrawArcTunnel();
private:
	CArcTunnel * arcTunnel = new CArcTunnel();
};

