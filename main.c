/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * Group Members:
 *
 * Name: Thomas Good
 * Student ID: 13291455
 *
 * Name: Reece Wallace
 * Student ID: 13192505
 *
 * Name: Jeremy Hoy
 * Student ID: 13590942
 *
 * Name: Lukas Gaspar
 * Student ID: 13910676
 *
 * Name: Carter Pisani
 * Student ID: 13536115
 *
 * Date of submission: - 28/05/21
 * 
 * instructions for compiling and running: in terminal write "make run"
 * 	create a customer for login details.
 * 	login as the customer.
*******************************************************************************/

/*******************************************************************************
 * List header files
*******************************************************************************/


/*******************************************************************************
 * rand()
 * srand()
 * atoi()
 * malloc()
 * abs()
 * sizeof()
 * opendir()
 * readdir()
 * authenticate()
 * getCustomer()
 * getAccounts()
 * getTransactions()
 * changeCustomerDetails()
*******************************************************************************/
#include <stdlib.h>

/*******************************************************************************
 * EOF
 * fclose()
 * FILE fopen()
 * fputc()
 * getchar()
 * fputs()
 * scanf()
 * printf()
 * fprintf()
 * sprintf()
 * remove()
 * perror()
 * stderr()
 * NULL
  * opendir()
 * readdir()
 * authenticate()
 * getCustomer()
 * getAccounts()
 * getTransactions()
*******************************************************************************/
#include <stdio.h>

/*******************************************************************************
 * strcat()
 * strchr()
 * strcmp()
 * strcpy()
 * strlen()
 * strstr()
 * strerror()
*******************************************************************************/
#include <string.h>

/*******************************************************************************
 * 
*******************************************************************************/
#include <math.h>

/*******************************************************************************
 * 
*******************************************************************************/
#include <ctype.h>

/*******************************************************************************
 * mkdir()
*******************************************************************************/
#include <sys/stat.h>

/*******************************************************************************
 * time()
*******************************************************************************/
#include <time.h>


#include <sys/types.h>

/*******************************************************************************
 * opendir()
 * readdir()
 * authenticate()
 * getCustomer()
 * getAccounts()
 * getTransactions()
*******************************************************************************/
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

/* 
gcc -Wall -Werror -ansi -o main.out main.c -lm
 */

/*******************************************************************************
 * List preprocessing directives
*******************************************************************************/

#define MAX_SELECTION_LEN 20
#define MAX_TRANSACTION_NAME 20
#define MAX_TRANSACTION_SIZE 100
#define MAX_NAME_SIZE 25
#define MAX_ACCOUNT_NAME_SIZE 15
#define MAX_ACCOUNT_SIZE 5
#define MAX_STATE_NAME_SIZE 20
#define MAX_STREET_NAME_SIZE 20
#define MAX_SUBURB_NAME_SIZE 30
#define MIN_EMAIL_LEN 5
#define MAX_EMAIL_LEN 20
#define MAX_POSTCODE_LEN 4
#define MAX_CLIENT_ID_LEN 4
#define MAX_PHONE_NUM_LEN 10
#define MAX_USERNAME_LEN 20
#define MIN_PASSWORD_LEN 3
#define MAX_PASSWORD_LEN 20
#define BUFFER_SIZE 1000
#define MAX_BIRTHDAY 31
#define MAX_BIRTHMONTH 12
#define MAX_BIRTHYEAR 2020
#define MIN_BIRTHYEAR 1850


/*******************************************************************************
 * List structs
*******************************************************************************/

/* Date struct */
struct date { 
	int day, month, year;

};
typedef struct date date_t;

/*transaction struct*/
struct transaction {
	int accNumber;
	char name[MAX_NAME_SIZE + 2];
	int amount;
};
typedef struct transaction transaction_t;

/* Account struct */
struct account {
    int accNumber;
    char accName[MAX_ACCOUNT_NAME_SIZE];
	transaction_t transactionList[MAX_TRANSACTION_SIZE];
	unsigned int numTransactions;
};
typedef struct account account_t;

/* Manager struct */
struct manager {
    char name[MAX_NAME_SIZE];
};
typedef struct manager manager_t;

/* Customer struct */
struct customer {
    char name[MAX_NAME_SIZE + 2];
	char postCode[MAX_POSTCODE_LEN + 2];
	char phone[MAX_PHONE_NUM_LEN + 2];
	char clientId[MAX_CLIENT_ID_LEN + 2];
	char email[MAX_EMAIL_LEN + 2];
    account_t accountList [MAX_ACCOUNT_SIZE];
    date_t birthday;
	unsigned int customerBalance;
	unsigned int numAccounts;
};
typedef struct customer customer_t;

/*******************************************************************************
 * Function prototypes
*******************************************************************************/

/* Manager functions */
void printManagerMenu(void);        			/* Author: Thomas Good - DONE */
customer_t createCustomer(void);          		
	/* Author: Thomas Good, Carter Pisani - DONE*/
void createDirectory(customer_t cust);			/* Author: Thomas Good - DONE */
void deleteDirectory(customer_t cust);			/* Author: Thomas Good - DONE */
void removeFromDatabase(customer_t cust);		/* Author: Thomas Good - DONE */
void deleteLine(FILE *srcFile, FILE *tempFile, const int line); 
	/* Author: Thomas Good - DONE */
void deleteCustomer(customer_t cust);       	/* Author: Thomas Good - DONE*/
void saveCustomer(customer_t customer);         /* Author: Thomas Good - DONE */
void displayCustomer(customer_t *customer);   /* Author: Lukas Gaspar - DONE */
void changeCustomerDetails(customer_t *customerp); /* Author: Lukas Gaspar */
int readManagerAnswer(void);        	/* Author: Thomas Good - Kinda DONE */
void invalidManagerChoice(void);    		/* Author: Thomas Good - DONE */
char *concatenate(const char *a, const char *b, const char *c);
/* Author: Thomas Good - DONE */

/* Customer functions */
void printCustomerMenu(void);       		/* Author: Thomas Good - DONE */

/* Author: Reece Wallace*/
void addAccount(customer_t *customer); 		/* Author: Reece Wallace - DONE */
unsigned long generateAccountNum(customer_t *customer); 
	/* Author: Reece Wallace - DONE */
void displayAccounts(customer_t *customer); 
	/* Author: Reece Wallace, Jeremy Hoy - DONE */
void displayAccount(account_t *account, int num); 	
	/* Author: Reece Wallace - DONE */
void deposit(customer_t *customer, account_t *account); 
	/* Author: Reece Wallace, Carter Pisani - DONE */
void withdraw(customer_t *customer, account_t *account); 
	/* Author: Reece Wallace, Carter Pisani - DONE */
void transfer(customer_t *customer); /* Author: Reece Wallace - DONE*/
int readCustomerAnswer(customer_t *customer);   
	/* Author: Thomas Good - kinda DONE */
void invalidCustomerChoice(customer_t *customer); 
	/* Author: Thomas Good - DONE */

int calcBalance(account_t *account); /* Author: Reece Wallace - DONE */
void printTransaction(transaction_t *transaction, int count); 	

/* Shared */
int printMenu(void);               	/* Author: Thomas Good - DONE */
char* login(void);                  	/* Author: Lukas Gaspar - DONE */
char *fgets_wrapper(char *buffer, size_t buflen, FILE *fp); 
	/* Author: Lukas Gaspar - DONE */
void changePassword(void);          	/* Author: Lukas Gaspar */
int encrypt(char filePath[25]);		/* Author: Thomas Good - DONE */
int decrypt(char filePath[25]); 	/* Author: Thomas Good - DONE */
void searchTransactions(customer_t *customer); 	
	/* Author: Reece Wallace, Carter Pisani */
