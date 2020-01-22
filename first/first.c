#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

struct node{
    char name[25];
    int* array;
};

struct LLnode{
	char name[25];
	int* array;
	struct LLnode* next;
};

 struct node* allocate_matrix(int rows, int cols);
void gray_code(struct node* input_table,int rows, int cols);
int AND(int bit1,int bit2);
int NAND(int bit1,int bit2);
int OR(int bit1,int bit2);
int NOR(int bit1,int bit2);
int NOT(int bit1);
int XNOR(int bit1,int bit2);
int XOR(int bit1,int bit2);
int search_in_table(char* ch, int number_of_inputs, struct node* input_table);
int* search_in_LL(char* ch, int number_of_inputs, struct LLnode* head);
struct LLnode* add_LL(struct LLnode* head, char* out, int* output);
void print_all(struct node* input_table, struct node* output_table,int number_of_inputs,int number_of_outputs, int rows);
int gray_to_index(int* temp, int inputs);


struct node* allocate_matrix(int rows, int cols){
	
	struct node* ret_val = malloc(cols * sizeof( struct node));
	/*int* array = malloc(rows* sizeof( int));
  for(int i = 0; i< cols; i++){

	ret_val[i].name = "";
	ret_val[i].array = array;
  }
*/
  return ret_val;
}

void gray_code(struct node* input_table,int rows, int cols){
	
	int change=2;
	int current_bit = 0;
	int count=1;
	int pre_count = 1;
for(int i=cols-1 ; i>=0; i--){
	int* arr = malloc(rows* sizeof(int));
	for(int j=0; j< rows; j++){
		if(count == 0){
			count = change;
			if(current_bit == 0){ current_bit = 1; }
			else if(current_bit == 1) { current_bit = 0; }
		
		}
		arr[j] = current_bit;
		count--;	
		}

	input_table[i].array = arr;

	change = change*2;
	current_bit = 0;
	pre_count = pre_count * 2;
	count = pre_count;

}

}

int AND(int bit1,int bit2){
    
    return bit1&bit2;
}

int OR(int bit1, int bit2){
    
    return bit1|bit2;
}

int NOT(int bit1){
    
    if(bit1 == 0){
		return 1;
	}
	else if(bit1 == 1){
		return 0;
	}
return 0;
}

int XOR(int bit1,int bit2){
    
    return (bit1^bit2);
}

int XNOR(int bit1,int bit2){
    
	int temp1 = XOR(bit1,bit2);
	//printf("%d ----", temp1);
	
	int temp2 = NOT(temp1);
	//printf("%d ----", temp2);

	return temp2;

}

int NAND(int bit1,int bit2){
    
    return NOT(AND(bit1,bit2));
}

int NOR(int bit1,int bit2){
    
    return NOT(OR(bit1,bit2));
}


int search_in_table(char ch[25], int number_of_inputs,struct node* input_table){
    
    for(int i=0; i< number_of_inputs; i++){
        
        if(strcmp(input_table[i].name , ch) ==0){
            return i;
        }
    }
     
    return -1;
}

int* search_in_LL(char ch[25], int number_of_inputs,struct LLnode* head){
    
   struct LLnode* ptr = head;
    while(ptr != NULL){
        if(strcmp(ptr->name, ch) == 0){
            return ptr->array;
        }
	ptr = ptr->next;
    }
    
    return NULL;
}

struct LLnode* add_LL(struct LLnode* head, char* out, int* output){

		struct LLnode* n = malloc(sizeof(struct LLnode));
		strcpy(n->name , out);
		n->array = output;
		n->next = NULL;

	if(head == NULL){
		head = n;
			return head;
	}
	
	n->next = head;
	head = n;	
	return head;
}

struct LLnode* add_LL_end(struct LLnode* head, char* out, int* output){

		struct LLnode* n = malloc(sizeof(struct LLnode));
		strcpy(n->name , out);
		n->array = output;
		n->next = NULL;

	if(head == NULL){
			head = n;
			return head;
	}
	struct LLnode* ptr = head;
	while(ptr->next != NULL){
		ptr = ptr->next;
	}
	ptr->next = n;	
	return head;
}




