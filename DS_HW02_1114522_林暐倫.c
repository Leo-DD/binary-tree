#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 10000 //定義MAX代表10000 

void printTree(); // 宣告函式 ,印出樹的中序遍歷（LVR）的節點值
void inorderTraversal(int index); // 宣告函式 ,進行樹的中序遍歷（LVR）印出節點值  
void insertNode(int key); // 宣告函式 ,能夠插入節點值
void deleteNode(int key); // 宣告函式 ,能夠刪除節點值
void moveSubtree(int index,int count,int multiple); // 宣告函式 ,移動子樹並符合二元搜索樹特性 
int searchValue(int key, int choose); // 宣告函式 ,能搜尋樹中節點是否存在
void printTree1(int arr[], int size); // 宣告函式 ,用圖形印出樹 

int arr[MAX]; // 宣告陣列 arr,能存放9999個數字和 \n  
int size = 0; // 宣告變數 size,計算樹中有多少個節點 

void printTree() { // 定義函式,印出樹的中序遍歷（LVR）的節點值
    printf("Inorder Traversal of the Tree: "); // 輸出樹的中序遍歷（LVR）,並用數字排列  
    inorderTraversal(1); // 從 arr[1] 開始進行
    printf("\n"); // 換行 
}

void inorderTraversal(int index) { // 定義函式,進行樹的中序遍歷（LVR）印出節點值,傳入索引值 
	int maxIndex = (int)pow(2, size) - 1; // 宣告變數maxIndex,計算樹中的最大索引值,計算最多有幾個節點2的 size次方減 1
    if (index <= maxIndex && arr[index] != -1) { // 檢查節點是否存在,並在範圍內 
        inorderTraversal(2 * index); // 遞迴呼叫左子節點
        printf("%d ", arr[index]); // 輸出節點值
        inorderTraversal(2 * index + 1); // 遞迴呼叫右子節點
    }
}

void insertNode(int key) { // 定義函式,能夠插入節點值,傳入要新增的值 
	
    if (size == MAX - 1) { // 檢查樹是否已滿 
        printf("Tree is full. Cannot insert more nodes.\n"); // 輸出樹已滿
        return; // 返回主程式 
    }

    if (searchValue(key, 1) != -1) { // 檢查樹中是否已存在要新增的值
        printf("Node %d already exists in the tree. Cannot insert duplicate nodes.\n", key); // 輸出插入的值已經存在
        return; // 返回主程式
    }

    int currentIndex = 1; // 宣告變數 currentIndex,從索引1(Root)開始
    int parentIndex = -1; // 宣告變數 parentIndex,用於跟蹤父節點索引
    int maxIndex = (int)pow(2, size) - 1; // 宣告變數 maxIndex,計算樹中的最大索引值(2的 size次方減 1)

    while (currentIndex <= maxIndex && arr[currentIndex] != -1) { // 循環直到找到合適的插入位置或遍歷完整棵樹
        
		parentIndex = currentIndex; // 在移至下一個節點之前更新父節點索引
        if (key < arr[currentIndex]) { // 判斷新增的值與節點值的大小關係 
            currentIndex = 2 * currentIndex; // 移至左子節點
        } 
		else {
            currentIndex = 2 * currentIndex + 1; // 移至右子節點
        }
    }

    if (parentIndex == -1) { // 如果父節點索引為-1 ,表示樹是空的
        arr[1] = key; // 當樹是空的時候，插入到根節點
    } 
	else if (key < arr[parentIndex]) { // 如果新增的值小於父節點的值
        arr[2 * parentIndex] = key; // 插入為左子節點
    } 
	else {
        arr[2 * parentIndex + 1] = key; // 插入為右子節點
    }

    size++; // 更新樹的大小
    printf("Node %d inserted successfully.\n", key); // 輸出成功新增節點 
}

