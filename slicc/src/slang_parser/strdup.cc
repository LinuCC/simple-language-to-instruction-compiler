#include "strdup.hh"
#include <stdlib.h>
#include <string.h>

/**
 * Define own version of strdup
 *
 * https://stackoverflow.com/questions/40766055/error-strdup-was-not-declared-in-this-scope
 */
char *strdup2(const char *s) {
  size_t slen = strlen(s);
  char *result = (char *)malloc(slen + 1);
  if (result == NULL) {
    return NULL;
  }

  memcpy(result, s, slen + 1);
  return result;
}