account_t* accountSelect
	(char* prompt, customer_t *customer); /* Author: Reece Wallace - DONE*/
void printSortedTransactions
	(account_t * account); /* Author: Reece Wallace - DONE */
transaction_t transferWithdraw
	(char transName[MAX_ACCOUNT_NAME_SIZE], int transAmount); 
	/* Author: Reece Wallace - DONE */
transaction_t transferDeposit
	(char transName[MAX_ACCOUNT_NAME_SIZE], int transAmount); 
	/* Author: Reece Wallace - DONE */
void sortTransactions(transaction_t* list, unsigned int numTransactions); 
	/* Author: Reece Wallace - DONE */
void searchByName(customer_t *customer);  /* Author: Reece Wallace - DONE*/
char *authenticate(char *email, char *password);	 /* Author: Lukas Gaspar */
customer_t *getAccounts(customer_t *customer);	 	/* Author: Lukas Gaspar */
customer_t *getCustomer(char *id); 					/* Author: Lukas Gaspar */
customer_t *getTransactions(customer_t *customer);	/* Author: Lukas Gaspar */
/*int logout;*/							/* Author: Jeremy Hoy - */
void createTempDir(char id[]);		/* Author: Thomas Good -DONE */


int main(void) {
	char *id = malloc(sizeof *id * MAX_CLIENT_ID_LEN);

	for(;;) {
		if(printMenu() == 0) {
			return 0;
		}
		else
		id = login();
		if(id == NULL) {
            printf("invalid login credentials\n");
			printManagerMenu();
            readManagerAnswer();
            return 0;
        }
		customer_t *customer = malloc(sizeof *customer * 10);
		customer = getCustomer(id);

		printf("id: %s\n", customer->clientId);
		printf("name: %s\n", customer->name);
		printf("day: %d\n", customer->birthday.day);
		printf("month: %d\n", customer->birthday.month);
		printf("year: %d\n", customer->birthday.year);
		printf("email: %s\n", customer->email);
		printf("phone: %s\n", customer->phone);
		printf("postcode: %s\n", customer->postCode);
		printf("balance: %d\n", customer->customerBalance);
		printf("number of accounts: %d\n", customer->numAccounts);

		customer = getAccounts(customer);
		printf("account number: %d\n", customer->accountList->accNumber);
		printf("account name: %s\n", customer->accountList->accName);
		printf("number of transactions: %d\n", 
			customer->accountList->numTransactions);

		customer = getTransactions(customer);

		printf("transaction list:\n%s\n%d\n",
			customer->accountList[0].transactionList[0].name, 
			customer->accountList[0].transactionList[0].amount);

		printCustomerMenu();
		readCustomerAnswer(customer);
		

		return 0;
	}
}


/*******************************************************************************
 * This function prints the initial message when the user starts the program 
 * on how to use this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
int printMenu(void){

	char selection[BUFFER_SIZE];

    for(;;){
    	printf("\n\n"
				"-----Welcome to EZY Banking System 1.0-----\n"
				"Please enter your login details to proceed\n"
				"-------------------------------------------\n");
		printf("select an option:\n"
				"login\n"
				"close\n\n"
				"choice: ");
		if(fgets_wrapper(selection, BUFFER_SIZE, stdin) != 0){
			printf("%s", selection);
			if(strcmp(selection, "close") == 0)
				return 0;
			if(strcmp(selection, "login") != 0) {
				printf("invalid selection\n");
				continue;
			}
			return 1;
		}
	}
}

/*******************************************************************************
 * This function will create and return a pointer to a customer object from the 
 * input of the customer id
 * inputs:
 * - id: user id
 * outputs:
 * - customer_t object
*******************************************************************************/
customer_t *getCustomer(char *id) {
    char path[BUFSIZ];
    FILE *fp;
    char ch;
    customer_t *customer = malloc(sizeof *customer * 10);

    sprintf(path, "customers/%s/%s", id, "data");
	decrypt(path);
    fp = fopen(path, "r");

    do {
            ch = fgetc(fp);
            char str[2];
            str[0] = ch;
            strcat(customer->clientId, str);
            if(ch == EOF) {
                fprintf(stderr, "Error : reach EOF to soon - 1\n");
                return NULL;
            }
            if(ch == ',') {
                customer->clientId[strlen(customer->clientId) - 1] = 0;
                break;
            }
        } while(1);

    do {
            ch = fgetc(fp);
            if(ch == EOF) {
                fprintf(stderr, "Error : reach EOF to soon - 1\n");
                return NULL;
            }
            if(ch == ',') {
                break;
            }
        } while(1);
    
    do {
            ch = fgetc(fp);
            char str[2];
            str[0] = ch;
            strcat(customer->name, str);
            if(ch == EOF) {
                fprintf(stderr, "Error : reach EOF to soon - 1\n");
                return NULL;
            }
            if(ch == ',') {
                customer->name[strlen(customer->name) - 1] = 0;
                break;
            }
        } while(1);

        fscanf(fp, "%d", &customer->birthday.day);
        fgetc(fp);
        fscanf(fp, "%d", &customer->birthday.month);
        fgetc(fp);
        fscanf(fp, "%d", &customer->birthday.year);
        fgetc(fp);

    do {
            ch = fgetc(fp);
            char str[2];
            str[0] = ch;
            strcat(customer->email, str);
            if(ch == EOF) {
                fprintf(stderr, "Error : reach EOF to soon - 1\n");
                return NULL;
            }
            if(ch == ',') {
                customer->email[strlen(customer->email) - 1] = 0;
                break;
            }
        } while(1);

    do {
            ch = fgetc(fp);
            char str[2];
            str[0] = ch;
            strcat(customer->phone, str);
            if(ch == EOF) {
                fprintf(stderr, "Error : reach EOF to soon - 1\n");
                return NULL;
            }
            if(ch == ',') {
                customer->phone[strlen(customer->phone) - 1] = 0;
                break;
            }
        } while(1);

    do {
            ch = fgetc(fp);
            char str[2];
            str[0] = ch;
            strcat(customer->postCode, str);
            if(ch == EOF) {
                fprintf(stderr, "Error : reach EOF to soon - 1\n");
                return NULL;
            }
            if(ch == ',') {
                customer->postCode[strlen(customer->postCode) - 1] = 0;
                break;
            }
        } while(1);

	fscanf(fp, "%d", &customer->customerBalance);
	fgetc(fp);
	fscanf(fp, "%d", &customer->numAccounts);
	fgetc(fp);
	fclose(fp);
	encrypt(path);

    return customer;
}

/*******************************************************************************
 * This function will add all accounts from the accounts file to the customer 
 * object and return it.
 * inputs:
 * - customer: customer_t object
 * outputs:
 * - customer: customer_t object
*******************************************************************************/

customer_t *getAccounts(customer_t *customer) {
    char path[BUFSIZ];
    FILE *fp;
    char ch;
	unsigned int i;


    sprintf(path, "customers/%s/%s", customer->clientId, "accounts");
	decrypt(path);
    fp = fopen(path, "r");

	for(i = 0; i < customer->numAccounts; i++) {

		fscanf(fp, "%d", &customer->accountList[i].accNumber);
		fgetc(fp);

		do {
				ch = fgetc(fp);
				char str[2];
				str[0] = ch;
				strcat(customer->accountList[i].accName, str);
				if(ch == EOF) {
					fprintf(stderr, "Error : reach EOF to soon - 1\n");
					printf("%s", customer->accountList[i].accName);
					return customer;
				}
				if(ch == ',') {
					customer->accountList[i].accName
						[strlen(customer->accountList[i].accName) - 1] = 0;
					break;
				}
			} while(1);

		fscanf(fp, "%d", &(customer->accountList[i].numTransactions));
		fgetc(fp);
	}

	fclose(fp);
	encrypt(path);

    return customer;
}

