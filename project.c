//charset : utf8  environment : vscode

//库函数
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h> 

//宏定义
#define HELP "\\h"
#define LOAD "\\l"
#define SAVE "\\s"
#define DESIGN "\\d"
#define GENERATE "\\g"
#define RUN "\\r"
#define EXIT "\\e"
#define QUIT "\\q"
#define PRINT "\\p"
#define END "end"

//全局变量的定义
char order[35];
int row = 0, col = 0;
int map[1000][1000];
char filename[35];
bool ifDesign = false;

//用到的函数的声明
void printWelcome();
void printOrder();
void receiveOrder();
void importMap();
void printMap(char* c);
void designMap();
void saveMap();
int countAliveNeighbors(int map[1000][1000], int x, int y);
void updateMap(int map[1000][1000]);
void exitGame();
void runMap();

//主函数入口
int main(){
    //打印欢迎界面
    printWelcome();
    printOrder();
    //开始进入命令循环
    while(true){
        //获取用户输入的命令
        receiveOrder();
        //获取命令帮助
        if(strcmp(order,HELP) == 0){
            system("cls");
            printOrder();
            continue;
        }
        //加载本地地图
        else if(strcmp(order,LOAD) == 0){
            system("cls");
            importMap();
            system("cls");
            printMap(filename);
            continue;
        }
        //打印当前地图
        else if(strcmp(order,PRINT) == 0){
        	if(strlen(filename) == 0){
        		printf("还未存有地图,请导入地图(\\l)或者自定义地图(\\d).\n"); 
			}
			else{ 
	            system("cls");
	            printMap(filename);
	            continue;
            } 
        }
        //进入设计地图模式
        else if(strcmp(order,DESIGN) == 0){
            system("cls");
            designMap();
            continue;
        }
        //将当前地图保存为本地地图
        else if(strcmp(order,SAVE) == 0){
            saveMap();
            continue;
        }
        //手动生成下一代细胞
        else if(strcmp(order,GENERATE) == 0){
            updateMap(map);
            system("cls");
            printMap(filename);
            continue;
        }
        //自动运行细胞更新
        else if(strcmp(order,RUN) == 0){
            runMap();
            continue;
        }
        //退出声明游戏
        else if(strcmp(order,EXIT) == 0){
            system("cls");
            printf("未进入自动生成模式! (使用 \\h 查看有效输入)\n");
            continue;
		}
        //结束自动运行细胞更新
		else if(strcmp(order,END) == 0){
			exitGame();
            continue;
		}
        //结束自定义地图
		else if(strcmp(order,QUIT) == 0){
			if(ifDesign == false){
                system("cls");
                printf("未进入地图设计模式! (使用 \\h 查看有效输入)\n"); 
			}
            continue;
		}
        //用户输入不合法输入
        printf("未知输入 (使用 \\h 查看有效输入)\n");
    }
    return 0;
}

//获取命令输入的函数
void receiveOrder(){
    printf("$ ");
    scanf("%s",order); 
}

//打印欢迎界面的函数
void printWelcome(){
    printf("*********************************************\n"); 
    printf("*********************************************\n\n");
    printf("\t生\t命\t游\t戏\n\n");
    printf("\t\t 欢迎来到生命游戏\n");
    printf("\t在这里您将体会到元胞自动机的乐趣\n\n");
    printf("\t\t准备好了吗?\n\n");
    printf("*********************************************\n"); 
    printf("*********************************************\n");
}

//打印命令提示的函数
void printOrder(){
    printf("\t[\\h]\t打印命令提示\n");
    printf("\t[\\p]\t打印当前地图\n");
    printf("\t[\\l]\t导入地图\n");
    printf("\t[\\s]\t保存地图\n");
    printf("\t[\\d]\t进入地图设计模式\n");
    printf("\t[\\q]\t退出地图设计模式\n");
    printf("\t[\\g]\t生成下一代生命\n");
    printf("\t[\\r]\t开始生命游戏\n");
    printf("\t[\\e]\t停止生命游戏\n");
    printf("\t[end]\t退出生命游戏\n");
}

