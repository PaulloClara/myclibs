size_t strsLen(char *str) {
  size_t len = 0;

  while(str[len++] != '\0' && str[len++] != '\n') {
    continue;
  }

  return len-1;
}

size_t strsCheckVowel(char ch) {
  switch (ch) {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':
      return 1;
    default:
      return 0;
  }
}

void strsSlice(char *stro, char *strd, int start, int end) {
  size_t len = 0;

  for (size_t i = start; i < end; i++) {
    strd[len++] = stro[i];
  }
  strd[len] = '\0';
}

void strsCopy(char *stro, char *strd) {
  size_t len = strsLen(stro);
  size_t newlen = 0;

  for (size_t i = 0; i < len; i++) {
    strd[newlen++] = stro[i];
  }
  strd[len] = '\0';
}

void strsCopyAndRmvChar(char *stro, char *strd, char ch, size_t n) {
  size_t len = strsLen(stro);
  size_t newlen = 0;

  if (!n) n = len;

  for (size_t i = 0; i < len; i++) {
    if (stro[i] != ch || !n) strd[newlen++] = stro[i];
    if (stro[i] == ch && n) n--;
  }
  strd[newlen] = '\0';
}

void strsReplace(char *str, char ch, char newch, size_t n) {
  size_t len = strsLen(str);

  if (!n) n = len;

  for (size_t i = 0; i < len; i++) {
    if (str[i] == ch && n) {
      str[i] = newch;
      n--;
    }
  }
}

void strsMerge(char *str1, char *str2, char ch) {
  /*
    str2 e usado como "forma" para a string final que sera guardada em str1,
    ch e o espaco "livre" que chars da str1 irao entrar

    ex:
      entrada => str1 = "pll clr" str2 = "*au**o***a*a" ch = '*'
      saida => str1 = "paullo clara"
  */
  size_t len1 = strsLen(str1);
  size_t len2 = strsLen(str2);

  size_t istr1 = 0;
  size_t newlen = 0;

  char strtemp[len1+len2];

  for (size_t i = 0; i < len2; i++) {
    if (str2[i] == ch) strtemp[newlen++] = str1[istr1++];
    else strtemp[newlen++] = str2[i];
  }
  strtemp[newlen] = '\0';

  strsCopy(strtemp, str1);
}

void strsRmvChar(char *str, char ch, size_t n) {
  size_t len = strsLen(str);
  char newstr[len];
  size_t newlen = 0;

  if (!n) n = len;

  for (size_t i = 0; i < len; i++) {
    if (str[i] != ch || !n) newstr[newlen++] = str[i];
    if (str[i] == ch && n > 0) n--;
  }
  newstr[newlen] = '\0';

  strsCopy(newstr, str);
}
