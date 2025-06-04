#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 10000 //�w�qMAX�N��10000 

void printTree(); // �ŧi�禡 ,�L�X�𪺤��ǹM���]LVR�^���`�I��
void inorderTraversal(int index); // �ŧi�禡 ,�i��𪺤��ǹM���]LVR�^�L�X�`�I��  
void insertNode(int key); // �ŧi�禡 ,������J�`�I��
void deleteNode(int key); // �ŧi�禡 ,����R���`�I��
void moveSubtree(int index,int count,int multiple); // �ŧi�禡 ,���ʤl��òŦX�G���j����S�� 
int searchValue(int key, int choose); // �ŧi�禡 ,��j�M�𤤸`�I�O�_�s�b
void printTree1(int arr[], int size); // �ŧi�禡 ,�ιϧΦL�X�� 

int arr[MAX]; // �ŧi�}�C arr,��s��9999�ӼƦr�M \n  
int size = 0; // �ŧi�ܼ� size,�p��𤤦��h�֭Ӹ`�I 

void printTree() { // �w�q�禡,�L�X�𪺤��ǹM���]LVR�^���`�I��
    printf("Inorder Traversal of the Tree: "); // ��X�𪺤��ǹM���]LVR�^,�åμƦr�ƦC  
    inorderTraversal(1); // �q arr[1] �}�l�i��
    printf("\n"); // ���� 
}

void inorderTraversal(int index) { // �w�q�禡,�i��𪺤��ǹM���]LVR�^�L�X�`�I��,�ǤJ���ޭ� 
	int maxIndex = (int)pow(2, size) - 1; // �ŧi�ܼ�maxIndex,�p��𤤪��̤j���ޭ�,�p��̦h���X�Ӹ`�I2�� size����� 1
    if (index <= maxIndex && arr[index] != -1) { // �ˬd�`�I�O�_�s�b,�æb�d�� 
        inorderTraversal(2 * index); // ���j�I�s���l�`�I
        printf("%d ", arr[index]); // ��X�`�I��
        inorderTraversal(2 * index + 1); // ���j�I�s�k�l�`�I
    }
}

void insertNode(int key) { // �w�q�禡,������J�`�I��,�ǤJ�n�s�W���� 
	
    if (size == MAX - 1) { // �ˬd��O�_�w�� 
        printf("Tree is full. Cannot insert more nodes.\n"); // ��X��w��
        return; // ��^�D�{�� 
    }

    if (searchValue(key, 1) != -1) { // �ˬd�𤤬O�_�w�s�b�n�s�W����
        printf("Node %d already exists in the tree. Cannot insert duplicate nodes.\n", key); // ��X���J���Ȥw�g�s�b
        return; // ��^�D�{��
    }

    int currentIndex = 1; // �ŧi�ܼ� currentIndex,�q����1(Root)�}�l
    int parentIndex = -1; // �ŧi�ܼ� parentIndex,�Ω���ܤ��`�I����
    int maxIndex = (int)pow(2, size) - 1; // �ŧi�ܼ� maxIndex,�p��𤤪��̤j���ޭ�(2�� size����� 1)

    while (currentIndex <= maxIndex && arr[currentIndex] != -1) { // �`��������X�A�����J��m�ιM������ʾ�
        
		parentIndex = currentIndex; // �b���ܤU�@�Ӹ`�I���e��s���`�I����
        if (key < arr[currentIndex]) { // �P�_�s�W���ȻP�`�I�Ȫ��j�p���Y 
            currentIndex = 2 * currentIndex; // ���ܥ��l�`�I
        } 
		else {
            currentIndex = 2 * currentIndex + 1; // ���ܥk�l�`�I
        }
    }

    if (parentIndex == -1) { // �p�G���`�I���ެ�-1 ,��ܾ�O�Ū�
        arr[1] = key; // ���O�Ū��ɭԡA���J��ڸ`�I
    } 
	else if (key < arr[parentIndex]) { // �p�G�s�W���Ȥp����`�I����
        arr[2 * parentIndex] = key; // ���J�����l�`�I
    } 
	else {
        arr[2 * parentIndex + 1] = key; // ���J���k�l�`�I
    }

    size++; // ��s�𪺤j�p
    printf("Node %d inserted successfully.\n", key); // ��X���\�s�W�`�I 
}

