//汉字编码格式为UTF-8,汉字编码格式不匹配会造成乱码
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
//设置用户输入的字符串以获得对应的命令,35是大于2的任意数
char string[35];
//二维数组的行和列
int row = 0, col = 0;    
int map[1000][1000];
int main()
{
    //声明并调用欢迎函数
    void printWelcome();
    //声明接收用户输入的字符串的函数
    void receiveString();
    //声明开始生命游戏的函数
    void startGame();
    //声明设计地图的函数
    void designMap();
    //声明用户手动更新函数
    void updateMap();
    //声明打印地图形式的函数
    void printMap();
    //声明退出游戏的函数
    void exitGame();
    //声明打印命令提示的函数
    void printOrder();
    //声明保存地图的函数
    void saveMap();
    //声明导入地图的函数
    void importMap();
    //打印欢迎界面
    printWelcome();
    while (true)
    {
        receiveString();
        if (string[0] == '\\' && string[1] == 'r'){
            startGame();
            continue;
        }
        if (string[0] == '\\' && string[1] == 'd'){
            designMap();
            printMap();
            printOrder();
            receiveString();
            continue;

        }
        if(string[0] == '\\' && string[1] == 'g'){
            updateMap();
            receiveString();
            continue;
        }
        if(string[0] == 'e' && string[1] == 'n' && string[2] == 'd'){
            exitGame();
            continue;
        }
        if(string[0] == '\\' && string[1] == 'h'){
            printOrder();
            continue;
        }
        if(string[0] == '\\' && string[1] == 'p'){
            printMap();
            continue;
        }
        if(string[0] == '\\' && string[1] == 's'){
            saveMap();
            printOrder();
            receiveString();
            continue;
        }
        if(string[0] == '\\' && string[1] == 'l'){
            importMap();
            printMap();
            printOrder();
            receiveString();
            continue;
        }
        printf("您的输入不合法,请重新输入:\n");
}
        return 0;
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
    printf("\t[\\h]\t打印命令提示\n");
    printf("\t[\\p]\t打印当前地图\n");
    printf("\t[\\l <filename]\t导入地图\n");
    printf("\t[\\s <filename]\t保存地图\n");
    printf("\t[\\d]\t进入地图设计模式\n");
    printf("\t[\\q]\t退出地图设计模式\n");
    printf("\t[\\g]\t生成下一代生命\n");
    printf("\t[\\r]\t开始生命游戏\n");
    printf("\t[\\e]\t停止生命游戏\n");
    printf("\t[end]\t退出生命游戏\n");
}

//接收用户输入的字符串的函数
void receiveString(){
    //用户从键盘输入的字符串
    scanf("%s", string);
    }


//用户选择"开始生命游戏"后的函数
void startGame(){
    //声明更新函数
    void updateMap();
    char instring[35];
    while(true){
        updateMap();
        printf("您已进入自动更新模式,输入\\e退出自动运行:\n");
        scanf("%s",instring);
        if(instring[0] == '\\' && instring[1] == 'e'){
            break;
        }
        Sleep(1500);
        system("cls");
    }
}

//设计地图的函数
void designMap(){
    int designRow, designCol;
    //声明函数
    void printMap();
    void printOrder();
    system("cls");
    int i, j;
    printf("请输入您要设计地图的行数:\n");
    scanf("%d", &row);
    printf("请输入您要设计地图的列数:\n");
    scanf("%d", &col);
    system("cls");
    //创建一个二维数组来给不同种子的生死状态加以记录
    map[row + 2][col + 2];
    for (i = 1; i < row + 1;i++){
        for (j = 1; j < col + 1;j++){
            map[i][j] = 0;
        }
    }
    printMap();
    //对要设计的存活细胞进行细胞输入
    while(true){
        
        printf("如果要退出地图设计模式,请依次输入9999和9999\n");
        printf("设置存活细胞:\n");
        printf("请输入第一个数据(行)\n");
        scanf("%d", &designRow);
        printf("请输入第二个数据(列)\n");
        scanf("%d", &designCol);
        if(designRow == 9999 && designCol == 9999){
            printf("您已退出地图设计模式");
            break;
        }
        else if((designRow > 0 && designRow <= row) && (designCol > 0 && designCol <= col)){
            map[designRow][designCol] = 1;
            system("cls");
            printMap();
        }
        else {
            printf("您输入的数据不合法,请重新输入\n");
        }
    }
    system("cls");
}

