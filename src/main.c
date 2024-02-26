#include <stdio.h>

void display_coucou(void) {
		printf("COUCOU");
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	display_coucou();
	return (0);
}
