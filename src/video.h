#ifndef _VIDEO_H
#define _VIDEO_H

#include <vector>
#include <string>

#ifdef WIN32
	#undef main
	#include <SDL.h>
	#undef main
#else
	#include <SDL.h>
#endif

#include "memory.h"

#define VF_FULLSCREEN		1
#define	VF_DOUBLE		2
#define VF_BLOCKFULLSCREEN	4

#define	VID_NORMAL	0
#define	VID_ALCO	1

struct VSize {
	uint32_t h;
	uint32_t v;
};

struct VidLayout {
	std::string name;
	VSize full,sync,bord;
	uint32_t intsz,intpos;
};

struct Video {
	int flags;
	bool intStrobe;
	uint8_t* scrptr;
	uint8_t* scrimg;
	VSize full,bord,curr,synh;
	VSize lcut,rcut,vsze,wsze;
	int frmsz;
	uint32_t t, intsz, intpos;
	struct {
		uint8_t *ac00,*ac01,*ac02,*ac03;	// alco parts (screen 0)
		uint8_t *ac10,*ac11,*ac12,*ac13;	// alco parts (screen 1)
	} ladrz[0x1800];
	uint8_t* scr5pix[0x1800];
	uint8_t* scr5atr[0x1800];
	uint8_t* scr7pix[0x1800];
	uint8_t* scr7atr[0x1800];
	int32_t mode;
	float zoom,brdsize, pxcnt;
	bool flash,curscr;
	uint8_t brdcol,nextBorder;
	uint8_t fcnt,atrbyte;
	std::string curlay;		// current layout name
//	void sync(int,float);
//	bool setLayout(std::string);
//	void update();
	int dotCount;
	uint16_t matrix[512 * 512];
//	void fillMatrix();
};

Video* vidCreate(Memory*);
void vidDestroy(Video*);

void vidSync(Video*,int,float);
bool vidSetLayout(Video*,std::string);
void vidUpdate(Video*);

void addLayout(std::string,int*);
void addLayout(VidLayout);
std::vector<VidLayout> getLayoutList();

#endif
