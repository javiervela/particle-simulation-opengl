/**
 * @file constants.h
 * @author Javier Vela
 * @brief Constants file for colors
 * @date 2021-10-12
 */

#ifndef CONTANTS__H
#define CONTANTS__H

/// 12 color palette
typedef enum ColorIndex
{
	kWHITE = 0,
	kBLACK,
	kRED,
	kGREEN,
	kBLUE,
	kYELLOW,
	kPURPLE,
	kORANGE,
	kPINK,
	kBROWN,
	kGREY,
	kTRANSPARENT,
	//
	kNB_COLORS // Number of colors
} ColorIndex;

/// Color values array
static float COLOR[kNB_COLORS][4] = {
	{1.f, 1.f, 1.f, 1.f}, //	white
	{0.f, 0.f, 0.f, 1.f}, //	black
	{1.f, 0.f, 0.f, 1.f}, //	red
	{0.f, 1.f, 0.f, 1.f}, //	green
	{0.f, 0.f, 1.f, 1.f}, //	blue
	{1.f, 1.f, 0.f, 1.f}, //	yellow
	{0.5, 0.f, 1.f, 1.f}, //	purple
	{1.f, 0.5, 0.f, 1.f}, //	orange
	{1.f, 0.6, 1.f, 1.f}, //	pink
	{0.5, 0.2, 0.f, 1.f}, //	brown
	{0.5, 0.5, 0.5, 1.f}, //	grey
	{1.f, 1.f, 1.f, 0.f}  //	transparent
};

typedef enum ParticleColorLevel
{
	pPrincipal = 0,
	pMedium,
	pFast,
	pNUMBERLEVELS
} ParticleColorLevel;

static ColorIndex PARTICLE_PALETTE[pNUMBERLEVELS] = {
	kWHITE,	 // PRINCIPAL
	kORANGE, // MEDIUM
	kRED	 // FAST
};

#endif