
#include <stdio.h>
#include <string.h>

enum {
  SKIPPING,
  CONSUMING,
};

#define consume(f) fgetc(f)

int entityStart(FILE* f, unsigned char c) {
  int has = 0;
  int consumed = 0;
  char buf[10] = {0};
  char* pbuf = buf;

  if (++consumed && (*pbuf++ = c)          == '<')
  if (++consumed && (*pbuf++ = consume(f)) == 'E') 
  if (++consumed && (*pbuf++ = consume(f)) == 'n')
  if (++consumed && (*pbuf++ = consume(f)) == 't')
  if (++consumed && (*pbuf++ = consume(f)) == 'i')
  if (++consumed && (*pbuf++ = consume(f)) == 't')
  if (++consumed && (*pbuf++ = consume(f)) == 'y')
    has = 1;

  if (has) fwrite(buf, 1, consumed, stdout);
  return has;
}

int entityEnd(FILE* f, unsigned char c) {
  int has = 0;
  int consumed = 0;
  char buf[8] = {0};
  char* pbuf = buf;

  if (++consumed && (*pbuf++ = c)          == '/')
  if (++consumed && (*pbuf++ = consume(f)) == 'E') 
  if (++consumed && (*pbuf++ = consume(f)) == 'n')
  if (++consumed && (*pbuf++ = consume(f)) == 't')
  if (++consumed && (*pbuf++ = consume(f)) == 'i')
  if (++consumed && (*pbuf++ = consume(f)) == 't')
  if (++consumed && (*pbuf++ = consume(f)) == 'y')
  if (++consumed && (*pbuf++ = consume(f)) == '>')
    has = 1;

  fwrite(buf, 1, consumed, stdout);
  if (has) fprintf(stdout, "\r\n");

  return has;
}

int main(int argc, char *argv[]) {
  unsigned char c;
  FILE* src = argc >= 2? fopen(argv[1], "rb") : stdin;
  int state = SKIPPING;

  printf("<Entities>\r\n");

  // up to first xml entry
  while (fread(&c, 1, 1, src) == 1) {
    switch (state) {
      case SKIPPING:
        if (entityStart(src, c)) {
          state = CONSUMING;
        }
        break;
      case CONSUMING:
        if (entityEnd(src, c)) {
          state = SKIPPING;
        }
        break;
    }
  }

  printf("</Entities>\r\n");

}