/*******************************************************************************
 * This function gets all transactions of user
 * inputs:
 * - customer_t object
 * outputs:
 * - customer_t object
*******************************************************************************/

customer_t *getTransactions(customer_t *customer) {
    char path[BUFSIZ];
    FILE *fp;
    char ch;
	int i, j;
    sprintf(path, "./customers/%s/%s", customer->clientId, "transactions");
	decrypt(path);
    fp = fopen(path, "r");

	for(j = 0;; j++) {
		int accNum;

		fscanf(fp, "%d", &accNum);
		for(i = 0; i < customer->numAccounts; i++) {

			if(customer->accountList[i].accNumber == accNum) {
				break;
			}
		}

		do {
				ch = fgetc(fp);
				char str[2];
				str[0] = ch;
				strcat(customer->accountList[i].transactionList[j].name, str);
				if(ch == EOF) {
					printf("transactions found\n");
					encrypt(path);
					fclose(fp);
					return customer;
				}
				if(ch == ',') {
					customer->accountList[i].transactionList[j].name[
						strlen(customer->accountList[i].transactionList
						[j].name) - 1] = 0;
					break;
				}
			} while(1);

		fscanf(fp, "%d", &customer->accountList[i].transactionList[j].amount);


		ch = getc(fp);
		if(ch == EOF)
			break;
	}

	fclose(fp);
	encrypt(path);

    return customer;
}

/*******************************************************************************
 * This function authenticates the user
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
char *authenticate(char *email, char *password)    
{
    DIR *FD;
    struct dirent *in_dir;
    FILE *entry_file;
    char path[BUFSIZ];
    char emailCheck[MAX_EMAIL_LEN];
    char pswdCheck[MAX_PASSWORD_LEN];
    int isPswdSame = 0;
    int isEmailSame = 0;
    char ch = 0;
	int i;
    char *cusID = malloc(sizeof(char) * 10);


    if(NULL == (FD = opendir("customers"))) {
        fprintf(stderr, "Error : Failed to open input directory - %s\n", 
			strerror(errno));

        return NULL;
    }

    while((in_dir = readdir(FD))) {

        if (!strcmp (in_dir->d_name, "."))
            continue;
        if (!strcmp (in_dir->d_name, ".."))
            continue;

        sprintf(path, "customers/%s/%s", in_dir->d_name, "data");
        printf("\nreading path: %s\n", path);
		decrypt(path);
        entry_file = fopen(path, "r");

        if (entry_file == NULL)
            {
                fprintf(stderr, "Error : Failed to open entry file - %s\n", 
					strerror(errno));

                return NULL;
            }
		
        do {
            ch = fgetc(entry_file);
            char str[2];
            str[0] = ch;
            strcat(cusID, str);
            if(ch == EOF) {
                fprintf(stderr, "Error : reach EOF to soon - 1\n");
                return NULL;
            }
            if(ch == ',') {
                cusID[strlen(cusID) - 1] = 0;
                printf("cus id: %s\n", cusID);
                break;
            }
        } while(1);
        do {
            ch = fgetc(entry_file);
            char str[2];
            str[0] = ch;
            strcat(pswdCheck, str);
            if(ch == EOF) {
                fprintf(stderr, "Error : reach EOF to soon - 2\n");
                return NULL;
            }
            if(ch == ',') {
                pswdCheck[strlen(pswdCheck) - 1] = 0;
                /*printf("pswdCheck: %s\n", pswdCheck);
                printf("password: %s\n", password);*/
                if(!strcmp(pswdCheck, password)) {
                    printf("correct password!\n");
                    isPswdSame = 1;
                    break;
                }
                else break;
            }
        } while(1);

        

        for(i = 0; i < 4; i++) {
            do {
                ch = fgetc(entry_file);
                if(ch == EOF) {
                    fprintf(stderr, "Error : reach EOF to soon - 3\n");
                    return NULL;
                }
                if(ch == ',') {
                    break;
                }
            } while(1);
        }

        do {
            ch = fgetc(entry_file);
            char str[2];
            str[0] = ch;
            strcat(emailCheck, str);
            if(ch == EOF) {
                fprintf(stderr, "Error : reach EOF to soon - 4\n");
                return NULL;
            }
            if(ch == ',') {
                emailCheck[strlen(emailCheck) - 1] = 0;
                /*printf("emailCheck: %s\n", emailCheck);*/
                if(!strcmp(emailCheck, email)) {
                    printf("correct email!\n");
                    isEmailSame = 1;
                    break;
                }
                else break;
            }
        } while(1);
        fclose(entry_file);
		encrypt(path);

        if(isEmailSame == 1 && isPswdSame == 1) {
            printf("authenticated as %s!\n", in_dir->d_name);
            return cusID;
        }
		
        isEmailSame = isPswdSame = 0;
        pswdCheck[0] = emailCheck[0] = cusID[0] = '\0';

    }
    printf("authentication failed\n");
    return "0";
}

/*******************************************************************************
 * This function logs in the user
 * inputs:
 * - none
 * outputs:
 * - int used to return the user's login status 
 		(0 - no authorisation, 1 - customer, 2 - manager)
*******************************************************************************/
char* login(void) {
	char selection[BUFFER_SIZE];
	char email[MAX_EMAIL_LEN];
	char password[MAX_PASSWORD_LEN];
	char* cusID = malloc(sizeof(char) * MAX_CLIENT_ID_LEN);

	for(;;) {
		printf("\nEnter \"back\" at any time to go back to the menu\n");
		printf("Enter email> ");
		if(fgets_wrapper(selection, BUFFER_SIZE, stdin) != 0) {
			if(strcmp(selection, "back") == 0)
				return 0;
			if(strlen(selection) > MAX_EMAIL_LEN ||
				 strlen(selection) < MIN_EMAIL_LEN) {
					printf("invalid email length");
					continue;
			}
			strcpy(email, selection);
			break;
		}
	}

	for(;;) {
		printf("\nEnter \"back\" at any time to go back to the menu\n");
		printf("Enter password> ");
		if(fgets_wrapper(selection, BUFFER_SIZE, stdin) != 0) {
			if(strcmp(selection, "back") == 0)
				return 0;
			if(strlen(selection) > MAX_PASSWORD_LEN || 
				strlen(selection) < MIN_PASSWORD_LEN) {
					printf("invalid password length");
					continue;
			}
			strcpy(password, selection);
			break;
		}
	}

	cusID = authenticate(email, password);

	if(cusID == NULL) {
		printf("error verifying credentials\n");
	    return NULL;
	}
	if(!strcmp(cusID, "0")) {
		return NULL;
	}
	
	return cusID;
}

/*******************************************************************************
 * This function is a wrapper for fgets that removes the new line character and 
 * eats any extra chars
 * inputs:
 * - buffer: pointer to an array of chars where we store the string
 * - buflen: max amount of chars read in
 * - fp: file pointer
 * outputs:
 * - the pointer to an array, either returns empty string or the modified buffer
*******************************************************************************/
char *fgets_wrapper(char *buffer, size_t buflen, FILE *fp)
{
    if (fgets(buffer, buflen, fp) != 0)
    {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n')
            buffer[len-1] = '\0';
        else
        {
             int ch; 
             while ((ch = getc(fp)) != EOF && ch != '\n') /* eats chars */
                ;
        }
        return buffer;
    }
    return 0;
}

