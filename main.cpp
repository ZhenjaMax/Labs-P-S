#include <iostream>
#include <cstring>
#include <getopt.h>

#define ERR_NO_FILE "[BMP] Error! Please, choose an image.\n"
#define ERR_FILE "[BMP] Error! An error occurred while processing the image.\n"
#define ERR_FEW_ARGS "[BMP] Error! Not enough arguments. Please, use -h for help.\n"
#define ERR_SAME_ARGS "[BMP] Error! There are more than one argument of same type.\n"
#define ERR_WRONG_ARGS "[BMP] Error! Incorrect arguments. Use -h for help.\n"
#define WARNING_COLOR "[BMP] Warning! Incorrect argument of color. Set the default color to black.\n"
#define WARNING_SAVE "[BMP] Warning! No arguments for save. Set the default out.bmp.\n"
#define WARNING_NO_SPACE "[BMP] Warning! Not enough space for paste. Some data will be lost.\n"

using namespace std;

#pragma pack (push, 1)
typedef struct{
    unsigned short signature;
    unsigned int sizeFile;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset;
}BMPFileHeader;
typedef struct{
    unsigned int sizeHeader;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bitPerPixel;
    unsigned int compression;
    unsigned int sizeImage;
    unsigned int xPerMeter;
    unsigned int yPerMeter;
    unsigned int colorTable;
    unsigned int colorCount;
}BMPInfoHeader;
typedef struct{
    unsigned char B;
    unsigned char G;
    unsigned char R;
}Pixel;
#pragma pack (pop)
typedef struct{
    int x;
    int y;
}Point;

class Parameters{
public:
    char loadFile[256] = {'\0'};
    bool loadFileF = 0;
    char saveFile[256] = "out.bmp";
    bool saveFileF = 0;
    bool infoF = 0;
    int queue[8] = {0};

    bool circleF = 0;
    int circleType = 0;
    Point circleA;
    Point circleB;
    Point circleO;
    int circleRadius = 0;
    int circleThickness = 0;
    bool circleColorCircleF = 0;
    Pixel circleColorCircle = {0, 0, 0};
    bool circleColorFillF = 0;
    Pixel circleColorFill = {0, 0, 0};

    bool copyF = 0;
    Point copyA;
    Point copyB;
    Point copyC;

    bool mirrorF = 0;
    Point mirrorA;
    Point mirrorB;
    int mirrorType = 0;

    void queueAdd(int n){
        for(int i=0; i<8; i++) if(queue[i]==0){
            queue[i] = n;
            return;
        }
    }
};