void deleteNode(int key){ // 定義函式,能夠刪除節點值,傳入要刪除的節點 
	int currentIndex = 1; // 宣告變數 currentIndex,從索引值1(Root)開始
    int parentIndex = -1; // 宣告變數 parentIndex,用於跟蹤父節點索引
    int movenum; // 宣告變數 movenum,用於要搬移左子樹還是右子樹的數字 
    int count=1; // 宣告變數 count,用於搬移的次數 
	int multiple; // 宣告變數 multiple,用於計算搬移的倍數 
    while (currentIndex <= (int)pow(2, size) - 1 && arr[currentIndex] != -1 && arr[currentIndex] != key) { // 循環找到該刪除的節點或遍歷完整棵樹
        parentIndex = currentIndex; // 在移動到下一個節點之前更新父節點索引
        if (key < arr[currentIndex]) { // 判斷刪除的值與節點值的大小關係 
            currentIndex = 2 * currentIndex; // 左子節點
        } 
		else {
            currentIndex = 2 * currentIndex + 1; // 右子節點
        }
    }

    if (arr[currentIndex] != key) { // 如果未找到該刪除的節點 
        printf("Node %d not found in the tree. Deletion failed.\n", key); //輸出未找到該節點 
        return;
    }
	else{
		// 情況 1：節點沒有子節點
		if (arr[2 * currentIndex] == -1 && arr[2 * currentIndex + 1] == -1) {
            arr[currentIndex] = -1; // 節點沒有子節點，直接刪除
        }
        // 情況 2：節點只有一個子節點
        else if (arr[2 * currentIndex] == -1) { // 當刪除節點只有右子節點時，將右子樹往上移動填補空缺
            arr[currentIndex] = arr[2 * currentIndex + 1]; // 將右子節點移到父節點的位置
            arr[2 * currentIndex + 1]=-1; // 將原右子節變成空節點 
            multiple=currentIndex + 1; // 將 multiple為父節點的索引值加一,設定搬移的倍數 
            currentIndex = 2 * currentIndex + 1; // 移到右子節點的索引,作為新的父節點          
    		if (arr[2 * currentIndex] != -1) { // 判斷新的父節點的左子節點是否為空 
               moveSubtree(2*currentIndex,count*2,multiple); // 遞迴呼叫搬移左子樹 
    		}
    		if (arr[2 * currentIndex + 1] != -1) { // 判斷新的父節點的右子節點是否為空 
        	   moveSubtree(2*currentIndex + 1,count*2,multiple);// 遞迴呼叫搬移右子樹
    		}
	    }
		else if (arr[2 * currentIndex + 1] == -1) { // 當刪除節點只有左子節點時，將左子樹往上移動填補空缺
    		arr[currentIndex] = arr[2 * currentIndex];// 將左子節點移到父節點的位置
    		arr[2 * currentIndex] = -1; // 將原左子節變成空節點
    		multiple=currentIndex; // 將 multiple為父節點的索引值加一,設定搬移的倍數
    		currentIndex = 2 * currentIndex; // 並移到左子節點的索引,作為新的父節點    		
			if (arr[2 * currentIndex + 1] != -1) { // 判斷新的父節點的右子節點是否為空
        	   moveSubtree(2 * currentIndex + 1,count*2,multiple); // 遞迴呼叫搬移右子樹    	   
    		}
			if (arr[2 * currentIndex] != -1) { // 判斷新的父節點的左子節點是否為空
               moveSubtree(2 * currentIndex,count*2,multiple); // 遞迴呼叫搬移左子樹 
    		}
    		
		}
		// 情況 3：節點有兩個子節點
        else {      
		    int minRight = 2 * currentIndex + 1; // 宣告變數 minRight ,找到右子樹的最小值來替代被刪除節點的位置
		    int Maxleft =2 * currentIndex; // 宣告變數 Maxleft ,找到左子樹的最大值來替代被刪除節點的位置
		    do {
       			printf("Please choose to move the left subtree up or the right subtree up (1 for left, 2 for right): "); // 使用者輸入選擇要搬移的子樹
        			if (scanf("%d", &movenum) != 1 || (movenum != 1 && movenum != 2)) { // 檢查使用者輸入的是否不是整數或者輸入不是1或2的數 
            			printf("Invalid input. Please enter a valid number.\n"); // 若輸入值為非整數或不等於1或不等於2，印出提示訊息 
            			while (getchar() != '\n'); // 清除輸入緩衝區
            			movenum=0; // 將 movenum 設為 0 以便再次進入迴圈要求重新輸入
        			}  
			}while(movenum==0); // 當使用者輸入的值為 0 時，持續迴圈要求重新輸入值
	        if(movenum==1){ // 選擇左子樹
	    	    while (arr[2 * Maxleft+1] != -1) { // 找到左子樹的最大值
	    	    	Maxleft = 2 * Maxleft + 1; // 更新左子樹的最大節點的索引值 
                }
                arr[currentIndex] = arr[Maxleft]; // 用左子樹的最大值替代被刪除節點
                arr[Maxleft]=-1; // 將左子樹的最大值變為空節點
				if(arr[2 * Maxleft] != -1  ){ // 如果左子樹的最大值的左子節點存在 
				    arr[Maxleft] = arr[2 * Maxleft]; // 將左子樹的最大值的左子節點值其替換成最大值 
				    arr[2 * Maxleft] = -1; // 將左子樹的最大值的左子節點變為空節點
				    multiple=Maxleft; // 更新搬移的倍數
					Maxleft = 2 * Maxleft; // 更新左子樹的最大值的左子節點的索引值  
					if (arr[2 * Maxleft + 1] != -1) { // 檢查左子樹的最大值的左子節點的右子節點是否為空
        	   			moveSubtree(2 * Maxleft + 1,count*2,multiple); // 遞迴呼叫搬移右子樹
    				}
					if (arr[2 * Maxleft] != -1) { // 檢查左子樹的最大值的左子節點的左子節點是否為空
                		moveSubtree(2 * Maxleft,count*2,multiple); // 遞迴呼叫搬移左子樹 
    				}
    				
				}
			    else if(arr[2 * Maxleft ] == -1){ // 如果左子樹的最大值的左子節點不存在 
				arr[Maxleft] = -1; // 將左子樹的最大值變為空節點
				}                 
            } 
            else if (movenum==2) { // 選擇右子樹
            	while (arr[2 * minRight] != -1) { // 找到右子樹的最小值
                    minRight = 2 * minRight; // 找到右子樹的最小節點的索引值
                }
                arr[currentIndex] = arr[minRight]; // 用右子樹的最小值替代被刪除節點
                arr[minRight]=-1; // 將子樹的最小值變成空節點
                if(arr[2 * minRight + 1] != -1  ){ // 如果右子樹的最小值的右子節點存在
				    arr[minRight] = arr[2 * minRight+1]; // 將右子樹的最小值的右子節點值其替換成最小值 
				    arr[2 * minRight + 1] = -1; // 將右子樹的最小值的右子節點變成空節點
				    multiple=minRight+1; // 更新搬移的倍數
					minRight = 2 * minRight+1; // 更新右子樹的最小值的右子節點的索引值
					if (arr[2 * minRight] != -1) { // 判斷右子樹的最小值的右子節點的左子節點是否為空
                		moveSubtree(2 * minRight,count*2,multiple); // 遞迴呼叫搬移右子樹
    				}
    				if (arr[2 * minRight + 1] != -1) { // 判斷右子樹的最小值的右子節點的右子節點是否為空
        	   			moveSubtree(2 * minRight + 1,count*2,multiple); // 遞迴呼叫搬移右子樹
    				}
				}
			    else if(arr[2 * minRight] == -1){ // 如果右子樹的最小值的右子節點不存在
				arr[minRight] = -1; // 將子樹的最小值變成空節點
				}    
            } 
		} 
	size--; // 縮小樹的大小
    printf("Node %d has been deleted successfully.\n", key); // 輸出成功刪除節點   
	}	
}

