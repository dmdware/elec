


#include "appmain.h"
#include "../sys/utils.h"
#include "../math/v3f.h"
#include "../math/3dmath.h"
#include "../sys/syswin.h"
#include "../sys/texture.h"
#include "../sim/simdef.h"
#include "../gui/font.h"
#include "../sim/simflow.h"
#include "../sim/simvars.h"
#include "../render/shader.h"
#include "../render/toxy.h"

char g_appmode = APPMODE_LOGO;
char g_viewmode = VIEWMODE_FIRST;
char g_restage = 0;


#ifdef PLAT_WIN
HINSTANCE g_hinst = NULL;
#endif

void loadsysres()
{
	g_appmode = APPMODE_PLAY;
}

void upload()
{

	switch(g_restage)
	{
	case 0:
/*		if(!loadqmod()) */ g_restage++;
		break;
	case 1:
		if(!loadqtex())
		{

	//		lfree(&g_modload);
			vfree(&g_texload);

//			g_lastLMd = -1;
			g_lastloadtex = -1;

			g_appmode = APPMODE_PLAY;
		}
		break;
	}
}

void upreload()
{
	g_restage = 0;
	g_lastloadtex = -1;
	freetexs();
	breakwin(APPTIT);
	makewin(APPTIT);

	/* Important - VBO only possible after window GL context made. */
	g_appmode = APPMODE_LOADING;

	loadsysres();
	queuesimres();

	/*
	TODO
	Overhaul ui system
	Make scrollable everywhere
	Croppable pipeline 
	*/
}

void update()
{
//	if(g_sock)
//		UpdNet();

	switch(g_appmode)
	{
	case APPMODE_LOGO:
		break;
//	case APPMODE_INTRO:
//		upintro();
//		break;
	case APPMODE_LOADING:
		upload();
		break;
	case APPMODE_RELOADING:
		upreload();
		break;
	case APPMODE_PLAY:
		upsim();
		break;
	case APPMODE_EDITOR:
//		uped();
		break;
	case APPMODE_MASPF:
		upsim();
		break;
	}
}

void drawscene()
{
#if 0
	//return;
	float dd[12];
	v3f *v;
	mesh q;

	makeq2(&q);

	glEnable(GL_TEXTURE_2D);
	drawpl();
	glDisable(GL_TEXTURE_2D);

	pfrust((float)g_currw/(float)g_currh, 1, g_camf.view, g_camf.pos, g_camf.up, g_camf.strafe, MAXD, MIND, FOV, dd, gpv, gpl, gpld, gsa);

	clipwalk(&v);

	glDisable(GL_CULL_FACE);

	drawwalk(v, g_walk.ns, g_walk.sh[0].nw);
	drawmesh(&q);


	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);

	drawwalk(v, g_walk.ns, g_walk.sh[0].nw);
	drawmesh(&q);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	glEnable(GL_CULL_FACE);

	free(q.v);
	free(v);
#endif


}

void drawscenedepth()
{
}

void makefbo(unsigned int* rendertex, unsigned int* renderrb, unsigned int* renderfb, unsigned int* renderdepthtex, int w, int h)
{
	/* OpenGL 1.4 way */
	GLenum DrawBuffers[2];

	glGenTextures(1, rendertex);
	glBindTexture(GL_TEXTURE_2D, *rendertex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glGenTextures(1, renderdepthtex);
	glBindTexture(GL_TEXTURE_2D, *renderdepthtex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, w, h, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glGenFramebuffers(1, renderfb);
	glBindFramebuffer(GL_FRAMEBUFFER, *renderfb);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *renderdepthtex, 0);

	DrawBuffers[0] = GL_COLOR_ATTACHMENT0;
	DrawBuffers[1] = GL_DEPTH_ATTACHMENT;
	glDrawBuffers(1, DrawBuffers);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		errm("Error", "Couldn't create framebuffer for render.");
		return;
	}
}

void delfbo(unsigned int* rendertex, unsigned int* renderrb, unsigned int* renderfb, unsigned int* renderdepthtex)
{
	/* delete resources */
	glDeleteTextures(1, rendertex);
	glDeleteTextures(1, renderdepthtex);
	/* Bind 0, which means render to back buffer, as a result, fb is unbound */
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, renderfb);
	CHECKGL();
}

