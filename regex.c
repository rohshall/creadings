#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcre.h>

#define OUTPUT_SIZE 12
#define SUBSTRING_SIZE 16

int main() {
 pcre *re;
 pcre_extra *extra;
 const char *input = "get food";
 const char *pattern = "^\\s*get\\s+(\\w+)\\s*$\0";
 const int options = PCRE_CASELESS | PCRE_UTF8 | PCRE_EXTRA;
 int error_offset;
 const char *error_str;
 int output[OUTPUT_SIZE];
 const char *substring;
 int match_count;
 int index;
 
 re = pcre_compile(pattern, options, &error_str, &error_offset, NULL);
 if (re == NULL) {
   fprintf(stderr, "PCRE compile error at position %d: %s", error_offset, error_str);
   exit(EXIT_FAILURE);
 }
 extra = pcre_study(re, 0, &error_str);
 if (error_str != NULL) {
   fprintf(stderr, "PCRE study error at position %d: %s", error_offset, error_str);
   exit(1);
 }
 match_count = pcre_exec(re, extra, input, (int)strlen(input), 0, 0, output, OUTPUT_SIZE);
 if (match_count < 1) {
   switch(match_count) {
     case PCRE_ERROR_NOMATCH:
       fprintf(stderr, "PCRE susbstring extraction error: %s", "Invalid substring number");
       break;
     case PCRE_ERROR_NOMEMORY:
       fprintf(stderr, "PCRE susbstring extraction error: %s", "Buffer too small");
       break;
     default:
       fprintf(stderr, "PCRE susbstring extraction error: code %d", match_count);
       break;
   }
 } else {
   for (index = 0; index < match_count; index++) {
     pcre_get_substring(input, output, match_count, index, &substring);
     printf("Match(%2d/%2d): (%2d:%2d) is: '%s'\n", index, match_count - 1, output[index*2], output[index*2+1], substring);
   }
   pcre_free_substring(substring);
 }
 pcre_free(re);
 // Free up the extra
 if (extra != NULL) {
   pcre_free(extra);
 }

 return EXIT_SUCCESS;
}
