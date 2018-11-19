#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

int main(void)
{
   FILE *f = 0;
   f = fopen("seoul.txt", "rt");

   if (f == 0)
   {
      printf("Unable to read file\n");
      return -1;
   }

   char buf[100];

   for (int i = 0; i < 10; i++)
   {
      fgets(buf, 99, f);
      printf("%s", buf);
      buf[0] = '\0';
   }
   fclose(f);

   return 0;
}