class BMPImage{
private:
    BMPFileHeader BFH;
    BMPInfoHeader BIH;
    Pixel** PixelArray = NULL;
    char filename[256];
public:
    ~BMPImage(){
        if(PixelArray!=NULL){
            for(int i=0; i<(int)BIH.height; i++) if (PixelArray[i] != NULL) free(PixelArray[i]);
            free(PixelArray);
        }
    }
    int checkHeader(){
        if ((BFH.signature != 0x4d42) && (BFH.signature != 0x4349) && (BFH.signature != 0x5450)) return 1;
        if (BIH.bitPerPixel != 24) return 1;
        if (BIH.compression != 0) return 1;
        if ((BIH.width > 8192) || (BIH.height > 8192)) return 2;
        return 0;
    }
    int checkPoint(Point A){
        if( (A.x < 0) || (A.y < 0) || (A.x >= (int)BIH.width) || (A.y >= (int)BIH.height) ) return 1;
        return 0;
    }
    void load(const char* name){
        strcpy(filename, name);
        FILE *f = fopen(filename, "rb");
        if(f == NULL){
            printf("[BMP] Error! Unable to open file %s.\n", filename);
            exit(1);
        }
        fread(&BFH, sizeof(BMPFileHeader), 1, f);
        fread(&BIH, sizeof(BMPInfoHeader), 1, f);
        if(checkHeader()==1){
            printf("[BMP] Error! Wrong version of file.\n");
            exit(1);
        } else if(checkHeader()==2){
            printf("[BMP] Error! Resolution of current file is too large! (%u x %x)\n", BIH.width, BIH.height);
            exit(1);
        }
        if(fseek(f, BFH.offset, SEEK_SET)!=0){
            printf(ERR_FILE);
            exit(1);
        }

        int padding = BIH.width%4;
        unsigned char* temp;
        if(padding) temp = (unsigned char*)malloc(padding*sizeof(unsigned char));

        if((PixelArray = (Pixel**)malloc(BIH.height*sizeof(Pixel*))) == NULL){
            printf(ERR_FILE);
            exit(1);
        }
        for(int i=0; i<(int)BIH.height; i++) if((PixelArray[i] = (Pixel*)malloc(BIH.width*sizeof(Pixel))) == 0){
            printf(ERR_FILE);
            exit(1);
        };
        for(int i=BIH.height-1; i>=0; i--){
            if(fread(PixelArray[i], sizeof(Pixel), BIH.width, f) != BIH.width){
                printf(ERR_FILE);
                exit(1);  
            }
            if(padding) fread(temp, sizeof(unsigned char), padding, f);
        }
        free(temp);
        fclose(f);
        printf("[BMP] File %s opened successfully.\n", filename);
        return;
    }
    void info(){
        printf("\n[BMP] Name:\t\t%s\n", filename);
        printf("[BMP] Signature:\t%x\n", BFH.signature);
        printf("[BMP] Size:\t\t%u bytes\n", BFH.sizeFile);
        printf("[BMP] Resolution:\t%u x %u\n", BIH.width, BIH.height);
        printf("[BMP] Bits per pixel:\t%u\n\n", BIH.bitPerPixel);
        return;
    }
    Pixel getColor(char* color){
        if(!strcmp(color, "red")) return {0, 0, 255};
        if(!strcmp(color, "orange")) return {0, 127, 255};
        if(!strcmp(color, "yellow")) return {0, 255, 255};
        if(!strcmp(color, "lime")) return {0, 255, 127};
        if(!strcmp(color, "green")) return {0, 255, 0};
        if(!strcmp(color, "turquoise")) return {127, 255, 0};
        if(!strcmp(color, "aqua")) return {255, 255, 0};
        if(!strcmp(color, "blue")) return {255, 0, 0};
        if(!strcmp(color, "purple")) return {255, 0, 127};
        if(!strcmp(color, "pink")) return {127, 63, 255};
        if(!strcmp(color, "brown")) return {0, 63, 127};
        if(!strcmp(color, "white")) return {255, 255, 255};
        if(!strcmp(color, "grey")) return {127, 127, 127};
        if(!strcmp(color, "black")) return {0, 0, 0};
        printf(WARNING_COLOR);
        return {0, 0, 0};
    }
    void drawCircle(Point O, int R, int thickness, Pixel colorCircle, int fillF, Pixel colorFill){
        int dx, dy, d, error;
        bool xmax, xmin, ymax, ymin, ymax1, ymin1;
        int thicknessIter = thickness;
        for(; thicknessIter>0; thicknessIter--){
            dx = 0;
            dy = R;
            d = 1 - 2*R;
            error = 0;
            while(dy>=0){
                xmax = O.x+dx<(int)BIH.width;
                xmin = O.x-dx>=0;
                ymax = O.y+dy<(int)BIH.height;
                ymin = O.y-dy>=0;
                ymax1 = O.y+dy+1<(int)BIH.height;
                ymin1 = O.y-dy-1>=0;
                if((ymax)&&(xmax)) PixelArray[O.y+dy][O.x+dx] = colorCircle;
                if((ymax)&&(xmin)) PixelArray[O.y+dy][O.x-dx] = colorCircle;
                if((ymin)&&(xmax)) PixelArray[O.y-dy][O.x+dx] = colorCircle;
                if((ymin)&&(xmin)) PixelArray[O.y-dy][O.x-dx] = colorCircle;
                if(thicknessIter != thickness){
                    if((ymax1)&&(xmax)) PixelArray[O.y+dy+1][O.x+dx] = colorCircle;
                    if((ymax1)&&(xmin)) PixelArray[O.y+dy+1][O.x-dx] = colorCircle;
                    if((ymin1)&&(xmax)) PixelArray[O.y-dy-1][O.x+dx] = colorCircle;
                    if((ymin1)&&(xmin)) PixelArray[O.y-dy-1][O.x-dx] = colorCircle;
                }
                if((fillF)&&(thicknessIter==1)) for(int i=O.y-dy+1; i<O.y+dy; i++){
                    if(i<0) continue;
                    if(i>=(int)BIH.height) break;
                    if(xmin) PixelArray[i][O.x-dx] = colorFill;
                    if(xmax) PixelArray[i][O.x+dx] = colorFill;
                }
                error = 2*(d+dy)-1;
                if((d<0)&&(error<0)){
                    d+=(2*++dx + 1);
                    continue;
                }
                if((d>0)&&(error>0)){
                    d-=(2*--dy + 1);
                    continue;
                }
                d += 2*(++dx - --dy);
            }
            R--;
        }
        return;
    }
    void copy(Point O1, Point O2, Point O3){
        Pixel tempPixelArray[O2.y-O1.y+1][O2.x-O1.x+1];
        for(int i=0; i<=O2.y-O1.y; i++) for(int j=0; j<=O2.x-O1.x; j++) tempPixelArray[i][j] = PixelArray[i+O1.y][j+O1.x];
        for(int i=0; i<=O2.y-O1.y; i++) for(int j=0; j<=O2.x-O1.x; j++){
            if(O3.y+i>=(int)BIH.height) break;
            if(O3.x+j>=(int)BIH.width) continue;
            PixelArray[O3.y+i][O3.x+j] = tempPixelArray[i][j];
        }
        if((O2.y-O1.y+O3.y>=(int)BIH.height)||(O2.x-O1.x+O3.x>=(int)BIH.width)) printf(WARNING_NO_SPACE);
        return;
    }
    void mirror(Point O1, Point O2, int type){
        Pixel temp;
        if(type == 1){                                                              //horizontally
            for(int i=O1.y; i<=O2.y; i++) for(int j=O1.x; j<(O1.x+O2.x)/2; j++){
                temp = PixelArray[i][j];
                PixelArray[i][j] = PixelArray[i][O1.x+O2.x-j];
                PixelArray[i][O1.x+O2.x-j] = temp;
            }
        } else if(type == 2){                                                       // verically
            for(int j=O1.x; j<=O2.x; j++) for(int i=O1.y; i<(O1.y+O2.y)/2; i++){
                temp = PixelArray[i][j];
                PixelArray[i][j] = PixelArray[O1.y+O2.y-i][j];
                PixelArray[O1.y+O2.y-i][j] = temp;
            }
        }
        return;
    }
    void save(const char* name){
        FILE *f = fopen(name, "wb");
        if(f == NULL){
            printf(ERR_FILE);
            exit(1);
        }

        fwrite(&BFH, sizeof(BMPFileHeader), 1, f);
        fwrite(&BIH, sizeof(BMPInfoHeader), 1, f);

        int padding = BIH.width%4;
        unsigned char* temp;
        if(padding) temp = (unsigned char*)calloc(padding, sizeof(unsigned char));

        fseek(f, BFH.offset, SEEK_SET);
        for(int i=0; i<(int)BIH.height; i++){
            fwrite(PixelArray[BIH.height-1-i], sizeof(Pixel), BIH.width, f);
            if(padding) fwrite(temp, sizeof(unsigned char), padding, f);
        }

        fclose(f);
        printf("[BMP] File successfully saved as %s.\n", name);
        return;
    }