void moveSubtree(int index,int count,int multiple) { // 定義函式,移動子樹並符合二元搜索樹特性,傳入索引值,次數,倍數 
    
        arr[index-multiple*count]=arr[index]; // 將當前索引處的節點向前移動 count * multiple 個位置
        arr[index]=-1; // 清空原節點位置
        count*=2; // 更新搬移次數
        if (arr[2 * index] != -1) {
            moveSubtree(2*index,count,multiple); // 遞迴處理右子節點
        }
        if (arr[2 * index + 1] != -1) {      	
            moveSubtree(2*index + 1,count,multiple); // 遞迴處理右子節點
        }
    
}

int searchValue(int key, int choose) { // 定義函式 ,能搜尋樹中節點是否存在,傳入節點,選擇 
    int currentIndex = 1; // 宣告變數 currentIndex,從索引1(Root)開始
    while (currentIndex <= (int)pow(2, size) - 1 && arr[currentIndex] != -1) {  // 循環搜尋目標值或遍歷完整棵樹
    	if (choose==4){	
		printf("%d \n", arr[currentIndex]); // 如果選擇為4，則印出在搜索過程中遇到的節點值
        }
        if (arr[currentIndex] == key) { // 如果找到指定的值
            return currentIndex; // 找到值時返回索引位置,表示找到 
        } else if (key < arr[currentIndex]) { // 如果目標值小於當前節點值 
            currentIndex = 2 * currentIndex; // 移至左子節點
        } else { // 如果目標值大於當前節點值
            currentIndex = 2 * currentIndex + 1; // 移至右子節點
        }
    }
    return -1 ; // 如果未找到指定值，返回 -1,表示未找到
}

