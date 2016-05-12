
/*************************************************************************
* Introduction:
* =============
* The Program "MSG_navigation.c" is an example code provided to give
* the users guidance for a possible implementation of the equations
* given in the LRIT/HRIT Global Specification [1] to navigate MSG
* (METEOSAT 8 onwards) data, i.e. to link the pixel coordinates column
* and line to the corresponding geograhical coordinates latitude and
* longitude.
*
* Users should take note, however, that it does NOT provide software
* for reading MSG data either in LRIT/HRIT, in native or any other
* format and that EUMETSAT cannot guarantee the accuracy of this
* software. The software is for use with MSG data only and will not
* work in the given implementation for Meteosat first generation data.
*
* Two functions/subroutines are provided:
*   pixcoord2geocoord: for conversion of column/line into lat./long.
*   geocoord2pixcoord: for conversion of lat./long. into column/line
*
* The main routine gives an example how to utilize these two functions by
* reading a value for column and line at the start of the program on the
* command line and convert these value into the cooresponding
* geographical coordinates and back again. The results are then printed
* out on the screen.
*
* To Compile the program use for example:
*
* COMMAND PROMPT: gcc MSG_navigation.c -o MSG_navigation -lm
*
* Run the program by typing
*
* COMMAND PROMPT: ./MSG_navigation <COLUMS> <ROWS>
*
* ----------------------------------------------------------------------
*
* NOTE: Please be aware, that the program assumes the MSG image is
* ordered in the operational scanning direction which means from south
* to north and from east to west. With that the VIS/IR channels contains
* of 3712 x 3712 pixels, start to count on the most southern line and the
* most eastern column with pixel number 1,1.
*
*
* NOTE on CFAC/LFAC and COFF/LOFF:
* The parameters CFAC/LFAC and COFF/LOFF are the scaling coefficients
* provided by the navigation record of the LRIT/HRIT header and used
* by the scaling function given in Ref [1], page 28.
*
* COFF/LOFF are the offsets for column and line which are basically 1856
* and 1856 for the VIS/IR channels and refer to the middle of the image
* (centre pixel). The values regarding the High Resolution Visible Channel
* (HRVis) will be made available in a later issue of this software.
*
* CFAC/LFAC are responsible for the image "spread" in the NS and EW
* directions. They are calculated as follows:
* CFAC = LFAC = 2^16 / delta
* with
* delta = 83.843 micro Radian (size of one VIS/IR MSG pixel)
*
* CFAC     = LFAC     =  781648343.404  rad^-1 for VIS/IR
*
* which should be rounded to the nearest integer as stated in Ref [1].
*
* CFAC     = LFAC     =  781648343  rad^-1 for VIS/IR
*
* The sign of CFAC/LFAC gives the orientation of the image.
* Negative sign give data scanned from south to north as in the
* operational scanning. Positive sign vice versa.
*
* The terms "line" and "row" are used interchangeable.
*
* PLEASE NOTE that the values of CFAC/LFAC which are given in the
* Header of the LRIT/HRIT Level 1.5 Data (see [2]) are actually in
* Degrees and should be converted in Radians for use with these
* routines (see example and values above).
*
* The other parameters are given in Ref [1].
*
* Further information may be found in either Ref [1], Ref [2] or
* Ref [3] or on the Eumetsat website http://www.eumetsat.de/ .
*
*  REFERENCE:
*  [1] LRIT/HRIT Global Specification
*      (CGMS 03, Issue 2.6, 12.08.1999)
*      for the parameters used in the program.
*  [2] MSG Ground Segment LRIT/HRIT Mission Specific
*      Implementation, EUMETSAT Document,
*      (EUM/MSG/SPE/057, Issue 5, 4. February 2005).
*  [3] MSG Level 1.5 Image Data Format Description
*      (EUM/PS-MSG/ICD/04/0730, Issue 3, 4. February 2005).
*
* Please email the User Service (via
* //http://www.eumetsat.de/feedback/form_ops.html)
* if you have any questions regarding this software.
*
*
*
*
************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "latlong.h"


/* parameters used in the routines as given in Ref. [1] */
#define  PI                  3.14159265359
#define  SAT_HEIGHT      42164.0             /* distance from earth centre to satellite */
#define  R_EQ             6378.169           /* radius from earth centre to equator     */
#define  R_POL            6356.5838          /* radius from earth centre to pol         */
#define  SUB_LON             0.0             /* longitude of sub-satellite pouint       */
#define	 CFAC       -781648343               /* scaling coefficients (see note above)   */
#define	 LFAC       -781648343               /* scaling coefficients (see note above)   */
#define	 COFF             1856               /* scaling coefficients (see note above)   */
#define	 LOFF             1856               /* scaling coefficients (see note above)   */