void draw()
{
	glshader *s;
	v3f t[4] = 
	{ {0,0,0.1f},
	{1,0,0.1f},
	{1,1,0.1f},
	{0,1,0.1f} };
	float white[4] = { 1,1,1,1 };
	float frame[4] = { 0,0,(float)g_width,(float)g_height };

	glViewport(0, 0, g_width, g_height);
	glClearColor(0, 0, 0, 0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	/* TODO leave as float for now then use fixmath int's */


	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	//drawim(g_tex[0].texname,
	//	0,0,100,100, 
	//	0,0,1,1,
	//	frame);
#if 0
	proj = pproj(45.0f,
		(float)g_width / (float)g_height,
		1.0f, MAXD);

	view = lookat(0, 0, 0,
		-1000, 1000, -1000,
		0, 1, 0);

	mfreset(&model);

	drawscene(proj.matrix,
		view.matrix,
		model.matrix,
		mvinv.matrix,
		lpos, ldir);
#endif

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	usesh(SH_B);
	s = g_shader + g_cursh;
	glUniform1f(s->slot[SSLOT_WIDTH], g_width);
	glUniform1f(s->slot[SSLOT_HEIGHT], g_height);
	glUniform3fv(s->slot[SSLOT_PARTP], PARTS, (float*)partp);
	glUniform1fv(s->slot[SSLOT_PARTQ], PARTS, (float*)partq);
	glUniform1fv(s->slot[SSLOT_PARTM], PARTS, (float*)partm);
	glVertexPointer(3, GL_FLOAT, 0, t);
	glEnable(GL_TRIANGLE_FAN);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	//if(g_appmode == APPMODE_PLAY)
		//drawscene();
	glDisable(GL_DEPTH_TEST);



	glEnable(GL_DEPTH_TEST);
}

void loadcfg()
{
	lnode *rit; /* v2i */
	v2i *rp;
	int w, h;
	char cfgfull[DMD_MAX_PATH+1];
	char line[128];
	char key[128];
	char act[128];
	FILE *fp;
	float valuef;
	int valuei;
	dbool valueb;
	//int i;

	enumdisp();

	if(g_ress.size)
	{
		rit = g_ress.head;
		rp = (v2i*)rit->data;
		g_selres = *rp;
	}
	else
	{
		SDL_GL_GetDrawableSize(g_win, &w, &h);

		g_selres.x = w;
		g_selres.y = h;
	}

	for(rit=g_ress.head; rit; rit=rit->next)
	{
		/* below acceptable height? */
		if(g_selres.y < 480)
		{
			rp = (v2i*)rit->data;

			if(rp->y > g_selres.y &&
				rp->x > rp->y)
			{
				g_selres = *(v2i*)rit->data;
			}
		}
		/* already of acceptable height? */
		else
		{
			rp = (v2i*)rit->data;
			//get smallest acceptable resolution
			if(rp->x < g_selres.y &&
				rp->x > rp->y)
			{
				g_selres = *(v2i*)rit->data;
			}

			break;
		}
	}

	//SwitchLang(LANG_ENG);

	fullwrite(CFGFILE, cfgfull);

	fp = fopen(cfgfull, "r");

	if(!fp)
		return;

	while(!feof(fp))
	{
		fgets(line, 127, fp);

		if(strlen(line) > 127)
			continue;

		act[0] = 0;
		key[0] = 0;

		if(sscanf(line, "%s %s", key, act) < 2)
			continue;

		sscanf(act, "%f", &valuef);
		valuei = (int)valuef;
		valueb = (dbool)valuef;

		if(strcmp(key, "fullscreen") == 0)					g_fs = valueb;
		else if(strcmp(key, "client_width") == 0)			g_width = g_selres.x = valuei;
		else if(strcmp(key, "client_height") == 0)			g_height = g_selres.y = valuei;
		else if(strcmp(key, "screen_bpp") == 0)				g_bpp = valuei;
//		else if(strcmp(key, "volume") == 0)					SetVol(valuei);
//		else if(strcmp(key, "language") == 0)				SwitchLang(GetLang(act));
	}

	fclose(fp);
}

void writecfg()
{
	char cfgfull[DMD_MAX_PATH+1];
	FILE* fp = fopen(cfgfull, "w");
	fullwrite(CFGFILE, cfgfull);
	if(!fp)
		return;
	fprintf(fp, "fullscreen %d \r\n\r\n", g_fs ? 1 : 0);
	fprintf(fp, "client_width %d \r\n\r\n", g_selres.x);
	fprintf(fp, "client_height %d \r\n\r\n", g_selres.y);
	fprintf(fp, "screen_bpp %d \r\n\r\n", g_bpp);
	//fprintf(fp, "volume %d \r\n\r\n", g_volume);
	//fprintf(fp, "language %s\r\n\r\n", g_lang);
	fclose(fp);
}

/* Define the function to be called when ctrl-c (SIGINT) signal is sent to process */
void sigcall(int signum)
{
	exit(0);
}

void appinit()
{
	char msg[128];
	//SDL_version compile_version;
	//SDL_version *link_version;
	//int flags;
	//int initted;
	char full[DMD_MAX_PATH + 1];

	fullpath("log.txt", full);
	g_applog = fopen(full, "wb");

#ifdef PLAT_LINUX
	signal(SIGINT, sigcall);
#endif

	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		sprintf(msg, "SDL_Init: %s\n", SDL_GetError());
		errm("Error", msg);
	}

#if 0
	if (SDLNet_Init() == -1)
	{
		sprintf(msg, "SDLNet_Init: %s\n", SDLNet_GetError());
		errm("Error", msg);
	}
#endif

#if 0
	link_version = (SDL_version*)Mix_Linked_Version();
	SDL_MIXER_VERSION(&compile_version);
	printf("compiled with SDL_mixer version: %d.%d.%d\n",
		compile_version.major,
		compile_version.minor,
		compile_version.patch);
	printf("running with SDL_mixer version: %d.%d.%d\n",
		link_version->major,
		link_version->minor,
		link_version->patch);

	// load support for the OGG and MOD sample/music formats
	flags = MIX_INIT_OGG | MIX_INIT_MP3;
	initted = Mix_Init(flags);
	if ((initted & flags) != flags)
	{
		sprintf(msg, "Mix_Init: Failed to init required ogg and mod support!\nMix_Init: %s", Mix_GetError());
		/* errm("Error", msg); */
	}

	if (SDL_Init(SDL_INIT_AUDIO) == -1) {
		sprintf(msg, "SDL_Init: %s\n", SDL_GetError());
		errm("Error", msg);
	}
	/* show 44.1KHz, signed 16bit, system byte order,
	stereo audio, using 1024 byte chunks */
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		errm("Error", msg);
	}

	Mix_AllocateChannels(SCHANS);
