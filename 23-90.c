#include <stdio.h>

int main(int argc, char **argv) {
    char pgmType[1000];
    int readWidth, readHeight;
    int writeWidth, writeHeight;
    int colorValue;
    int readPixels[1024][768];
    int writePixels[768][1024];

    //読み込み
    FILE *readFp = fopen(argv[1], "r");
    fscanf(readFp,"%s",pgmType);
    fscanf(readFp,"%d %d", &readWidth,&readHeight);
    fscanf(readFp,"%d", &colorValue);
    for ( int y = 0; y < readHeight; y++ ){
        for ( int x = 0; x < readWidth; x++ ){
            fscanf(readFp,"%d",&readPixels[x][y]);
        }
    }
    fclose(readFp);

    //処理
    writeWidth = readHeight;
    writeHeight = readWidth;
    for( int y = 0; y < readHeight; y++ ){
        for ( int x = 0; x < readWidth; x++ ){
            writePixels[y][x] = readPixels[x][readHeight - y - 1];
        }
    }

    //書き込み
    FILE *writeFp = fopen(argv[2],"w");
    fprintf(writeFp, "%s\n%d %d\n%d\n", pgmType,writeWidth,writeHeight,colorValue);
    for (int y = 0; y < writeHeight; y++) {
        for (int x = 0; x < writeWidth; x++) {
            fprintf(writeFp,"%d ",writePixels[x][y]);
        }
    }
    return 0;
}