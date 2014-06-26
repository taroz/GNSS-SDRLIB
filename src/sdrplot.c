/*------------------------------------------------------------------------------
* sdrplot.c : SDR plot functions
*
* Copyright (C) 2014 Taro Suzuki <gnsssdrlib@gmail.com>
*-----------------------------------------------------------------------------*/
#include "sdr.h"

/* global variables ----------------------------------------------------------*/
#ifdef WIN32
#define PSIZE 2 
#else
#define PSIZE 10
#endif
thread_t hpltthread; /* plot thread */

/* modify gnuplot ini file -----------------------------------------------------
* modify gnuplot ini file to set window size and position
* args   : int    nx        I   window width (pixel)
*          int    ny        I   window height (pixel)
*          int    posx      I   window x position (pixel)
*          int    posy      I   window y position (pixel)
* return : none
*-----------------------------------------------------------------------------*/
extern int updatepltini(int nx, int ny, int posx, int posy)
{
    FILE *fp;
    char apppath[500];

#ifdef WIN32
    /* Generating "gnuplot.ini" file */
    SHGetFolderPath(0,CSIDL_APPDATA,0,0,apppath);
    strcat(apppath,"\\gnuplot.ini");

    if (!(fp=fopen(apppath,"w"))) {
        SDRPRINTF("error: updatepltini path=%s \n",apppath);
        return -1;
    }
    fprintf(fp,"set terminal windows\n");
    fflush(fp);
    fclose(fp);

    /* Generating "wgnuplot.ini" file */
    SHGetFolderPath(0,CSIDL_APPDATA,0,0,apppath);
    strcat(apppath,"\\wgnuplot.ini");
    if (!(fp=fopen(apppath,"w"))) { 
        SDRPRINTF("error: updatepltini path=%s \n",apppath);
        return -1;
    }
    fprintf(fp,"[WGNUPLOT]\n");
    fprintf(fp,"TextOrigin=263 200\n");
    fprintf(fp,"TextSize=1393 790\n");
    fprintf(fp,"TextMinimized=0\n");
    fprintf(fp,"TextFont=Arial,14\n");
    fprintf(fp,"TextWrap=1\n");
    fprintf(fp,"TextLines=400\n");
    fprintf(fp,"SysColors=0\n");
    fprintf(fp,"GraphOrigin=%d %d\n",posx,posy);
    fprintf(fp,"GraphSize=%d %d\n",nx,ny);
    fflush(fp);
    fclose(fp);
#else
    /* Generating ".gnuplot" file */
    strcpy(apppath,getenv("HOME"));
    strcat(apppath,"/.gnuplot");
    if (!(fp=fopen(apppath,"w"))) { 
        SDRPRINTF("error: updatepltini path=%s \n",apppath);
        return -1;
    }
    fprintf(fp,"set terminal x11 ");
    fprintf(fp,"size %d,%d ",nx,ny);
    fprintf(fp,"position %d,%d ",posx,posy);
    fprintf(fp,"enhanced font \"Arial,12\"\n");
    fflush(fp);
    fclose(fp);
#endif
    return 0;
}
/* set plot parameter ----------------------------------------------------------
* set plot parameter to plot struct
* args   : sdrplt_t *plt    I   sdr plot struct
*          int    type      I   plot type (PLT_Y/PLT_XY/...)
*          int    nx        I   number of x data
*          int    ny        I   number of y data
*          int    skip      I   number of skip data (0: plot all data)
*          int    abs       I   absolute plotting flag (0:normal 1:absolute)
*          double s         I   scale factor of y/z data
*          int    h         I   plot window height (pixel)
*          int    w         I   plot window width (pixel)
*          int    mh        I   plot window margin height (pixel)
*          int    mw        I   plot window margin width (pixel)
*          int    no        I   plot window number
* return : none
*-----------------------------------------------------------------------------*/
extern void setsdrplotprm(sdrplt_t *plt, int type, int nx, int ny, int skip,
                        int abs, double s, int h, int w, int mh, int mw, int no)
{
    plt->type=type;
    plt->nx=nx;
    plt->ny=ny;
    plt->skip=skip;
    plt->flagabs=abs;
    plt->scale=s;
    plt->plth=h;
    plt->pltw=w;
    plt->pltmh=mh;
    plt->pltmw=mw;
    plt->pltno=no;
}
/* initialization of plot struct -----------------------------------------------
* allocate memory and open pipe
* args   : sdrplt_t *plt    I   sdr plot struct
* return : none
*-----------------------------------------------------------------------------*/
extern int initsdrplot(sdrplt_t *plt)
{
    int xi,yi;
    int posx,posy;

    /* memory allocation */
    switch (plt->type) {
    case PLT_Y:
        if (!(plt->y=(double*)malloc(sizeof(double)*plt->ny))) {
            SDRPRINTF("error: initsdrplot memory allocation\n");
            return -1;
        }
        break;
    case PLT_XY:
        if (!(plt->x=(double*)malloc(sizeof(double)*plt->nx)) ||
            !(plt->y=(double*)malloc(sizeof(double)*plt->nx))) {
                SDRPRINTF("error: initsdrplot memory allocation\n");
                return -1;
        }
        break;
    case PLT_SURFZ:
        if (!(plt->z=(double*)malloc(sizeof(double)*plt->nx*plt->ny))){
            SDRPRINTF("error: initsdrplot memory allocation\n");
            return -1;
        }
        break;
    default:
        break;
    }
    /* figure position */
    xi=(plt->pltno-1)%PLT_WN;
    yi=(plt->pltno-1-xi)/PLT_WN;
    posx=plt->pltmw+xi*plt->pltw;
    posy=plt->pltmh+yi*plt->plth;

    /* Lock */
    mlock(hpltmtx);

    /* update config file */
    if ((updatepltini(plt->pltw,plt->plth,posx,posy)<0)){
        SDRPRINTF("error: updatepltini\n");
        return -1;
    }
    /* pipe open */
#ifdef WIN32
    if (!(plt->fp=_popen(".\\gnuplot\\gnuplot.exe","w"))) {
#else
    if (!(plt->fp=popen("gnuplot","w"))) {
#endif
        unmlock(hpltmtx);
        SDRPRINTF("error: gnuplot doesn't exist \n");
        return -1;
    }
    sleepms(200);
    unmlock(hpltmtx);
#ifdef GUI
    /* hide window */
    plt->hw=FindWindow(NULL,"c:\\Windows\\system32\\cmd.exe");
    ShowWindow(plt->hw,SW_HIDE);
#endif
    return 0;
}
/* quit plot function ----------------------------------------------------------
* close pipe handle and free memory
* args   : sdrplt_t *plt    I   sdr plot struct
* return : none
*-----------------------------------------------------------------------------*/
extern void quitsdrplot(sdrplt_t *plt)
{
    /* pipe close */
#ifdef WIN32
    if (plt->fp!=NULL)_pclose(plt->fp); plt->fp=NULL;
#else
    if (plt->fp!=NULL) pclose(plt->fp); plt->fp=NULL;
#endif
    if (plt->x!=NULL) free(plt->x); plt->x=NULL;
    if (plt->y!=NULL) free(plt->y); plt->y=NULL;
    if (plt->z!=NULL) free(plt->z); plt->z=NULL;
}
/* gnuplot set x axis range ----------------------------------------------------
* set x axis range
* args   : sdrplt_t *plt    I   sdr plot struct
*          double *xmin     I   minimum value in x-axis
*          double *xmax     I   maximum value in x-axis
* return : none
*-----------------------------------------------------------------------------*/
extern void setxrange(sdrplt_t *plt, double xmin, double xmax)
{
    fprintf(plt->fp,"set xr[%.1f:%.1f]\n",xmin,xmax);
    fflush(plt->fp);
}
/* gnuplot set y axis range ----------------------------------------------------
* set y axis range
* args   : sdrplt_t *plt    I   sdr plot struct
*          double *ymin     I   minimum value in y-axis
*          double *ymax     I   maximum value in y-axis
* return : none
*-----------------------------------------------------------------------------*/
extern void setyrange(sdrplt_t *plt, double ymin, double ymax)
{
    fprintf(plt->fp,"set yr[%.1f:%.1f]\n",ymin,ymax);
    fflush(plt->fp);
}
/* gnuplot set labels ----------------------------------------------------------
* set labels in x and y axes
* args   : sdrplt_t *plt    I   sdr plot struct
*          char   *xlabel   I   x-axis label string
*          char   *ylabel   I   y-axis label string
* return : none
*-----------------------------------------------------------------------------*/
extern void setlabel(sdrplt_t *plt, char *xlabel, char *ylabel)
{
    fprintf(plt->fp,"set xl '%s'\n",xlabel);
    fprintf(plt->fp,"set yl '%s'\n",ylabel);
    fflush(plt->fp);
}
/* gnuplot set title -----------------------------------------------------------
* set title in figure
* args   : sdrplt_t *plt    I   sdr plot struct
*          char   *title    I   title string
* return : none
*-----------------------------------------------------------------------------*/
extern void settitle(sdrplt_t *plt, char *title)
{
    fprintf(plt->fp,"set title '%s'\n",title);
    fflush(plt->fp);
}
/* plot 1D function ------------------------------------------------------------
* gnuplot plot 1D data function
* args   : FILE   *fp       I   gnuplot pipe handle
*          double *y        I   y data
*          int    n         I   number of input data
*          int    skip      I   number of skip data (0: plot all data)
*          double s         I   scale factor of y data
* return : none
*-----------------------------------------------------------------------------*/
extern void ploty(FILE *fp, double *y, int n, int skip, double s)
{
    int i;
    fprintf(fp, "set grid\n");
    fprintf(fp, "unset key\n");
    fprintf(fp, "plot '-' with lp lw 1 pt 6 ps %d\n",PSIZE);
    for(i=0;i<n;i+=(skip+1))
        fprintf(fp,"%.3f\n",y[i]*s);
    fprintf(fp,"e\n");
    fflush(fp);
}
/* plot 2D function ------------------------------------------------------------
* gnuplot plot 2D data function
* args   : FILE   *fp       I   gnuplot pipe handle
*          double *x        I   x data
*          double *y        I   y data
*          int    n         I   number of input data
*          int    skip      I   number of skip data (0: plot all data)
*          double s         I   scale factor of y data
* return : none
*-----------------------------------------------------------------------------*/
extern void plotxy(FILE *fp, double *x, double *y, int n, int skip, double s)
{
    int i;
    fprintf(fp, "set grid\n");
    fprintf(fp, "unset key\n");
    fprintf(fp, "plot '-' with p pt 6 ps %d\n",PSIZE);
    for(i=0;i<n;i+=(skip+1))
        fprintf(fp,"%.3f\t%.3f\n",x[i],y[i]*s);
    fprintf(fp,"e\n"); 
    fflush(fp);
}
/* plot surface function -------------------------------------------------------
* gnuplot plot 3D surface data function
* args   : FILE   *fp       I   gnuplot pipe handle
*          double *z        I   2D array of z value
*          int    nx        I   number of x data
*          int    ny        I   number of y data
*          int    skip      I   number of skip data (0: plot all data)
*          double s         I   scale factor of z data
* return : none
*-----------------------------------------------------------------------------*/
extern void plotsurfz(FILE *fp, double*z, int nx, int ny, int skip, double s)
{
    int i,j;
    fprintf(fp, "unset key\n");
    fprintf(fp, "splot '-' with pm3d\n");
    for(i=0;i<ny;i+=(skip+1)) {
        for(j=0;j<nx;j+=(skip+1))
            fprintf(fp,"%.3f\n",z[j*ny+i]*s);
        fprintf(fp,"\n");
    }
    fprintf(fp,"e\n");
    fflush(fp);
}
/* plot boxes function ---------------------------------------------------------
* gnuplot plot boxes function
* args   : FILE   *fp       I   gnuplot pipe handle
*          double *x        I   x data
*          double *y        I   y data
*          int    n         I   number of input data
*          int    skip      I   number of skip data (0: plot all data)
*          double s         I   scale factor of y data
* return : none
*-----------------------------------------------------------------------------*/
extern void plotbox(FILE *fp, double *x, double *y, int n, int skip, double s)
{
    int i;
    fprintf(fp, "set grid\n");
    fprintf(fp, "unset key\n");
    fprintf(fp, "set boxwidth 0.95\n");
    fprintf(fp, "set style fill solid border rgb \"black\"\n");
    fprintf(fp, "plot '-' with boxes\n");
    for(i=0;i<n;i+=(skip+1))
        fprintf(fp,"%.3f\t%.3f\n",x[i],y[i]*s);
    fprintf(fp,"e\n"); 
    fflush(fp);
}
/* plot function/thread --------------------------------------------------------
* gnuplot plot function/thread called from plot/plotthread
* args   : void   *arg      I   sdr plot struct
* return : none
*-----------------------------------------------------------------------------*/
#ifdef WIN32
static void plotgnuplot(void *arg)
#else
static void *plotgnuplot(void *arg)
#endif
{
    int i;
    sdrplt_t *plt=(sdrplt_t*)arg; /* input plt struct */

#ifndef WIN32
    pthread_detach(pthread_self()); /* release memory */
#endif

    /* selection of plot type */
    switch (plt->type) {
    case PLT_Y: /* 1D plot */
        if (plt->flagabs)
            for (i=0;i<plt->ny;i++) plt->y[i]=fabs(plt->y[i]);
        ploty(plt->fp,plt->y,plt->ny,plt->skip,plt->scale);
        break;
    case PLT_XY: /* 2D plot*/
        if (plt->flagabs)
            for (i=0;i<plt->nx;i++) plt->y[i]=fabs(plt->y[i]);
        plotxy(plt->fp,plt->x,plt->y,plt->nx,plt->skip,plt->scale);
        break;
    case PLT_SURFZ: /* 3D surface plot */
        if (plt->flagabs)
            for (i=0;i<plt->nx*plt->ny;i++) plt->z[i]=fabs(plt->z[i]);
        plotsurfz(plt->fp,plt->z,plt->nx,plt->ny,plt->skip,plt->scale);
        break;
    case PLT_BOX: /* box plot */
        plotbox(plt->fp,plt->x,plt->y,plt->nx,plt->skip,plt->scale);
        break;
    default:
        break;
    }
    return THRETVAL;
}
/* plot (thread version) -------------------------------------------------------
* gnuplot plot function (thread version)
* args   : sdrplt_t *plt    I   sdr plot struct
* return : none
* note : thread version don't waits drawing graphs
*-----------------------------------------------------------------------------*/
extern void plotthread(sdrplt_t *plt)
{
    mlock(hpltmtx);
    cratethread(hpltthread,plotgnuplot,plt);
    unmlock(hpltmtx);
}
/* plot (function version) -----------------------------------------------------
* gnuplot plot function (function version)
* args   : sdrplt_t *plt    I   sdr plot struct
* return : none
* note : function version waits drawing graphs
*-----------------------------------------------------------------------------*/
extern void plot(sdrplt_t *plt)
{
    mlock(hpltmtx);
    plotgnuplot(plt);
    unmlock(hpltmtx);
}
