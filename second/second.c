#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<stdbool.h>

struct node{
    char name[25];
    int* array;
};

struct BigLL{
	char name[25];
	struct BigLL* next;
	struct SmallLL* sl;
};

struct SmallLL{
	char name[25];
	struct SmallLL* next;
};

struct LLnode{
	char name[25];
	int* array;
	struct LLnode* next;
};

struct BigLL* big_head = NULL;
struct SmallLL* small_head = NULL;
struct SmallLL* known  = NULL;

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
struct BigLL* insert_big(struct BigLL* temp , char* tk);
struct SmallLL* insert_small(struct BigLL* temp, struct SmallLL* sml, char* tk);
struct BigLL* move_it_back(struct BigLL* ptr);
bool search_in_known(char* ch);
void add_to( char* ch);
int get_inputs( char* ch, struct BigLL* ptr);




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


struct SmallLL* insert_small(struct BigLL* temp, struct SmallLL* sml, char* tk){
	
	struct SmallLL* tp = sml;
	struct SmallLL* ret = malloc(sizeof(struct SmallLL));
	strcpy(ret->name, tk);
	ret->next = NULL;
	
	if(temp->sl == NULL){
		small_head = ret;
		temp->sl = small_head;
		return small_head;
	}

	while( tp->next != NULL){
		tp = tp->next;
	}
	
	tp->next = ret;
	return small_head;

}




struct BigLL* insert_big(struct BigLL* temp , char* tk){
	
	struct BigLL* tp = temp;
	struct BigLL* ret = malloc(sizeof(struct BigLL));
	strcpy(ret->name, tk);
	ret->next = NULL;
	ret->sl = NULL;

	if(strcmp(tk,"INPUTVAR")==0  || strcmp(tk,"OUTPUTVAR")==0){
	
		big_head = ret;
		ret->next = tp;
		return big_head;
	}
	else{

		if(temp == NULL){
			big_head = ret;
			return big_head;
		}

		while(tp->next != NULL){
			tp = tp->next;
		}
		
		tp->next = ret;
		return ret;
	}

}


struct BigLL* move_it_back(struct BigLL* ptr){

	struct BigLL* ret = ptr->next;
	struct BigLL* tp = ptr;
	struct BigLL* tpp = big_head;

	while(tpp->next != tp){
		tpp = tpp->next;
	}
	ret = tpp;
	tpp->next = tp->next;
	
	while(tpp->next != NULL){
		tpp = tpp->next;
	}
	
	tpp->next = tp;
	tp->next = NULL;
	return ret;	
	
}





bool search_in_known(char* ch){
	
	if(strcmp(ch,"0")==0 || strcmp(ch, "1")==0){
		return true;
	}	

	struct SmallLL* tp = known;
	while(tp != NULL){
		if(strcmp(tp->name, ch) == 0){
			return true;
		}
		tp = tp->next;
	}
	return false;
}







void add_to( char* ch){

	struct SmallLL* t = malloc(sizeof(struct SmallLL));
	strcpy(t->name , ch);
	t->next = NULL;	

	if(known == NULL){
		known = t;
	}
	else{
		struct SmallLL* ptr = known;
		t->next = ptr;
		known = t;
	
	}
	
}

int get_inputs( char* ch, struct BigLL* ptr){
	
	if(strcmp(ch, "AND") == 0 || strcmp(ch, "NAND") == 0 || strcmp(ch, "OR") == 0 || strcmp(ch, "NOR") == 0 || strcmp(ch, "XOR") == 0 || strcmp(ch, "XNOR") == 0){

	return 2;
}
	else if(strcmp(ch, "NOT") == 0){
		return 1;
	}


	else if(strcmp(ch, "DECODER") == 0){
		int t = atoi(ptr->sl->name)+1;
		return t;
	}
	else if(strcmp(ch,"MULTIPLEXER") == 0){
		int t= atoi(ptr->sl->name);
		t = t+ (log(t)/log(2))+1;
		return t;

	}
return -1;

}