void printTree1(int arr[], int size) { // 定義函式 ,用圖形印出樹,傳入陣列,節點數 
    int lastIndex = -1; // 宣告變數 lastIndex,初始設定索引為 -1，若找不到任何非空值，回傳 -1
    int count=0; // 宣告變數 count,記錄找到第幾個節點 
    int i,j,k; // 宣告變數 i,計算有幾層;宣告變數 j,每層需要填幾個節點;宣告變數k,計算空白有幾格 
    
	for ( i = 1; i <= (double)pow(2, size); i++) { // 找到最後一個非空值的索引位置
        if (arr[i] != -1) {
            lastIndex = i; // 更新最後一個非空值的索引位置
            count++; //每找到一個節點,count加一 
            if (count==size){
                break; // 如果已經找到所有節點值，退出迴圈
            }
        }
    }
    int levels = ceil(log2(lastIndex+1));  // 宣告變數 levels, 計算有多少層 
    int index = 0; // 宣告變數 index,把陣列 arr有值的插入圖樹中 
    int spaces = (int)pow(2,levels-1); // 宣告變數 spaces,計算節點跟節點之間的空白 
    for (i = 0; i < levels; i++) { // 層數 
    	for (j = 0; j <(int)pow(2,i) ; j++) { // 每層的節點數 
		spaces = ((int)pow(2,levels-i))/2; // 每層最開始節點前的空格數 
            for(k = 0; k < spaces; k++) {printf("  "); } // 輸出空格
            if (index <= (int)pow(2, size) - 1 && arr[index+1] != -1) { // 印出節點 
                if (arr[index+1]<10 && arr[index+1] >=0){ // 節點介於0~9之間 
                	printf("0%d", arr[index+1]); // 輸出節點 
				}
				else{
				printf("%d", arr[index+1]); // 輸出節點
				}
				index++; // 找下一個節點 
                for(k = 0; k < spaces-1; k++) {printf("  ");} // 輸出空格
            }        
            else if (index <= (int)pow(2, size) - 1 && arr[index+1] == -1){ //印出空節點 
                printf("  "); // 輸出空格
                index++; // 找下一個節點
                for(k = 0; k < spaces-1; k++) {printf("  ");} // 輸出空格
            }            
        }
        printf("\n"); // 換行至下一層	  
    }
	printf("%d\n",levels); // 輸出樹的層數
}

