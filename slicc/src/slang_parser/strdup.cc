#include <stdlib.h>
#include <string.h>

char *strdup(const char *s) {
  size_t slen = strlen(s);
  char *result = (char *)malloc(slen + 1);
  if (result == NULL) {
    return NULL;
  }

  memcpy(result, s, slen + 1);
  return result;
}
