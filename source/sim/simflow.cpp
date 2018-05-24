

#include "simflow.h"
#include "simvars.h"
#include "../app/appmain.h"
#include "../sys/utils.h"
#include "../sys/syswin.h"
#include "../math/3dmath.h"

dbool g_play = dtrue;

void upsim()
{
	int i;
	int j;
	v3f a;
	float d;
	float e;
	float g;

	for (i = 0; i < PARTS; ++i)
	{
		for (j = 0; j < PARTS; ++j)
		{
			if (j == i)
				continue;
			memset(&a, 0, sizeof(v3f));
			v3fsub(&a, partp[i], partp[j]);
			d = mag3f(a);
			e = partq[i] * partq[j];
			g = - partm[i] * partm[j];
			e /= partm[i];
			g /= partm[i];
			v3fmul(&a, a, e / 1.0f);// +
				//g / 10000.0f);
			v3fadd(&partv[i], partv[i], a);
		}
	}

	for (i = 0; i < PARTS; ++i)
		v3fadd(&partp[i], partp[i], partv[i]);
}