int main(int argc ,char** argv){
    if(argc > 2){
        printf("Error\n");
        exit(0);
    }
   
    FILE* fp = fopen(argv[1], "r");
   
    //FILE* fp1= fp;
     
    int number_of_inputs;  
    int number_of_outputs;
    char check[200];
    char inputvar[25];
    char outputvar[25];
struct node* input_table;
struct node* output_table;


	while( fscanf(fp, "%[^\n]\n" , check) != EOF){


	char* tk = strtok(check," ");
	struct BigLL* temp = big_head;
	struct SmallLL* sml = small_head;
	int counter=0;

	while(tk != NULL){
			if(counter ==0){
	// insert the token to bigLL and check if token is inputvar or outputvar..!! then create it the the head; or add the the end of the LL and return a pointer
		temp = insert_big(temp,tk);
	
			}
			else{
			sml = insert_small(temp,sml,tk);
			// add the other elements inside the smallLL
			}
		tk = strtok(NULL," ");
		counter++;
		}

	}	
// sorting starts here

	
	
	struct BigLL* ptr = big_head;
	
	for(int i=0; i<2; i++){
		struct SmallLL* list = ptr->sl;
		while(list != NULL){
			add_to(list->name);
			list = list->next;
		}
		ptr = ptr->next;
	}

	while(ptr != NULL){
		struct SmallLL* list = ptr->sl;
	int counter = 0;
	int inp = get_inputs(ptr->name , ptr);

		while(list != NULL){
			if( counter < inp){
			
				if(counter == 0){
					if(atoi(list->name) >0){
						counter++;
						list = list->next;
						continue;
					}
				}
				if(search_in_known(list->name)){
				counter++;
				list = list->next;
				continue;	
				}
				else{
					ptr = move_it_back(ptr); 
					break;
				}
			}
			else {
				add_to(list->name);
				list = list->next;
			}		
		}
			if(ptr == NULL){
				break;
			}
			ptr = ptr->next;
	}



	strcpy(check, big_head->name);


   
 //   fscanf(fp, "%s", check);
   
        if(check[0] == 'I'){

           	number_of_inputs = atoi(big_head->sl->name);
               struct SmallLL* hp = big_head->sl->next;
                input_table = allocate_matrix(pow(2,number_of_inputs), number_of_inputs);
                for(int i=0; i<number_of_inputs; i++){
			
			strcpy(inputvar,hp->name);
			hp = hp->next;
                   // fscanf(fp, " %s", inputvar);
			strcpy(input_table[i].name, inputvar);
			
                }
	
		strcpy(check, big_head->next->name);
		number_of_outputs = atoi(big_head->next->sl->name);
		/*fscanf(fp, "%s", check);
                 fscanf(fp, " %d" , &number_of_outputs);*/

               struct SmallLL* hpp = big_head->next->sl->next;
               output_table = allocate_matrix(pow(2,number_of_outputs), number_of_outputs);
                for(int i=0; i<number_of_outputs; i++){
			strcpy(outputvar, hpp->name);
			hpp = hpp->next;
                    //fscanf(fp, "%s ", outputvar);
			strcpy(output_table[i].name, outputvar);
                }
        }
       
        else if(check[0] == 'O'){
           	number_of_inputs = atoi(big_head->next->sl->name);
             //fscanf(fp1, "\n%d" , &number_of_inputs);
                struct SmallLL* hp = big_head->next->sl->next;
                input_table = allocate_matrix(pow(2,number_of_inputs), number_of_inputs);
			
                for(int i=0; i<number_of_inputs; i++){
                  //  fscanf(fp1, "%s ", inputvar);
			strcpy(inputvar,hp->name);
			hp = hp->next;
			strcpy(input_table[i].name, inputvar);
			
                }

		strcpy(check, big_head->next->name);
		number_of_outputs = atoi(big_head->sl->name);
		/*fscanf(fp, "%s", check);
                 fscanf(fp, " %d" , &number_of_outputs);*/
               
                output_table = allocate_matrix(pow(2,number_of_outputs), number_of_outputs);
		struct SmallLL* hpp = big_head->sl->next;
                for(int i=0; i<number_of_outputs; i++){
                   // fscanf(fp, "%s ", outputvar);
			strcpy(outputvar, hpp->name);
			hpp = hpp->next;
			strcpy(output_table[i].name, outputvar);
                }
        }
       
        else{
            printf("error\n");
            exit(0);
        }
       
	gray_code(input_table, pow(2,number_of_inputs), number_of_inputs);
	
	struct LLnode* head = NULL;
	//char temp[25];
	int rows = pow(2,number_of_inputs);

	struct BigLL* yash = big_head->next->next;

	while(yash != NULL){
	
		if(strcmp(yash->name,"AND")==0){
				char var1[25];
				//fscanf(fp,"%s ", var1);
				strcpy(var1,yash->sl->name);
				char var2[25];
				//fscanf(fp,"%s ", var2);
				strcpy(var2, yash->sl->next->name);
				char out[25];
				//fscanf(fp,"%s ", out);
				strcpy(out,yash->sl->next->next->name);
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
		else if(strcmp(yash->name,"OR")==0){

				char var1[25];
				//fscanf(fp,"%s ", var1);
				strcpy(var1,yash->sl->name);
				char var2[25];
				//fscanf(fp,"%s ", var2);
				strcpy(var2, yash->sl->next->name);
				char out[25];
				//fscanf(fp,"%s ", out);
				strcpy(out,yash->sl->next->next->name);
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
		else if(strcmp(yash->name,"NAND")==0){

				char var1[25];
				//fscanf(fp,"%s ", var1);
				strcpy(var1,yash->sl->name);
				char var2[25];
				//fscanf(fp,"%s ", var2);
				strcpy(var2, yash->sl->next->name);
				char out[25];
				//fscanf(fp,"%s ", out);
				strcpy(out,yash->sl->next->next->name);
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
		else if(strcmp(yash->name,"NOR")==0){
				char var1[25];
				//fscanf(fp,"%s ", var1);
				strcpy(var1,yash->sl->name);
				char var2[25];
				//fscanf(fp,"%s ", var2);
				strcpy(var2, yash->sl->next->name);
				char out[25];
				//fscanf(fp,"%s ", out);
				strcpy(out,yash->sl->next->next->name);
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
		else if(strcmp(yash->name,"XOR")==0){
				char var1[25];
				//fscanf(fp,"%s ", var1);
				strcpy(var1,yash->sl->name);
				char var2[25];
				//fscanf(fp,"%s ", var2);
				strcpy(var2, yash->sl->next->name);
				char out[25];
				//fscanf(fp,"%s ", out);
				strcpy(out,yash->sl->next->next->name);
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
		else if(strcmp(yash->name,"XNOR")==0){
				char var1[25];
				//fscanf(fp,"%s ", var1);
				strcpy(var1,yash->sl->name);
				char var2[25];
				//fscanf(fp,"%s ", var2);
				strcpy(var2, yash->sl->next->name);
				char out[25];
				//fscanf(fp,"%s ", out);
				strcpy(out,yash->sl->next->next->name);
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
		else if(strcmp(yash->name,"NOT")==0){


				char var1[25];
				//fscanf(fp,"%s ", var1);
				strcpy(var1,yash->sl->name);
				char out[25];
				//fscanf(fp,"%s ", var2);
				strcpy(out, yash->sl->next->name);
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
		else if(strcmp(yash->name,"DECODER")==0){
				
				struct node* head_input = NULL;
				struct node* head_output= NULL;
				int inputs;
				char var1[25];
				inputs = atoi(yash->sl->name);
				//fscanf(fp,"%d ", &inputs);
				int outputs = pow(2,inputs);

				struct SmallLL* ykp = yash->sl->next;
				head_input = allocate_matrix(rows, inputs);
               			 for(int i=0; i<inputs; i++){
                   			// fscanf(fp, " %s", var1);
					strcpy(var1 ,ykp->name);
					ykp = ykp->next;
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
			
					// fscanf(fp, " %s", var1);
					strcpy(var1 ,ykp->name);
					ykp = ykp->next;
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
		else if(strcmp(yash->name,"MULTIPLEXER")==0){


				struct node* head_input = NULL;
				struct node* head_output= NULL;
				struct node* head_final = NULL;
				int inputs;
				char var1[25];
				inputs = atoi(yash->sl->name);
				fscanf(fp,"%d ", &inputs);
				int selectors = log(inputs)/log(2);
				struct SmallLL* ykp = yash->sl->next;

				head_input = allocate_matrix(rows, inputs);
               			 for(int i=0; i<inputs; i++){
                   			// fscanf(fp, " %s", var1);
					strcpy(var1 ,ykp->name);
					ykp = ykp->next;
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
			
					// fscanf(fp, " %s", var1);
					strcpy(var1 ,ykp->name);
					ykp = ykp->next;
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

					//fscanf(fp, " %s", var1);
					strcpy(var1 ,ykp->name);
					ykp = ykp->next;
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
		yash = yash->next;

	}   


	print_all(input_table, output_table, number_of_inputs, number_of_outputs,rows);

	
return 0;
}

