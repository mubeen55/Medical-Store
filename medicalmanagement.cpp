#include <stdio.h>
#include <string.h>
struct medicine{
	int medid;
	char medname[20];
	char medformula[20];
	char medmfg[20];
	char medexpiry[20];
	float medprice;
};
struct staff{
	char suser[20];
	char spass[20];
};
void info(medicine med[]);
void search(medicine med[], int id);
void add(medicine tempo);
void remove(medicine med[], int id);
void update(medicine med[], int id);
void purchase(medicine med[], int id, int quantity);
int main()
{
	printf("-------------------------------------------------------------------------\n");
	printf("|\t\t\tMedical Management System\t\t\t|\n");
	printf("-------------------------------------------------------------------------\n\n");
	FILE *med, *log;
	medicine medi[20], tempo;
	staff account[2];
	char user[20], pass[20];
	int option=0, j=0, test=0, opt = 0, id, quantity;
	printf("\t\tSelect Login Type:\n\t\t1. Staff\n\t\t2. Customer\n\t\tYour Option: ");
	scanf("%d",&option);
	if(option == 1)
	{
		printf("\nEnter Username: ");
		scanf("%s",&user);
		printf("Enter Password: ");
		scanf("%s",&pass);
		log = fopen("accounts.txt","r+");
		while(fread(&account[j], sizeof(struct staff), 1, log))
		{
			if(strcmp(user, account[j].suser) == 0 && strcmp(pass, account[j].spass) == 0)
			{
				test = 1;
			}
			j++;
		}
		if(test == 1)
		{
			printf("\nLogin Successful !\n");
			while(opt != 6)
			{
				med = fopen("medicine.txt","r+");
				printf("\nSelect an Option:\n1. Medicines Information\n2. Search a Medicine\n3. Add a Medicine\n4. Remove a Medicine\n5. Update a Medicine\n6. Exit\n\nYour Choice: ");
				scanf("%d",&opt);
				if(opt == 1)
				{
					info(medi);
				}
				else if(opt == 2)
				{
					printf("\nEnter Medicine ID: ");
					scanf("%d",&id);
					search(medi, id);
				}
				else if(opt == 3)
				{
					add(tempo);
				}
				else if(opt == 4)
				{
					printf("\nEnter Medicine ID to Remove: ");
					scanf("%d",&id);
					remove(medi, id);
				}
				else if(opt == 5)
				{
					printf("\nEnter Medicine ID to Update: ");
					scanf("%d",&id);
					update(medi, id);
				}
				else if(opt == 6)
				{
					printf("\nProgram Terminated !");
				}
				else
				{
					printf("\nInvalid Option Entered !\n");
				}
			}
		}
	}
	else if(option == 2)
	{
		while(opt != 3)
		{
			printf("\nSelect an Option:\n1. Medicines Information\n2. Purchase a Medicine\n3. Exit\n\nYour Choice: ");
			scanf("%d",&opt);
			if(opt == 1)
			{
				info(medi);
			}
			else if(opt == 2)
			{
				printf("Enter Medicine ID: ");
				scanf("%d",&id);
				printf("Enter Quantity: ");
				scanf("%d",&quantity);
				purchase(medi, id, quantity);
			}
		}
	}
}
void info(medicine med[])
{
	FILE *c;
	int j=0;
	c = fopen("medicine.txt","r+");
	printf("------------------------------ Medicines List ------------------------------\n");
	while(fread(&med[j], sizeof(medicine), 1, c))
	{
		printf("\n\t\t\tMedicine ID: %d\n\t\t\tMedicine Name: %s\n\t\t\tMedicine Formula: %s\n\t\t\tMedicine Mfg: %s\n\t\t\tMedicine Exp: %s\n\t\t\tMedicine Price: $%0.2f\n",med[j].medid,med[j].medname,med[j].medformula,med[j].medmfg,med[j].medexpiry,med[j].medprice);
		j++;
	}
	fclose(c);
}
void search(medicine med[], int id)
{
	FILE *c;
	int j=0, check = 0;
	c = fopen("medicine.txt","r+");
	while(fread(&med[j], sizeof(medicine), 1, c))
	{
		if(med[j].medid == id)
		{
			check = 1;
			printf("\nMatch Found !\n");
			printf("\nMedicine ID: %d\nMedicine Name: %s\nMedicine Formula: %s\nMedicine Mfg: %s\nMedicine Exp: %s\nMedicine Price: $%0.2f\n",med[j].medid,med[j].medname,med[j].medformula,med[j].medmfg,med[j].medexpiry,med[j].medprice);
		}
	}
	if(check == 0)
	{
		printf("Medicine Not Found !\n");
	}
	fclose(c);
}
void add(medicine tempo)
{
	FILE *c;
	c = fopen("medicine.txt","a");
	printf("Med ID: ");
	scanf("%d",&tempo.medid);
	printf("Med Name: ");
	scanf("%s",&tempo.medname);
	printf("Med Formula: ");
	scanf("%s",&tempo.medformula);
	printf("Med Mfg: ");
	scanf("%s",&tempo.medmfg);
	printf("Med Exp: ");
	scanf("%s",&tempo.medexpiry);
	printf("Med Price: ");
	scanf("%f",&tempo.medprice);
	fwrite(&tempo, sizeof(medicine), 1, c);
	fclose(c);
	printf("\nMedicine Added Successfully !\n");
}
void remove(medicine med[], int id)
{
	FILE *c, *temp;
	int j=0, check = 0;
	c = fopen("medicine.txt","r+");
	temp = fopen("temp.txt","w+");
	while(fread(&med[j], sizeof(medicine), 1, c))
	{
		if(med[j].medid == id)
		{
			check = 1;
		}
		else
		{
			fwrite(&med[j], sizeof(medicine), 1, temp);
		}
		j++;
	}
	fclose(c);
	fclose(temp);
	
	if(check == 1)
	{
		printf("\nMedicine Deleted Successfully !\n");
	}
	else
	{
		printf("Medicine Not Found !\n");
	}
	c = fopen("medicine.txt","w+");
	temp = fopen("temp.txt","r+");
	j = 0;
	while(fread(&med[j], sizeof(medicine), 1, temp))
	{
		fwrite(&med[j], sizeof(medicine), 1, c);
		j++;
	}
	fclose(c);
	fclose(temp);
}
void update(medicine med[], int id)
{
	FILE *c, *temp;
	int j=0, check = 0;
	float cost;
	printf("Enter New Price: ");
	scanf("%f",&cost);
	c = fopen("medicine.txt","r+");
	temp = fopen("temp.txt","w+");
	while(fread(&med[j], sizeof(medicine), 1, c))
	{
		if(med[j].medid == id)
		{
			med[j].medprice = cost;
			check = 1;
		}
		fwrite(&med[j], sizeof(medicine), 1, temp);
		j++;
	}
	fclose(c);
	fclose(temp);
	
	c = fopen("medicine.txt","w+");
	temp = fopen("temp.txt","r+");
	if(check == 1)
	{
		printf("\nMedicine Updated Successfully !\n");
	}
	else
	{
		printf("Medicine Not Found !\n");
	}
	j = 0;
	while(fread(&med[j], sizeof(medicine), 1, temp))
	{
		fwrite(&med[j], sizeof(medicine), 1, c);
		j++;
	}
	fclose(c);
	fclose(temp);
}
void purchase(medicine med[], int id, int quantity)
{
	FILE *c;
	int j=0, check = 0, select = 0;
	float total;
	c = fopen("medicine.txt","r+");
	while(fread(&med[j], sizeof(medicine), 1, c))
	{
		if(med[j].medid == id)
		{
			total = med[j].medprice * quantity;
			check = 1;
		}
		j++;
	}
	if(check == 1)
	{
		printf("Confirm Checkout:\n1. Yes\n2. No\nYour Choice: ");
		scanf("%d",&select);
		if(select == 1)
		{
			printf("\nMedicine Successfully Purchased for %0.2f\n",total);
			total = 0;
		}
		else if(select == 2)
		{
			printf("\nMedicine Purchase Failed, Add Medicine to Cart Again !\n");
			total = 0;
		}
		else
		{
			printf("\nInvalid Option Entered !\n");
		}
	}
	else
	{
		printf("\nMedicine Not Found !\n");
	}
	fclose(c);
}