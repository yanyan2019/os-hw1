#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct formovie information
struct movie{
	char   	*title;
 	int	year;
  	char   	*languages;
  	float  	rating;
  	struct	movie  *next;
};

// parse lines and input data into movie structs
struct movie *createMovie(char *currLine){
	
	struct movie *currMovie = malloc(sizeof(struct movie));

	// pointer for using strtok_r
	char *ptr;

	// token for title
	char *token = strtok_r(currLine, ",", &ptr);
	currMovie->title = calloc(strlen(token)+1, sizeof(char));
	strcpy(currMovie->title, token);
	printf("name: %s\n", currMovie->title);	

	// token for year
	token = strtok_r(NULL, ",", &ptr);
	currMovie->year = atoi(token);
	printf("year: %i\n", currMovie->year);

	// token for languages
	token = strtok_r(NULL, ",", &ptr);
//	printf("lang: %s\n", token);
//	currMovie->languages = calloc(strlen());
	

	// set the next node to null
	currMovie->next = NULL;
	return currMovie;	
}

// takes the file path input and parse the data
struct movie *processFile(char *filePath){
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
  	}

	// free space and close files
	free(currLine);	
	fclose(movieFile);
	return head;
}

int main(int argc, char *argv[]){
	// print failure message if incorrect input
  	if(argc < 2){
     		printf("you must provide the name of the file to process\n");
     		printf("example usage: ./movies movie_sample_1.csv\n");
     		return EXIT_FAILURE;
  	}	 

	// call function to parse file
	struct movie *list = processFile(argv[1]);

//  	printf("Processed file %s and parsed data for 24 movies\n", argv[1]);
  	return EXIT_SUCCESS;
}
