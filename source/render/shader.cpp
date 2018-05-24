



#include "shader.h"
#include "../sys/inc.h"
#include "../sys/syswin.h"
#include "../sys/debug.h"
#include "../sys/utils.h"

glshader g_shader[SHADERS];
signed char g_cursh = 0;

shdef SHDEF[SHADERS] =
{
	/* SH_ORTHO */
	{
"SH_ORTHO v",
"SH_ORTHO f",
"														\r\n"
"#version 120											\r\n"\
"														\r\n"\
"														\r\n"\
"uniform float width;									\r\n"\
"uniform float height;									\r\n"\
"														\r\n"\
"void main(void)										\r\n"\
"{														\r\n"\
"	gl_Position = vec4(gl_Vertex.x * 2.0 / width - 1.0,	\r\n"\
"		gl_Vertex.y * -2.0 / height + 1.0,				\r\n"\
"		0.5,											\r\n"\
"		1.0);											\r\n"\
"														\r\n"\
"	gl_TexCoord[0] = gl_MultiTexCoord0;					\r\n"\
"}														\r\n"\
"														\r\n",

"														\r\n"\
"#version 120											\r\n"\
"														\r\n"\
"uniform vec4 color;									\r\n"\
"														\r\n"\
"uniform sampler2D texture0;							\r\n"\
"														\r\n"\
"void main(void)										\r\n"\
"{														\r\n"\
"	gl_FragColor = color * texture2D(texture0, gl_TexCoord[0].xy);\r\n"\
"}														\r\n"\
"														\r\n",
dtrue,
dfalse
	},

	/* SH_COLOR2D */
	{
"SH_COLOR2D v",
"SH_COLOR2D f",
"														\r\n"\
"#version 120											\r\n"\
"														\r\n"\
"														\r\n"\
"uniform float width;									\r\n"\
"uniform float height;									\r\n"\
"														\r\n"\
"														\r\n"\
"void main(void)										\r\n"\
"{														\r\n"\
"	gl_Position = vec4(gl_Vertex.x * 2.0 / width - 1.0,	\r\n"\
"		gl_Vertex.y * -2.0 / height + 1.0,				\r\n"\
"		0.5,											\r\n"\
"		1.0);											\r\n"\
"														\r\n"\
"}														\r\n"\
"														\r\n",
"														\r\n"\
"#version 120											\r\n"\
"														\r\n"\
"uniform vec4 color;									\r\n"\
"														\r\n"\
"														\r\n"\
"void main(void)										\r\n"\
"{														\r\n"\
"	gl_FragColor = color;								\r\n"\
"}														\r\n"\
"														\r\n",
dfalse,
dfalse
	},
	{
"SH_COLOR3D v",
"SH_COLOR3D f",
#include "../shaders/color3d.vert"
,
#include "../shaders/color3d.frag"
,
dfalse,
dfalse
	},
	{
"SH_B v",
"SH_B f",
#include "../shaders/b.vert"
,
#include "../shaders/b.frag"
,
dfalse,
dfalse
	},
	{
		"SH_GRID v",
"SH_GRID f",
#include "../shaders/grid.vert"
,
#include "../shaders/grid.frag"
,
dfalse,
dfalse
	},
	{
		"SH_E v",
			"SH_E f",
			"#version 120\r\n"
			"varying vec3 outpos;\r\n"
	"uniform vec3 corner[4];\r\n"
			"uniform vec3 campos;\r\n"
"uniform vec3 camview;\r\n"
"uniform vec3 camright;\r\n"
"uniform vec3 camup;\r\n"
"uniform float width;\r\n"
"uniform float height;\r\n"
"uniform float fov;\r\n"
""
"void main(void)\r\n"
"{\r\n"
"vec3 rv = corner[1] - corner[0];\r\n"
"vec3 uv = corner[1] - corner[2];\r\n"
"rv = normalize(rv);\r\n"
"uv = normalize(uv);\r\n"
"vec3 vv = cross(uv, rv);\r\n"
"vv = normalize(vv);\r\n"
"vec3 c = (corner[0] + corner[2]) / 2.0;\r\n"
"rv.z = 0;\r\n"
"uv.z = 0;\r\n"
"vec3 vp = gl_Vertex.xyz - c;\r\n"
"vp.z = 0;\r\n"
"float rc = dot(rv, (vp));\r\n"
"float uc = dot(uv, (vp));\r\n"
"float ta = tan(fov / 180.0 * 3.14159 / 2.0f);\r\n"
"vec3 v = camright * rc * width/height * ta + camup * uc * ta;\r\n"
"	outpos = v;\r\n"
"	gl_Position = gl_Vertex; gl_Position.w = 1;\r\n"
"}",
"#version 120											\r\n"\
"#extension GL_EXT_gpu_shader4 : enable\r\n"
"uniform float gplm[10];\r\n"
"uniform float gplr[10];\r\n"
"uniform vec3 gplp[10];\r\n"
"uniform vec3 gpla[10*3];\r\n"
"uniform int gplon[10];\r\n"
"uniform sampler2D gpltd;\r\n"
"uniform sampler2D gplth;\r\n"
"uniform float pathlen;\r\n"
"uniform float pathnstep;\r\n"
"uniform float pathspeed;\r\n"
"uniform vec3 camvel;\r\n"
"uniform int hasth;\r\n"
"uniform int gpli;\r\n"
"varying vec3 outpos;\r\n"
"uniform vec3 corner[4];\r\n"
"uniform vec3 campos;\r\n"
"uniform vec3 camview;\r\n"
"uniform vec3 camright;\r\n"
"uniform vec3 camup;\r\n"
"uniform float mind;\r\n"
"uniform float maxd;\r\n"
"uniform float width;\r\n"
"uniform float height;\r\n"
"vec3 refract(vec3 from, vec3 dp)\r\n"
"{\r\n"
"int i = 0;"
"vec3 to = from + dp;"
"while(true)\r\n"
"{\r\n"
"if((i > 10) || !bool(gplon[i]))\r\n"
"{break;}\r\n"
"vec3 d = gplp[i] - from;\r\n"
"float dd = length(d);\r\n"
"to = to - d * gplm[i]/ (pathnstep*dd*dd*dd);\r\n"
"i++;\r\n"
"}\r\n"
"return to;\r\n"
"}\r\n"
"vec4 trylook(vec3 from, vec3 to)\r\n"
"{\r\n"
"vec3 fv = gplp[gpli] - from;\r\n"
"vec3 tv = gplp[gpli] - to;\r\n"
"vec3 mv = (fv+tv)/2.0;\r\n"
"float fd = length(fv);\r\n"
"float td = length(tv);\r\n"
"vec4 color = vec4(0,0,0,0);"
"if(td <= fd && td <= gplr[gpli])\r\n"
"//if(to.z >= gplp[gpli].z && from.z <= gplp[gpli].z && td <= gplr[gpli])\r\n"
"{\r\n"
"vec2 tc;\r\n"
"vec3 tp;\r\n"
"tp.x = dot(mv, gpla[gpli*3+0]);\r\n"
"tp.y = dot(mv, gpla[gpli*3+1]);\r\n"
"tp.z = dot(mv, gpla[gpli*3+2]);\r\n"
"tc.x = atan(tp.x / gplr[gpli], tp.z / gplr[gpli]) / (2.0 * 3.14159);\r\n"
"//tc.x = (1.0 + tp.x / gplr[gpli]) / 2.0;\r\n"
"tc.y = (1.0 + tp.y / gplr[gpli]) / 2.0;\r\n"
"color = texture2D(gpltd, tc);\r\n"
"}\r\n"
"return color;\r\n"
"}\r\n"
"void main (void)\r\n"
"{\r\n"
"vec3 v = (outpos + camview);\r\n"
"float i;\r\n"
"float pathstep = pathlen/pathnstep;\r\n"
"vec3 dp = v * pathstep;\r\n"
"vec3 to = dp + campos;\r\n"
"vec4 color = vec4(0,0,0,0);\r\n"
"vec4 cs = vec4(0,0,0,0);\r\n"
"float fd = 1;\r\n"
"float step = - (1.0 - ((i+1)/pathnstep) * ((i+1)/pathnstep)) * maxd + (1.0 - ((i+1-1)/pathnstep) * ((i+1-1)/pathnstep)) * maxd;\r\n"
//"for(i=0; i<pathlen; i+=pathstep)\r\n"
"for(i=0; i<pathlen; i+=step)\r\n"
"{\r\n"
"vec3 from = to;\r\n"
"to = refract(to, dp);\r\n"
"dp = to - from;\r\n"
"cs = trylook(from,to);\r\n"
"fd = fd * color.w + (step-mind)/(maxd-mind)*cs.w*(1.0 - color.w) + 1*(1.0 - cs.w)*(1.0 - color.w);\r\n"
"color = color + (1.0 - color.w) * cs;\r\n"
"step = - (1.0 - ((i+1)/pathnstep) * ((i+1)/pathnstep)) * maxd + (1.0 - ((i+1-1)/pathnstep) * ((i+1-1)/pathnstep)) * maxd;\r\n"
"}\r\n"
"gl_FragColor = color;\r\n"
"gl_FragDepth = fd;\r\n"
	"}"
		,
		dfalse,
		dfalse
	},
	{
		"SH_VP0 v",
		"SH_VP0 f",
#include "../shaders/vp0.vert"
		,
#include "../shaders/vp0.frag"
		,
		dfalse,
		dfalse
	},
	{
		"SH_VP1 v",
		"SH_VP1 f",
#include "../shaders/vp1.vert"
		,
#include "../shaders/vp1.frag"
		,
		dfalse,
		dfalse
	},
	{
		"SH_VP2 v",
		"SH_VP2 f",
#include "../shaders/vp2.vert"
		,
#include "../shaders/vp2.frag"
		,
		dfalse,
		dfalse
	},
	{
		"SH_VP3 v",
		"SH_VP3 f",
#include "../shaders/vp3.vert"
		,
#include "../shaders/vp3.frag"
		,
		dfalse,
		dfalse
	}
};

