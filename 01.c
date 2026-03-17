#include<stdio.h>
#include<string.h>
struct account
{
    int account_number;
    char name[200];
    int pin;
    float balance;
};
void create_account();
void create_login();
int main ()
{
    int choice;
    printf("---Welcome to the bank serivce-----\n");
    while(1)
    {
        printf("----------------------------------\n");
        printf("1.create account\n");
        printf("2.login\n");
        printf("3.exit\n");
        printf("Enter your choice:");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            create_account();
            break;
            case 2:
            create_login();
            break;
            case 3:
            printf("Thank you for using our serivce\n");
            return 0;
        }
    }
}

void create_account()
{
    FILE *fp;
    struct account a;
    fp=fopen("uday.bin","ab");
    printf("Enter account number:");
    scanf("%d",&a.account_number);
    printf("Enter your name:");
    scanf(" %[^\n]", a.name);
    printf("Enter your pin:");
    scanf("%d",&a.pin);
    printf("Enter your balance:");
    scanf("%f",&a.balance);
   fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);
    printf("Account created successfully\n");
}

void create_login()
{
    struct account a;
    FILE *fp;
    int found=0;
    fp=fopen("uday.bin","rb+");
    int acc,pin;
    printf("Enter your account number:");
    scanf("%d",&acc);
    printf("Enter your pin:");
    scanf("%d",&pin);
    
    while(fread(&a, sizeof(a), 1, fp) == 1)
    {
        if(a.account_number==acc && a.pin==pin)
        {
            found=1;
            printf("Login successful\n");
            break;
        }
    }
    if(!found)
    {
        printf("Invalid account number or pin\n");
        fclose(fp);
        return;
    }
    while(1)
    {
        printf("----------------------------------\n");
        printf("1.Balance Enquiry\n");
        printf("2.Deposit\n");
        printf("3.Withdraw\n");
        printf("4.Account Details\n");
        printf("5.Exit\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("Your current balance is: %.2f\n",a.balance);
                break;
            case 2:
            {
                float am;
                printf("Enter the amount to deposit:");
                scanf("%f",&am);
                a.balance+=am;
                fseek(fp,-sizeof(a),SEEK_CUR);
                fwrite(&a,sizeof(a),1,fp);
                printf("Amount deposited successfully\n");
                break;
            }
            case 3:
            {
                float am;
                printf("Enter the ammount to withdraw:");
                scanf("%f",&am);
                if(am>a.balance)
                {
                    printf("Insufficent balance\n");
                }
                else
                {
                    a.balance-=am;
                    fseek(fp,-sizeof(a),SEEK_CUR);
                    fwrite(&a,sizeof(a),1,fp);
                    printf("Amount withdrawn successfully\n");
                }
                break;
            }
            case 4:
                printf("------------Account Details------------\n");
                printf("Account Number:-%d\n",a.account_number);
                printf("Name:-%s\n",a.name);
                printf("Balance:-%.2f\n",a.balance);
                 FILE *fp1 = fopen("uday.txt","w");
                 if(fp1 != NULL)
                {
                fprintf(fp1,"Account Number:-%d\n",a.account_number);
                fprintf(fp1,"Name:-%s\n",a.name);
                fprintf(fp1,"Balance:-%.2f\n",a.balance);
                fclose(fp1);
                }
                break;
            case 5:
                fclose(fp);
                return;
            default:
                printf("Invalid choice\n");
        }
    }
}