void deleteNode(int key){ // �w�q�禡,����R���`�I��,�ǤJ�n�R�����`�I 
	int currentIndex = 1; // �ŧi�ܼ� currentIndex,�q���ޭ�1(Root)�}�l
    int parentIndex = -1; // �ŧi�ܼ� parentIndex,�Ω���ܤ��`�I����
    int movenum; // �ŧi�ܼ� movenum,�Ω�n�h�����l���٬O�k�l�𪺼Ʀr 
    int count=1; // �ŧi�ܼ� count,�Ω�h�������� 
	int multiple; // �ŧi�ܼ� multiple,�Ω�p��h�������� 
    while (currentIndex <= (int)pow(2, size) - 1 && arr[currentIndex] != -1 && arr[currentIndex] != key) { // �`�����ӧR�����`�I�ιM������ʾ�
        parentIndex = currentIndex; // �b���ʨ�U�@�Ӹ`�I���e��s���`�I����
        if (key < arr[currentIndex]) { // �P�_�R�����ȻP�`�I�Ȫ��j�p���Y 
            currentIndex = 2 * currentIndex; // ���l�`�I
        } 
		else {
            currentIndex = 2 * currentIndex + 1; // �k�l�`�I
        }
    }

    if (arr[currentIndex] != key) { // �p�G�����ӧR�����`�I 
        printf("Node %d not found in the tree. Deletion failed.\n", key); //��X�����Ӹ`�I 
        return;
    }
	else{
		// ���p 1�G�`�I�S���l�`�I
		if (arr[2 * currentIndex] == -1 && arr[2 * currentIndex + 1] == -1) {
            arr[currentIndex] = -1; // �`�I�S���l�`�I�A�����R��
        }
        // ���p 2�G�`�I�u���@�Ӥl�`�I
        else if (arr[2 * currentIndex] == -1) { // ��R���`�I�u���k�l�`�I�ɡA�N�k�l�𩹤W���ʶ�ɪů�
            arr[currentIndex] = arr[2 * currentIndex + 1]; // �N�k�l�`�I������`�I����m
            arr[2 * currentIndex + 1]=-1; // �N��k�l�`�ܦ��Ÿ`�I 
            multiple=currentIndex + 1; // �N multiple�����`�I�����ޭȥ[�@,�]�w�h�������� 
            currentIndex = 2 * currentIndex + 1; // ����k�l�`�I������,�@���s�����`�I          
    		if (arr[2 * currentIndex] != -1) { // �P�_�s�����`�I�����l�`�I�O�_���� 
               moveSubtree(2*currentIndex,count*2,multiple); // ���j�I�s�h�����l�� 
    		}
    		if (arr[2 * currentIndex + 1] != -1) { // �P�_�s�����`�I���k�l�`�I�O�_���� 
        	   moveSubtree(2*currentIndex + 1,count*2,multiple);// ���j�I�s�h���k�l��
    		}
	    }
		else if (arr[2 * currentIndex + 1] == -1) { // ��R���`�I�u�����l�`�I�ɡA�N���l�𩹤W���ʶ�ɪů�
    		arr[currentIndex] = arr[2 * currentIndex];// �N���l�`�I������`�I����m
    		arr[2 * currentIndex] = -1; // �N�쥪�l�`�ܦ��Ÿ`�I
    		multiple=currentIndex; // �N multiple�����`�I�����ޭȥ[�@,�]�w�h��������
    		currentIndex = 2 * currentIndex; // �ò��쥪�l�`�I������,�@���s�����`�I    		
			if (arr[2 * currentIndex + 1] != -1) { // �P�_�s�����`�I���k�l�`�I�O�_����
        	   moveSubtree(2 * currentIndex + 1,count*2,multiple); // ���j�I�s�h���k�l��    	   
    		}
			if (arr[2 * currentIndex] != -1) { // �P�_�s�����`�I�����l�`�I�O�_����
               moveSubtree(2 * currentIndex,count*2,multiple); // ���j�I�s�h�����l�� 
    		}
    		
		}
		// ���p 3�G�`�I����Ӥl�`�I
        else {      
		    int minRight = 2 * currentIndex + 1; // �ŧi�ܼ� minRight ,���k�l�𪺳̤p�ȨӴ��N�Q�R���`�I����m
		    int Maxleft =2 * currentIndex; // �ŧi�ܼ� Maxleft ,��쥪�l�𪺳̤j�ȨӴ��N�Q�R���`�I����m
		    do {
       			printf("Please choose to move the left subtree up or the right subtree up (1 for left, 2 for right): "); // �ϥΪ̿�J��ܭn�h�����l��
        			if (scanf("%d", &movenum) != 1 || (movenum != 1 && movenum != 2)) { // �ˬd�ϥΪ̿�J���O�_���O��ƩΪ̿�J���O1��2���� 
            			printf("Invalid input. Please enter a valid number.\n"); // �Y��J�Ȭ��D��ƩΤ�����1�Τ�����2�A�L�X���ܰT�� 
            			while (getchar() != '\n'); // �M����J�w�İ�
            			movenum=0; // �N movenum �]�� 0 �H�K�A���i�J�j��n�D���s��J
        			}  
			}while(movenum==0); // ��ϥΪ̿�J���Ȭ� 0 �ɡA����j��n�D���s��J��
	        if(movenum==1){ // ��ܥ��l��
	    	    while (arr[2 * Maxleft+1] != -1) { // ��쥪�l�𪺳̤j��
	    	    	Maxleft = 2 * Maxleft + 1; // ��s���l�𪺳̤j�`�I�����ޭ� 
                }
                arr[currentIndex] = arr[Maxleft]; // �Υ��l�𪺳̤j�ȴ��N�Q�R���`�I
                arr[Maxleft]=-1; // �N���l�𪺳̤j���ܬ��Ÿ`�I
				if(arr[2 * Maxleft] != -1  ){ // �p�G���l�𪺳̤j�Ȫ����l�`�I�s�b 
				    arr[Maxleft] = arr[2 * Maxleft]; // �N���l�𪺳̤j�Ȫ����l�`�I�Ȩ�������̤j�� 
				    arr[2 * Maxleft] = -1; // �N���l�𪺳̤j�Ȫ����l�`�I�ܬ��Ÿ`�I
				    multiple=Maxleft; // ��s�h��������
					Maxleft = 2 * Maxleft; // ��s���l�𪺳̤j�Ȫ����l�`�I�����ޭ�  
					if (arr[2 * Maxleft + 1] != -1) { // �ˬd���l�𪺳̤j�Ȫ����l�`�I���k�l�`�I�O�_����
        	   			moveSubtree(2 * Maxleft + 1,count*2,multiple); // ���j�I�s�h���k�l��
    				}
					if (arr[2 * Maxleft] != -1) { // �ˬd���l�𪺳̤j�Ȫ����l�`�I�����l�`�I�O�_����
                		moveSubtree(2 * Maxleft,count*2,multiple); // ���j�I�s�h�����l�� 
    				}
    				
				}
			    else if(arr[2 * Maxleft ] == -1){ // �p�G���l�𪺳̤j�Ȫ����l�`�I���s�b 
				arr[Maxleft] = -1; // �N���l�𪺳̤j���ܬ��Ÿ`�I
				}                 
            } 
            else if (movenum==2) { // ��ܥk�l��
            	while (arr[2 * minRight] != -1) { // ���k�l�𪺳̤p��
                    minRight = 2 * minRight; // ���k�l�𪺳̤p�`�I�����ޭ�
                }
                arr[currentIndex] = arr[minRight]; // �Υk�l�𪺳̤p�ȴ��N�Q�R���`�I
                arr[minRight]=-1; // �N�l�𪺳̤p���ܦ��Ÿ`�I
                if(arr[2 * minRight + 1] != -1  ){ // �p�G�k�l�𪺳̤p�Ȫ��k�l�`�I�s�b
				    arr[minRight] = arr[2 * minRight+1]; // �N�k�l�𪺳̤p�Ȫ��k�l�`�I�Ȩ�������̤p�� 
				    arr[2 * minRight + 1] = -1; // �N�k�l�𪺳̤p�Ȫ��k�l�`�I�ܦ��Ÿ`�I
				    multiple=minRight+1; // ��s�h��������
					minRight = 2 * minRight+1; // ��s�k�l�𪺳̤p�Ȫ��k�l�`�I�����ޭ�
					if (arr[2 * minRight] != -1) { // �P�_�k�l�𪺳̤p�Ȫ��k�l�`�I�����l�`�I�O�_����
                		moveSubtree(2 * minRight,count*2,multiple); // ���j�I�s�h���k�l��
    				}
    				if (arr[2 * minRight + 1] != -1) { // �P�_�k�l�𪺳̤p�Ȫ��k�l�`�I���k�l�`�I�O�_����
        	   			moveSubtree(2 * minRight + 1,count*2,multiple); // ���j�I�s�h���k�l��
    				}
				}
			    else if(arr[2 * minRight] == -1){ // �p�G�k�l�𪺳̤p�Ȫ��k�l�`�I���s�b
				arr[minRight] = -1; // �N�l�𪺳̤p���ܦ��Ÿ`�I
				}    
            } 
		} 
	size--; // �Y�p�𪺤j�p
    printf("Node %d has been deleted successfully.\n", key); // ��X���\�R���`�I   
	}	
}