void shinit(glshader* s)
{
	s->program = 0;
	s->vertshader = 0;
	s->fragshader = 0;
}

void shfree(glshader* s)
{
	if(s->vertshader)
	{
		glDetachShader(s->program, s->vertshader);
		glDeleteShader(s->vertshader);
		s->vertshader = 0;
	}

	if(s->fragshader)
	{
		glDetachShader(s->program, s->fragshader);
		glDeleteShader(s->fragshader);
		s->fragshader = 0;
	}

	if(s->program)
	{
		glDeleteProgram(s->program);
		s->program = 0;
	}
}

GLint shgu(glshader* s, const char* strvar)
{
	if(!s->program)
		return -1;
	return glGetUniformLocation(s->program, strvar);
}

GLint shga(glshader* s, const char* strvar)
{
	if(!s->program)
		return -1;
	return glGetAttribLocation(s->program, strvar);
}

void shmu(glshader* s, int slot, const char* variable)
{
	s->slot[slot] = shgu(s, variable);
}

void shma(glshader* s, int slot, const char* variable)
{
	s->slot[slot] = shga(s, variable);
}

void glver(int* major, int* minor)
{
	/* for all versions */
	char* ver;

	char vermaj[6];
	char vermin[6];

	int i;
	int j;

	ver = (char*)glGetString(GL_VERSION); /* ver = "3.2.0" */

	for(i=0; i<6; i++)
	{
		if(ver[i] != '.')
			vermaj[i] = ver[i];
		else
		{
			vermaj[i] = '\0';
			i++;
			break;
		}
	}

	for(j=0; j<6; j++, i++)
	{
		if(ver[i] != '.')
			vermin[j] = ver[i];
		else
		{
			vermin[j] = '\0';
			i++;
			break;
		}
	}

	sscanf(vermaj, "%d", major);
	sscanf(vermin, "%d", minor);

	ver = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
}