int main() {
    int choose = 0; // 宣告變數choose,儲存使用者選擇的操作選項
    int i; // 宣告變數i,用於初始化陣列 
    arr[0] = 0; // 設置 arr[0] 為 0

    for (i = 1; i < MAX; i++) { // 初始化陣列，將其它位置都設為 -1，表示空節點
        arr[i] = -1;
    }

    do { // 持續運行程式直到使用者選擇退出程式為止
    	do {// 顯示操作選單
        printf("Menu:\n1) Show tree (Inorder Traversal)\n2) Insert new node\n3) Delete node\n4) Search node\n5) Exit the program\n6) Show Binary tree\n"); // 輸出選擇的選項 
        printf("Enter your choice: "); // 使用者輸入 

         
        if (scanf("%d", &choose) != 1) { // 確認使用者輸入的是整數
            printf("Invalid input. Please enter a number.\n"); //無效的輸入,印出提示訊息
            while (getchar() != '\n'); // 清除輸入緩衝區
            continue; // 繼續下一輪迴圈
        }
      	if (choose <= 0 || choose > 6) { // 檢查使用者輸入的選項是否在合法範圍內
           printf("Invalid choice. Please enter a number between 1 and 6.\n"); // 輸入不在合法範圍內，印出提示訊息
      	}
        } while (choose <= 0 || choose > 6); // 確保使用者選擇在合法範圍內
        int value; // 宣告變數 value,用於節點的操作 
        switch (choose) { // 根據使用者選擇的不同選項，執行相對應的操作
            case 1: // 顯示二元樹的中序遍歷結果
                printTree(); //呼叫函式,印出樹的中序遍歷（LVR）的節點值
                break; // 跳出迴圈 
            case 2: // 插入新節點到二元樹
                do {
       				printf("Enter the value to insert: "); // 提示使用者輸入值 
        			if (scanf("%d", &value) != 1 || value == -1) { // 檢查使用者輸入的是否不是整數或者輸入-1
            			printf("Invalid input. Please enter a valid number.\n"); // 若輸入值為非整數或 -1，印出提示訊息 
            			while (getchar() != '\n'); // 清除輸入緩衝區
            			value = -1; // 將 value 設為 -1 以便再次進入迴圈要求重新輸入
        			}
    			} while (value == -1); // 當使用者輸入的值為非整數或 -1 時，持續迴圈要求重新輸入值
                insertNode(value);// 呼叫函式 ,能夠插入節點值
                break; // 跳出迴圈 
            case 3: // 刪除二元樹中的節點
            	do{
                	printf("Enter the value to delete:"); // 提示使用者輸入值 
                	if (scanf("%d", &value) != 1 || value == -1) { // 檢查使用者輸入的是否不是整數或者輸入-1
            			printf("Invalid input. Please enter a valid number.\n"); // 若輸入值為非整數或 -1，印出提示訊息 
            			while (getchar() != '\n'); // 清除輸入緩衝區
            			value = -1; // 將 value 設為 -1 以便再次進入迴圈要求重新輸入
        			}
				}while(value == -1); // 當使用者輸入的值為 -1 時，持續迴圈要求重新輸入值
                deleteNode(value); // 定義函式 ,能夠刪除節點值
                break;// 跳出迴圈
            case 4: // 搜尋二元樹中的節點
            	do{
                	printf("Enter the value to search: "); // 提示使用者輸入值
                	if (scanf("%d", &value) != 1 || value == -1) { // 檢查使用者輸入的是否不是整數或者輸入-1
            			printf("Invalid input. Please enter a valid number.\n"); // 若輸入值為非整數或 -1，印出提示訊息 
            			while (getchar() != '\n'); // 清除輸入緩衝區
            			value = -1; // 將 value 設為 -1 以便再次進入迴圈要求重新輸入
        			}
				}while(value==-1); // 當使用者輸入的值為 -1 時，持續迴圈要求重新輸入值
				int Index = searchValue(value, choose); // 宣告變數 Index,呼叫函式並將回傳的索引值存入 Index 變數中
				if (Index != -1) { 				    
                    printf("Node %d found in the tree at index %d.\n", value, Index); // 輸出找到的訊息及索引值
                } 
				else {
                    printf("Node %d not found in the tree.\n", value); // 輸出未找到的訊息 
                }
                break;// 跳出迴圈
            case 5: // 結束程式
            	printf("Exiting the program.\n"); // 輸出結束程式 
                return 0; // 程式結束
            case 6: // 顯示二元樹的結構圖
                if(size==0){ // 沒有節點時 
                	printf("The tree is currently empty. No nodes to display.\n"); // 輸出這是一顆空樹 
				}
				else{
                printTree1(arr, size); // 呼叫函式 ,用圖形印出樹
                }
				break;// 跳出迴圈
            default: // 當使用者輸入的選項無效
                printf("Invalid choice. Please enter a valid option.\n"); // 提示使用者輸入無效選項
        }
    } while (choose != 5); // 使用者選擇 5 時退出迴圈
    return 0; // 程式結束
}