void moveSubtree(int index,int count,int multiple) { // �w�q�禡,���ʤl��òŦX�G���j����S��,�ǤJ���ޭ�,����,���� 
    
        arr[index-multiple*count]=arr[index]; // �N��e���޳B���`�I�V�e���� count * multiple �Ӧ�m
        arr[index]=-1; // �M�ŭ�`�I��m
        count*=2; // ��s�h������
        if (arr[2 * index] != -1) {
            moveSubtree(2*index,count,multiple); // ���j�B�z�k�l�`�I
        }
        if (arr[2 * index + 1] != -1) {      	
            moveSubtree(2*index + 1,count,multiple); // ���j�B�z�k�l�`�I
        }
    
}

int searchValue(int key, int choose) { // �w�q�禡 ,��j�M�𤤸`�I�O�_�s�b,�ǤJ�`�I,��� 
    int currentIndex = 1; // �ŧi�ܼ� currentIndex,�q����1(Root)�}�l
    while (currentIndex <= (int)pow(2, size) - 1 && arr[currentIndex] != -1) {  // �`���j�M�ؼЭȩιM������ʾ�
    	if (choose==4){	
		printf("%d \n", arr[currentIndex]); // �p�G��ܬ�4�A�h�L�X�b�j���L�{���J�쪺�`�I��
        }
        if (arr[currentIndex] == key) { // �p�G�����w����
            return currentIndex; // ���Ȯɪ�^���ަ�m,��ܧ�� 
        } else if (key < arr[currentIndex]) { // �p�G�ؼЭȤp���e�`�I�� 
            currentIndex = 2 * currentIndex; // ���ܥ��l�`�I
        } else { // �p�G�ؼЭȤj���e�`�I��
            currentIndex = 2 * currentIndex + 1; // ���ܥk�l�`�I
        }
    }
    return -1 ; // �p�G�������w�ȡA��^ -1,��ܥ����
}