void inglsl()
{
	int major, minor;
	GLenum glewError;
	char* glexts;
	char i;

#ifndef PLAT_MAC
	glewExperimental = GL_TRUE;
	glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		errm("Error initializing GLEW!", (const char*)glewGetErrorString(glewError));
		return;
	}
#endif

#ifdef __glew_h__
	if (!GLEW_VERSION_1_4)
	{
		errm("Error", "OpenGL 1.4 not supported!\n");
		goto quit;
	}
#endif

#ifndef PLAT_MOBILE
	/* glGetString deprecated after 3.0 */
	glexts = (char*)glGetString(GL_EXTENSIONS);

	fprintf(g_applog, glexts);

#if !defined( PLAT_MAC ) && !defined( PLAT_IOS )
#ifdef GLDEBUG
	if (!strstr(glexts, "GL_ARB_debug_output"))
	{
		fprintf(g_applog, "GL_ARB_debug_output extension not supported\r\n");
	}
	else
	{
		glDebugMessageCallback(&glmess, 0);

		CHECKGL();
	}
#endif
#endif

	if (!strstr(glexts, "GL_ARB_shader_objects"))
	{
		errm("Error", "GL_ARB_shader_objects extension not supported!");
		goto quit;
	}

	if (!strstr(glexts, "GL_ARB_shading_language_100"))
	{
		errm("Error", "GL_ARB_shading_language_100 extension not supported!");
		goto quit;
	}