#endif

	if (!g_applog)
		openlog("log.txt", APPVER);

	srand((unsigned int)getticks());

	vinit(&g_texload, sizeof(textoload));

	/* TODO c-style inits, not constructors */
	loadcfg();
	//	MapKeys();

}

void appdeinit()
{
//	lnode *cit;

//	endsess();
//	FreeMap();

	breakwin(APPTIT);

	SDL_Quit();
}

int evproc(void *userdata, SDL_Event *e)
{
	switch(e->type)
	{
		case SDL_QUIT:
			g_quit = dtrue;
			break;
	}

	return 0;
}

void evloop()
{
	SDL_Event e;

	CHECKGL();
	while (!g_quit)
	{
		CHECKGL();
		while (SDL_PollEvent(&e))
		{
			evproc(NULL, &e);
		}
		CHECKGL();

		if(g_quit)
			break;

		if ( !g_bg &&
			( (g_appmode == APPMODE_LOADING || g_appmode == APPMODE_RELOADING) || drawnext() ) )
		{
			CHECKGL();

			calcdrawrate();

			CHECKGL();
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

			draw();
			CHECKGL();
			SDL_GL_SwapWindow(g_win);
			CHECKGL();

			CHECKGL();
		}

		if((g_appmode == APPMODE_LOADING || g_appmode == APPMODE_RELOADING) || upnext() )
		{
			calcuprate();
			update();
		}

		CHECKGL();
	}
}

#ifdef BUILD_STEAM
//-----------------------------------------------------------------------------
// Purpose: callback hook for debug text emitted from the Steam API
//-----------------------------------------------------------------------------
extern "C" void __cdecl SteamAPIDebugTextHook( int nSeverity, const char *pchDebugText )
{
	// if you're running in the debugger, only warnings (nSeverity >= 1) will be sent
	// if you add -debug_steamapi to the command-line, a lot of extra informational messages will also be sent
#ifdef PLAT_WIN
	::OutputDebugString( pchDebugText );
#endif

	if(!g_applog)
		openlog("log.txt", APPVER);

	fprintf(g_applog, pchDebugText);


	if ( nSeverity >= 1 )
	{
		// place to set a breakpoint for catching API errors
		int x = 3;
		x = x;
	}
}
#endif