void printTree1(int arr[], int size) { // �w�q�禡 ,�ιϧΦL�X��,�ǤJ�}�C,�`�I�� 
    int lastIndex = -1; // �ŧi�ܼ� lastIndex,��l�]�w���ެ� -1�A�Y�䤣�����D�ŭȡA�^�� -1
    int count=0; // �ŧi�ܼ� count,�O�����ĴX�Ӹ`�I 
    int i,j,k; // �ŧi�ܼ� i,�p�⦳�X�h;�ŧi�ܼ� j,�C�h�ݭn��X�Ӹ`�I;�ŧi�ܼ�k,�p��ťզ��X�� 
    
	for ( i = 1; i <= (double)pow(2, size); i++) { // ���̫�@�ӫD�ŭȪ����ަ�m
        if (arr[i] != -1) {
            lastIndex = i; // ��s�̫�@�ӫD�ŭȪ����ަ�m
            count++; //�C���@�Ӹ`�I,count�[�@ 
            if (count==size){
                break; // �p�G�w�g���Ҧ��`�I�ȡA�h�X�j��
            }
        }
    }
    int levels = ceil(log2(lastIndex+1));  // �ŧi�ܼ� levels, �p�⦳�h�ּh 
    int index = 0; // �ŧi�ܼ� index,��}�C arr���Ȫ����J�Ͼ� 
    int spaces = (int)pow(2,levels-1); // �ŧi�ܼ� spaces,�p��`�I��`�I�������ť� 
    for (i = 0; i < levels; i++) { // �h�� 
    	for (j = 0; j <(int)pow(2,i) ; j++) { // �C�h���`�I�� 
		spaces = ((int)pow(2,levels-i))/2; // �C�h�̶}�l�`�I�e���Ů�� 
            for(k = 0; k < spaces; k++) {printf("  "); } // ��X�Ů�
            if (index <= (int)pow(2, size) - 1 && arr[index+1] != -1) { // �L�X�`�I 
                if (arr[index+1]<10 && arr[index+1] >=0){ // �`�I����0~9���� 
                	printf("0%d", arr[index+1]); // ��X�`�I 
				}
				else{
				printf("%d", arr[index+1]); // ��X�`�I
				}
				index++; // ��U�@�Ӹ`�I 
                for(k = 0; k < spaces-1; k++) {printf("  ");} // ��X�Ů�
            }        
            else if (index <= (int)pow(2, size) - 1 && arr[index+1] == -1){ //�L�X�Ÿ`�I 
                printf("  "); // ��X�Ů�
                index++; // ��U�@�Ӹ`�I
                for(k = 0; k < spaces-1; k++) {printf("  ");} // ��X�Ů�
            }            
        }
        printf("\n"); // ����ܤU�@�h	  
    }
	printf("%d\n",levels); // ��X�𪺼h��
}

