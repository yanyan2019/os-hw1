#include "movie.h"

// parse lines and input data into movie structs
struct movie *createMovie(char *currLine){
	
	struct movie *currMovie = malloc(sizeof(struct movie));

	// pointer for using strtok_r
	char *ptr;

	// total number of languages
	int langSize = 5;

	// token for title
	char *token = strtok_r(currLine, ",", &ptr);
	currMovie->title = calloc(strlen(token)+1, sizeof(char));
	strcpy(currMovie->title, token);
//	printf("name: %s ", currMovie->title);	

	// token for year
	token = strtok_r(NULL, ",", &ptr);
	currMovie->year = atoi(token);
//	printf("year: %i ", currMovie->year);

	// token for languages
	token = strtok_r(NULL, ",", &ptr);
	// remove the brackets
	char *token2 = strtok_r(NULL, "[", &token);
	token = strtok_r(NULL, "]", &token2);
	// allocate dynamic array for languages 
	currMovie->lang = calloc(strlen(token)+1, sizeof(char)*langSize);
	int i;
//	printf("lang: ");
	// dynamic array for languages
	for(i = 0; i < langSize; i++){
		currMovie->lang[i] = (char*)malloc(langSize+1);
		currMovie->lang[i] = strtok_r(NULL, ";", &token);
//		if(currMovie->lang[i] != NULL){
//			
//			printf("%s, ", currMovie->lang[i]);
//		}
	}	
//	printf("\n");

	// token for rating
	token = strtok_r(NULL, ",", &ptr);
	currMovie->rating = strtod(token, NULL);
//	printf("rating: %.1f\n", currMovie->rating);

	// token for 
	// set the next node to null
	currMovie->next = NULL;
	return currMovie;	
}

// takes the file path input and parse the data
struct movie *processFile(char *filePath, int *m_count){
  	// read file 
  	FILE *movieFile = fopen(filePath, "r");
  	char *currLine = NULL;
  	size_t len = 0;
  	size_t nread;
  	char *token;
	

  	// head and tail of the linked list
  	struct movie *head = NULL;
  	struct movie *tail = NULL;

	// skip the first line of the csv file
	getline(&currLine, &len,movieFile);	

	// read file line by line until the end of file	
  	while((nread = getline(&currLine, &len, movieFile)) != -1 ) {

		// call function to input data into movie struct
		struct movie *newNode = createMovie(currLine);
		if(head == NULL){
			head = newNode;
			tail = newNode;
		}else{
			tail->next = newNode;
			tail = newNode;
		}
		
		//count number of movies
		*m_count += 1;
  	}

	// free space and close files
	free(currLine);	
	fclose(movieFile);
	return head;
}

// user interactive function
void interactive(){
	int input = 0;
	// loop until user exit
	while(input != 4){

		printf("1. Show movies released the in the sepcified year\n");
		printf("2. Show highest rated movie for each year\n");
		printf("3. Show the title and year of release of all movies in a specific language\n");
		printf("4. Exit the Program\n\n");
		printf("Enter a choice from 1 to 4: ");

		scanf("%i", &input);
		if(input > 4 || input < 1){
			printf("You entered an incorrect choice. Try again.\n\n");
		}
	}
	return;
}

int main(int argc, char *argv[]){
	// print failure message if incorrect input
  	if(argc < 2){
     		printf("you must provide the name of the file to process\n");
     		printf("example usage: ./movies movie_sample_1.csv\n");
     		return EXIT_FAILURE;
  	}	 

	// call function to parse file
	int m_count = 0;
	struct movie *list = processFile(argv[1], &m_count);
  	printf("Processed file %s and parsed data for %i movies\n\n", argv[1], m_count);

	// call inteactive function
	interactive();		

  	return EXIT_SUCCESS;
}