/*******************************************************************************
 * This function logs the user out to the main login menu
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
/*void logout(void){
	login();
	
}
*/

/*******************************************************************************
 * This function reads the managers input and executes the appropriate function
 * inputs:
 * - answer(1-8), for the action the manager would like to execute
 * outputs:
 * - int 
 * 1 Creates a customer and automaticly saves them.
 * 2 Deletes a selected customer from the database.
 * 3 Displays a selected customers infomation.
 * 4
 * 5 Allows manager to update customer details.
 * 6 Logs the manager out of the program.
*******************************************************************************/
int readManagerAnswer(void){
	char answer;
 	answer = getchar();
	if (answer == '\n') {
		invalidManagerChoice();
	} else {
		getchar();	/* Collects the '\n' character after entering answer */
		if (answer == '-') {
			getchar();
			getchar();
			invalidManagerChoice();
		}
		else if (answer == '1') {
			/* Create customer */
			customer_t cust = createCustomer();
    		saveCustomer(cust);
			createDirectory(cust);

		} else if (answer == '2') {
			/* Delete customer - TODO: Select customer to delete ?*/
			char id[4];
			printf("Enter customer ID>");
			scanf("%s", id);
			customer_t cust;
			cust = *getCustomer(id);
			deleteCustomer(cust);
		} else if (answer == '3') {
			/* Display customer - TODO: Select customer to display ?*/
			
		} else if (answer == '4') {
			/* Search customer transactions */
		} else if (answer == '5') {
			/* Update customer details */
		} else if (answer == '6') {
				printMenu();
				
			/* Log out */
		} else {
			invalidManagerChoice();
		}
	}
	return 0;
}

/*******************************************************************************
 * This function reads the customers input and executes the appropriate function
 * inputs:
 * - answer(1-8), The customers answer for the action they would like to execute 
 * - Ans(1-2), for the type of search they would like to execute, name or amount 
 * outputs:
 * - int
 * 1 Adds an amount into a choosen account
 * 2 Subtracts an amount from a choosen account
 * 3 Subtracts an amount from a choosen account and adds it to another
 * 4 Creates an account
 * 5 Prompts a search type and displays all transactions within search
 * 6 Displays all of the customers account infomation
 * 7 Allows the user to change their password
 * 8 Logs the customer out
*******************************************************************************/
int readCustomerAnswer(customer_t *customer){
	char answer;
 	answer = getchar();
	if (answer == '\n') {
		invalidCustomerChoice(customer);
	} else {
		getchar();	/* Collects the '\n' character after entering answer */
		if (answer == '-') {
			getchar();
			getchar();
			invalidCustomerChoice(customer);
		}
		else if (answer == '1') {
			account_t *acc;
			acc = accountSelect("select an account", customer);
			deposit(customer, acc);

			printCustomerMenu();
			readCustomerAnswer(customer);
			/* Make deposit */
		} else if (answer == '2') {
			account_t *acc;
			acc = accountSelect("select an account", customer);
			withdraw(customer, acc);

			printCustomerMenu();
			readCustomerAnswer(customer);
			/* Withdraw */
		} else if (answer == '3') {
			/* Transfer */
			transfer(customer);
			printCustomerMenu();
			readCustomerAnswer(customer);
		} else if (answer == '4') {
			addAccount(customer);
			printCustomerMenu();
			readCustomerAnswer(customer);
			/* Create account */
		} else if (answer == '5') {
			char ans[1];
			printf("search by\n1. name.\n2. amount range.\n");
			scanf("%s", ans);
			if(strcmp("1", ans) == 0){
				searchByName(customer);
			}
			else if (strcmp("2", ans) == 0){
				searchTransactions(customer);
			}
			else {
				printf("Invalid input.");
			}
			printCustomerMenu();
			readCustomerAnswer(customer);
			/* Search customer transactions */
		} else if (answer == '6') {
			displayAccounts(customer);
			printCustomerMenu();
			readCustomerAnswer(customer);
			/* Display your information */
		} else if (answer == '7') {
			/* Change password */
		} else if (answer == '8') {
			
			/* Log out */
		} else {
			invalidCustomerChoice(customer);
		}
	}
	return 0;
}

/*******************************************************************************
 * This function prints the initial menu for the manager with all instructions 
 * on how to use this program.
 * inputs:
 * - none
 * outputs:
 * - list of actions the manager can make
*******************************************************************************/
void printManagerMenu(void){
    printf("\n\n"
    	"1. Create customer\n"
    	"2. Delete customer\n"
    	"3. Display customer\n"
        "4. Search customer transactions\n"
        "5. Update customer details\n"
    	"6. Log out\n"
		"Enter your choice>\n");
}

/*******************************************************************************
 * This function prints the initial menu for the customer with all instructions 
 * on how to use this program.
 * inputs:
 * - none
 * outputs:
 * - list of actions the customer can make
*******************************************************************************/
void printCustomerMenu(void){
    printf("\n\n"
    	"1. Make deposit\n"
    	"2. Withdraw\n"
    	"3. Transfer\n"
    	"4. Create account\n"
        "5. Search transactions\n"
        "6. Display your information\n"
        "7. Change password\n"
        "8. Log out\n"
		"Enter your choice>");
}