int gray_to_index(int* temp, int inputs){

	int* temp2 = malloc(inputs * sizeof(int));	
	
	int index=0;
	for(int i=0; i<inputs; i++){
		if(temp[i] == 1){
			index = i;
			break;
		}
	else if(i== inputs-1 && temp[i]==0){
		return 0;
	}	
		
	}

	temp2[index] = temp[index];
	int p = index+1;

	while(p<inputs){
	
	temp2[index+1] = XOR(temp2[index], temp[p]);
	index++;
	p++;
}
	int power=0;
	int result=0;
	for(int j=inputs-1; j>=0; j--){
		if(temp2[j] == 1){
			result = result + pow(2,power);
		}
	power++;
	}

	return result;

}





void print_all(struct node* input_table, struct node* output_table,int number_of_inputs,int number_of_outputs, int rows){
	
	for(int i = 0; i< rows; i++){
		for(int j=0 ; j<number_of_inputs; j++){
			printf("%d ", input_table[j].array[i]);
		}
		for(int k=0; k<number_of_outputs; k++){
			printf("%d ", output_table[k].array[i]);
		}
		printf("\n");
	}
	
}


int main(int argc ,char** argv){
    if(argc > 2){
        printf("Error\n");
        exit(0);
    }
   
    FILE* fp = fopen(argv[1], "r");
   
    FILE* fp1= fp;
     
    int number_of_inputs;  
    int number_of_outputs;
    char check[20];
    char inputvar[25];
    char outputvar[25];
struct node* input_table;
struct node* output_table;
   
    fscanf(fp, "%s", check);
   
        if(check[0] == 'I'){
            fscanf(fp, " %d" , &number_of_inputs);
               
                input_table = allocate_matrix(pow(2,number_of_inputs), number_of_inputs);
                for(int i=0; i<number_of_inputs; i++){
                    fscanf(fp, " %s", inputvar);
			strcpy(input_table[i].name, inputvar);
			
                }
		fscanf(fp, "%s", check);
                 fscanf(fp, " %d" , &number_of_outputs);
               
               output_table = allocate_matrix(pow(2,number_of_inputs), number_of_outputs); //
                for(int i=0; i<number_of_outputs; i++){
                    fscanf(fp, "%s ", outputvar);
			strcpy(output_table[i].name, outputvar);
                }
        }
       
        else if(check[0] == 'O'){
           	//fscanf(fp1, "%*[^\n]\n");
	
                 fscanf(fp, " %d" , &number_of_outputs);
               
                output_table = allocate_matrix(pow(2,number_of_outputs), number_of_outputs);
                for(int i=0; i<number_of_outputs; i++){
                    fscanf(fp, "%s ", outputvar);
			strcpy(output_table[i].name, outputvar);
                }
			fscanf(fp, "%s", check);
             fscanf(fp1, "\n%d" , &number_of_inputs);
               
                input_table = allocate_matrix(pow(2,number_of_inputs), number_of_inputs);
                for(int i=0; i<number_of_inputs; i++){
                    fscanf(fp1, "%s ", inputvar);
		
			strcpy(input_table[i].name, inputvar);
			
                }
		
            fp = fp1;
      
        }
       
        else{
            printf("error\n");
            exit(0);
        }
       
	gray_code(input_table, pow(2,number_of_inputs), number_of_inputs);
	
	struct LLnode* head = NULL;
	char temp[25];
	int rows = pow(2,number_of_inputs);

	while(fscanf(fp, "%s ", temp) != EOF){
	
		if(strcmp(temp,"AND")==0){
				char var1[25];
				fscanf(fp,"%s ", var1);
				char var2[25];
				fscanf(fp,"%s ", var2);
				char out[25];
				fscanf(fp,"%s ", out);
				int* array1;
				int* array2;
				int* output;
				int c1 = search_in_table(var1,number_of_inputs, input_table);
				if(c1 == -1){

					if(strcmp(var1,"0") ==0){
						array1 = malloc( rows * sizeof(struct node));
						for(int i=0; i<rows; i++){
							array1[i] = 0;
						}
					}

					else if(strcmp(var1,"1") ==0){
						array1 = malloc( rows * sizeof(struct node));
						for(int i=0; i<rows; i++){
							array1[i] = 1;
						}
					}
					else{
						array1 = search_in_LL(var1,number_of_inputs,head);
					}
					
				}
				else{
					array1 = input_table[c1].array;
				}
				int c2 = search_in_table(var2,number_of_inputs, input_table);
				if(c2 == -1){
						if(strcmp(var2,"0") ==0){
						array2 = malloc( rows * sizeof(struct node));
						for(int i=0; i<rows; i++){
							array2[i] = 0;
						}
					}

					else if(strcmp(var2,"1") ==0){
						array2 = malloc( rows * sizeof(struct node));
						for(int i=0; i<rows; i++){
							array2[i] = 1;
						}
					}
					else{
						array2 = search_in_LL(var2,number_of_inputs,head);
					}

				}
				else{
					array2 = input_table[c2].array;
				}
				output = malloc(rows * (sizeof(int)));

				for(int i=0; i<rows; i++){
					output[i] = AND(array1[i],array2[i]);
				}
				
				int out1 = search_in_table(out,number_of_outputs, output_table);
				
				if(out1 == -1){
					head = add_LL(head,out,output);
				}
				else{
					output_table[out1].array = output;
				}
				
			}
		else if(strcmp(temp,"OR")==0){

					char var1[25];
				fscanf(fp,"%s ", var1);
				char var2[25];
				fscanf(fp,"%s ", var2);
				char out[25];
				fscanf(fp,"%s ", out);
				int* array1;
				int* array2;
				int* output;
				int c1 = search_in_table(var1,number_of_inputs, input_table);
				if(c1 == -1){
					if(strcmp(var1,"0") ==0){
						array1 = malloc( rows * sizeof(struct node));
						for(int i=0; i<rows; i++){
							array1[i] = 0;
						}
					}

					else if(strcmp(var1,"1") ==0){
						array1 = malloc( rows * sizeof(struct node));
						for(int i=0; i<rows; i++){
							array1[i] = 1;
						}
					}
					else{
						array1 = search_in_LL(var1,number_of_inputs,head);
					}
				}
				else{
					array1 = input_table[c1].array;
				}
				int c2 = search_in_table(var2,number_of_inputs, input_table);
				if(c2 == -1){
					if(strcmp(var2,"0") ==0){
					array2 = malloc( rows * sizeof(struct node));
					for(int i=0; i<rows; i++){
						array2[i] = 0;
					}
					}

					else if(strcmp(var2,"1") ==0){
						array2 = malloc( rows * sizeof(struct node));
						for(int i=0; i<rows; i++){
							array2[i] = 1;
						}
					}
					else{
						array2 = search_in_LL(var2,number_of_inputs,head);
					}
				}
				else{
					array2 = input_table[c2].array;
				}
				output = malloc(rows * (sizeof(int)));

				for(int i=0; i<rows; i++){
					output[i] = OR(array1[i],array2[i]);
				}
				
				int out1 = search_in_table(out,number_of_outputs, output_table);
				
				if(out1 == -1){
					head = add_LL(head,out,output);
				}
				else{
					output_table[out1].array = output;
				}
			}
		else if(strcmp(temp,"NAND")==0){

				char var1[25];
				fscanf(fp,"%s ", var1);
				char var2[25];
				fscanf(fp,"%s ", var2);
				char out[25];
				fscanf(fp,"%s ", out);
				int* array1;
				int* array2;
				int* output;
				int c1 = search_in_table(var1,number_of_inputs, input_table);
				if(c1 == -1){
					if(strcmp(var1,"0") ==0){
						array1 = malloc( rows * sizeof(struct node));
						for(int i=0; i<rows; i++){
							array1[i] = 0;
						}
					}

					else if(strcmp(var1,"1") ==0){
						array1 = malloc( rows * sizeof(struct node));
						for(int i=0; i<rows; i++){
							array1[i] = 1;
						}
					}
					else{
						array1 = search_in_LL(var1,number_of_inputs,head);
					}
				}
				else{
					array1 = input_table[c1].array;
				}
				int c2 = search_in_table(var2,number_of_inputs, input_table);
				if(c2 == -1){
					if(strcmp(var2,"0") ==0){
					array2 = malloc( rows * sizeof(struct node));
					for(int i=0; i<rows; i++){
						array2[i] = 0;
					}
					}

					else if(strcmp(var2,"1") ==0){
						array2 = malloc( rows * sizeof(struct node));
						for(int i=0; i<rows; i++){
							array2[i] = 1;
						}
					}
					else{
						array2 = search_in_LL(var2,number_of_inputs,head);
					}
				}
				else{
					array2 = input_table[c2].array;
				}
				output = malloc(rows * (sizeof(int)));

				for(int i=0; i<rows; i++){
					output[i] = NAND(array1[i],array2[i]);
				}
				
				int out1 = search_in_table(out,number_of_outputs, output_table);
				
				if(out1 == -1){
					head = add_LL(head,out,output);
				}
				else{
					output_table[out1].array = output;
				}
			}
		else if(strcmp(temp,"NOR")==0){
				char var1[25];
				fscanf(fp,"%s ", var1);
				char var2[25];
				fscanf(fp,"%s ", var2);
				char out[25];
				fscanf(fp,"%s ", out);
				int* array1;
				int* array2;
				int* output;
				int c1 = search_in_table(var1,number_of_inputs, input_table);
				if(c1 == -1){
					if(strcmp(var1,"0") ==0){
						array1 = malloc( rows * sizeof(struct node));
						for(int i=0; i<rows; i++){
							array1[i] = 0;
						}
					}

					else if(strcmp(var1,"1") ==0){
						array1 = malloc( rows * sizeof(struct node));
						for(int i=0; i<rows; i++){
							array1[i] = 1;
						}
					}
					else{
						array1 = search_in_LL(var1,number_of_inputs,head);
					}
				}
				else{
					array1 = input_table[c1].array;
				}
				int c2 = search_in_table(var2,number_of_inputs, input_table);
				if(c2 == -1){
					if(strcmp(var2,"0") ==0){
					array2 = malloc( rows * sizeof(struct node));
					for(int i=0; i<rows; i++){
						array2[i] = 0;
					}
					}

					else if(strcmp(var2,"1") ==0){
						array2 = malloc( rows * sizeof(struct node));
						for(int i=0; i<rows; i++){
							array2[i] = 1;
						}
					}
					else{
						array2 = search_in_LL(var2,number_of_inputs,head);
					}
				}
				else{
					array2 = input_table[c2].array;
				}
				output = malloc(rows * (sizeof(int)));

				for(int i=0; i<rows; i++){
					output[i] = NOR(array1[i],array2[i]);
				}
				
				int out1 = search_in_table(out,number_of_outputs, output_table);
				
				if(out1 == -1){
					head = add_LL(head,out,output);
				}
				else{
					output_table[out1].array = output;
				}
			}
		else if(strcmp(temp,"XOR")==0){
				char var1[25];
				fscanf(fp,"%s ", var1);
				char var2[25];
				fscanf(fp,"%s ", var2);
				char out[25];
				fscanf(fp,"%s ", out);
				int* array1;
				int* array2;
				int* output;
				int c1 = search_in_table(var1,number_of_inputs, input_table);
				if(c1 == -1){
					if(strcmp(var1,"0") ==0){
						array1 = malloc( rows * sizeof(struct node));
						for(int i=0; i<rows; i++){
							array1[i] = 0;
						}
					}

					else if(strcmp(var1,"1") ==0){
						array1 = malloc( rows * sizeof(struct node));
						for(int i=0; i<rows; i++){
							array1[i] = 1;
						}
					}
					else{
						array1 = search_in_LL(var1,number_of_inputs,head);
					}
				}
				else{
					array1 = input_table[c1].array;
				}
				int c2 = search_in_table(var2,number_of_inputs, input_table);
				if(c2 == -1){
					if(strcmp(var2,"0") ==0){
					array2 = malloc( rows * sizeof(struct node));
					for(int i=0; i<rows; i++){
						array2[i] = 0;
					}
					}

					else if(strcmp(var2,"1") ==0){
						array2 = malloc( rows * sizeof(struct node));
						for(int i=0; i<rows; i++){
							array2[i] = 1;
						}
					}
					else{
						array2 = search_in_LL(var2,number_of_inputs,head);
					}
				}
				else{
					array2 = input_table[c2].array;
				}
				output = malloc(rows * (sizeof(int)));

				for(int i=0; i<rows; i++){
					output[i] = XOR(array1[i],array2[i]);
				}
				
				int out1 = search_in_table(out,number_of_outputs, output_table);
				
				if(out1 == -1){
					head = add_LL(head,out,output);
				}
				else{
					output_table[out1].array = output;
				}
			}
		else if(strcmp(temp,"XNOR")==0){
				char var1[25];
				fscanf(fp,"%s ", var1);
				char var2[25];
				fscanf(fp,"%s ", var2);
				char out[25];
				fscanf(fp,"%s ", out);
				int* array1;
				int* array2;
				int* output;
				int c1 = search_in_table(var1,number_of_inputs, input_table);
				if(c1 == -1){
					if(strcmp(var1,"0") ==0){
						array1 = malloc( rows * sizeof(struct node));
						for(int i=0; i<rows; i++){
							array1[i] = 0;
						}
					}

					else if(strcmp(var1,"1") ==0){
						array1 = malloc( rows * sizeof(struct node));
						for(int i=0; i<rows; i++){
							array1[i] = 1;
						}
					}
					else{
						array1 = search_in_LL(var1,number_of_inputs,head);
					}
				}
				else{
					array1 = input_table[c1].array;
				}
				int c2 = search_in_table(var2,number_of_inputs, input_table);
				if(c2 == -1){
					if(strcmp(var2,"0") ==0){
					array2 = malloc( rows * sizeof(struct node));
					for(int i=0; i<rows; i++){
						array2[i] = 0;
					}
					}

					else if(strcmp(var2,"1") ==0){
						array2 = malloc( rows * sizeof(struct node));
						for(int i=0; i<rows; i++){
							array2[i] = 1;
						}
					}
					else{
						array2 = search_in_LL(var2,number_of_inputs,head);
					}
				}
				else{
					array2 = input_table[c2].array;
				}
				output = malloc(rows * (sizeof(int)));

				for(int i=0; i<rows; i++){
					output[i] = XNOR(array1[i],array2[i]);
				}
				
				int out1 = search_in_table(out,number_of_outputs, output_table);
				
				if(out1 == -1){
					head = add_LL(head,out,output);
				}
				else{
					output_table[out1].array = output;
				}
			}
		else if(strcmp(temp,"NOT")==0){
				char var1[25];
				fscanf(fp,"%s ", var1);
				char out[25];
				fscanf(fp,"%s ", out);
				int* array1;
				int* output;
				int c1 = search_in_table(var1,number_of_inputs, input_table);
				if(c1 == -1){
					if(strcmp(var1,"0") ==0){
					array1 = malloc( rows * sizeof(struct node));
					for(int i=0; i<rows; i++){
						array1[i] = 0;
						}
					}

					else if(strcmp(var1,"1") ==0){
						array1 = malloc( rows * sizeof(struct node));
						for(int i=0; i<rows; i++){
							array1[i] = 1;
						}
					}
					else{
						array1 = search_in_LL(var1,number_of_inputs,head);
					}
				}
				else{
					array1 = input_table[c1].array;
				}
				output = malloc(rows * (sizeof(int)));

				for(int i=0; i<rows; i++){
					output[i] = NOT(array1[i]);
				}
				int out1 = search_in_table(out,number_of_outputs, output_table);
				if(out1 == -1){
					head = add_LL(head,out,output);
				}
				else{
					output_table[out1].array = output;
				}
				
				
			}
		else if(strcmp(temp,"DECODER")==0){
				
				struct node* head_input = NULL;
				struct node* head_output= NULL;
				int inputs;
				char var1[25];
				fscanf(fp,"%d ", &inputs);
				int outputs = pow(2,inputs);

				head_input = allocate_matrix(rows, inputs);
               			 for(int i=0; i<inputs; i++){
                   			 fscanf(fp, " %s", var1);
					strcpy(head_input[i].name, var1);
					int* array1;
					int c1 = search_in_table(var1,number_of_inputs, input_table);
					if(c1 == -1){
							if(strcmp(var1,"0") ==0){
							array1 = malloc( rows * sizeof(struct node));
							for(int i=0; i<rows; i++){
								array1[i] = 0;
							}
						}

						else if(strcmp(var1,"1") ==0){
							array1 = malloc( rows * sizeof(struct node));
							for(int i=0; i<rows; i++){
								array1[i] = 1;
							}
						}
						else{
							array1 = search_in_LL(var1,number_of_inputs,head);
						}

					}
					else{
					array1 = input_table[c1].array;
					}
					head_input[i].array = array1;
				}
					
					head_output = allocate_matrix(rows, outputs);

				for(int i=0; i< outputs; i++){
			
					 fscanf(fp, " %s", var1);
					strcpy(head_output[i].name, var1);
					int* array1;
					int* output;
					output = malloc(rows * (sizeof(int)));
						for(int i =0; i<rows ; i++){
							output[i] = 0;
						}
						//head = add_LL(head , var1, output);
						array1 = output;
					
						head_output[i].array = array1;
				}
			
			
					for(int i = 0; i<rows; i++){
					
					int* temp = malloc(inputs* sizeof(int));
					
					for(int j=0; j<inputs; j++){
						temp[j] = head_input[j].array[i];
					}
					
					int index_out = gray_to_index(temp, inputs);
					//printf(" %d \n", index_out);
					head_output[index_out].array[i] = 1;
					}

				for(int i=0; i<outputs ; i++){
				
				int out1 = search_in_table(head_output[i].name ,number_of_outputs, output_table);
				
				if(out1 == -1){
					head = add_LL(head,head_output[i].name,head_output[i].array);
				}
				else{
					output_table[out1].array = head_output[i].array;
				}
					
				}	 
						

			}
		else if(strcmp(temp,"MULTIPLEXER")==0){


				struct node* head_input = NULL;
				struct node* head_output= NULL;
				struct node* head_final = NULL;
				int inputs;
				char var1[25];
				fscanf(fp,"%d ", &inputs);
				int selectors = log(inputs)/log(2);

				head_input = allocate_matrix(rows, inputs);
               			 for(int i=0; i<inputs; i++){
                   			 fscanf(fp, " %s", var1);
					strcpy(head_input[i].name, var1);
					int* array1;
					int c1 = search_in_table(var1,number_of_inputs, input_table);
					if(c1 == -1){
									if(strcmp(var1,"0") ==0){
								array1 = malloc( rows * sizeof(struct node));
								for(int i=0; i<rows; i++){
									array1[i] = 0;
								}
							}

							else if(strcmp(var1,"1") ==0){
								array1 = malloc( rows * sizeof(struct node));
								for(int i=0; i<rows; i++){
									array1[i] = 1;
								}
							}
							else{
								array1 = search_in_LL(var1,number_of_inputs,head);
							}
					}
					else{
					array1 = input_table[c1].array;
					}
					head_input[i].array = array1;
				}
					
					head_output = allocate_matrix(rows, selectors);

				for(int i=0; i< selectors; i++){
			
					 fscanf(fp, " %s", var1);
					strcpy(head_output[i].name, var1);
					int* array1;
					int c1 = search_in_table(var1,number_of_inputs, input_table);
					if(c1 == -1){
									if(strcmp(var1,"0") ==0){
								array1 = malloc( rows * sizeof(struct node));
								for(int i=0; i<rows; i++){
									array1[i] = 0;
								}
							}

							else if(strcmp(var1,"1") ==0){
								array1 = malloc( rows * sizeof(struct node));
								for(int i=0; i<rows; i++){
									array1[i] = 1;
								}
							}
							else{
								array1 = search_in_LL(var1,number_of_inputs,head);
							}
					}
					else{
						array1 = input_table[c1].array;
					}
					head_output[i].array = array1;
				}
					head_final  = malloc( sizeof(struct node));

					fscanf(fp, " %s", var1);
					strcpy(head_final->name, var1);
					int* array1;
					int* output;
					output = malloc(rows * (sizeof(int)));
						for(int i =0; i<rows ; i++){
							output[i] = 0;
						}
						//head = add_LL(head , var1, output);
						array1 = output;
					
						head_final->array = array1;
				
					for(int i=0; i<rows; i++){
						int* temp = malloc( selectors* sizeof(int));

						for(int j=0; j<selectors; j++){
							temp[j] = head_output[j].array[i];
						}
						int index_out = gray_to_index(temp, selectors);
	
						if(head_input[index_out].array[i] == 1){
							head_final->array[i] = 1;
						}	
			
					}

						int out1 = search_in_table(head_final->name ,number_of_outputs, output_table);
				
						if(out1 == -1){
							head = add_LL(head,head_final->name,head_final->array);
						}
						else{
							output_table[out1].array = head_final->array;
						}

				
			}

	}   


	print_all(input_table, output_table, number_of_inputs, number_of_outputs,rows);

	
return 0;
}
   

















