#include "Functions.h"

FILE* pok; //pokazivac na datoteku

void open() //otvaranje binarne datoteke
{
	pok = fopen("shop.txt", "ab+");
	if (pok == NULL)
		exit(EXIT_FAILURE);
}
int structCount() //broji koliko je flowers(struktura) u fileu
{
	fseek(pok, 0, SEEK_END); //odi na pocetak
	int count = ftell(pok) / sizeof(flower);
	rewind(pok); //odi na pocetak
	return count;
}

void warningMessage(char* message) //funkcija za ispis poruke u boji
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("WARNING: %s\n", message);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void add()
{
	printf("Add flower:\n");
	flower temp = { 0 }; //stvaranje privremene strukture za unos podataka
	//unos podataka
	printf("ID:\n");
	scanf("%d", &temp.id);
	printf("Name:\n");
	scanf("%s", &temp.name);
	printf("Price[$]:\n");
	scanf("%f", &temp.pricePerUnit);
	printf("Diameter[cm]:\n");
	scanf("%f", &temp.size);
	printf("Type(family):\n");
	scanf("%s", &temp.type);
	printf("Color:\n");
	scanf("%s", &temp.color);
	fseek(pok, 0, SEEK_END); //odi na kraj filea
	fwrite(&temp, sizeof(flower), 1, pok); //upisi na kraj filea novi flower
	printf("Flower added to shop!\n");
}
void swap(flower* f1, flower* f2) //zamijena vrijednosti dvije varijable
{
	flower temp = *f1;
	*f1 = *f2;
	*f2 = temp;
}
void sortByName(flower* f)
{
	for (int i = 0; i < structCount() - 1; i++) //selection sort
	{
		for (int j = i + 1; j < structCount(); j++)
		{
			if (strcmp(f[i].name, f[j].name) > 0) //uzlazno sortiranje po imenu
				swap(&f[i], &f[j]);
		}
	}
}
void sortBySize(flower* f)
{
	for (int i = 0; i < structCount() - 1; i++) //selection sort
	{
		for (int j = i + 1; j < structCount(); j++)
		{
			if (f[i].size > f[j].size) //uzlazno sortiranje po velicini
				swap(&f[i], &f[j]);
		}
	}
}
void sortByPrice(flower* f)
{
	for (int i = 0; i < structCount() - 1; i++) //selection sort
	{
		for (int j = i + 1; j < structCount(); j++)
		{
			if (f[i].pricePerUnit > f[j].pricePerUnit) //uzlazno sortiranje po jedinicnoj cijeni
				swap(&f[i], &f[j]);
		}
	}
}
void read(int option)
{
	int n = structCount();
	//ako je prazan file onda ispisi poruku i vrati se u main menu
	if (!n)
	{
		warningMessage("Shop is empty! Check back later...");
		return;
	}
	flower* flowers = (flower*)malloc(sizeof(flower) * n); //niz struktura za prihvat podataka iz filea
	//fseek(pok, 0, SEEK_SET);
	rewind(pok); //odi na pocetak filea
	fread(flowers, sizeof(flower), n, pok); //procitaj sve zapise u datoteci i spremi u niz struktura flowers
	switch (option)
	{
		case 1:
			sortByPrice(flowers);
			break;
		case 2:
			sortByName(flowers);
			break;
		case 3:
			sortBySize(flowers);
			break;
	}
	//ispisi sve na ekran
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("|ID||NAME||PRICE[$]||SIZE[cm]||TYPE||COLOR|\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN);
	for (int i = 0; i < structCount(); i++)
	{
		printf("|%d|", flowers[i].id);
		printf("|%s|", flowers[i].name);
		printf("|%.2f|", flowers[i].pricePerUnit);
		printf("|%.2f|", flowers[i].size);
		printf("|%s|", flowers[i].type);
		printf("|%s|\n", flowers[i].color);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("\n");
	//oslobodi dinamicki zauzetu memoriju
	free(flowers);
}
void purchase()
{
	if (!structCount())
	{
		warningMessage("No flowers in shop!");
		return;
	}
	printf("Enter ID of flower you want to buy:\n");
	int id, amount, n = structCount();
	scanf("%d", &id);
	flower* f = (flower*)malloc(sizeof(flower) * n);
	rewind(pok); //odi na pocetak filea
	fread(f, sizeof(flower), n, pok); //procitaj sve zapise u datoteci i spremi u polje struktura f
	for (int i = 0; i < n; i++)
	{
		if (f[i].id == id)
		{
			printf("Enter amount:\n");
			scanf("%d", &amount);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
			printf("Order: %d-%s-%.2fcm-%s-%s -- amount:%d\n", f[i].id, f[i].name, f[i].size, f[i].type, f[i].color, amount);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN);
			printf("Your order is sucessfully processed! You will be charged %.2f$\n\n", amount*f[i].pricePerUnit);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			return;
		}
	}
	warningMessage("Flower with that ID was not found!");
}
void deleteItem()
{
	//ako je prazan file onda ispisi poruku i vrati se u main menu
	if (!structCount())
	{
		warningMessage("No flowers in shop!");
		return;
	}
	int id = 0, n = structCount(), found = 0;
	printf("Flower ID to delete:\n");
	scanf("%d", &id);
	flower* f = (flower*)malloc(sizeof(flower) * n);
	rewind(pok); //odi na pocetak filea
	fread(f, sizeof(flower), n, pok); //procitaj sve zapise u datoteci i spremi u polje struktura f

	for (int i = 0; i < n; i++)
	{
		if (f[i].id == id) //testiranje odgovarajuceg ID-a
		{
			found = 1;
			while (i < n - 1) //prepisuj sve cvjetove redom do zadnjeg
			{
				f[i] = f[i + 1];
				++i;
			}
			break;
		}
	}
	if (found == 0) //ako nije naden element sa danim ID-om ispisi poruku	
	{
		warningMessage("Flower with that ID was not found.");
		free(f);
		return;
	}
	fclose(pok);
	//brisanje svega iz filea
	remove("shop.txt");
	open();
	rewind(pok); //odi na pocetak filea
	fwrite(f, sizeof(flower), n - 1, pok); //pisanje u file, zadnji cvijet ne ukljucujemo jer je na mjestu onog obrisanog zato n-1
	printf("Flower has beed deleted!\n");
	free(f);
}