/*******************************************************************************
 * This function allows a manager to create a customer
 * inputs:
 * - none
 * outputs:
 * - customer information stored in customer_t customer
*******************************************************************************/
customer_t createCustomer(void){
	int check = 0;
	int val;
	customer_t customer;
	date_t birthday;
	char tempDay[20];
	char tempMonth[20];
	char tempYear[20];	
	int b =0;
	
			/**************************** Name ****************************/

	printf("\nEnter Name: ");
	scanf("%100[^\n]", customer.name);
	getchar();
	

	/**************************** Phone number ****************************/
	while (check == 0) {
		printf("\nEnter Phone Number: ");
		scanf("%11[^\n]", customer.phone);
		getchar();
		val = atoi(customer.phone);
			int i, flag=2;
			for(i=0;i<strlen(customer.phone);i++){
			if(customer.phone[i]<48 || customer.phone[i]>57){
			flag=1;}}
			if(flag!=1){
				b=1;}
			else {
				b=0;
				} 
	if(val == 0 || b == 0){
			printf("\nPhone Numbers MUST contain only numbers.");
	} else{

		int i, count = 0;
    	for (i = 0; customer.phone[i] != '\0'; ++i){
			count++;
		}
		if (i != 10) {
			printf("\nPhone Number MUST be 10 digits in length");
		} else {
			check = 1;
			printf("\n\n");
		}
	}
	}
	check = 0;
	
	/**************************** Post Code ****************************/
	while (check == 0) {
		printf("\nEnter Post Code: ");
		scanf("%5[^\n]", customer.postCode);
		getchar();
		val = atoi(customer.postCode);
		int i, flag=2;
			for(i=0;i<strlen(customer.postCode);i++){
			if(customer.postCode[i]<48 || customer.postCode[i]>57){
			flag=1;}}
			if(flag!=1){
				b=1;}
			else b=0;
	if(val == 0 || b == 0){
			printf("\nPost Code MUST contain only numbers.");
	} else{

		int i, count = 0;
    	for (i = 0; customer.postCode[i] != '\0'; ++i){
			count++;
		}
		if (i != 4) {
			printf("\nPost Code MUST be 4 digits in length");
		} else {
			check = 1;
			printf("\n\n");
		}
	}
}
	check = 0;


	/**************************** Email Adress ****************************/
	printf("\nEnter Email Address: ");
	scanf("%20[^\n]", customer.email);
	getchar();


	/**************************** Birthday Day ****************************/
	while(check == 0) {
		printf("\nEnter Birthday (Day): ");
		scanf("%s", &tempDay[0]);
		/* Checks if given value is int */
		val = atoi(tempDay);
			int i, flag=2;
			for(i=0;i<strlen(tempDay);i++){
			if(tempDay[i]<48 || tempDay[i]>57){
			flag=1;}}
			if(flag!=1){
				b=1;}
			else b=0;
	if(val == 0 || b == 0){
			printf("\nBirthday (Day) MUST contain only numbers.");
		} else {
			if (val >= 1 && val <= 31) {
				birthday.day = val;
				check = 1; 
				printf("\n\n");
			} else printf("\nInvalid Day."); 
		}
	}
	check = 0;
	
	/**************************** Birthday Month ****************************/
	while(check == 0) {
		printf("\nEnter Birthday (Month): ");
		scanf("%s", &tempMonth[0]);
		/* Checks if given value is int */
		val = atoi(tempMonth);
			int i, flag=2;
			for(i=0;i<strlen(tempMonth);i++){
			if(tempMonth[i]<48 || tempMonth[i]>57){
			flag=1;}}
			if(flag!=1){
				b=1;}
			else b=0;
	if(val == 0 || b == 0){
			printf("\nBirthday (Month) MUST contain only numbers. ");
		} else {
			if (val >= 1 && val <= 12) {
				birthday.month = val;
				check = 1; 
				printf("\n\n");
			} else printf("\nInvalid Month."); 
		}
	}
	/* Resets check */
	check = 0;
	
	/**************************** Birthday Year ****************************/
	while(check == 0) {
		printf("\nEnter Birthday (Year): \n");
		scanf("%s", &tempYear[0]);
		/* Checks if given value is int */
		val = atoi(tempYear);
		int i, flag=2;
			for(i=0;i<strlen(tempYear);i++){
			if(tempYear[i]<48 || tempYear[i]>57){
			flag=1;}}
			if(flag!=1){
				b=1;}
			else b=0;	
	if(val == 0 || b == 0){
			printf("\nBirthday (Month) MUST contain only numbers. ");
		} else {
			if (val >= 1800 && val <= 2017) {
				birthday.year = val;
				check = 1; 
				printf("\n\n");
			} else printf("Invalid year. "); 
		}
	}
	/* Resets check */
	check = 0;
	getchar();
	customer.birthday = birthday;
	int a;
    srand ( time(NULL) );
    a = 1000+(rand()%9000);
	sprintf(customer.clientId, "%04d", a);
	customer.customerBalance = 0;
	customer.numAccounts = 0;
	return customer;
}

/*******************************************************************************
 * This function initialises the customer directory with savings account
 * inputs:
 * - customer cust
 * outputs:
 * - none
*******************************************************************************/
void createDirectory(customer_t cust) {

	char *dirPath = (char *)malloc(20);
	strcpy(dirPath, "customers/");
	strcat(dirPath, cust.clientId); 

	mkdir("customers",0777);
	int check = mkdir(dirPath,0777);

	long number = 10000001 + (rand() % 1000);
	char* accNumber = malloc(9);
	sprintf(accNumber, "%ld", number);

    if (!check) {
		FILE *fp;
		char accountPath[25];
		strcpy(accountPath,concatenate
			("customers/", cust.clientId, "/accounts"));

		fp = fopen(accountPath, "w");
		fprintf(fp, "%s,Savings,1\n", accNumber);	
		fclose (fp);

		encrypt(accountPath);

		char transactionPath[25];
		strcpy(transactionPath,concatenate
			("customers/", cust.clientId, "/transactions"));

		fp = fopen(transactionPath, "w");
		fprintf(fp, "%s,Opening deposit,5\n", accNumber); 
		fclose (fp);

		encrypt(transactionPath);

		char* password = malloc(50);
		printf("Enter Customer Password> ");
		scanf("%50[^\n]", password);
		getchar();

		char dataPath[25];
		strcpy(dataPath,concatenate("customers/", cust.clientId, "/data"));

		fp = fopen(dataPath, "w");
		fprintf(fp, "%s,%s,%s,%d,%d,%d,%s,%s,%s,%d,%d\n",
		cust.clientId, 
		password,
		cust.name, 
		cust.birthday.day, 
		cust.birthday.month, 
		cust.birthday.year,
		cust.email,
		cust.phone,
		cust.postCode,
		cust.customerBalance,
		cust.numAccounts);
		fclose (fp);

		encrypt(dataPath);
		
		printf("Customer created\n");
	} else {
        perror("Error: Unable to create customer\n");
    }
}

/*******************************************************************************
 * This function deletes the customer from the database & directory
 * inputs:
 * - customer_t cust
 * outputs:
 * - none
*******************************************************************************/
void deleteCustomer(customer_t cust) {
	int check = 0;
	int yResult;
	int nResult;
	char* answer = malloc(1);
	printf("Are you sure you want to delete this customer? Y/N> ");
	while(check == 0) {
		scanf("%s", answer);
		char* yes = "Y";
		char* no = "N";
		yResult = strcmp(answer, yes);
		nResult = strcmp(answer, no);	
		if (yResult == 0){

			removeFromDatabase(cust);
			deleteDirectory(cust);

			printf("Customer Deleted\n");
			check = 1;
		} else if (nResult == 0){
			printf("Customer Not Deleted\n");
			check = 1;
		} else {
			printf("Invalid answer. Please enter 'Y' or 'N'>");
		}
	}
}

/*******************************************************************************
 * This function deletes the customers directory
 * inputs:
 * - customer_t cust
 * outputs:
 * - none
*******************************************************************************/
void deleteDirectory(customer_t cust) {
	char accountPath[25], transactionPath[25], dataPath[25];
	char *dirPath = (char *)malloc(25);

	strcpy(accountPath, concatenate("customers/", cust.clientId, "/accounts"));
	strcpy(transactionPath, concatenate("customers/", cust.clientId, 
		"/transactions"));
	strcpy(dataPath, concatenate("customers/", cust.clientId, "/data"));
	strcpy(dirPath, "customers/");
	strcat(dirPath, cust.clientId); 

	remove(dataPath);
	remove(accountPath);
	remove(transactionPath);
	remove(dirPath);
}

/*******************************************************************************
 * This function removes customer from database file
 * inputs:
 * - customer cust
 * outputs:
 * - none
*******************************************************************************/
void removeFromDatabase(customer_t cust){
	char string[200];
	int line_number = 1;
	int line_to_delete;
	FILE* fp = NULL;
	FILE* tempFile = NULL;
	decrypt("database"); 
    fp = fopen("database", "r");
	if(fp == NULL) {
        printf("Read error\n");
    } else {
		while (fgets(string, sizeof string, fp)) {
			if (strstr(string, cust.clientId)) {
				line_to_delete = line_number;
        	}	
			if (strchr(string, '\n')) {
				line_number += 1;
			}
    	}
		tempFile = fopen("tempDB", "w");
		rewind(fp);
		deleteLine(fp, tempFile, line_to_delete);
		fclose(fp);
    	fclose(tempFile);
		remove("database");
    	rename("tempDB", "database");
		encrypt("database");
	}
}

/*******************************************************************************
 * This function deletes the line in the database file in which 
 * the desired customer occurs.
 * inputs:
 * - FILE *srcFile, FILE *tempFile, const int line
 * outputs:
 * - none
*******************************************************************************/
void deleteLine(FILE *srcFile, FILE *tempFile, const int line) {
    char buffer[BUFFER_SIZE];
    int count = 1;
    while ((fgets(buffer, BUFFER_SIZE, srcFile)) != NULL)
    {
        if (line != count) {
            fputs(buffer, tempFile);
		}
        count++;
    }
}