#define LatSud            15.0               /* latitude sud of image seleced           */
#define LonEst            15.0               /* longitude East of image selected        */
#define pix               1100               /* nombre de pixel l'image choisi          */
#define lin               1100               /* nombre de line de l'image choisi        */


/* function prototypes

int nint(double val);
int pixcoord2geocoord(int column, int row, int coff, int loff, double *latitude,
double *longitude);
int geocoord2pixcoord(double latitude, double longitude, int coff, int loff, int
*column, int *row);
int Getlinepixel(double lat, double lon, int *line, int *pixel  );
int Getlatlon(double *dlat, double *dlon, int line, int pixel   );

*/
/**************************************************************************
*
* The following program gives an example how to utilize the
* functions "geocoord2pixcoord" and "pixcoord2geocoord"
*
***************************************************************************/

int LatLong::Getlinepixel(double lat, double lon, int *line, int *pixel  )
 {
    lat = lat * -1;
    lon = lon * -1;
  int  row=0,  col=0;
  int  coff=0, loff=0;

  coff=COFF;
  loff=LOFF;

  geocoord2pixcoord(lat, lon, coff, loff, &col, &row);
  *line = row;
  *pixel= col;

  return (0);
}

int LatLong::Getlatlon(double *dlat, double *dlon, int line, int pixel   )
 {

  int  coff=0, loff=0;
  int  c=0, l=0;

  double lat=0.0, lon=0.0;

  c = pixel;
  l = line;

  coff=COFF;
  loff=LOFF;

  pixcoord2geocoord( c, l, coff, loff, &lat, &lon);

  *dlat=lat * -1;
  *dlon=lon * -1;

  return (0);
}



/**********************************************************
 * function pixcoord2geocoord                             *
 *                                                        *
 * PURPOSE:                                               *
 *   return the latitude and longitude of an MSG image    *
 *   for a given pair of pixel column and row.            *
 *   (based on the formulas given in Ref. [1])            *
 *                                                        *
 *                                                        *
 * DEPENDENCIES:                                          *
 *   none                                                 *
 *                                                        *
 *                                                        *
 * REFERENCE:                                             *
 * [1] LRIT/HRIT Global Specification                     *
 *     (CGMS 03, Issue 2.6, 12.08.1999)                   *
 *     for the parameters used in the program.            *
 * [2] MSG Ground Segment LRIT/HRIT Mission Specific      *
 *     Implementation, EUMETSAT Document,                 *
 *     (EUM/MSG/SPE/057, Issue 5, 4. February 2005).      *
 *                                                        *
 *                                                        *
 * MODIFICATION HISTORY:                                  *
 *   Version 1.0                                          *
 *   17.01.2005 written by Knut Dammann                   *
 *   (c) EUMETSAT                                         *
 *                                                        *
 *                                                        *
 * INPUT:                                                 *
 *   row    (int) row-value of the pixel                  *
 *   column (int) line-value of the pixel                 *
 *   coff   (int) coefficient of the scalling function    *
 *                (see page 28, Ref [1])                  *
 *   loff   (int) coefficient of the scalling function    *
 *                (see page 28, Ref [1])                  *
 *                                                        *
 * OUTPUT:                                                *
 *   latitude  (double) geographic Latitude of the given  *
 *                      pixel [Degrees]                   *
 *   longitude (double) geographic Longitude of the given *
 *                      pixel [Degrees]                   *
 *                                                        *
 *                                                        *
 *********************************************************/

