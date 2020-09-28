//每个细胞的状态由该细胞和周围八个细胞的上一次的状态所决定
//如果一个细胞周围有三个细胞为生,则该细胞不论原先是生是死,都转为生状态
//如果一个细胞周围有两个细胞为生,则该细胞的生死状态保持不变
//在其他情况,不论细胞原先是生是死,都转为死状态
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
//该变量用于在循环中看是否终止程序 
static int c; 
//记录帧数 
static int count = 0; 


void nextFrame(int* a,int x,int y){
	int i,j;
	for(i = 1;i < x - 1;i++){
		for(j = 1;j < y - 1;j++){
			//将条件应用于这个数组的遍历以形成下一帧
			//记录周围的细胞有几个是活着的 
			int amount = 0;
			if(*(a + i*x + j - x -1) != 0){
				amount++; 
		}
			if(*(a + i*x + j - x) != 0){
				amount++;
			}
			if(*(a + i*x + j - x +1) != 0){
				amount++; 
		}
			if(*(a + i*x + j -1) != 0){
				amount++; 
		}
			if(*(a +i*x + j+1) != 0){
				amount++; 
		}
			if(*(a + i*x + j + x -1) != 0){
				amount++; 
		}
			if(*(a + i*x + j + x ) != 0){
				amount++; 
		}	
			if(*(a + i*x + j+x +1) != 0){
				amount++; 
		}
		//将三个生死规则带入运算,更改其中的下一帧数据 
		if(amount == 3){
			*(a + i*x + j) = 1;
		}
		else if(amount == 2){
			*(a + i*x + j) = *(a + i*x + j);
		}
		else{
			*(a + i*x + j) = 0;
		}
	}
	
}
}
int main(){
	int col,row,i,j;
	//给出交互UI界面
	int cho;
	printf("*********************************\n");
	printf("*********************************\n");
	printf("        生   命   游   戏\n\n");
	printf("          欢迎来到生命游戏\n");
	printf(" 在这里您将体会到元胞自动机的乐趣\n\n");
	printf("            准备好了吗\n\n");
	printf("*********************************\n");
	printf("*********************************\n\n\n\n\n\n\n");
	printf("开始游戏:请输入1\t退出游戏:请输入0:\n");
	while(1){
	scanf("%d",&cho);
	if(cho == 1){
		system("cls");
		break;
	}
	else if(cho == 0){
		exit(0);
	}
	else{
		printf("您输入的数据不合法,请重新输入:\n"); 
	}
}  
	//该变量用于控制行和列的数目以及行和列的循环控制 
	
	printf("请输入要进行游戏的行数:\n");
	scanf("%d",&row); 
	printf("请输入要进行游戏的列数:\n");
	scanf("%d",&col); 
	//创建一个二维数组来给不同种子的生死状态加以记录 
	int game[row + 2][col + 2];
	//以下变量用于生成随机数
	long now;
	//用时间来给随机数函数的种子进行清零 
	srand(time(&now));
	for(i = 0;i < row +2;i++){
		for(j = 0;j < col +2;j++){
			//尝试使用随机数来生成第一帧的细胞状态,并赋值给二维数组
			//利用扩边法使得边框的数是0 
			if(i == 0 || i == (row +1) || j == 0 || j == col + 1){
				game[i][j] = 0;
			}
			else{
				game[i][j] =  rand()%2; 
			}
		}
}
 	
	//将现在已有的细胞状态输出
	for(i = 1;i < row +1;i++){
		for(j = 1;j < col +1;j++){
			if(game[i][j] == 0){
				printf("□");
			}
			else{
				printf("■") ;
			}
		}
		printf("\n");
		}
	//输出当前是第几帧,并对是否进入下一帧进行交互 
	printf("\n 当前是第%d帧,输入0退出程序,输入1查看下一帧:\n",++count);
	while(1){
	scanf("%d",&c);
	if(c == 0){
		exit(0);
	}
	else if(c == 1){
		
	system("cls");
	break; 
}
	else{
		printf("您输入的数据不合法,请重新输入:"); 
	}
}
	while(1){
		nextFrame(game,row+2,col+2);
	//将现在已有的细胞状态输出
	for(i = 1;i < row +1;i++){
		for(j = 1;j < col +1;j++){
			if(game[i][j] == 0){
				printf("□");
			}
			else{
				printf("■") ;
			}
			}
			printf("\n");
		}
		//输出当前是第几帧,并对是否进入下一帧进行交互 
	printf("\n 当前是第%d帧,输入0退出程序,输入1查看下一帧:\n",++count);
	while(1){
	scanf("%d",&c);
	if(c == 0){
		exit(0);
	}
	else if(c == 1){
	system("cls");
	break;
}
	else{
		printf("您输入的数据不合法,请重新输入:"); 
	}
}
	}
	return 0;
}
//注:需要合理使用指针的使用,其中通过指针的地址以及行数可以控制取出对应位置的元素
//同时这里C语言需要将所有的变量声明在最前面,否则会造成程序运行错误 