/*******************************************************************************
 * This function saves the given customer to the database file
 * inputs:
 * - customer_t cust
 * outputs:
 * - none
*******************************************************************************/
void saveCustomer(customer_t cust) {

	createTempDir(cust.clientId);
	
	FILE *fp;

	if(access("database", F_OK ) == 0 ) {
		decrypt("database");
	}

	fp = fopen("database", "a");
	
	fprintf(fp, "%s,%s,%d,%d,%d,%s,%s,%s,%d,%d\n",
	cust.clientId, 
	cust.name, 
	cust.birthday.day, 
	cust.birthday.month, 
	cust.birthday.year,
	cust.email,
	cust.phone,
	cust.postCode,
	cust.customerBalance,
	cust.numAccounts);

	fclose (fp);

	encrypt("database"); 
	
}

/*******************************************************************************
 * This function allows a manager to change a customer's details
 * inputs:
 * - customer_t
 * outputs:
 * - none
*******************************************************************************/
void changeCustomerDetails(customer_t *customerp) {
	char choice[100];
	char check[100];
	int numCheck;
	for(;;) {
		displayCustomer(customerp);
		printf("------------------------------------\n"
			"Enter what you would like to change\n"
			"of customer \"%s\":\n"
			"name\n"
			"postcode\n"
			"phone number\n"
			"clientID\n"
			"email\n"
			"birthday\n"
			"customer balance\n"
			"accounts\n"
			"c (to exit)"
			"------------------------------------\n", customerp->name);
		
		printf("Enter what you would like to change (enter c to exit)> ");
		fgets_wrapper(choice, BUFSIZ, stdin);
		if(strcmp(choice, "c") == 0) {
			break;
		}

		if(strcmp(choice, "name") == 0) {
			printf("Current name> %s\n", customerp->name);
			printf("Enter new name> (enter c to cancel)");
			fgets_wrapper(check, BUFSIZ, stdin);
			if(strcmp(check, "c") == 0) {
				continue;
			}
			if(strlen(check) < 3 || strlen(check) > MAX_NAME_SIZE) {
				printf("invalid character length");
				continue;
			}
			strcpy(check, customerp->name);
			continue;
		}

		if(strcmp(choice, "postcode") == 0) {
			printf("Current postcode> %s\n", customerp->postCode);
			printf("Enter new postcode> (enter c to cancel)");
			fgets_wrapper(check, BUFSIZ, stdin);
			if(strcmp(check, "c") == 0) {
				continue;
			}
			if(strlen(check) < 3 || strlen(check) > MAX_POSTCODE_LEN) {
				printf("invalid character length");
				continue;
			}
			strcpy(check, customerp->postCode);
			continue;
		}

		if(strcmp(choice, "phone number") == 0) {
			printf("Current phone> %s\n", customerp->phone);
			printf("Enter new phone number> (enter c to cancel)");
			fgets_wrapper(check, BUFSIZ, stdin);
			if(strcmp(check, "c") == 0) {
				continue;
			}
			if(strlen(check) < 3 || strlen(check) > MAX_PHONE_NUM_LEN) {
				printf("invalid character length");
				continue;
			}
			strcpy(check, customerp->phone);
			continue;
		}

		if(strcmp(choice, "clientID") == 0) {
			printf("Current clientID> %s\n", customerp->clientId);
			printf("Enter new clientID> (enter c to cancel)");
			fgets_wrapper(check, BUFSIZ, stdin);
			if(strcmp(check, "c") == 0) {
				continue;
			}
			if(strlen(check) < 3 || strlen(check) > MAX_CLIENT_ID_LEN) {
				printf("invalid character length");
				continue;
			}
			strcpy(check, customerp->clientId);
			continue;
		}
		

		if(strcmp(choice, "email") == 0) {
			printf("Current email> %s\n", customerp->email);
			printf("Enter new email> (enter c to cancel)");
			fgets_wrapper(check, BUFSIZ, stdin);
			if(strcmp(check, "c") == 0) {
				continue;
			}
			if(strlen(check) < 3 || strlen(check) > MAX_EMAIL_LEN) {
				printf("invalid character length");
				continue;
			}
			strcpy(check, customerp->email);
			continue;
		}

		if(strcmp(choice, "birthday") == 0) {
			printf("Current birthday> %d/%d/%d\n", customerp->birthday.day, 
				customerp->birthday.month, customerp->birthday.year);
			printf("Enter new birthday day>");
			fscanf(stdin, "%d", &numCheck);
			if(numCheck > 0 && numCheck < MAX_BIRTHDAY) {
				printf("invalid character length");
				continue;
			}
			customerp->birthday.day = numCheck;

			printf("Enter new birthday month>");
			fscanf(stdin, "%d", &numCheck);
			if(numCheck > 0 && numCheck < MAX_BIRTHMONTH) {
				printf("invalid character length");
				continue;
			}
			customerp->birthday.day = numCheck;
			
			printf("Enter new birthday year>");
			fscanf(stdin, "%d", &numCheck);
			if(numCheck > MIN_BIRTHYEAR && numCheck < MAX_BIRTHYEAR) {
				printf("invalid character length");
				continue;
			}
			customerp->birthday.day = numCheck;
			continue;
		}
		if(strcmp(choice, "accounts") == 0) {
			printf("Current accounts>\n");
			displayAccounts(customerp);

		}
	}
	
	return;
	
}

/*******************************************************************************
 * This function allows a manager or authorised customer to display customer 
 * 		details
 * inputs:
 * - customer: customer's details
 * outputs:
 * - none
*******************************************************************************/
void displayCustomer(customer_t *customer) {

	printf("full name> %s\n", customer->name);
	printf("postcode> %s\n", customer->postCode);
	printf("phone number> %s\n", customer->phone);
	printf("client ID> %s\n", customer->clientId);
	printf("email> %s", customer->email);
	printf("birthday> %d/%d/%d", customer->birthday.day, 
		customer->birthday.month, customer->birthday.year);
	printf("balance> %d", customer->customerBalance);
	printf("number of accounts> %d", customer->numAccounts);

	printf("accounts> \n");
	displayAccounts(customer);

}

/*******************************************************************************
 * This function resets the menu if the manager chooses an invalid option
 * inputs:
 * - none
 * outputs:
 * - invalid choice. printed, manger list and chioice exectued again.
*******************************************************************************/
void invalidManagerChoice(void) {
	printf("Invalid choice.\n");
	printManagerMenu();
	readManagerAnswer();
}

/*******************************************************************************
 * This function allows the customer to create an account
 * inputs:
 * - New accountList array position from customer struct
 * outputs:
 * - Hew acccount infomation is sotred in an accountList
*******************************************************************************/
void addAccount(customer_t *customer) {
	account_t account;
	if(customer->numAccounts == MAX_ACCOUNT_SIZE) {
		return;
	}
	account.accNumber = generateAccountNum(customer);
	printf("Enter account name>");
	scanf("%s", account.accName);
	account.numTransactions = 0;
	customer->accountList[customer->numAccounts++] = account;

}

/*******************************************************************************
 * This function generates an account number that is unique for each account.
 * inputs:
 * - the number of acconts stored in the customer struct.
 * outputs:
 * - an account number (nextAccount).
*******************************************************************************/
unsigned long generateAccountNum(customer_t *customer) {
	unsigned long nextAccount = 
	10000000 + customer->numAccounts + (rand() % 1000);
	return nextAccount;
}

