#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "FileSystem.h"
/*Wyswietlenie listy komend*/
void help(char *command)
{
	printf("\n============================================================\n");
	printf("Uzycie:%s <komenda> ", command);
	printf("Lista komend: \n");
	printf("c [rozmiar w bajtach]- Utworzenie wirtualnego dysku\n");
	printf("m [nazwa_pliku]      - przeniesienie pliku na wirutalny dysk\n");
	printf("v [nazwa_pliku]      - przeniesienie pliku z wirutalnego dysku\n");
	printf("l - wyswietlenie listy plikow\n");
	printf("s - wyswietlenie statystyki dysku\n");
	printf("d - usuniecie dysku\n");
	printf("r [nazwa_pliku] - usuniecie zadanego pliku\n");
	printf("============================================================\n");
}

int main(int argc, char * argv[])
{
	struct VFS* v;
	if (argc<2) help(argv[0]);
	else {
		switch (argv[1][0])
		{
			case 'c':
			{
						v = CreateVFS(atoi(argv[2]));

						break;
			}
			case 'm':
			{
						v = openVFS();
						addFileToVFS(v, argv[2]);
						break;
			}
			case 'v':
			{
					if (argc>2)
					{
						v = openVFS();
						copyFileFromVFS(v, argv[2], argv[3]);
					}
					else printf("Brak nazwy pliku.\n");
					break;
			}
			case 'l':
			{
						v = openVFS();
						ls(v);
						break;
			}
			case 's':
			{
						v = openVFS();
						diskStatistics(v);
						break;
			}
			case 'd':
			{
						destroyVFS();
						break;
			}
			case 'r':
			{
						v = openVFS();
						removeFileFromVFS(v, argv[2]);
						break;
			}
			default:
			{
				help(argv[0]);
				break;
			}

		}
	}
	return 0;
}
