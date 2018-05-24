

#ifndef SHADER_H
#define SHADER_H

#include "../sys/inc.h"
#include "../algo/bool.h"

#define SSLOT_TEXTURE0			0
#define SSLOT_POSITION			1
#define SSLOT_NORMAL			2
#define SSLOT_COLOR				3
#define SSLOT_WIDTH				4
#define SSLOT_HEIGHT			5
#define SSLOT_TEXCOORD0			6
#define SSLOT_UP				7
#define SSLOT_RIGHT				8
#define SSLOT_VIEW				9
#define SSLOT_POS				10
#define SSLOT_FOV				11
#define SSLOT_NEARD				12
#define SSLOT_FARD				13
#define SSLOT_GPLON			14
#define SSLOT_GPLP				15
#define SSLOT_GPLR				16
#define SSLOT_GPLM				17
#define SSLOT_GPLS				18
#define SSLOT_GPLTD			19
#define SSLOT_GPLTH			20
#define SSLOT_GPLA				21
#define SSLOT_GPLAR			22
#define SSLOT_GPLAS			23
#define SSLOT_GPLHTH			24
#define SSLOT_GPLI				25
#define SSLOT_PATHLEN			26
#define SSLOT_PATHNSTEP			27
#define SSLOT_PATHSPEED			28
#define SSLOT_CAMVEL			29
#define SSLOT_CORNER			30
#define SSLOT_CAMPOS			31
#define SSLOT_CAMVIEW			32
#define SSLOT_CAMRIGHT			33
#define SSLOT_CAMUP				34
#define SSLOT_MIND				35
#define SSLOT_MAXD				36
#define SSLOT_GPLT				37
#define SSLOT_PARTQ				38
#define SSLOT_PARTM				39
#define SSLOT_PARTP				40
#define SSLOTS					41

struct glshader
{
	dbool hastexc;
	dbool hasnorm;
	GLint slot[SSLOTS];

	// http://lists.apple.com/archives/mac-opengl/2005/Nov/msg00182.html
#if defined( PLAT_MAC ) || defined( PLAT_IOS )
	GLuint vertshader;
	GLuint fragshader;
	GLuint program;
#else
	GLhandleARB vertshader;
	GLhandleARB fragshader;
	GLhandleARB program;
#endif
};

typedef struct glshader glshader;

#define SH_ORTHO				0
#define SH_COLOR2D				1
#define SH_COLOR3D				2
#define SH_B					3
#define SH_GRID					4
#define SH_E					5
#define SH_VP0					6
#define SH_VP1					7
#define SH_VP2					8
#define SH_VP3					9
#define SHADERS					10

struct shdef
{
	const char *vn;
	const char *fn;
	const char *vs;
	const char *fs;
	dbool ht;
	dbool hn;
};

typedef struct shdef shdef;

extern shdef SHDEF[SHADERS];

extern glshader g_shader[SHADERS];
extern signed char g_cursh;

void shinit(glshader* s);
void shfree(glshader* s);

GLint shgu(glshader *s, const char* strvar);
GLint shga(glshader *s, const char* strvar);

void shmu(glshader *s, int slot, const char* variable);
void shma(glshader *s, int slot, const char* variable);

void usesh(int shader);
void endsh();
void inglsl();
void loadsh(int shader, 
			const char* namev,
			const char* namef,
			const char* strv, 
			const char* strf, 
			dbool hastexc, 
			dbool hasnorm);

#endif