/*******************************************************************************
 * This function dsiplays the account infomation of the customer.
 * inputs:
 * - The number of accounts stored in customer struct.
 * - The list of accounts in the customer struct.
 * outputs:
 * - printed list of accounts.
*******************************************************************************/
void displayAccounts(customer_t *customer) {
	unsigned int i;
	int count = 1; 
	for(i = 0; i < customer->numAccounts; i++) {
		displayAccount(&customer->accountList[i], count);
		++count;
	}

}

/*******************************************************************************
 * This function displays an individual account.
 * inputs:
 * - Account infomation (name, number) from the specific accounts from 
 * - 	displayAccouns function.
 * outputs:
 * - Prints the account infomation (name, number) and its balance.
 * - Prints a sorted list of the transactions within the account.
*******************************************************************************/
void displayAccount(account_t *account, int num) {
	printf("\n[%d] Account Number: %d\nAccount Name: %s\nBalance: $%d\n", 
	num, account->accNumber, account->accName, calcBalance(account));
	printf("-----------------------------");
	printf("\ntransactions: \n");
	printSortedTransactions(account);
	printf("\n");
}

/*******************************************************************************
 * This function adds an amount inputed by the customer into a choosen account.
 * inputs:
 * - Number of accounts stored in the customer struct.
 * - A specified account.
 * - User inputed amount and name of transaction.
 * outputs:
 * - Stores the transaction within the transaction list in the account struct.
 * - Increases customer balance by choosen amount.
 * - Outputs the calculated balance using the calcBalance function.
*******************************************************************************/
void deposit(customer_t *customer, account_t *account) {
	transaction_t transaction;

	printf("Enter reason for transaction: ");
	scanf("%s", transaction.name);
	printf("enter the amount you would like to deposit: ");
	scanf("%d", &(transaction.amount));

	account->transactionList[account->numTransactions++] = transaction;
	customer->customerBalance = customer->customerBalance + transaction.amount;

	printf("account balance: %d", calcBalance(account));
}

/*******************************************************************************
 * This function subtracts an amount inp[utted by the customer from the choosen 
 * - 	account.
 * inputs:
 * - Number of accounts stored in the customer struct.
 * - A specified account.
 * - User inputed amount and name of transaction.
 * outputs:
 * - Stores the transaction within the transaction list in the account struct.
 * - Decreases customer balance by choosen amount.
 * - Outputs the calculated balance using the calcBalance function.
*******************************************************************************/
void withdraw(customer_t *customer, account_t *account) {
	transaction_t transaction;

	printf("Enter reason for transaction: ");
	scanf("%s", transaction.name);
	printf("enter the amount you would like to withdraw: ");
	scanf("%d", &(transaction.amount));
	transaction.amount = abs(transaction.amount) * -1;

	if(calcBalance(account) < -transaction.amount) {
		printf("insufficent funds!\n");
	} else {
		account->transactionList[account->numTransactions++] = transaction;
		customer->customerBalance = customer->customerBalance + 
		transaction.amount;
	}

	printf("account balance: %d", calcBalance(account));
}

/*******************************************************************************
 * This function withdraws an amount from one account and places it in another.
 * inputs:
 * - The account and transaction details stored in the customer struct:
 * - 	The number of transactions.
 * - 	The account name.
* - The amount and reason for the transfer(transferAmount, reason).
* - From and to stoires the selcted accounts to be transfered from and to.
 * outputs:
 * - The two transactions are stored into the transaction list.
 * - The transaction that has occured is printed amount and accounts.
*******************************************************************************/
void transfer(customer_t *customer) {
	account_t *from;
	account_t *to;
	char reason[MAX_NAME_SIZE];
	unsigned int transferAmount;

	printf("Enter the amount you would like to transfer: ");
	scanf("%d", &transferAmount);
	printf("enter reason> ");
	scanf("%s", reason);

	from = accountSelect("choose an account name to tranfer from: ", customer);
	to = accountSelect("choose an account name to tranfer to: ", customer);

	from->transactionList[from->numTransactions++] = 
		transferWithdraw(reason, transferAmount);

	to->transactionList[to->numTransactions++] = 
		transferDeposit(reason, transferAmount);


	printf("you have sucsessfully tranfered $%d from %s to %s\n", 
	transferAmount, from->accName, to->accName);

}

/*******************************************************************************
 * This function promts the user to select an account from the exsisting list.
 * inputs:
 * - A string that prompts the user to select an account.
 * - Account list stored in the customer struct for account name.
 * - The number of accounts stored in the customer struct.
 * outputs:
 * - Returns the selcted account.
*******************************************************************************/
account_t* accountSelect(char* prompt, customer_t *customer) {
	unsigned int choice;
	unsigned int i;
	displayAccounts(customer);
	printf("%s", prompt);
	scanf("%d", &choice);
	for(i=1; i<=customer->numAccounts; i++) {
			if(choice == i) {
				return &(customer->accountList[i-1]);
			}
	}
	printf("invalid selection");
	return accountSelect(prompt, customer);
}

/*******************************************************************************
 * This function returns the deatails of the account transfered from (negative). 
 * inputs:
 * - Name of transaction.
 * - The amount in the transaction.
 * outputs:
 * - Returns the details of the transaction to be stored in transaction list.
*******************************************************************************/
transaction_t transferWithdraw(char transName[MAX_ACCOUNT_NAME_SIZE], 
int transAmount) {
	transaction_t transaction;

	strcpy(transaction.name, transName);
	transaction.amount = -transAmount;

	return transaction;
}

/*******************************************************************************
 * This function returns the deatails of the account transfered to (positive). 
 * inputs:
 * - Name of transaction.
 * - The amount in the transaction.
 * outputs:
 * - Returns the details of the transaction to be stored in transaction list.
*******************************************************************************/
transaction_t transferDeposit(char transName[MAX_ACCOUNT_NAME_SIZE], 
int transAmount) {
	transaction_t transaction;

	strcpy(transaction.name, transName);
	transaction.amount = transAmount;

	return transaction;
}

/*******************************************************************************
 * This function prints the details of a transaction.
 * inputs:
 * - The name and amount stored in the choosen transaction.
 * - A count for listing the transactions by number.
 * outputs:
 * - The details of the transaction.
*******************************************************************************/
void printTransaction(transaction_t *transaction, int count) {
	printf("%d. %s $%d\n", count, transaction->name, transaction->amount);
}

/*******************************************************************************
 * This function calculates the balance in a choosen account.
 * inputs:
 * - The account choosen for the number of transactions and amount stored in the
 * - 	transaction list.
 * outputs:
 * - Returns the balance of the account.
*******************************************************************************/
int calcBalance(account_t *account) {
	int balance = 0;
	unsigned int i;
	for(i=0; i<account->numTransactions; ++i) {
		balance += account->transactionList[i].amount;
	}
	return balance;
}

/*******************************************************************************
 * This function is used for inccorect user inputs in the main menu.
 * inputs:
 * - Details stored in customer.
 * outputs:
 * - Prints invalid choice.
 * - 	Recursive function:
 * - Executes the customer menu function.
 * - Executes the read customer answer function. 
*******************************************************************************/
void invalidCustomerChoice(customer_t *customer) {
	printf("Invalid choice.\n");
	printCustomerMenu();
	readCustomerAnswer(customer);
}