int LatLong::pixcoord2geocoord(int column, int row, int coff, int loff, double *latitude,
double *longitude){


  double s1=0.0, s2=0.0, s3=0.0, sn=0.0, sd=0.0, sxy=0.0, sa=0.0;
  double x=0.0, y=0.0;
  double longi=0.0, lati=0.0;

  int c=0, l=0;


  c=column;
  l=row;


  /*  calculate viewing angle of the satellite by use of the equation  */
  /*  on page 28, Ref [1]. */

  x = pow(2,16) * ( c - coff) / CFAC ;
  y = pow(2,16) * ( l - loff) / LFAC ;


  /*  now calculate the inverse projection */

  /* first check for visibility, whether the pixel is located on the earth   */
  /* surface or in space. 						     */
  /* To do this calculate the argument to sqrt of "sd", which is named "sa". */
  /* If it is negative then the sqrt will return NaN and the pixel will be   */
  /* located in space, otherwise all is fine and the pixel is located on the */
  /* earth surface.                                                          */

  sa =  pow(SAT_HEIGHT * cos(x) * cos(y),2 )  - (cos(y)*cos(y) + 1.006803 * sin(y)*sin(y)) * 1737121856. ;


  /* now calculate the rest of the formulas using equations on */
  /* page 25, Ref. [1]  */

  sd = sqrt( pow((SAT_HEIGHT * cos(x) * cos(y)),2)
         - (cos(y)*cos(y) + 1.006803 * sin(y)*sin(y)) * 1737121856 );
  sn = (SAT_HEIGHT * cos(x) * cos(y) - sd)
    / ( cos(y)*cos(y) + 1.006803 * sin(y)*sin(y) ) ;

  s1 = SAT_HEIGHT - sn * cos(x) * cos(y);
  s2 = sn * sin(x) * cos(y);
  s3 = -sn * sin(y);

  sxy = sqrt( s1*s1 + s2*s2 );

  /* using the previous calculations the inverse projection can be  */
  /* calculated now, which means calculating the lat./long. from    */
  /* the pixel row and column by equations on page 25, Ref [1].     */

  /* produce error values */
  if ( sa <= 0.0 ) {
    lati = -999.999*PI/180.;
    longi = -999.999*PI/180.;
  }
  else {
    longi = atan(s2/s1 + SUB_LON);
    lati  = atan((1.006803*s3)/sxy);
  }

  /* convert from radians into degrees */
  *latitude = lati*180./PI;
  *longitude = longi*180./PI;


  return (0);

}

/**********************************************************
 * function geocoord2pixcoord                             *
 *                                                        *
 * PURPOSE:                                               *
 *   return the pixel cloumn and line of an MSG image     *
 *   for a given pair of latitude/longitude.              *
 *   (based on the formulas given in Ref. [1])            *
 *                                                        *
 *                                                        *
 * DEPENDENCIES:                                          *
 *   up to now none                                       *
 *                                                        *
 *                                                        *
 * REFERENCE:                                             *
 * [1] LRIT/HRIT Global Specification                     *
 *     (CGMS 03, Issue 2.6, 12.08.1999)                   *
 *     for the parameters used in the program             *
 * [2] MSG Ground Segment LRIT/HRIT Mission Specific      *
 *     Implementation, EUMETSAT Document,                 *
 *     (EUM/MSG/SPE/057, Issue 5, 4. February 2005)      *
 *                                                        *
 *                                                        *
 * MODIFICATION HISTORY:                                  *
 *   Version 1.0                                          *
 *   17.01.2005 written by Knut Dammann                   *
 *   (c) EUMETSAT                                         *
 *                                                        *
 *                                                        *
 * INPUT:                                                 *
 *   latitude  (double) geographic Latitude of a point    *
 *                      [Degrees]                         *
 *   longitude (double) geographic Longitude of a point   *
 *                      [Degrees]                         *
 *   coff (int)   coefficient of the scalling function    *
 *                (see page 28, Ref [1])                  *
 *   loff (int)   coefficient of the scalling function    *
 *                (see page 28, Ref [1])                  *
 *                                                        *
 *                                                        *
 * OUTPUT:                                                *
 *   row    (int) row-value of the wanted pixel           *
 *   column (int) column-value of the wanted pixel        *
 *                                                        *
 *********************************************************/