//用户导入地图的函数
void importMap(){
    FILE *fp = NULL;
    //获取文件
    while(true){
        printf("请输入您要导入的地图名称(包括文件后缀名,空格请用下划线代替)\n举例:1.txt):\n");
        scanf("%s",filename);
        fp = fopen(filename, "r");
        if(fp == NULL){
            printf("未找到文件,请重新输入:\n");
        }
        else{
            break;
        }
    }
    //将地图数据导入地图数组
    fscanf(fp, "%d", &row);
    fscanf(fp, "%d", &col);
    for(int i = 0;i < row;i++){
		for(int j = 0;j < col;j++){
            fscanf(fp,"%d", &map[i][j]);
        }
    }
    //此处必须要关闭输出流
    fclose(fp);    
}

//输出当前地图形式的函数
void printMap(char filename[35]){
    //提醒读取文件的位置的输出方式
    if(filename[0] != ' '){
       printf("读取自<%s>\n", filename);
       for(int i = 0;i < row; i++){
            for(int j = 0;j < col; j++){
                if(map[i][j] == 0){
                    printf("□ ");
                }
                else{
                    printf("■ ") ;
                }
            }
            printf("\n");
        }
        filename[0] = ' ';
    }
    //不提醒读取文件的位置的输出方式
    else{
        for(int i = 0;i < row; i++){
            for(int j = 0;j < col; j++){
                if(map[i][j] == 0){
                    printf("□ ");
                }
                else{
                    printf("■ ") ;
                }
            }
            printf("\n");
        }
    }
}

//设计地图的函数
void designMap(){
    system("cls");
    printf(">进入自定义地图模式<\n");
    ifDesign = true;
    //防止用户输入的数据超过地图数组的边界
    while(true){
    	printf("请输入您要设计地图的行数:\n");
	    scanf("%d", &row);
	    printf("请输入您要设计地图的列数:\n");
	    scanf("%d", &col);
	    if((row>0 && row<1000) && (col>0 && col<1000)){
	    	break;
		}
		else{
			printf("输入的数据存在问题(行数和列数不得超过1000),请重新输入:\n"); 
		}
	}
    system("cls");
    //初始化自定义地图
    for (int i = 0; i < row;i++){
        for (int j = 0; j < col;j++){
            map[i][j] = 0;
        }
    }
    strcpy(filename, "自定义地图");
    printMap(filename);
    //对要设计的存活细胞进行细胞输入
    while(true){
        int designRow, designCol;
        char designRowStr[35];
        printf("如果要退出地图设计模式,请直接输入\\q\n");
        printf("设置存活细胞:\n");
        //行数据
        printf("请输入第一个数据(行):\n");
        scanf("%s", designRowStr);
        bool noEnglish = true;
        if(strcmp(designRowStr,QUIT) == 0 && ifDesign == true){
            printf("您已退出地图设计模式,请及时保存!\n");
            ifDesign = false; 
            break;
        }
        else{
            designRow = atoi(designRowStr);
            if(strlen(designRowStr) > 1 && designRow == 0){
                noEnglish = false;
            }
            else if(designRowStr[0] != '0' && designRow == 0){
                noEnglish = false;
            }
        }
        //列数据
        printf("请输入第二个数据(列):\n");
        scanf("%d", &designCol);
        //判断输入的数据是否合法
        if((designRow >= 0 && designRow < row) && (designCol >= 0 && designCol < col) && noEnglish == true){
            map[designRow][designCol] = 1;
            system("cls");
            printMap(filename);
        }
        else {
            printf("您输入的数据不合法,请重新输入:\n");
        }
    }
    printf("输入\\s 可以将自定义地图保存到本地\n");
}

