#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define TRUE 1
#define FALSE 0
typedef unsigned char byte; // needed for gif writer
int WriteGIF( FILE *fp, byte *pic, int   ptype, int w, int h, byte *rmap, byte *gmap, byte *bmap, int   numcols, int colorstyle, char *comment);
static unsigned char Rainbow2_Red[] = { 0, 34, 35, 35, 36, 37, 38, 39, 39, 40, 40, 41,
41, 42, 42, 42, 42, 42, 42, 42, 41, 41, 41, 40, 40, 39, 38, 38, 37, 37, 36, 35,
35, 34, 33, 33, 32, 32, 31, 30, 30, 29, 28, 28, 27, 27, 26, 25, 25, 24, 24, 23,
23, 22, 22, 21, 21, 20, 20, 19, 19, 19, 18, 18, 17, 17, 17, 16, 16, 16, 15, 15,
15, 14, 14, 14, 13, 13, 13, 13, 12, 12, 12, 12, 11, 11, 11, 11, 11, 10, 10, 10,
10, 10, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 7, 7, 7, 7, 12, 17, 24, 29, 35,
42, 48, 53, 60, 67, 73, 79, 84, 91, 97, 103, 109, 115, 120, 126, 131, 136, 141,
147, 152, 156, 161, 165, 169, 173, 177, 181, 184, 188, 191, 194, 197, 200, 203,
206, 208, 211, 213, 215, 217, 220, 222, 224, 226, 228, 230, 232, 234, 236, 236,
236, 236, 236, 237, 237, 237, 237, 237, 238, 238, 238, 238, 238, 238, 239, 239,
239, 239, 239, 239, 240, 240, 240, 240, 240, 240, 241, 241, 241, 241, 241, 241,
242, 242, 242, 242, 242, 242, 243, 243, 243, 243, 243, 243, 244, 244, 244, 244,
244, 245, 245, 245, 245, 245, 246, 246, 246, 246, 246, 247, 247, 247, 247, 247,
248, 248, 248, 248, 249, 249, 249, 249, 250, 250, 250, 251, 251, 251, 251, 252,
252, 252, 253, 253, 253, 253, 254, 254, 254, 255 };

static unsigned char Rainbow2_Grn[] = { 0, 44, 45, 47, 49, 51, 53, 55, 57, 58, 60, 62,
64, 66, 67, 69, 71, 72, 74, 75, 76, 78, 79, 80, 81, 82, 84, 85, 86, 87, 88, 90,
91, 92, 93, 95, 96, 98, 99, 101, 102, 104, 106, 107, 109, 111, 113, 115, 117,
119, 121, 124, 126, 129, 131, 134, 137, 140, 143, 146, 149, 152, 156, 160, 163,
167, 171, 176, 180, 185, 189, 194, 199, 205, 207, 208, 208, 209, 209, 210, 211,
211, 212, 212, 213, 213, 213, 214, 214, 215, 215, 216, 216, 217, 217, 217, 218,
218, 218, 219, 219, 219, 220, 220, 220, 221, 221, 221, 222, 222, 222, 223, 223,
223, 223, 224, 224, 224, 225, 225, 225, 225, 226, 226, 226, 227, 227, 227, 227,
228, 228, 228, 228, 229, 229, 229, 229, 230, 230, 230, 231, 231, 231, 231, 232,
232, 232, 232, 232, 233, 233, 233, 233, 234, 234, 234, 234, 234, 235, 235, 235,
235, 235, 236, 236, 234, 233, 231, 229, 228, 226, 225, 223, 221, 219, 217, 215,
213, 211, 209, 207, 205, 203, 201, 199, 198, 195, 194, 192, 190, 188, 186, 184,
183, 180, 178, 177, 175, 173, 171, 169, 167, 165, 163, 161, 159, 157, 156, 154,
151, 149, 147, 145, 143, 141, 139, 136, 134, 132, 129, 127, 125, 122, 119, 117,
114, 111, 108, 105, 102, 99, 95, 92, 89, 85, 82, 78, 74, 70, 67, 62, 58, 54,
50, 45, 41, 37, 33, 28, 24, 20, 16, 12, 7, 3, 0 };

