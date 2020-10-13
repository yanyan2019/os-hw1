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

	// token for year
	token = strtok_r(NULL, ",", &ptr);
	currMovie->year = atoi(token);

	// token for languages
	token = strtok_r(NULL, ",", &ptr);

	// remove the brackets
	char *token2 = strtok_r(NULL, "[", &token);
	token = strtok_r(NULL, "]", &token2);

	// allocate dynamic array for languages 
	currMovie->lang = (char**)calloc(langSize ,sizeof(char*));
	
	// dynamic array for languages
	int i;
	for(i = 0; i < langSize; i++){
		currMovie->lang[i] = (char*)calloc(strlen(token)+1 ,sizeof(char));
		token2 = strtok_r(NULL, ";", &token);
	
		// fill the empty language with string
		if(token2 == NULL){
			strcpy(currMovie->lang[i], "NULL");

		}else{
			strcpy(currMovie->lang[i], token2);
		}
		
	}	

	// token for rating
	token = strtok_r(NULL, ",", &ptr);
	currMovie->rating = strtod(token, NULL);

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

// print all movies in a linked list
void printMovie(struct movie * m){
	while(m != NULL){
		printf("%i %.1f %s\n",m->year, m->rating, m->title);
		m = m->next;
	}
	printf("\n");
}

// show movies released in the specified year 
void movieInSpecYr(struct movie *list){
	printf("Enter the year of which you want to see movies: ");
	bool exist = false;
	int yr = 0;

	// user input
	scanf("%i", &yr);

	// loop through the linked list
	struct movie *m = list;
	while(m != NULL){

		// if year matches, print the title
		if(m->year == yr){
			printf("%s\n",m->title);
			exist = true;
		}
		// go to the next node
		m = m->next;
	}
	
	// print if no matches movies
	if(exist == false){
		printf("No data about movies released in the year %i\n", yr);
	}
	printf("\n");	
}

// allocate new movie struct
struct movie * createNewList(){
	int i;
	struct movie *m =(struct movie*)malloc(sizeof(struct movie));
	m->title = calloc(100, sizeof(char));
	m->lang = (char**)calloc(5 ,sizeof(char*));
	for(i = 0;i < 5; i++){
		m->lang[i] = (char*)calloc(50, sizeof(char));
	}
	return m;
}

//copy data form movie2 to movie
void copyMovie(struct movie *m,  struct movie *m2){
	int i;
	strcpy(m->title, m2->title);
	m->year = m2->year;
  	for(i = 0; i < 5; i++){
		strcpy(m->lang[i], m2->lang[i]);
	}
	m->rating = m2->rating;
	m->next = m2->next;
}

// show highest rated movie in the specific year
void highRatedMovInSpecYr(struct movie *list, int m_count){
		
	bool exist = false;

	// origin list
	struct movie *temp = list;

	// temporary holder for replacing	
	struct movie *temp2 = createNewList();

	// New list after sorting
	struct movie *m = createNewList();
	struct movie *m2 = m;

	//head of the new list
	copyMovie(m ,temp);
	m->next = NULL;

	// loop through the original list for comparsion
	while(temp != NULL){

		// loop through the new list
		while(m2 != NULL){
			
			// check for replacing condition
			if(m2->year == temp->year){

				// if original list has larger rating movie, then copy the data from it to the new list
				if(m2->rating < temp->rating){
					copyMovie(temp2, m2);
					copyMovie(m2, temp);
					m2->next = temp2->next;
					exist = true;
					temp = temp->next;

				}else{
					// if nothing is changing
					break;
				}
			}else if(m2->year != temp->year){ 
				
				// insert the new node at the end of the new list
				if(m2->next == NULL){

					//insert new node
					struct movie * newNode = createNewList();
					copyMovie(newNode, temp);
					newNode->next = NULL;
					m2->next = newNode;
	
					// back to the head of the new list
					m2 = m;
					temp = temp->next;
				}else{
					// continute to loop if not at the end of the new list
					m2 = m2->next;
				}
			}
		}
		temp = temp->next;
		m2 = m;
	}
	printMovie(m);
	free(m);
	free(temp2);
}

// show the title and year of release of all movies in a specific languages
void movInSpecLang(struct movie * list){
	int i;

	// check if any matches results
	bool exist = false;

	char user[50];
	struct movie *m = list;
	printf("Enter the language for which you want to see movies: ");
	scanf("%s", &user);

	// loop through the list to matches languages
	while(m != NULL){

		// for each language in the movie
		for(i = 0; i < 5; i++){

			// if matches, print the movie
			int j = strcmp(user, m->lang[i]);
			if(j == 0){
				printf("%i %s\n", m->year, m->title);
			
				// no need for data no found message
				exist = true;
			}
		}
		m = m->next;	
	}
	printf("\n");
	
	// print if no data found
	if(exist == false){
		printf("No matches result for movies in %s \n\n", user);
	}
}

// user interactive function
void interactive(struct movie * list, int m_count){
	int input = 0;
	// loop until user exit
	while(input != 4){

		// print user options
		printf("1. Show movies released the in the sepcified year\n");
		printf("2. Show highest rated movie for each year\n");
		printf("3. Show the title and year of release of all movies in a specific language\n");
		printf("4. Exit the Program\n\n");
		printf("Enter a choice from 1 to 4: ");

		scanf("%i", &input);

		// call differents functions for inputs
		if(input == 1){
			movieInSpecYr(list);
		}else if(input == 2){
			highRatedMovInSpecYr(list, m_count);
		}else if(input == 3){
			movInSpecLang(list);
		}else if(input > 4 || input < 1){
			printf("You entered an incorrect choice. Try again.\n\n");
		}
	}
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
	interactive(list,m_count);
	
  	return EXIT_SUCCESS;
}