void appmain()
{
	//*((int*)0) = 0;

#ifdef BUILD_STEAM

	if ( SteamAPI_RestartAppIfNecessary( k_uAppIdInvalid ) )
	{
		// if Steam is not running or the game wasn't started through Steam, SteamAPI_RestartAppIfNecessary starts the 
		// local Steam client and also launches this game again.

		// Once you get a public Steam AppID assigned for this game, you need to replace k_uAppIdInvalid with it and
		// removed steaappid.txt from the game depot.

		return;
	}

	// appinit Steam CEG
	if ( !Steamworks_InitCEGLibrary() )
	{
#ifdef PLAT_WIN
		OutputDebugString( "Steamworks_InitCEGLibrary() failed\n" );
#endif
		errm( "Fatal Error", "Steam must be running to play this game (InitDrmLibrary() failed).\n" );
		return;
	}

	// Initialize SteamAPI, if this fails we bail out since we depend on Steam for lots of stuff.
	// You don't necessarily have to though if you write your code to check whether all the Steam
	// interfaces are NULL before using them and provide alternate paths when they are unavailable.
	//
	// This will also load the in-game steam overlay dll into your process.  That dll is normally
	// injected by steam when it launches games, but by calling this you cause it to always load,
	// even when not launched via steam.
	if ( !SteamAPI_Init() )
	{
#ifdef PLAT_WIN
		OutputDebugString( "SteamAPI_Init() failed\n" );
#endif
		errm( "Fatal Error", "Steam must be running to play this game (SteamAPI_Init() failed).\n" );
		return;
	}

	// set our debug handler
	SteamClient()->SetWarningMessageHook( &SteamAPIDebugTextHook );

#endif

	appinit();

	makewin(APPTIT);

	//SDL_ShowCursor(dfalse);
	loadsysres();
	queuesimres();

	evloop();

	appdeinit();
	//SDL_ShowCursor(dtrue);
}

dbool runops(const char* cmdline)
{
	if(strcmp(cmdline, "") == 0)
	{
//		strcpy(g_startmap, "");

		return dfalse;
	}
	else
	{
		/*
		TODO c90
		std::string cmdlinestr(cmdline);
		std::string find("+devmap ");
		int found = cmdlinestr.rfind(find);

		if(found != std::string::npos)
		{
			strcpy(g_startmap, "");

			startmap = cmdlinestr.psubstr(found+find.length(), cmdlinestr.length()-found-find.length());

			fprintf(g_applog, "%s\r\n", cmdline);
			fprintf(g_applog, "%s\r\n", startmap);

			//LoadMap(startmap.c_str());
			g_startmap = startmap;
		}
		*/
	}

	return dfalse;
}


#ifdef BUILD_STEAM
//-----------------------------------------------------------------------------
// Purpose: Wrapper around SteamAPI_WriteMiniDump which can be used directly 
// as a se translator
//-----------------------------------------------------------------------------
#ifdef _WIN32
void MiniDumpFunction(unsigned int nExceptionCode, EXCEPTION_POINTERS *pException)
{
	// You can build and set an arbitrary comment to embed in the minidump here,
	// maybe you want to put what level the user was playing, how many players on the server,
	// how much memory is free, etc...
	SteamAPI_SetMiniDumpComment("Minidump comment: SteamworksExample.exe\n");

	// The 0 here is a build ID, we don't set it
	SteamAPI_WriteMiniDump(nExceptionCode, pException, 0);
}
#endif
#endif

#ifdef PLAT_WIN
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char* argv[])
#endif
{
  //  SDL_SetMainReady();

#ifdef PLAT_WIN
	g_hinst = hInstance;
#endif

#ifdef PLAT_WIN
	//runops(lpCmdLine);
#else
	char cmdline[DMD_MAX_PATH+124];
	cmdline[0] = 0;
	for(int ai=0; ai<argc; ai++)
	{
		strcat(cmdline, argv[ai]);

		if(ai+1<argc)
			strcat(cmdline, " ");
	}
	runops(cmdline);
#endif

#ifdef PLAT_WIN
	if ( IsDebuggerPresent() )
	{
		// We don't want to mask exceptions (or report them to Steam!) when debugging.
		// If you would like to step through the exception handler, attach a debugger
		// after running the game outside of the debugger.	

		appmain();
		return 0;
	}
#endif

#ifdef PLAT_WIN
#ifdef BUILD_STEAM
	_set_se_translator( MiniDumpFunction );

	try  // this try block allows the SE translator to work
	{
#endif
#endif
		appmain();
#ifdef PLAT_WIN
#ifdef BUILD_STEAM
	}
	catch( ... )
	{
		return -1;
	}
#endif
#endif

	return 0;
}
