#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define P 0
#define F 1
#define U -1
#define TODO_FILENAME ".todo.txt"
char* filename;
/* Task related declarations and other stuff*/
typedef enum {
	NOT_STATRTED = -1,
	IN_PROGRESS = 0,
	DONE = 1
}Status_t;
#define MAX_TASK_LEN 256
typedef struct {
	char name [MAX_TASK_LEN];
	Status_t status;
} task_t;

int
print_usage(){
	printf("Todo utility with basic stuff\n\n");
	printf("Usage: todo [OPTIONS]\n\n");
	printf("Options:\n");
	printf("add	-> todo add task_name		=> Adds a new task to the list\n");
	printf("list	-> todo list			=> Lists the tasks\n");
	printf("update	-> todo update task_name status	=> Updates status of the task in the list\n");
	printf("remove	-> todo remove task_name	=> Removes a task from the list\n");
	printf("clear	-> removes all tasks		=> Removes all tasks from the list\n");
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
	filename = malloc(path_len);
	if (filename == NULL){
		fprintf(stderr, "Memory allocation failed\n");
		return F;
	}
	snprintf(filename, path_len, "%s/%s", home, TODO_FILENAME);
	// checking for file existence
	if (access(filename, F_OK) == 0){
		printf("File exists\n");
	} else{
		printf("File does not exist. Creating it\n");
		FILE* fl;
		fl = fopen(filename, "w");
		if (fl == NULL)
			return F;
		fclose(fl);
	}
	return P;
}

int save_task(task_t task){
	int ret = P;
	FILE* fl = fopen(filename, "a");
	if (fl == NULL)
		return F;
	else
		fclose(fl);
	return P;
}

int
add_req(int len, char** args){
	printf("Call to %s\n", __FUNCTION__);
	int ret = P;
	// creating task structure
	task_t task;
	if (len!=3){
		printf("Task name not passed entirely or as a single string\n");
		ret = F;
	} else {
		strncpy(task.name, args[2], sizeof(task.name) - 1);
		task.name[sizeof(task.name) - 1] = '\0';
		task.status = NOT_STATRTED;
		ret = save_task(task);
	}
	return ret;
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

int
clear_req(int len, char** args){
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
	} else if ((strcmp(st, "clear"))==0){
		ret = clear_req(len, args);
	}else{
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
