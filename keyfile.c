#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>

#define LETTER 26
#define NUMBER 10

int print_help(void);
static char random_letter(int is_cap);
static char random_number();

static char random_letter(int is_cap)
{
   int letter = (int)(LETTER * (rand() / (RAND_MAX + 1.0)));
   return((char)((is_cap == 1) ? (letter + 65) : (letter + 97)));
}

static char random_number()
{
   int num = (int)(NUMBER * (rand() / (RAND_MAX + 1.0)));
   return((char)(num + 48));
}

static void random_string(int length, char *str)
{
   int i;
   int char_type;
   
   for(i = 0; i < length; i++)
   {
      char_type = (int)(3 * (rand() / (RAND_MAX + 1.0)));
      
      switch(char_type)
      {
      case 0:
         str[i] = random_letter(0);
         break;
      case 1:
         str[i] = random_letter(1);
         break;
      case 2:
         str[i] = random_number();
         break;
      default:
         str[i] = random_number();
         break;
      }
   }  
}

int main(int argc, char *argv[])  
{
   /*char key[STRING_SIZE + 1];*/
   char *key;
   char *value;
   int keylen = 8;
   int vallen = 1000;
   int num = 1;
   int opt = 0;
   int i = 0;

   while ((opt = getopt(argc, argv, "hn:k:l:")) != -1) {
     switch(opt) {
       case 'h':
         print_help();
         break;
       case 'n':
         num = atoi(optarg);
         break;
       case 'k': /* key length */
         keylen = atoi(optarg);
         break;
       case 'l': /* value length */
         vallen = atoi(optarg);
         break;
       case ':': 
         fprintf(stderr, "Error - Option '%d',  needs an argument\n\n", optopt);
         print_help();
       break;
     } /* switch */
   } /* while */

   key= calloc(keylen + 1, sizeof(char));
   value= calloc(vallen + 1, sizeof(char));

   srand((unsigned)time(NULL));

   key[keylen] = '\0';
   value[vallen] = '\0';

   for (i = 0; i < num; i++) {
     random_string(keylen, key);
     printf("%s", key);
     random_string(vallen, value);
     printf(" %s\n", value);
   }

   free(key);
   free(value);
   
   return(0);
}
int print_help(void) {
        printf("\nkeyfile: prints key/values for testing. key and value separated by space\n\n\n");
	printf("keyfile [-k] [-l] [-n] > file.txt\n")
	printf("OPTIONS:\n");
	printf("-k <number>   length of key\n");
	printf("-l <number>   length of value\n");
	printf("-n <number>   number of key values\n\n");
}
