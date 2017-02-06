/*
 * @file pgwrap.c
 * A code-efficient PGPLOT wrapper
 * 
 * @author Jayanth Chennamangalam
 * @date 2012.03.02
 */

#include "pgwrap.h"

/* TODO: adjust viewport margins to make sure aspect ratio is correct */

void pgwrapPlot2D(float* pfBuf, float fDataMin, float fDataMax,
                  float* pfX, int iLenX, float fXStep,
                  float* pfY, int iLenY, float fYStep,
                  char* pcXLabel, char* pcYLabel, char* pcTitle,
                  float* pfXCollapsed, float fXCMin, float fXCMax,
                  float* pfYCollapsed, float fYCMin, float fYCMax,
                  float fAspect, int iColourMap, char cShowScale)
{
    float afTM[6] = {0.0};                      /* the transformation matrix */
    char acXAxisConfig[PGWRAP_LEN_GENSTRING] = {0};
    char acYAxisConfig[PGWRAP_LEN_GENSTRING] = {0};
    float fRightMargin = PGWRAP_VP_MR;
    float fTopMargin = PGWRAP_VP_MT;

    /* x-width of the one pixel = (xmax - xmin + xstep) / xlen */
    afTM[1] = (pfX[iLenX-1] - pfX[0] + fXStep) / iLenX;
    /* starting position (left) in world co-ordinates */
    afTM[0] = pfX[0] - afTM[1];
    afTM[2] = 0;
    /* y-height of one pixel = (ymax - ymin + ystep) / ylen */
    afTM[5] = (pfY[iLenY-1] - pfY[0] + fYStep) / iLenY;
    /* starting position (bottom) in world co-ordinates */
    afTM[3] = pfY[0] - afTM[5];
    afTM[4] = 0;

    /* set the paper size */
    cpgpap(0.0, fAspect);

    /* adjust the right margin if showing scale */
    if (cShowScale)
    {
        fRightMargin = PGWRAP_VP_MR_S;
        /* this needs to be adjusted so that the aspect ratio doesn't change */
        fTopMargin = PGWRAP_VP_MT_S;
    }

    /* set the viewport margins, in normalised device co-ordinates */
    if ((NULL == pfXCollapsed) && (NULL == pfYCollapsed))
    {
        cpgsvp(PGWRAP_VP_ML, fRightMargin, PGWRAP_VP_MB, fTopMargin);
        (void) strcpy(acXAxisConfig, "N");
        (void) strcpy(acYAxisConfig, "N");
    }
    else if ((pfXCollapsed != NULL) && (NULL == pfYCollapsed))
    {
        cpgsvp(PGWRAP_VP_MC, fRightMargin, PGWRAP_VP_MB, fTopMargin);
        (void) strcpy(acXAxisConfig, "N");
    }
    else if ((NULL == pfXCollapsed) && (pfYCollapsed != NULL))
    {
        cpgsvp(PGWRAP_VP_ML, fRightMargin, PGWRAP_VP_MC, fTopMargin);
        (void) strcpy(acYAxisConfig, "N");
    }
    else
    {
        cpgsvp(PGWRAP_VP_MC, fRightMargin, PGWRAP_VP_MC, fTopMargin);
    }
    /* set the window boundaries in world co-ordinates */
    cpgswin(pfX[0], pfX[iLenX-1], pfY[0], pfY[iLenY-1]);
    /* set the colour map */
    pgwrapSetColourMap(iColourMap, PGWRAP_FALSE, fDataMin, fDataMax);
    /* plot the image */
    cpgimag((const float *) pfBuf,  /* data to be plotted */
            iLenX,
            iLenY,
            1,
            iLenX,
            1,
            iLenY,
            fDataMin,
            fDataMax,
            afTM);
    /* draw a box around the image */
    cpgbox("CST", 0.0, 0, "CST", 0.0, 0);
    /* mark the x-axis */
    cpgaxis(acXAxisConfig,
            pfX[0], pfY[0],
            pfX[iLenX-1], pfY[0],
            pfX[0], pfX[iLenX-1],
            0.0,
            0,
            0.5,
            0.0,
            0.5,
            0.5,
            0);
    /* mark the y-axis */
    cpgaxis(acYAxisConfig,
            pfX[0], pfY[0],
            pfX[0], pfY[iLenY-1],
            pfY[0], pfY[iLenY-1],
            0.0,
            0,
            0.0,
            0.5,
            0.5,
            -0.5,
            0);
    if (cShowScale)
    {
        /* plot the colour index for reference */
        cpgwedg("RI", 1.0, 5.0, fDataMin, fDataMax, "");
    }
    /* add labels and title */
    if ((NULL == pfXCollapsed) && (NULL == pfYCollapsed))
    {
        cpglab(pcXLabel, pcYLabel, pcTitle);
    }
    else if ((pfXCollapsed != NULL) && (NULL == pfYCollapsed))
    {
        cpglab(pcXLabel, "", pcTitle);
    }
    else if ((NULL == pfXCollapsed) && (pfYCollapsed != NULL))
    {
        cpglab("", pcYLabel, pcTitle);
    }
    else
    {
        cpglab("", "", pcTitle);
    }

    if (pfXCollapsed != NULL)
    {
        if (pfYCollapsed != NULL)
        {
            cpgsvp(PGWRAP_VP_ML, PGWRAP_VP_MC, PGWRAP_VP_MC, fTopMargin);
        }
        else
        {
            cpgsvp(PGWRAP_VP_ML, PGWRAP_VP_MC, PGWRAP_VP_MB, fTopMargin);
        }
        cpgswin(fXCMin,
                fXCMax,
                pfY[0],
                pfY[iLenY-1]);
        cpglab("", pcYLabel, "");
        cpgbox("BCMT", 0.0, 0, "BNST", 0.0, 0);
        cpgline(iLenY, pfXCollapsed, pfY);
    }
    if (pfYCollapsed != NULL)
    {
        if (pfXCollapsed != NULL)
        {
            cpgsvp(PGWRAP_VP_MC, fRightMargin, PGWRAP_VP_MB, PGWRAP_VP_MC);
        }
        else
        {
            cpgsvp(PGWRAP_VP_ML, fRightMargin, PGWRAP_VP_MB, PGWRAP_VP_MC);
        }
        cpgswin(pfX[0],
                pfX[iLenX-1],
                fYCMin,
                fYCMax);
        cpglab(pcXLabel, "", "");
        cpgbox("BNST", 0.0, 0, "BCNT", 0.0, 0);
        cpgline(iLenX, pfX, pfYCollapsed);
    }

    return;
}

