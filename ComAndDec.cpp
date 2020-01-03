#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <locale.h>
#include"huffmancode.h"
#include"huffmanrecode.h"
#define MAXSIZE 1024



typedef unsigned char  unit8;
typedef unsigned short unit16;typedef unsigned int   unit32;
typedef unsigned char unit1G[MAXSIZE];

struct header
{
	unit8 magic[4];//PAC\0
	unit32 num;//记录文件数量
	unit32 mode;//用于储存模式
}por_header;

unit1G buf;
void compress(char* fname) {
	FILE *src, *dst;
	unit8* udata, * cdata, dstname[200];
		
	unsigned long size=0;
	src = fopen(fname, "rb");
	if (src==NULL) {
		printf("文件打开失败\n");
		exit(0);
	}
	udata = (unit8*)malloc(MAXSIZE);
	size = fread(udata, 1, MAXSIZE, src);
	cdata = (unit8*)malloc(size);
	sprintf((char*)dstname, "%s.por", fname);
	dst = fopen((char*)dstname, "wb");
		huffman_compress(cdata,&size,udata,0);
		fwrite(cdata,size,1, dst);
		fwrite(&size, 1, 4, dst);
		free(cdata);
		free(udata);
		fclose(dst);

}
void uncompress(char* fname) {
	FILE* src, * dst;
	unit8* udata, * cdata, dstname[200];
	unit32 size;
	src = fopen(fname, "rb");
	sprintf((char*)dstname,fname);
	size=fread(udata,MAXSIZE,1,src);
	fseek(src,  size, SEEK_SET);
	cdata = (unit8*)malloc(size);
	fread(cdata, size, 1, src);
	huffman_uncompress(udata, 0, cdata,size );
	dst = fopen((char*)dstname, "wb");
	fwrite(udata, size,1, dst);
	free(cdata);
	free(udata);
	fclose(dst);

}
int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "chs");
	printf("project：哈夫曼解压与压缩。\n用于解包本程序的par文件。\n将par文件拖到程序上解压。\n或将其他文件拖到程序上压缩\nby 卑微的二人小组 2020.1.02\n\n");
	
	
	int a;
	switch (a)
	{
	case 1:compress(argv[1]);break;
	case 2:uncompress(argv[1]);break;
	default:
		break;
	}
	printf("已完成\n");
	system("pause");
	return 0;}