int LatLong::geocoord2pixcoord(double latitude, double longitude, int coff, int loff, int *column, int *row){

  int ccc=0, lll=0;

  double lati=0.0, longi=0.0;
  double c_lat=0.0;
  double lat=0.0;
  double lon=0.0;
  double r1=0.0, r2=0.0, r3=0.0, rn=0.0, re=0.0, rl=0.0;
  double xx=0.0, yy=0.0;
  double cc=0.0, ll=0.0;
  double dotprod=0.0;

  lati= latitude;
  longi= longitude;

  /* check if the values are sane, otherwise return error values */
  if (lati < -90.0 || lati > 90.0 || longi < -180.0 || longi > 180.0 ){
    *row = -999;
    *column = -999;
    return (-1);
  }


  /* convert them to radiants */
  lat = lati*PI / 180.;
  lon = longi *PI / 180.;

  /* calculate the geocentric latitude from the          */
  /* geograhpic one using equations on page 24, Ref. [1] */

  c_lat = atan ( (0.993243*(sin(lat)/cos(lat)) ));


  /* using c_lat calculate the length form the earth */
  /* centre to the surface of the earth ellipsoid    */
  /* equations on page 24, Ref. [1]                  */

  re = R_POL / sqrt( (1 - 0.00675701 * cos(c_lat) * cos(c_lat) ) );


  /* calculate the forward projection using equations on */
  /* page 24, Ref. [1]                                        */

  rl = re;
  r1 = SAT_HEIGHT - rl * cos(c_lat) * cos(lon - SUB_LON);
  r2 = - rl *  cos(c_lat) * sin(lon - SUB_LON);
  r3 = rl * sin(c_lat);
  rn = sqrt( r1*r1 + r2*r2 +r3*r3 );


  /* check for visibility, whether the point on the earth given by the */
  /* latitude/longitude pair is visible from the satellte or not. This */
  /* is given by the dot product between the vectors of:               */
  /* 1) the point to the spacecraft,			               */
  /* 2) the point to the centre of the earth.			       */
  /* If the dot product is positive the point is visible otherwise it  */
  /* is invisible.						       */

  dotprod = r1*(rl * cos(c_lat) * cos(lon - SUB_LON)) - r2*r2 - r3*r3*(pow((R_EQ/R_POL),2));

  if (dotprod <= 0 ){
    *column = -999;
    *row = -999;
    return (-1);
  }


  /* the forward projection is x and y */

  xx = atan( (-r2/r1) );
  yy = asin( (-r3/rn) );


  /* convert to pixel column and row using the scaling functions on */
  /* page 28, Ref. [1]. And finding nearest integer value for them. */


  cc = coff + xx *  pow(2,-16) * CFAC ;
  ll = loff + yy *  pow(2,-16) * LFAC ;


  ccc=nint(cc);
  lll=nint(ll);

  *column = ccc;
  *row = lll;


  return (0);

}



/* this function returns the nearest integer to the value val */
/* and is used in function geocoord2pixcoord */

int LatLong::nint(double val){

  double a=0.0; /* integral  part of val */
  double b=0.0; /* frational part of val */

  b = modf(val,&a);

  if ( b > 0.5 ){
    val = ceil(val);
  }
  else{
    val = floor(val);
  }

  return (int)val;

}

