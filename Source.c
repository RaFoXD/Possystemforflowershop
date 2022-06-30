#include "Functions.h"

extern FILE* pok;

int main()
{
	int option;
	printf("[Flower Shop]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY); //promijeni boju teksta u zelenu i pojacaj intenzitet
	open(); //otvaranje datoteke
	//glavni menu
	do {
		printf("\nMAIN MENU:\n");
		printf("Slelect:\n[1] to sort flowers by price,\n[2] to sort flowers by name,\n[3] to sort flowers by size,\n[4] to add new flower,\n[5] to delete flower,\n[6] to purchase flower,\n[Other number] to exit shop:\n");
		printf("Option:");
		scanf("%d", &option);
		switch (option)
		{
			case 1:
				read(option);
				break;
			case 2:
				read(option);
				break;
			case 3:
				read(option);
				break;
			case 4:
				add();
				break;
			case 5:
				deleteItem();
				break;
			case 6:
				purchase();
				break;
			default:
				break;
		}
	} while (option == 1 || option == 2 || option == 3 || option == 4 || option == 5 || option == 6);
	fclose(pok);
	return 0;
}