#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define S1_E 9
#define S2_E 18
#define S3_E 20
#define COLS 17
#define ROWS 20
void print_arr_int(int* arr, int len){
  for(int i = 0; i < len; i++){
    printf("%d ", arr[i]);
  } 
  printf("\n");
}
void print_cypher(int (*cypher)[COLS], int rows){
  // Prints the cypher text. If it prints random values,
  // then you made some error in writing down the cypher
  // translation
  for(int i=0; i < rows; i++){
    for(int j=0; j < COLS; j++){
      printf("%d ", cypher[i][j]);
    }
    printf("\n");
  }
}
int* transpose_section_1(int (*cypher)[COLS]){
  // Applies the transposition matrix to 
  // the first section of the cypher.
  // Returns a pointer to an array that contains
  // the re-ordered cypher.
  int *arr = malloc(S1_E*17*sizeof(int));
  int index=0; 
  for(int s=0; s < COLS; s++){ // s is the starting point
    int c = 0; 
    int j = s;
    int i = 0;
    for(;c < 9; ++c, ++i, j+=2){
      i = i % S1_E;
      j = j % COLS;
      arr[index++] = cypher[i][j];
    }
  }
  return arr;
}
char* decode(int* arr, char* convs){ 
  // Takes in input the array containing
  // symbols (integers) and maps them
  // to characters using the rules provided
  // in the file (first argument)
  // The file must contain in the first line the
  // number of rules, followed by the rules in this format:
  // <int> <char>
  FILE *file = fopen(convs, "r");
  if (file == NULL){
    printf("Erorr in opening the file");
    return NULL;
  }
  int symbols;
  fscanf(file, "%d", &symbols);
  printf("Reading %d symbols\n", symbols);
  char *decoded = (char*)malloc(S1_E*COLS+1);
  char *symbol_table = (char*)malloc(symbols); // +1 because of an error
  for(int i =0; i<symbols; i++){
    int index;
    fscanf(file, "%d", &index);
    fscanf(file, " %c", &symbol_table[index]);
  }
  printf("Symbol table build.\n");
  for(int i = 0; i < S1_E*COLS; i++){
    decoded[i] = symbol_table[arr[i]];
  }
  decoded[S1_E*COLS] = '\0';
  free(symbol_table);
  return decoded;
}
void print_transposed(int *arr){
  printf("Printing cypher after transposition: \n");
  for(int i=0; i < S1_E; i++){
    for(int j=0; j < COLS; j++){
      printf("%d ", arr[i*COLS + j]); 
    }
    printf("\n");
  }
}
int main(int argc, char **argv){
  // Z340 decrypter. Applies a transposition matrix
  // and a homophonic subsitution by using a custom
  // parser.
  int cypher [ROWS][COLS];
  for(int i=0; i < ROWS; i++){
    for(int j = 0; j < COLS; j++){
      int value;
      scanf("%d", &value);
      cypher[i][j] = value;
    }
  }
  print_cypher(cypher, ROWS);
  int* transposed_1= transpose_section_1(cypher);
  print_transposed(transposed_1);
  char* solution = decode(transposed_1,argv[1]);
  printf("%s\n", solution);
  free(transposed_1); 
  return 0;
}
