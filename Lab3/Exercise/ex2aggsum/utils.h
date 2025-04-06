
#define PACKAGE "aggsum"
#define VERSION "0.01"

#define SEEDNO 1024   /* default seed for randomizer */
#define ARG1 "<arrsz>"
#define ARG2 "<tnum>"
#define ARG3 "<seednum>"

#define THRSL_MIN 5      /* minimum threshold of computation size per thread */
#define UPBND_DATA_VAL 100 /* upper bound (maximum threshold) of generated data value*/
#define LWBND_DATA_VAL 0   /* lower bound (minimum threshold) of generated data value*/

int tonum (const char * nptr, int * num);

struct _appconf {
  int arrsz;
  int tnum;
  int seednum;
} appconf;

struct _range {
  int start;
  int end;
};

/** process command line argument.
 *  values are made available through the 'conf' struct.
 *  using the parsed conf to get arguments: the arrsz, tnum, and seednum
 */
int processopts (int argc, char **argv, struct _appconf *conf); 

/** process string to number.
 *  string is stored in 'nptr' char array.
 *  'num' is returned the valid integer number.
 *  return 0 valid number stored in num
 *        -1 invalid and num is useless value.
 */
int tonum (const char * nptr, int * num);

/** validate the array size argument.
 *  the size must be splitable "num_thread".
 */
int validate_and_split_argarray (int arraysize, int num_thread, struct _range* thread_idx_range);

/** generate "arraysize" data for the array "buf"
 *  validate the array size argument.
 *  the size must be splitable "num_thread".
 */
int generate_array_data (int* buf, int arraysize, int seednum);

/** display help */
void help (int xcode);
