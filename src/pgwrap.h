/*
 * @file pgwrap.h
 * Header file for pgwrap
 * 
 * @author Jayanth Chennamangalam
 * @date 2012.02.28
 */

#ifndef __PGWRAP_H__
#define __PGWRAP_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cpgplot.h>

#define PGWRAP_VP_ML            0.10    /* normalised left margin */
#define PGWRAP_VP_MR            0.90    /* normalised right margin */
#define PGWRAP_VP_MR_S          0.85    /* normalised right margin when showing
                                           scale */
#define PGWRAP_VP_MB            0.10    /* normalised bottom margin */
#define PGWRAP_VP_MT            0.90    /* normalised top margin */
#define PGWRAP_VP_MT_S          0.85    /* normalised top margin when showing
                                           scale */
#define PGWRAP_VP_MW            0.10    /* normalised margin width */

#define PGWRAP_VP_MC            0.30    /* collapsed margin */

#define PGWRAP_LEN_GENSTRING    256

#define PGWRAP_CMAP_LEVELS      64
#define PGWRAP_NUM_CMAPS        24

typedef enum PGWRAP_CMap_e
{
    PGWRAP_CMAP_AUTUMN = 0,
    PGWRAP_CMAP_BLUE,
    PGWRAP_CMAP_BONE,
    PGWRAP_CMAP_COLORCUBE,
    PGWRAP_CMAP_COOL,
    PGWRAP_CMAP_COPPER,
    PGWRAP_CMAP_FLAG,
    PGWRAP_CMAP_GRAY,
    PGWRAP_CMAP_GRAY_INV,
    PGWRAP_CMAP_HOT,
    PGWRAP_CMAP_HOT_INV,
    PGWRAP_CMAP_HSV,
    PGWRAP_CMAP_JET,
    PGWRAP_CMAP_LINES,
    PGWRAP_CMAP_PINK,
    PGWRAP_CMAP_PRISM,
    PGWRAP_CMAP_SPRING,
    PGWRAP_CMAP_SUMMER,
    PGWRAP_CMAP_WHITE,
    PGWRAP_CMAP_WINTER,
    PGWRAP_CMAP_RDBU,
    PGWRAP_CMAP_BURD,
    PGWRAP_CMAP_CUBEHELIX,
    PGWRAP_CMAP_CUBEHELIX_INV,
} PGWRAP_CMap_t;

#define PGWRAP_CMAP_STR_AUTUMN          "autumn"
#define PGWRAP_CMAP_STR_BLUE            "blue"
#define PGWRAP_CMAP_STR_BONE            "bone"
#define PGWRAP_CMAP_STR_COLORCUBE       "colorcube"
#define PGWRAP_CMAP_STR_COOL            "cool"
#define PGWRAP_CMAP_STR_COPPER          "copper"
#define PGWRAP_CMAP_STR_FLAG            "flag"
#define PGWRAP_CMAP_STR_GRAY            "gray"
#define PGWRAP_CMAP_STR_GRAY_INV        "gray-inv"
#define PGWRAP_CMAP_STR_HOT             "hot"
#define PGWRAP_CMAP_STR_HOT_INV         "hot-inv"
#define PGWRAP_CMAP_STR_HSV             "hsv"
#define PGWRAP_CMAP_STR_JET             "jet"
#define PGWRAP_CMAP_STR_LINES           "lines"
#define PGWRAP_CMAP_STR_PINK            "pink"
#define PGWRAP_CMAP_STR_PRISM           "prism"
#define PGWRAP_CMAP_STR_SPRING          "spring"
#define PGWRAP_CMAP_STR_SUMMER          "summer"
#define PGWRAP_CMAP_STR_WHITE           "white"
#define PGWRAP_CMAP_STR_WINTER          "winter"
#define PGWRAP_CMAP_STR_RDBU            "RdBu"
#define PGWRAP_CMAP_STR_BURD            "BuRd"
#define PGWRAP_CMAP_STR_CUBEHELIX       "cubehelix"
#define PGWRAP_CMAP_STR_CUBEHELIX_INV   "cubehelix-inv"

#define PGWRAP_DEF_CMAP             PGWRAP_CMAP_JET
#define PGWRAP_DEF_CMAP_STR         PGWRAP_CMAP_STR_JET

#define PGWRAP_FALSE                0
#define PGWRAP_TRUE                 1

int pgwrapSetColourMap(int iCMap, int iIsColInv, float fColMin, float fColMax);
int pgwrapGetColourMapFromName(char *pcCMapName);
void pgwrapPlot2D(float* pfBuf, float fDataMin, float fDataMax,
                  float* pfX, int iLenX, float fXStep,
                  float* pfY, int iLenY, float fYStep,
                  char* pcXLabel, char* pcYLabel, char* pcTitle,
                  float* pfXCollapsed, float fXCMin, float fXCMax,
                  float* pfYCollapsed, float fYCMin, float fYCMax,
                  float fAspect, int iColourMap, char cShowScale);


#endif  /* __PGWRAP_H__ */