int main() {
    int choose = 0; // �ŧi�ܼ�choose,�x�s�ϥΪ̿�ܪ��ާ@�ﶵ
    int i; // �ŧi�ܼ�i,�Ω��l�ư}�C 
    arr[0] = 0; // �]�m arr[0] �� 0

    for (i = 1; i < MAX; i++) { // ��l�ư}�C�A�N�䥦��m���]�� -1�A��ܪŸ`�I
        arr[i] = -1;
    }

    do { // ����B��{������ϥΪ̿�ܰh�X�{������
    	do {// ��ܾާ@���
        printf("Menu:\n1) Show tree (Inorder Traversal)\n2) Insert new node\n3) Delete node\n4) Search node\n5) Exit the program\n6) Show Binary tree\n"); // ��X��ܪ��ﶵ 
        printf("Enter your choice: "); // �ϥΪ̿�J 

         
        if (scanf("%d", &choose) != 1) { // �T�{�ϥΪ̿�J���O���
            printf("Invalid input. Please enter a number.\n"); //�L�Ī���J,�L�X���ܰT��
            while (getchar() != '\n'); // �M����J�w�İ�
            continue; // �~��U�@���j��
        }
      	if (choose <= 0 || choose > 6) { // �ˬd�ϥΪ̿�J���ﶵ�O�_�b�X�k�d��
           printf("Invalid choice. Please enter a number between 1 and 6.\n"); // ��J���b�X�k�d�򤺡A�L�X���ܰT��
      	}
        } while (choose <= 0 || choose > 6); // �T�O�ϥΪ̿�ܦb�X�k�d��
        int value; // �ŧi�ܼ� value,�Ω�`�I���ާ@ 
        switch (choose) { // �ھڨϥΪ̿�ܪ����P�ﶵ�A����۹������ާ@
            case 1: // ��ܤG���𪺤��ǹM�����G
                printTree(); //�I�s�禡,�L�X�𪺤��ǹM���]LVR�^���`�I��
                break; // ���X�j�� 
            case 2: // ���J�s�`�I��G����
                do {
       				printf("Enter the value to insert: "); // ���ܨϥΪ̿�J�� 
        			if (scanf("%d", &value) != 1 || value == -1) { // �ˬd�ϥΪ̿�J���O�_���O��ƩΪ̿�J-1
            			printf("Invalid input. Please enter a valid number.\n"); // �Y��J�Ȭ��D��Ʃ� -1�A�L�X���ܰT�� 
            			while (getchar() != '\n'); // �M����J�w�İ�
            			value = -1; // �N value �]�� -1 �H�K�A���i�J�j��n�D���s��J
        			}
    			} while (value == -1); // ��ϥΪ̿�J���Ȭ��D��Ʃ� -1 �ɡA����j��n�D���s��J��
                insertNode(value);// �I�s�禡 ,������J�`�I��
                break; // ���X�j�� 
            case 3: // �R���G���𤤪��`�I
            	do{
                	printf("Enter the value to delete:"); // ���ܨϥΪ̿�J�� 
                	if (scanf("%d", &value) != 1 || value == -1) { // �ˬd�ϥΪ̿�J���O�_���O��ƩΪ̿�J-1
            			printf("Invalid input. Please enter a valid number.\n"); // �Y��J�Ȭ��D��Ʃ� -1�A�L�X���ܰT�� 
            			while (getchar() != '\n'); // �M����J�w�İ�
            			value = -1; // �N value �]�� -1 �H�K�A���i�J�j��n�D���s��J
        			}
				}while(value == -1); // ��ϥΪ̿�J���Ȭ� -1 �ɡA����j��n�D���s��J��
                deleteNode(value); // �w�q�禡 ,����R���`�I��
                break;// ���X�j��
            case 4: // �j�M�G���𤤪��`�I
            	do{
                	printf("Enter the value to search: "); // ���ܨϥΪ̿�J��
                	if (scanf("%d", &value) != 1 || value == -1) { // �ˬd�ϥΪ̿�J���O�_���O��ƩΪ̿�J-1
            			printf("Invalid input. Please enter a valid number.\n"); // �Y��J�Ȭ��D��Ʃ� -1�A�L�X���ܰT�� 
            			while (getchar() != '\n'); // �M����J�w�İ�
            			value = -1; // �N value �]�� -1 �H�K�A���i�J�j��n�D���s��J
        			}
				}while(value==-1); // ��ϥΪ̿�J���Ȭ� -1 �ɡA����j��n�D���s��J��
				int Index = searchValue(value, choose); // �ŧi�ܼ� Index,�I�s�禡�ñN�^�Ǫ����ޭȦs�J Index �ܼƤ�
				if (Index != -1) { 				    
                    printf("Node %d found in the tree at index %d.\n", value, Index); // ��X��쪺�T���ί��ޭ�
                } 
				else {
                    printf("Node %d not found in the tree.\n", value); // ��X����쪺�T�� 
                }
                break;// ���X�j��
            case 5: // �����{��
            	printf("Exiting the program.\n"); // ��X�����{�� 
                return 0; // �{������
            case 6: // ��ܤG���𪺵��c��
                if(size==0){ // �S���`�I�� 
                	printf("The tree is currently empty. No nodes to display.\n"); // ��X�o�O�@���ž� 
				}
				else{
                printTree1(arr, size); // �I�s�禡 ,�ιϧΦL�X��
                }
				break;// ���X�j��
            default: // ��ϥΪ̿�J���ﶵ�L��
                printf("Invalid choice. Please enter a valid option.\n"); // ���ܨϥΪ̿�J�L�Ŀﶵ
        }
    } while (choose != 5); // �ϥΪ̿�� 5 �ɰh�X�j��
    return 0; // �{������
}