static unsigned char Rainbow2_Blu[] = { 0, 89, 93, 96, 99, 102, 106, 109, 113, 116,
120, 123, 126, 130, 132, 136, 139, 141, 143, 146, 148, 150, 152, 154, 156, 158,
159, 161, 162, 164, 165, 167, 168, 169, 171, 172, 173, 174, 176, 177, 178, 179,
180, 181, 182, 184, 185, 186, 186, 188, 189, 189, 190, 191, 192, 193, 194, 195,
196, 196, 197, 198, 199, 199, 200, 201, 202, 202, 203, 204, 205, 205, 206, 207,
205, 200, 197, 192, 187, 183, 178, 173, 168, 162, 157, 153, 147, 141, 135, 130,
124, 118, 112, 106, 100, 95, 89, 83, 77, 71, 65, 60, 54, 48, 43, 38, 32, 26,
21, 14, 9, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5,
5, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


static unsigned char Rainbow3_Red[] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,7,11,15,19,23,27,31,35,39,43,47,51,55,59,63,67,71,75,79,83,87,91,95
,99,103,107,111,115,119,123,127,131,135,139,143,147,151,155,159,163,167,171,175,179,183,187,191,195,199,203,207,211,215,219,223,227,231,235,239,243,247,251,255,255
,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,250,246,241,237,233,228,224,219,215,211,206,202,197,193,189,184,180,175,171
,167,162,158,153,149,145,140,136,131,131};



static unsigned char Rainbow3_Grn[] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,7,11,15,19,23,27
,31,35,39,43,47,51,55,59,63,67,71,75,79,83,87,91,95,99,103,107,111,115,119,123,127,131,135,139,143,147,151,155,159,163,167,171,175,179,183,187,191
,195,199,203,207,211,215,219,223,227,231,235,239,243,247,251,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,251
,247,243,239,235,231,227,223,219,215,211,207,203,199,195,191,187,183,179,175,171,167,163,159,155,151,147,143,139,135,131,127,123,119,115,111,107,103,99,95,91,87
,83,79,75,71,67,63,59,55,51,47,43,39,35,31,27,23,19,15,11,7,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0};



static unsigned char Rainbow3_Blu[] = {
131,131,135,139,143,147,151,155,159,163,167,171,175,179,183,187,191,195,199,203,207,211,215,219,223,227,231,235,239,243,247,251,255,255,255,255,255,255,255,255,255
,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,251,247,243,239,235,231,227,223,219,215,211,207,203,199,195,191,187,183,179,175,171,167,163,159
,155,151,147,143,139,135,131,127,123,119,115,111,107,103,99,95,91,87,83,79,75,71,67,63,59,55,51,47,43,39,35,31,27,23,19,15,11,7,3,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0};


/**
 *   Routine to write out a GIF image
 */
void DumpGif( char *FilenameBase, int W, int H, double **Image ){

    double           Val, Min, Max, dVal;
    int              w, h;
    unsigned char   *uImage, uVal, Filename[1024];
    FILE            *fp_gif, *fp_info;

    int             LogScale;

    LogScale = FALSE;
    LogScale = TRUE;


    // Determine Min/Max values...
    Min =  9e99;
    Max = -9e99;
    for ( w=0; w<W; w++ ){
        for ( h=0; h<H; h++ ) {

            if ( LogScale ) {
                Val = Image[h][w] > 0.0 ? log10( Image[h][w] ) : -9e99;
            } else {
                Val = Image[h][w];
            }
            if (Val > Max) Max = Val;
            if ((Val < Min)&&(Val > -1e99)) Min = Val;

        }
    }

    printf("Min, Max = %g %g\n", Min, Max);

    sprintf( Filename, "%s.info", FilenameBase);
    fp_info = fopen( Filename, "w" );
    fprintf( fp_info, "Min: %g\n", Min );
    fprintf( fp_info, "Max: %g\n", Max );
    fclose( fp_info );



    uImage = (unsigned char *)calloc( W*H, sizeof(unsigned char) );

    for ( w=0; w<W; w++ ){
        for ( h=0; h<H; h++ ) {

            if ( LogScale ) {
                Val = Image[h][w] > 0.0 ? log10( Image[h][w] ) : -9e99;
            } else {
                Val = Image[h][w];
            }
            if ( Val < -1e99 ) {
                uVal = 0;
            } else {
                dVal = (Val - Min)/(Max-Min)*255.0;
                uVal = (dVal > 255.0) ? 255 : (unsigned char)dVal;
            }
            *(uImage + W*(H-1-h) + w) = uVal;

        }
    }

    sprintf( Filename, "%s.gif", FilenameBase);
    fp_gif = fopen(Filename, "w");
    WriteGIF(fp_gif, (byte *)uImage, 0, W, H, Rainbow3_Red, Rainbow3_Grn, Rainbow3_Blu, 256, 0, "");
    fclose(fp_gif);

    free( uImage );



    // dump a colorbar image
    W = 10; H = 256;
    uImage = (unsigned char *)calloc( W*H, sizeof(unsigned char) );
    for ( w=0; w<W; w++ ){
        for ( h=0; h<H; h++ ) {
            *(uImage + W*(H-1-h) + w) = h;
        }
    }
    sprintf( Filename, "%s_Bar.gif", FilenameBase);
    fp_gif = fopen(Filename, "w");
    WriteGIF(fp_gif, (byte *)uImage, 0, W, H, Rainbow3_Red, Rainbow3_Grn, Rainbow3_Blu, 256, 0, "");
    fclose(fp_gif);
    free( uImage );

}


