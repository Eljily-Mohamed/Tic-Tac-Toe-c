#ifndef _UTILS_H_
#define _UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif 

/* num2str
 *   convert a number 'number' in base 'base' to the string s (the string
 *   variable must be large enough)
 */
void num2str(char *s, unsigned int number, unsigned int base);
unsigned int str2num(char *s, unsigned base);

#ifdef __cplusplus
}
#endif
#endif