//用户保存地图生成txt文件的函数
void saveMap(){
    char saveFilename[53];
    int i, j;
    //防止用户输入的地图名称不合法
    while(true){
    	printf("请输入您要保存的地图名称(包括文件后缀名,空格请用下划线代替)\n举例:1.txt\n");
    	scanf("%s", saveFilename);
    	if(saveFilename[strlen(saveFilename)-1] == 't' && saveFilename[strlen(saveFilename)-2] == 'x' && saveFilename[strlen(saveFilename)-3] == 't' && saveFilename[strlen(saveFilename)-4] == '.'){
    		break;
		} 
		else{
			printf("文件后缀名不合法,请重新输入:\n");
		}
	} 
    //将地图数组的数据写入地图文件
    FILE *fp = NULL;
    fp = fopen(saveFilename, "w+");
    fprintf(fp,"%d %d\n", row, col);
    for(i = 0;i < row;i++){
		for(j = 0;j < col;j++){
            fprintf(fp,"%d ", map[i][j]);
            }
        fprintf(fp, "\n");
        }
    //此处必须要关闭输出流
    if(fclose(fp) == 0){
        system("cls");
        printf("保存成功!<%s>\n",saveFilename);
    }
    else{
        printf("保存失败!\n");
    }
}

//计算单个细胞周围的存活细胞数目的函数
int countAliveNeighbors(int map[1000][1000], int x, int y){
    int count = 0;
    //计算细胞周围8个位置存活细胞的数量
    if(map[(x+col-1)%col][(y+row-1)%row] == 1){
        count++;
    }
    if(map[(x+row)%row][(y+col-1)%col] == 1){
        count++;
    }
    if(map[(x+row+1)%row][(y+col-1)%col] == 1){
        count++;
    }
    if(map[(x+row-1)%row][(y+col)%col] == 1){
        count++;
    }
    if(map[(x+row+1)%row][(y+col)%col] == 1){
        count++;
    }
    if(map[(x+row-1)%row][(y+col+1)%col] == 1){
        count++;
    }
    if(map[(x+row)%row][(y+col+1)%col] == 1){
        count++;
    }
    if(map[(x+row+1)%row][(y+col+1)%col] == 1){
        count++;
    }
    return count;
}

//更新地图的函数
void updateMap(int map[1000][1000]){
    //获取每个细胞周围存活细胞数
    int aliveNeighbors[row][col];
    for (int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            aliveNeighbors[i][j] = countAliveNeighbors(map, i, j);
        }
    }
    //将每个细胞按照规则进行演化
    for (int i = 0; i < row;i++){
        for (int j = 0; j < col;j++){
            if(map[i][j] == 1 && aliveNeighbors[i][j] < 2){
                map[i][j] = 0;
            }
            else if(map[i][j] == 1 && (aliveNeighbors[i][j] == 2 || aliveNeighbors[i][j] == 3)){
                map[i][j] = 1;
            }
            else if(map[i][j] == 1 && (aliveNeighbors[i][j] > 3)){
                map[i][j] = 0;
            }
            else if (map[i][j] == 0 && aliveNeighbors[i][j] == 3){
                map[i][j] = 1;
            }
            else{
                map[i][j] = 0;
            }
        }
    }
}

//用户输入end后退出游戏的函数
void exitGame(){
    system("cls");
    printf("您已退出游戏,感谢使用!\n");
    exit(1);
}

//自动更新细胞图的函数
void runMap(){
    while(true){
        //自动更新细胞图
        flag1 :system("cls");
        printf("按回车键暂停游戏\n"); 
        updateMap(map);
        printMap(filename);
        Sleep(500);
        //当输入回车时暂停
        if(kbhit() != 0){
            char ch1 = getch();
            if(ch1 == '\r'){
                printf("输入\\e停止生命游戏\n"); 
                while(true){
                    //当再次输入回车时就继续
                    char ch2 = getch();
                    if(ch2 == '\r'){
                        goto flag1;
                    }
                    //当输入\e时就退出自动更新
                    else if(ch2 == '\\'){
                        printf("%c",ch2);
                        char ch3 = getch();
                        printf("%c",ch3);
                        char ch4 = getch();
                        if(ch3 == 'e' && ch4 == '\r'){
                            goto flag2;
                        }
                        //防止用户输入不合法
                        else{
                            printf("输入不合法,请重新输入\n"); 
                        }
                    }
                    else{
                            printf("输入不合法,请重新输入\n"); 
                    }
                }
            }
        }
    } 
    flag2 :
        system("cls");
}