#include "get_next_line.h"

int main()
{
	int i = 0;
	int fd = open("text.txt", O_RDWR | O_CREAT , 0777);
	char *s;
	write(fd, "\n\n", 2);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	// while ((s = get_next_line(fd)))
	// {
	// 	printf("%d-  %s", i++, s);
	// 	free(s);
	// 	if (s == NULL)
	// 		break;
	// }
}