//玩家手动更新细胞图
void updateMap(){
    //声明打印地图形式的函数
    void printMap();
    system("cls");
    int i,j,count = 0;
    for (i = 1; i < row + 1; i++)
    {
        for (j = 1; j < col + 1; j++)
        {
            if(map[i-1][j-1] == 1){
                count++;
            }
            if(map[i-1][j] == 1){
                count++;
            }
            if(map[i-1][j+1] == 1){
                count++;
            }
            if(map[i][j-1] == 1){
                count++;
            }
            if(map[i][j+1] == 1){
                count++;
            }
            if(map[i+1][j-1] == 1){
                count++;
            }
            if(map[i+1][j] == 1){
                count++;
            }
            if(map[i+1][j+1] == 1){
                count++;
            }
            //count为周围存活细胞数目,接下来进行下一帧的刷新
            //当存活时:
            if(map[i][j] == 1){
                if(count < 2){
                    map[i][j] = 0;
                }
                else if(count == 2 || count == 3){
                    map[i][j] = 1;
                }
                else{
                    map[i][j] = 0;
                }
            }
            if(map[i][j] == 0){
                if(count == 3){
                    map[i][j] = 1;
                }
                else{
                    map[i][j] = 0;
                }
            }
        }
    }
    printMap();
}

//打印命令提示的函数
void printOrder(){
    printf("\t[\\h]\t打印命令提示\n");
    printf("\t[\\p]\t打印当前地图\n");
    printf("\t[\\l <filename]\t导入地图\n");
    printf("\t[\\s <filename]\t保存地图\n");
    printf("\t[\\d]\t进入地图设计模式\n");
    printf("\t[\\q]\t退出地图设计模式\n");
    printf("\t[\\g]\t生成下一代生命\n");
    printf("\t[\\r]\t开始生命游戏\n");
    printf("\t[\\e]\t停止生命游戏\n");
    printf("\t[end]\t退出生命游戏\n");
}

//输出当前地图形式的函数
void printMap(){
    system("cls");
    int i, j;
    for(i = 1;i < row + 1;i++){
		for(j = 1;j < col +1;j++){
			if(map[i][j] == 0){
				printf("□");
			}
			else{
				printf("■") ;
			}
			}
			printf("\n");
		}
}

//用户输入end后退出游戏的函数
void exitGame(){
    system("cls");
    printf("您已退出游戏,感谢使用!");
    exit(1);
}

//用户保存地图生成txt文件的函数
void saveMap(){
    char filename[53];
    int i, j;
    printf("请输入您要保存的地图名称(包括文件后缀名,空格请用下划线代替)\n举例:1.txt\n");
    scanf("%s", filename);
    FILE *fp = NULL;
    fp = fopen(filename, "w+");
    fprintf(fp,"%d %d\n", row, col);
    for(i = 1;i < row + 1;i++){
		for(j = 1;j < col +1;j++){
            fprintf(fp,"%d ", map[i][j]);
            }
        fprintf(fp, "\n");
        }
        //此处必须要关闭输出流
        fclose(fp);
}

//用户导入地图的函数
void importMap(){
    char filename[53];
    int i, j;
    FILE *fp = NULL;
    while(1){
    printf("请输入您要导入的地图名称(包括文件后缀名,空格请用下划线代替)\n举例:1.txt):\n");
    scanf("%s", filename);
    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("未找到文件,请重新输入:\n");
    }
    else{
        break;
    }
    }
    fscanf(fp, "%d", &row);
    fscanf(fp, "%d", &col);
    for(i = 1;i < row + 1;i++){
		for(j = 1;j < col +1;j++){
            fscanf(fp,"%d", &map[i][j]);
            }
        }
        //此处必须要关闭输出流
        fclose(fp);    
}

//在sleep中无法输入回车后调出循环