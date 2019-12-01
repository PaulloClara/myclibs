/*
  Essa lib foi feita de partes de codigos encontrados na web e extremamente
  adaptados para o mundo linux.
*/

#include <errno.h>   /* for errno */
#include <unistd.h>  /* for EINTR */
#include <termios.h>
#include <sys/time.h>

void clearOut(int len) {
  for (int i = 0; i < len*2; i++) {
    fputc (0x8, stdout);
    fputc (' ', stdout);
    fputc (0x8, stdout);
  }
}

int getInputMaskingOutput(char **string, int len, int mask, FILE *fp) {
  /* index, number of chars in read */
  char ch;
  int index = 0;

  /* orig keyboard settings */
  struct termios old_kbd_mode;
  struct termios new_kbd_mode;

  /* save orig settings   */
  tcgetattr(0, &old_kbd_mode);

  /* copy old to new */
  memcpy(&new_kbd_mode, &old_kbd_mode, sizeof(struct termios));

  /* new kbd flags */
  new_kbd_mode.c_lflag &= ~(ICANON | ECHO);
  new_kbd_mode.c_cc[VTIME] = 0;
  new_kbd_mode.c_cc[VMIN] = 1;

  tcsetattr(0, TCSANOW, &new_kbd_mode);

  /* read chars from fp, mask if valid char specified */
  while (
    ((ch = fgetc(fp)) != '\n' && ch != EOF && index < len - 1) ||
    (index == len - 1 && ch == 127)
  ) {
    if (ch != 127) {
      /* valid ascii char */
      if (31 < mask && mask < 127) fputc(mask, stdout);

      (*string)[index++] = ch;
    } else {
      /* handle backspace (del) */
      if (index > 0) {
        if (31 < mask && mask < 127) {
          fputc (0x8, stdout);
          fputc (' ', stdout);
          fputc (0x8, stdout);
        }

        (*string)[--index] = 0;
      }
    }
  }

  (*string)[index] = 0; /* null-terminate */

  /* reset original keyboard */
  tcsetattr(0, TCSANOW, &old_kbd_mode);

  /* number of chars in string */
  return index;
}

int getInputAndCountChars(char **string, int len, char *msg, FILE *fp) {
  char ch = 0;
  int index = 0;

  /* orig keyboard settings */
  struct termios old_kbd_mode;
  struct termios new_kbd_mode;

  /* save orig settings  */
  tcgetattr(0, &old_kbd_mode);

  /* copy old to new */
  memcpy(&new_kbd_mode, &old_kbd_mode, sizeof(struct termios));

  /* new kbd flags */
  new_kbd_mode.c_lflag &= ~(ICANON | ECHO);
  new_kbd_mode.c_cc[VTIME] = 0;
  new_kbd_mode.c_cc[VMIN] = 1;

  tcsetattr(0, TCSANOW, &new_kbd_mode);

  /* read chars from fp, msg if valid char specified */
  printf("%d %s ", index, msg);
  while (
    ((ch = fgetc(fp)) != '\n' && ch != EOF && index < len - 1) ||
    (index == len - 1 && ch == 127)
  ) {
    if (ch != 127) {
      (*string)[index] = ch;
      (*string)[++index] = 0;

      clearOut(len);
      printf("%d %s %s", index, msg, *string);
    } else {
      if (index > 0) {
        (*string)[--index] = 0;

        clearOut(len);
        printf("%d %s %s", index, msg, *string);
      }
    }
  }

  /* reset original keyboard */
  tcsetattr (0, TCSANOW, &old_kbd_mode);

  /* number of chars in string */
  return index;
}