    void help(){
        printf("[BMP] --load|-l <filename>, --save|-s <filename> - load or save BMP image.\n");
        printf("[BMP] --info|-i - show information about BMP image.\n");
        printf("[BMP] --circle <x1,y1>|<x2,y2,x3,y3> - draw circle centered at x1,y1 or inscribed in square at x2,y2,x3,y3. Centered circle don't requires radius.\n");
        printf("[BMP] --radius|-r <R> - set radius R of centered circle; --thickness|-t <T> - set thickness T of circle.\n");
        printf("[BMP] --color|-c <color> - set color of circle; --fill|-f <color> - set color of filling, optional.\n");
        printf("[BMP] Available colors: red, orange, yellow, lime, green, turquoise, aqua, blue, purple, pink, brown, white, gray, black.\n");
        printf("[BMP] --mirror <x1,y1,x2,y2> - mirror part of image at x1,y1,x2,y2.\n");
        printf("[BMP] --axis|-a h|v - type of mirror (horizontally or vertically).\n");
        printf("[BMP] --copy <x1,y1,x2,y2,x3,y3> - copy part of image from x1,y1,x2,y2 to x3,y3.\n");
        printf("[BMP] --help|h - show this message. Use this key standalone.\n\n");
        return;
    }
};

int main(int argc, char* argv[]){
    BMPImage BMP;
    Parameters parameters;
	int opt;
	int longIndex;
    char* pointCoordsRaw;
    int pointCoords[6] = {0};
	const char opts[] = "l:s:hir:t:c:f:a:";
    struct option longOpts[]={
        {"load", required_argument, NULL, 'l'},
        {"save", required_argument, NULL, 's'},
        {"help", no_argument, NULL, 'h'},
        {"info", no_argument, NULL, 'i'},
        {"radius", required_argument, NULL, 'r'},
        {"thickness", required_argument, NULL, 't'},
        {"color", required_argument, NULL, 'c'},
        {"fill", required_argument, NULL, 'f'},
        {"axis", required_argument, NULL, 'a'},
	    {"circle", required_argument, NULL, 1},
	    {"mirror", required_argument, NULL, 2},
	    {"copy", required_argument, NULL, 3},
	    {NULL, 0, NULL, 0}
    };
    opterr = 0;

    if(argc==1){
        printf(ERR_FEW_ARGS);
        return 1;
    }

	while((opt = getopt_long(argc, argv, opts, longOpts, &longIndex))!=-1){
		switch(opt){
			case 'l':
                if(parameters.loadFileF){
                    printf(ERR_SAME_ARGS);
                    return 1;
                }
				parameters.loadFileF = 1;
                strcpy(parameters.loadFile, optarg);
				break;
			case 's':
                if(parameters.saveFileF){
                    printf(ERR_SAME_ARGS);
                    return 1;
                }
                parameters.saveFileF = 1;
                strcpy(parameters.saveFile, optarg);
				break;
			case 'h':
				BMP.help();
				break;
			case 'i':
				parameters.infoF = 1;
				break;
			case 'r':
				if( ((atoi(optarg)==0)&&(optarg[0]!='0')) || parameters.circleRadius || (atoi(optarg)<0) ){
				    printf(ERR_WRONG_ARGS);
                    return 1;
                }
                parameters.circleRadius = atoi(optarg);
				break;
			case 't':
				if( ((atoi(optarg)==0)&&(optarg[0]!='0')) || (atoi(optarg)<0) ){
				    printf(ERR_WRONG_ARGS);
                    return 1;
                }
                parameters.circleThickness = atoi(optarg);
				break;
			case 'c':
                if(parameters.circleColorCircleF){
                    printf(ERR_SAME_ARGS);
                    return 1;
                }
                parameters.circleColorCircleF = 1;
				parameters.circleColorCircle = BMP.getColor(optarg);
				break;
			case 'f':
                if(parameters.circleColorFillF){
                    printf(ERR_SAME_ARGS);
                    return 1;
                }
                parameters.circleColorFillF = 1;
				parameters.circleColorFill = BMP.getColor(optarg);
				break;
			case 'a':
                if(parameters.mirrorType){
                    printf(ERR_SAME_ARGS);
                    return 1;
                }
                if(!strcmp(optarg, "h")) parameters.mirrorType = 1;
                else if (!strcmp(optarg, "v")) parameters.mirrorType = 2;
                else{
                    printf(ERR_WRONG_ARGS);
				    return 1;
                }
				break;
			case 1:
				if(parameters.circleF){
                    printf(ERR_SAME_ARGS);
                    return 1;
                }
                parameters.circleF = 1;
                pointCoordsRaw = strtok(optarg, ",");
                for(int i=0; i<2; i++){
                    if( (pointCoordsRaw==NULL) || ((atoi(pointCoordsRaw)==0)&&(pointCoordsRaw[0]!='0')) ){
                        printf(ERR_WRONG_ARGS);
				        return 1;
                    }
                    pointCoords[i] = atoi(pointCoordsRaw);
                    pointCoordsRaw = strtok(NULL, ",");
                }
                parameters.circleType = 1;
                if(pointCoordsRaw!=NULL){
                    for(int i=2; i<4; i++){
                        if( (pointCoordsRaw==NULL) || ((atoi(pointCoordsRaw)==0)&&(pointCoordsRaw[0]!='0')) ){
                            printf(ERR_WRONG_ARGS);
				            return 1;
                        }
                        pointCoords[i] = atoi(pointCoordsRaw);
                        pointCoordsRaw = strtok(NULL, ",");
                    }
                    parameters.circleType = 2;
                }
                if(parameters.circleType==1){
                    parameters.circleO = {pointCoords[0], pointCoords[1]};
                    if( pointCoordsRaw!=NULL ){
                        printf(ERR_WRONG_ARGS);
				        return 1;
                    }
                }else{
                    parameters.circleA = {pointCoords[0], pointCoords[1]};
                    parameters.circleB = {pointCoords[2], pointCoords[3]};
                    if( (pointCoordsRaw!=NULL) || (parameters.circleA.x > parameters.circleB.x) || (parameters.circleA.y > parameters.circleB.y) || parameters.circleRadius ){
                        printf(ERR_WRONG_ARGS);
				        return 1;
                    }
                    if(parameters.circleB.x - parameters.circleA.x != parameters.circleB.y - parameters.circleA.y){
                        printf(ERR_WRONG_ARGS);
                        return 1;
                    }
                    parameters.circleRadius = (parameters.circleB.x - parameters.circleA.x) / 2;
                    parameters.circleO = {(parameters.circleB.x + parameters.circleA.x)/2, (parameters.circleB.y + parameters.circleA.y)/2};
                }
                parameters.queueAdd(1);
				break;

			case 2:
				if(parameters.mirrorF){
                    printf(ERR_SAME_ARGS);
                    return 1;
                }
                parameters.mirrorF = 1;
                pointCoordsRaw = strtok(optarg, ",");
                for(int i=0; i<4; i++){
                    if( (pointCoordsRaw==NULL) || ((atoi(pointCoordsRaw)==0)&&(pointCoordsRaw[0]!='0')) ){
                        printf(ERR_WRONG_ARGS);
				        return 1;
                    }
                    pointCoords[i] = atoi(pointCoordsRaw);
                    pointCoordsRaw = strtok(NULL, ",");
                }
                parameters.mirrorA = {pointCoords[0], pointCoords[1]};
                parameters.mirrorB = {pointCoords[2], pointCoords[3]};
                if( (pointCoordsRaw!=NULL) || (parameters.mirrorA.x > parameters.mirrorB.x) || (parameters.mirrorA.y > parameters.mirrorB.y) ){
                    printf(ERR_WRONG_ARGS);
				    return 1;
                }
            	parameters.queueAdd(2);
				break;

			case 3:
				if(parameters.copyF){
                    printf(ERR_SAME_ARGS);
                    return 1;
                }
                parameters.copyF = 1;
                pointCoordsRaw = strtok(optarg, ",");
                for(int i=0; i<6; i++){
                    if( (pointCoordsRaw==NULL) || ((atoi(pointCoordsRaw)==0)&&(pointCoordsRaw[0]!='0')) ){
                        printf(ERR_WRONG_ARGS);
				        return 1;
                    }
                    pointCoords[i] = atoi(pointCoordsRaw);
                    pointCoordsRaw = strtok(NULL, ",");
                }
                parameters.copyA = {pointCoords[0], pointCoords[1]};
                parameters.copyB = {pointCoords[2], pointCoords[3]};
                parameters.copyC = {pointCoords[4], pointCoords[5]};
                if( (pointCoordsRaw!=NULL) || (parameters.copyA.x > parameters.copyB.x) || (parameters.copyA.y > parameters.copyB.y) ){
                    printf(ERR_WRONG_ARGS);
				    return 1;
                }
				parameters.queueAdd(3);
				break;
			case '?':
				printf(ERR_WRONG_ARGS);
				return 1;
		}
	}
    if(parameters.loadFileF == 0){ 
        printf(ERR_NO_FILE);
        return 1;
    }
    BMP.load(parameters.loadFile);
    if(parameters.infoF) BMP.info();
    for(int i=0; i<8; i++){
        switch(parameters.queue[i]){
            case 0:
                break;
            case 1:
                if( (parameters.circleRadius < parameters.circleThickness) || BMP.checkPoint(parameters.circleO) || (parameters.circleThickness == 0) || (parameters.circleRadius == 0) ){
                    printf(ERR_WRONG_ARGS);
				    return 1;
                }
                BMP.drawCircle(parameters.circleO, parameters.circleRadius, parameters.circleThickness, parameters.circleColorCircle, parameters.circleColorFillF, parameters.circleColorFill);
                printf("[BMP] Drawing circle in point %d,%d...\n", parameters.circleO.x, parameters.circleO.y);
                break;
            case 2:
                if( (BMP.checkPoint(parameters.mirrorA)) || (BMP.checkPoint(parameters.mirrorB)) || (parameters.mirrorType == 0) ){
                    printf(ERR_WRONG_ARGS);
				    return 1;
                }
                BMP.mirror(parameters.mirrorA, parameters.mirrorB, parameters.mirrorType);
                printf("[BMP] Mirror image inside points %d,%d %d,%d...\n", parameters.mirrorA.x, parameters.mirrorA.y, parameters.mirrorB.x, parameters.mirrorB.y);
                break;
            case 3:
                if ( BMP.checkPoint(parameters.copyA) || BMP.checkPoint(parameters.copyB) || BMP.checkPoint(parameters.copyC) ){
                    printf(ERR_WRONG_ARGS);
				    return 1;
                }
                BMP.copy(parameters.copyA, parameters.copyB, parameters.copyC);
                printf("[BMP] Copy image inside points %d,%d %d,%d to %d,%d...\n", parameters.copyA.x, parameters.copyA.y, parameters.copyB.x, parameters.copyB.y, parameters.copyC.x, parameters.copyC.y);
                break;
        }
    }
    if( (parameters.saveFileF == 0) && (parameters.queue[0] == 0) ) return 0;
    if(parameters.saveFileF == 0) printf(WARNING_SAVE);
    BMP.save(parameters.saveFile);
    return 0;
}