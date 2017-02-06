/* test/demo program for pgwrap */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>                  /* for FLT_MAX */
#include <math.h>
#include <cpgplot.h>
#include <pgwrap.h>

#define FALSE               0
#define TRUE                1

#define LEN_ARRAY_X         128       /* length of the x-axis array */
#define LEN_ARRAY_Y         128        /* length of the y-axis array */

/* PGPLOT definitions */
#define PG_DEV              "1/XS"  /* device for screen plotting */
//#define PG_DEV              "pgimag.ps/CPS"  /* plot to file */

int main(int argc, char *argv[])
{
    /* sample data values to be plotted */
    float afPlotBuf[LEN_ARRAY_Y][LEN_ARRAY_X] = {{0.0}};
    /* x-axis */
    float afX[LEN_ARRAY_X] = {0.0};
    /* y-axis */
    float afY[LEN_ARRAY_Y] = {0.0};
    /* array to store the x-collapsed values */
    float afXCollapsed[LEN_ARRAY_Y] = {0.0};
    /* array to store the y-collapsed values */
    float afYCollapsed[LEN_ARRAY_X] = {0.0};
    float fXStep = 0.0;                                 /* step size in x */
    float fYStep = 0.0;                                 /* step size in y */
    float fXCMin = FLT_MAX;                             /* min. of data */
    float fXCMax = -(FLT_MAX);                          /* max. of data */
    float fYCMin = FLT_MAX;                             /* min. of data */
    float fYCMax = -(FLT_MAX);                          /* max. of data */
    float fAspect = (float) LEN_ARRAY_Y / LEN_ARRAY_X;  /* aspect ratio */
    int i = 0;
    int j = 0;

    /* generate data */
    for (j = 0; j < LEN_ARRAY_Y; ++j)
    {
        afY[j] = (float) j - ((float) LEN_ARRAY_Y / 2);
        for (i = 0; i < LEN_ARRAY_X; ++i)
        {
            afX[i] = (float) i - ((float) LEN_ARRAY_X / 2);
            afPlotBuf[j][i] = expf(-((afX[i] * afX[i] / (2 * (LEN_ARRAY_X / 8) * (LEN_ARRAY_X / 8)))
                                     + (afY[j] * afY[j] / (2 * (LEN_ARRAY_Y / 8) * (LEN_ARRAY_Y / 8)))));
        }
    }
    fXStep = afX[1] - afX[0];             /* step size in x */
    fYStep = afY[1] - afY[0];             /* step size in y */

    /* integrate over x */
    for (j = 0; j < LEN_ARRAY_Y; ++j)
    {
        for (i = 0; i < LEN_ARRAY_X; ++i)
        {
            afXCollapsed[j] += afPlotBuf[j][i];
            if (fXCMin > afXCollapsed[j])
            {
                fXCMin = afXCollapsed[j];
            }
            if (fXCMax < afXCollapsed[j])
            {
                fXCMax = afXCollapsed[j];
            }
        }
    }
    /* integrate over y */
    for (i = 0; i < LEN_ARRAY_X; ++i)
    {
        for (j = 0; j < LEN_ARRAY_Y; ++j)
        {
            afYCollapsed[i] += afPlotBuf[j][i];
            if (fYCMin > afYCollapsed[i])
            {
                fYCMin = afYCollapsed[i];
            }
            if (fYCMax < afYCollapsed[i])
            {
                fYCMax = afYCollapsed[i];
            }
        }
    }

    /* increase the upper limit by 10% so that we can see the peak */
    fXCMax *= 1.1;
    fYCMax *= 1.1;

    /* open the plotting device */
    cpgopen(PG_DEV);

    /* plot */
    pgwrapPlot2D((float*) afPlotBuf, 0.0, 1.0,
                 afX, LEN_ARRAY_X, fXStep,
                 afY, LEN_ARRAY_Y, fYStep,
                 "X", "Y", "Z vs. X and Y",
                 /* uncomment each of these lines one by one for demo */
                 //afXCollapsed, fXCMin, fXCMax, afYCollapsed, fYCMin, fYCMax,
                 //afXCollapsed, fXCMin, fXCMax, NULL, 0.0, 0.0,
                 //NULL, 0.0, 0.0, afYCollapsed, fYCMin, fYCMax,
                 NULL, 0.0, 0.0, NULL, 0.0, 0.0,
                 fAspect, PGWRAP_CMAP_BURD, TRUE);

    /* close the plotting device */
    cpgclos();

    return EXIT_SUCCESS;
}