#endif

	glver(&major, &minor);

#ifndef PLAT_MOBILE
	if (major < 1 || (major == 1 && minor < 4))
	{
		errm("Error", "OpenGL 1.4 is not supported!");
		goto quit;
	}
#endif

	for(i=0; i<SHADERS; ++i)
		loadsh(i, SHDEF[i].vn, SHDEF[i].fn,
			SHDEF[i].vs, SHDEF[i].fs,
			SHDEF[i].ht, SHDEF[i].hn);

	return;

quit:
	g_quit = dtrue;
}


void loadsh(int shader,
	const char* namev,
	const char* namef,
	const char* strv,
	const char* strf,
	dbool hastexc,
	dbool hasnorm)
{
	glshader* s;
	GLint loglen;
	GLchar* log;
	GLint status;

	s = g_shader + shader;

	if (s->vertshader || s->fragshader || s->program)
		shfree(s);

	s->hastexc = hastexc;
	s->hasnorm = hasnorm;
	s->vertshader = glCreateShader(GL_VERTEX_SHADER);
	s->fragshader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(s->vertshader, 1, &strv, NULL);
	glShaderSource(s->fragshader, 1, &strf, NULL);

	glCompileShader(s->vertshader);

	glGetShaderiv(s->vertshader, GL_INFO_LOG_LENGTH, &loglen);
	if (loglen > 0)
	{
		log = (GLchar*)malloc(loglen);

		if (NOMEM(log))
			return;

		glGetShaderInfoLog(s->vertshader, loglen, &loglen, log);
		fprintf(g_applog, "shader %s compile log: %s\r\n", namev, log);
		fflush(g_applog);
		free(log);
	}

	glCompileShader(s->fragshader);
	glGetShaderiv(s->fragshader, GL_INFO_LOG_LENGTH, &loglen);
	if (loglen > 0)
	{
		log = (GLchar*)malloc(loglen);

		if (NOMEM(log))
			return;

		glGetShaderInfoLog(s->fragshader, loglen, &loglen, log);
		fprintf(g_applog, "shader %s compile log: %s\r\n", namef, log);
		fflush(g_applog);
		free(log);
	}

	s->program = glCreateProgram();
	glAttachShader(s->program, s->vertshader);
	glAttachShader(s->program, s->fragshader);
	glLinkProgram(s->program);

	fprintf(g_applog, "Program %s / %s :", namev, namef);
	fflush(g_applog);

	glGetProgramiv(s->program, GL_INFO_LOG_LENGTH, &loglen);
	if (loglen > 0)
	{
		log = (GLchar*)malloc(loglen);
		glGetProgramInfoLog(s->program, loglen, &loglen, log);
		fprintf(g_applog, "Program link log: %s\r\n", log);
		fflush(g_applog);
		free(log);
	}

	glGetProgramiv(s->program, GL_LINK_STATUS, &status);
	if (status == 0)
	{
		fprintf(g_applog, "link status 0\r\n");
		fflush(g_applog);
	}
	else
	{
		fprintf(g_applog, "link status ok, program=%d\r\n", s->program);
		fflush(g_applog);
	}

	fprintf(g_applog, "\r\n");
	fflush(g_applog);

	shma(s, SSLOT_POSITION, "position");
	shma(s, SSLOT_NORMAL, "normalin");
	shma(s, SSLOT_TEXCOORD0, "texcoordin0");
	shmu(s, SSLOT_TEXTURE0, "texture0");
	shmu(s, SSLOT_COLOR, "color");
	shmu(s, SSLOT_WIDTH, "width");
	shmu(s, SSLOT_HEIGHT, "height");
	shmu(s, SSLOT_UP, "up");
	shmu(s, SSLOT_RIGHT, "right");
	shmu(s, SSLOT_VIEW, "view");
	shmu(s, SSLOT_POS, "pos");
	shmu(s, SSLOT_FOV, "fov");
	shmu(s, SSLOT_NEARD, "neard");
	shmu(s, SSLOT_FARD, "fard");
	shmu(s, SSLOT_GPLON, "gplon");
	shmu(s, SSLOT_GPLP, "gplp");
	shmu(s, SSLOT_GPLR, "gplr");
	shmu(s, SSLOT_GPLM, "gplm");
	shmu(s, SSLOT_GPLS, "gpls");
	shmu(s, SSLOT_GPLTD, "gpltd");
	shmu(s, SSLOT_GPLTH, "gplth");
	shmu(s, SSLOT_GPLA, "gpla");
	shmu(s, SSLOT_GPLAS, "gplas");
	shmu(s, SSLOT_GPLHTH, "gplhth");
	shmu(s, SSLOT_GPLI, "gpli");
	shmu(s, SSLOT_PATHLEN, "pathlen");
	shmu(s, SSLOT_PATHNSTEP, "pathnstep");
	shmu(s, SSLOT_PATHSPEED, "pathspeed");
	shmu(s, SSLOT_CAMVEL, "camvel");
	shmu(s, SSLOT_CORNER, "corner");
	shmu(s, SSLOT_CAMPOS, "campos");
	shmu(s, SSLOT_CAMVIEW, "camview");
	shmu(s, SSLOT_CAMRIGHT, "camright");
	shmu(s, SSLOT_CAMUP, "camup");
	shmu(s, SSLOT_MIND, "mind");
	shmu(s, SSLOT_MAXD, "maxd");
	shmu(s, SSLOT_GPLT, "gplt");
	shmu(s, SSLOT_PARTQ, "partq");
	shmu(s, SSLOT_PARTM, "partm");
	shmu(s, SSLOT_PARTP, "partp");
}

void usesh(int shader)
{
	glshader* s;

	CHECKGL();
	g_cursh = shader;

	s = g_shader+g_cursh;

	glUseProgram(s->program);
	CHECKGL();

#ifdef PLAT_GL14
	/* opengl 1.4 way */
	glEnableClientState(GL_VERTEX_ARRAY);
	if(s->hastexc)	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	if(s->hasnorm)	glEnableClientState(GL_NORMAL_ARRAY);
#endif
}

void endsh()
{
	glshader* s;
	CHECKGL();

	if(g_cursh < 0)
		return;

	s = g_shader+g_cursh;

#ifdef PLAT_GL14
	//opengl 1.4 way
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
#endif

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glUseProgram(0);

	g_cursh = -1;
}
