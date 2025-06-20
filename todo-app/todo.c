#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define P 0
#define F 1
#define U -1
#define TODO_FILENAME ".todo.txt"

int
print_usage(){
	printf("Todo utility with basic stuff\n\n");
	printf("Usage: todo [OPTIONS]\n\n");
	printf("Options:\n");
	printf("add	-> todo add task_name		=> Adds a new task to the list\n");
	printf("list	-> todo list			=> Lists the tasks\n");
	printf("update	-> todo update task_name status	=> Updates status of the task in the list\n");
	printf("remove	-> todo remove task_name	=> Removes a task from the list\n");
	return P;
}

/* ToDo CRUD methods start*/
int
check_todo_file_existence_or_create(){
	char *home = getenv("HOME");
	if (home == NULL){
		printf("Could not find Home env variable\n");
		return F;
	}
	size_t path_len = strlen(home) + strlen("/") + strlen(TODO_FILENAME) + 1;
	char *file = malloc(path_len);
	if (file == NULL){
		fprintf(stderr, "Memory allocation failed\n");
		return F;
	}
	snprintf(file, path_len, "%s/%s", home, TODO_FILENAME);
	// checking for file existence
	if (access(file, F_OK) == 0){
		printf("File exists\n");
	} else{
		printf("File does not exist. Creating it\n");
		FILE* fl;
		fl = fopen(file, "w");
		if (fl == NULL)
			return F;
		fclose(fl);
	}
	return P;
}


int
add_req(int len, char** args){
	printf("Call to %s\n", __FUNCTION__);
	return P;
}

int
list_req(int len, char** args){
	printf("Call to %s\n", __FUNCTION__);
	return P;
}
int
update_req(int len, char** args){
	printf("Call to %s\n", __FUNCTION__);
	return P;
}

int
remove_req(int len, char** args){
	printf("Call to %s\n", __FUNCTION__);
	return P;
}

/* ToDo CRUD methods end*/


int
entertain_request(int len, char **args){
	char *st = args[1];
	int ret = P;
	ret = check_todo_file_existence_or_create();
	if ((strcmp(st, "add"))==0){
		ret = add_req(len, args);
	} else if ((strcmp(st, "list"))==0){
		ret = list_req(len, args);
	} else if ((strcmp(st, "update"))==0){
		ret = update_req(len, args);
	} else if ((strcmp(st, "remove"))==0){
		ret = remove_req(len, args);
	} else{
		ret = print_usage();
		ret = U;
	}
	return ret;
}

int
main(int argc, char **argv){
	int ret = U;
	if (argc == 1){
		ret = print_usage();
	} else {
		ret = entertain_request(argc, argv);
	}
	return ret;
}
