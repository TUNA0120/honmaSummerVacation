#include <stdio.h>

int leftPixels[1024][768], rightPixels[1024][768];
int writePixels[2048][768];

int main(int argc, char **argv) {
    char pgmType[1000];
    int leftWidth, leftHeight, rightWidth, rightHeight;
    int writeWidth, writeHeight;
    int colorValue;

    //読み込み
    FILE *readFp = fopen(argv[1], "r");
    fscanf(readFp,"%s",pgmType);
    fscanf(readFp,"%d %d", &leftWidth,&leftHeight);
    fscanf(readFp,"%d", &colorValue);
    for ( int y = 0; y < leftHeight; y++ ){
        for ( int x = 0; x < leftWidth; x++ ){
            fscanf(readFp,"%d",&leftPixels[x][y]);
        }
    }
    fclose(readFp);

    readFp = fopen(argv[2], "r");
    fscanf(readFp,"%s",pgmType);
    fscanf(readFp,"%d %d", &rightWidth,&rightHeight);
    fscanf(readFp,"%d", &colorValue);
    for ( int y = 0; y < rightHeight; y++ ){
        for ( int x = 0; x < rightWidth; x++ ){
            fscanf(readFp,"%d",&rightPixels[x][y]);
        }
    }
    fclose(readFp);

    //処理
    writeHeight = leftHeight > rightHeight ? leftHeight : rightHeight;
    writeWidth = leftWidth + rightWidth;
    for( int y = 0; y < writeHeight; y++ ){
        for ( int x = 0; x < leftWidth; x++ ){
            writePixels[x][y] = y < leftHeight ? leftPixels[x][y] : 0;
        }
        for ( int x = 0; x < rightWidth; x++ ){
            writePixels[leftWidth + x][y] = y < rightHeight ? rightPixels[x][y] : 0;
        }
    }

    //書き込み
    FILE *writeFp = fopen(argv[3],"w");
    fprintf(writeFp, "%s\n%d %d\n%d\n", pgmType,writeWidth,writeHeight,colorValue);
    for (int y = 0; y < writeHeight; y++) {
        for (int x = 0; x < writeWidth; x++) {
            fprintf(writeFp,"%d ",writePixels[x][y]);
        }
    }
    return 0;
}