/*******************************************************************************
 * This function searches customer transactions by amount range.
 * inputs:
 * - Choice of range to search in.
 * - The number of transactions.
 * - The number of accounts.
 * - The amounts stored in account transaction lists.
 * outputs:
 * -  printed list of the transactions that are within the choosen range.
*******************************************************************************/
void searchTransactions(customer_t *customer) {
	int choice;
	char tempchoice[20];
	int check =0;
	int r1,r2;
	int results =0;
	unsigned int iter, i;

	
	while (check ==0) {	
	printf(
		"Select either 1,2,3,4 or 5:\n"
		"1) $0 - $99\n"
		"2) $100 - $999\n"
		"3) $1000 - $99,999\n"
		"4) $100,000 - $999,999\n"
		"5) $1,000,000 and above\n");
		scanf("%s", &tempchoice[0]);
		choice = atoi(tempchoice);
		if(choice == 0) {
			printf("Invalid Answer. ");
		} else {
			if (choice >=1 && choice <= 5) {
				check = 1;
			} else printf("Invalid Answer. ");
		}
	}
	
	if (choice ==1) {
		r1 = 0;
		r2 = 99;
	} else if (choice ==2) {
		r1 = 100;
		r2 = 999;
	} else if (choice ==3) {
		r1 = 1000;
		r2 = 99999;
	} else if (choice ==4) {
		r1 = 100000;
		r2 = 999999;
	} else if (choice ==5) {
		r1 = 1000000;
		r2 = 999999999;
	}

	for(i = 0; i<customer->numAccounts; i++) {
		for(iter = 0; iter<customer->accountList[i].numTransactions; iter++) {
			if(r1 <= customer->accountList[i].transactionList[iter].amount &&
				r2 >= customer->accountList[i].transactionList[iter].amount) {
					++results;
					printTransaction(&customer->
						accountList[i].transactionList[iter], results);
			}
			else {
				continue;
			}
		}	
	}
	if(results == 0) {
		printf("no results found in this range\n");
	}
}

/*******************************************************************************
 * This function search customer transactions by name.
 * inputs:
 * - The name of transaction the user is searching for.
 * - The number of accounts.
 * - The number of transactions.
 * - The name of transactions stored in the transaction lists.
 * outputs:
 * - Prints the transaction details of transactions with the choosen name. 
*******************************************************************************/
void searchByName(customer_t *customer) {
	int results = 0;
	unsigned int i, iter;
	char searchName[MAX_TRANSACTION_NAME];

	printf("enter transaction name you would like to search for: ");
	scanf("%s", searchName);

	for(i = 0; i<customer->numAccounts; i++) {
		for(iter = 0; iter<customer->accountList[i].numTransactions; iter++) {
			if(strcmp((searchName), 
				(customer->accountList[i].transactionList[iter].name)) == 0) {
					++results;
					printTransaction(&customer->
						accountList[i].transactionList[iter], results);
			}
			else {
				continue;
			}
		}
	}
	if(results == 0) {
		printf("no results with that name found");
	}
}

/*******************************************************************************
 * This function sorts the transactions from lowest to highest amounts.
 * inputs:
 * - The list of transactions stored within a copy 
 * - 	(so actual list is not affected).
 * - The number of tranactions.
 * outputs:
 * - Creates a list of sorted trnasactions from lowest to highest.
*******************************************************************************/
void sortTransactions(transaction_t* list, unsigned int numTransactions) {
	unsigned int i,j;
	transaction_t temp;

	for(i=0; i<numTransactions; ++i) {
		for(j=0; j<numTransactions-i-1; ++j){
			if(abs(list[j].amount) > abs(list[j+1].amount)) {
				temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
			}
		}
	}
}

/*******************************************************************************
 * This function prints the list of sorted transactions.
 * inputs:
 * - Number of transactions.
 * - A temporary list.
 * - The list of transactions.
 * outputs:
 * - Stores the list of transactions in a temporary list.
 * - Prints a sorted list of transactions using the print transaction function.
*******************************************************************************/
void printSortedTransactions(account_t * account) {
	transaction_t sortedList[MAX_TRANSACTION_SIZE];
	unsigned int i;
	for(i=0; i<account->numTransactions; ++i) {
		sortedList[i] = account->transactionList[i];
	}
	sortTransactions(sortedList, account->numTransactions);
	for(i=0; i<account->numTransactions; ++i) {
		printTransaction(&sortedList[i], i+1);
	}

}

/*******************************************************************************
 * This function encrypts the file with the given path
 * inputs:
 * - char filePath[]
 * outputs:
 * - none
*******************************************************************************/
int encrypt(char filePath[]) {

	char *tempPath = (char *)malloc(50);
	
	if (strcmp("database",filePath) != 0) {
		strcpy(tempPath, "temp/");
		strcat(tempPath, filePath);
	} else {
		strcpy(tempPath, "temp/database");
	}

    char ch;
    FILE *fps, *fpt;
    fps = fopen(filePath, "r");
    if(fps == NULL)
        return 0;
    fpt = fopen(tempPath, "w");
    if(fpt == NULL) {
        return 0;
		printf("Error");
	}
    ch = fgetc(fps);
    while(ch != EOF)
    {
        ch = ch+100;
        fputc(ch, fpt);
        ch = fgetc(fps);
    }
    fclose(fps);
    fclose(fpt);
    fps = fopen(filePath, "w");
    if(fps == NULL){
        return 0;
		printf("Error");
	}
    fpt = fopen(tempPath, "r");
    if(fpt == NULL){
        return 0;
		printf("Error");
	}
    ch = fgetc(fpt);
    while(ch != EOF)
    {
        ch = fputc(ch, fps);
        ch = fgetc(fpt);
    }
    fclose(fps);
    fclose(fpt);
    
    return 0;
}

/*******************************************************************************
 * This function decrypts the file with the given path
 * inputs:
 * - char filePath[]
 * outputs:
 * - none
*******************************************************************************/
int decrypt(char filePath[]) {

	char *tempPath = (char *)malloc(50);
	
	if (strcmp("database",filePath) != 0) {
		strcpy(tempPath, "temp/");
		strcat(tempPath, filePath);
	} else {
		strcpy(tempPath, "temp/database");
	}

    char ch;
    FILE *fps, *fpt;
    fps = fopen(filePath, "w");
    if(fps == NULL){
        return 0;
		printf("Error");
	}
    fpt = fopen(tempPath, "r");
    if(fpt == NULL){
        return 0;
		printf("Error");
	}
    ch = fgetc(fpt);
    while(ch != EOF)
    {
        ch = ch-100;
        fputc(ch, fps);
        ch = fgetc(fpt);
    }
    fclose(fps);
    fclose(fpt);
    return 0;
}

/*******************************************************************************
 * This function assists in creating directory values by concatenating
 * the appropriate variables
 * inputs:
 * - char const char *a, const char *b, const char *c
 * outputs:
 * - none
*******************************************************************************/
char *concatenate(const char *a, const char *b, const char *c) {
    size_t alen = strlen(a);
    size_t blen = strlen(b);
    size_t clen = strlen(c);
    char *res = malloc(alen + blen + clen + 1);
    if (res) {
        memcpy(res, a, alen);
        memcpy(res + alen, b, blen);
        memcpy(res + alen + blen, c, clen + 1);
    }
    return res;
}

/*******************************************************************************
 * This function assists in creating directory values by creating a temp
 * directory for crypting reference.
 * inputs:
 * - char id[]
 * outputs:
 * - none
*******************************************************************************/
void createTempDir(char id[]) {
	char *tempPath = (char *)malloc(50);
	strcpy(tempPath, "temp/customers/");
	strcat(tempPath, id);
	mkdir("temp",0777);
	mkdir("temp/customers", 0777);
	mkdir(tempPath, 0777);
}

/*******************************************************************************
 * - End of program.
*******************************************************************************/
