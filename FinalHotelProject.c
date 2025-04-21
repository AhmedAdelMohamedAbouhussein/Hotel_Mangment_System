#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>

typedef struct {
    int room_number;
    int price;
    char roomtype[20];
    char package[50];
    bool is_occupied;
    int customeridinroom;
    bool businessdiscount;
    int level;
}Hotelrooms;

Hotelrooms rooms[100];

typedef struct {
    int number;
    char name[40];
    int price;
} Customer;
Customer customer[100];

void Book(int*,int, char name[]); // book available room
void Available_rooms(); // list available rooms with their details 
void Edit_rooms(int,int*); //
void List_rooms(); //list all rooms (available and occupied) with their details
void Delete_customer(int); // Delete customer
void Delete_Room(int); // delete booked room

int Services(int*); // prints out hotel available services and allow users to choose a service
void changeroom(int, int*,int); //part of edit function allows users to change booked rooms
void changepackage(int,int, int*); //part of edit function allows users to change selected packages

int main(void)
{    

    for(int i = 0;i < 100;i++)
    {
        //initialize roomnumber/ customerid/ package/ name/ customer.price/ customer.customeridinroom
        rooms[i].room_number = i + 1;
        customer[i].number= i + 1;
        strcpy(rooms[i].package,"");
        strcpy(customer[i].name,"");
        customer[i].price = 0;
        rooms[i].customeridinroom = 0;
        rooms[i].is_occupied = false;
        rooms[i].businessdiscount = false;

        //initialize room.roomtype and room.price
        if(i <= 19)
        {
            rooms[i].price = 100;
            strcpy(rooms[i].roomtype, "Single");
        }
        else if(i > 19 && i <= 49)
        {
            rooms[i].price = 150;
            strcpy(rooms[i].roomtype, "Double");
        }
        else if(i > 49 && i <= 69)
        {
            rooms[i].price = 200;
            strcpy(rooms[i].roomtype, "Triple");
        }
        else if(i > 69)
        {
            rooms[i].price = 250;
            strcpy(rooms[i].roomtype, "Suite");
        }

        //initialize levels in the hotel 10 levels
        if(i <= 9)
        {
            rooms[i].level = 1;
        }
        else if (i > 9 && i <= 19)
        {
            rooms[i].level = 2;
        }
        else if (i > 19 && i <= 29)
        {
            rooms[i].level = 3;
        }
        else if (i > 29 && i <= 39)
        {
            rooms[i].level = 4;
        }
        else if (i > 39 && i <= 49)
        {
            rooms[i].level = 5;
        }
        else if (i > 49 && i <= 59)
        {
            rooms[i].level = 6;
        }
        else if (i > 59 && i <= 69)
        {
            rooms[i].level = 7;
        }
        else if (i > 69 && i <= 79)
        {
            rooms[i].level = 8;
        }
        else if (i > 79 && i <= 89)
        {
            rooms[i].level = 9;
        }
        else if (i > 89 && i <= 99)
        {
            rooms[i].level = 10;
        }
    }

    printf("\nWelcome to the Hotel\n");
    
    while(true)
    {
        //write customer's info and fees in a file (customerinfoandfee.txt)
        FILE* file = fopen("customerinfoandfee.txt","w"); 
        if (file != NULL)
        {
            fprintf(file,"id            name            fees\n");
            for (int i = 0; i < 100; i++)
            {
                if(strcmp(customer[i].name,"") != 0)
                {
                    fprintf(file, "%d         %s           %d\n", customer[i].number,customer[i].name,customer[i].price);
                }
            }
            fclose(file);
        }

        //write occupied rooms in a file (occupiedrooms.txt)
        FILE* f = fopen("occupiedrooms.txt","w"); 
        if (f != NULL)
        {
            fprintf(f,"Occupies rooms:\n");
            for (int i = 0; i < 100; i++)
            {
                if(rooms[i].is_occupied == true)
                {
                    int customerid;

                    fprintf(f,"room: %d   level: %d",rooms[i].room_number, rooms[i].level);

                    fprintf(f,"   package: %s   Roomtype: %s",rooms[i].package,rooms[i].roomtype); 

                    fprintf(f,"   Occupied by: ");
                    customerid = rooms[i].customeridinroom;

                    for(int j = 0; j < 100; j++)
                    {
                        if((customerid == customer[j].number))
                        {
                                fprintf(f,"%s (ID: %d)",strlwr(customer[j].name),customer[j].number);
                        }
                    }
            
                    if(rooms[i].businessdiscount == true)
                    {
                        fprintf(f,"   On Business");
                    }

                    fprintf(f,"\n");
                }
            }
        }
        fclose(f);

        //user enters the service he wants
        char yesorno;
        int servicesflag = 0;
        int customer_id;
        char Name[40];
        char secondname[20];

        int choice = Services(&servicesflag);
        if(servicesflag == 1)
        {
            servicesflag = 0;
            continue;
        }
        //if user wants to exit
        if(choice == 7)
        {
            printf("\nHope you enjoyed our services\n\n");
            return(0);
        }

        int bookflag= 0, flag = 0, flag1 = 0, flag2 = 0,flag3 = 0,index,iii;

        // 5 input potentials in a switch statment
        switch(choice)
        {
            case 1:
                //user wants to book room
                printf("Do you have a customer-ID (y/n): ");
                scanf(" %c",&yesorno);
            
                if(toupper(yesorno) == 'N')//if customer doesn't have an ID
                {
                    printf("Please enter your first name: ");
                    scanf("%s",&Name);
                    printf("Please enter your second name: ");
                    scanf("%s",&secondname);
                    strcat(Name," ");
                    strcat(Name,secondname);

                    printf("Your customer ID is ");
                    
                    for(iii = 0; iii < 100; iii++) //give customer an id
                    {
                        if(strcmp(customer[iii].name,"")== 0)
                        {
                            customer_id = customer[iii].number;
                            printf("(%d) \n",customer_id);
                            break;
                        }

                    }
                    if(iii == 100)// if all rooms are occupied
                    {
                        printf("\nAll rooms are occupied\n");
                        continue;
                    }
                }
                else if(toupper(yesorno) == 'Y') //if customer already has an ID
                {
                    
                    printf("Enter your customer ID: ");
                    scanf("%d", &customer_id);
                    printf("Enter your first Name: ");
                    scanf("%s",&Name);
                    printf("Please enter your second name: ");
                    scanf("%s",&secondname);
                    strcat(Name," ");
                    strcat(Name,secondname);
                    for(index = 0; index < 100; index++)//check if customer ID matches name
                    {
                        if((strcmp(strupr(Name), strupr(customer[index].name)) == 0) && (customer_id == customer[index].number))
                        {
                            printf("Welcome:  %s\n",strlwr(customer[index].name));
                            break;
                        }
                    }
                    if(index == 100) //if customer ID doesnt match name or if user doesnt exist
                    {
                        printf("\nUsername and ID do not match\n");
                        continue;
                    }

                }
                else if(toupper(yesorno) != 'Y' && toupper(yesorno) != 'N')// if input is invalis not "y" or "n"
                {
                    printf("\nInvalid choice\n");
                    continue; 
                }

                Book(&bookflag,customer_id,Name); //enter book function
                if(bookflag == 1)
                {
                    bookflag = 0;
                    break;
                }

            break;
            case 2:
                Available_rooms();
            break;
            case 3:
                int in;
                printf("Enter your customer ID: ");
                scanf("%d", &customer_id);
                printf("Enter your first name: ");
                scanf("%s",&Name);
                printf("Please enter your second name: ");
                scanf("%s",&secondname);
                strcat(Name," ");
                strcat(Name,secondname);

                for(in = 0; in < 100; in++) //check if name matches ID
                    {
                        if((strcmp(strupr(Name), strupr(customer[in].name)) == 0) && (customer_id == customer[in].number))
                        {
                            break;
                        }
                    }
                    if(in == 100) //if ID and name dont match or user doesnt exist
                    {
                        printf("\nUsername and ID do not match\n");
                        continue;
                    }
                
                Edit_rooms(customer_id, &flag);
                if(flag == 1)
                {
                    flag = 0;
                    continue;
                }
            break;
            case 4:
                List_rooms();
            break;
            case 5:
                int ind;
                printf("Enter your customer ID: ");
                scanf("%d", &customer_id);
                printf("Enter your first name: ");
                scanf("%s",&Name);
                printf("Please enter your second name: ");
                scanf("%s",&secondname);
                strcat(Name," ");
                strcat(Name,secondname);

                for(ind = 0; ind < 100; ind++) //check if ID matches name
                    {
                        if((strcmp(strupr(Name), strupr(customer[ind].name)) == 0) && (customer_id == customer[ind].number))
                        {
                            printf("Welcome %s\n",strlwr(customer[ind].name));
                            break;
                        }
                    }
                    if(ind == 100)//if userid and name dont match or user doesnt exist
                    {
                        printf("\nUsername and ID do not match\n");
                        continue;
                    }

                Delete_Room(customer_id);
                printf("\nRoom Deleted\n");
            break;
            case 6:
            int ii;
                printf("Enter your customer ID: ");
                scanf("%d", &customer_id);
                printf("Enter your first name: ");
                scanf("%s",&Name);
                printf("Please enter your second name: ");
                scanf("%s",&secondname);
                strcat(Name," ");
                strcat(Name,secondname);

                for(ii = 0; ii < 100; ii++) //check if ID matches name
                    {
                        if((strcmp(strupr(Name), strupr(customer[ii].name)) == 0) && (customer_id == customer[ii].number))
                        {
                            printf("Welcome %s\n",strlwr(customer[ii].name));
                            break;
                        }
                    }
                    if(ii == 100)//if userid and name dont match or user doesnt exist
                    {
                        printf("\nUsername and ID do not match\n");
                        continue;
                    }

                Delete_customer(customer_id);
                printf("\nCustomer Deleted\n");
            break;
        }
    }
}

int Services(int* flag)
{
    int choice;
    FILE *ptr = fopen("Services.txt", "r");     //open Services.txt file
    if(ptr == NULL) //if file doesnt open
    {
        printf("\nError file was not opened.Terminate program\n");
        *flag = 1;
        return(0);
    }
    char ch;
    printf("\nChoose a service (1-7)\n");
    while ((ch = fgetc(ptr)) != EOF) //read file content
    {
        printf("%c", ch);
    }
    fclose(ptr); //close file
    printf("\n");
    scanf("%d",&choice);
    if(choice > 7 || choice < 1)//if choice is invalid
    {
        printf("\nInvalid Input choose a service from 1 to 7\n");
        *flag = 1;
        return(0);
    }
    return(choice);
}
void Book(int* flag,int customer_id, char Name[]) 
{
    int room;
    int business;

    FILE *ptr = fopen("Rooms.txt", "r");    //open Room.txt file
    if(ptr == NULL)//if file doesnt open
    {
        printf("\nError file was not opened.Terminate program\n");
        *flag = 1;
        return;
    }
    printf("Are you staying for business reasons? (1 for yes, 0 for no): ");
    scanf("%d",&business);
    if(business != 1 && business != 0) //if input is invalid
    {
        printf("\nInvalid Input\n");
        *flag = 1;
        return;
    }
    char ch;
    printf("choose the room type (1-4)\n");
    while ((ch = fgetc(ptr)) != EOF)    //read file content
    {
        printf("%c", ch);
    }
    printf("\n");    
    
    scanf("%d",&room);
    fclose(ptr);//close file
    if(room > 4 || room < 1) //if input is invalid
    {
        printf("\nInvalid Input\n");
        *flag = 1;
        return;
    }

    int price,package,roomnumber;
    if( room == 1)
    {
        printf("pick a single room from 1 to 20: ");
        scanf("%d",&roomnumber);
        if((roomnumber < 1) || (roomnumber > 20))
        {
            printf("\nroom %d is not a single room \n",roomnumber);//if user input is invalid
            *flag = 1;
            return;
        }
        price = 100; //initialize price
    }
    else if( room == 2)
    {
        printf("pick a double room from 21 to 50: ");
        scanf("%d",&roomnumber);
        if((roomnumber < 21) || (roomnumber > 50))//if user input is invalid
        {
            printf("\nroom %d is not a double room \n",roomnumber);
            *flag = 1;
            return;
        }
        price = 150; //initialize price
    }
    else if( room == 3)
    {
        printf("pick a triple room from 51 to 70: ");
        scanf("%d",&roomnumber);
        if((roomnumber < 51) || (roomnumber > 70))//if user input is invalid
        {
            printf("\nroom %d is not a triple room \n",roomnumber);
            *flag = 1;
            return;
        }
        price = 200; //initialize price
    }
    else if( room == 4)
    {
        printf("pick a suite from 71 to 100: ");
        scanf("%d",&roomnumber);
        
        if((roomnumber < 71) || (roomnumber > 100)) //if user input is invalid
        {
            printf("\nroom %d is not a suite \n",roomnumber);
            *flag = 1;
            return;
        }
        price = 250;   //initialize price
    }

        for(int i = 0 ;i < 100; i++) //if room is occupied
    {
        if(rooms[i].room_number == roomnumber)
        {
            if(rooms[i].is_occupied == true)
            {
                printf("\nroom %d is already occupied\n",roomnumber);
                *flag = 1;
                return; 
            }
        }
    }

    if(business == 1) //change price if user is on business
    {
        price = price * 0.80;
        
    }
    printf("choose package: (1-3)\n1-breakfast only ($5)\n2-half board ($10)\n3-all inclusive ($15)\n"); //user chooses a package
    scanf("%d",&package);

    char pack[20];

    if(package != 1 && package != 2 && package !=3)
    {
        printf("\nInvalid Input\n");
        *flag = 1;
        return;
    }
    if(package == 1)
    {
        strcpy(pack , "breakfast only");
        price = price + 5;
    }
    else if(package == 2)
    {
        strcpy(pack, "half board");
        price = price + 10;

    }
    else if(package == 3)
    {
        strcpy(pack , "all inclusive");
        price = price + 15;
    }


    for(int i = 0;i < 100;i++) //store all data collected in room structure
    {
        if(rooms[i].room_number == roomnumber)
        {
            rooms[i].price = price;
            strcpy(rooms[i].package, pack);
            rooms[i].is_occupied = true;
            if(business == 1)
            {
                rooms[i].businessdiscount = true;
            }
            rooms[i].customeridinroom = customer_id;
        }
    }
    for(int i = 0;i < 100;i++)  //Store all data in customer structure
    {
        if (customer[i].number == customer_id)
        {            
            strcpy(customer[i].name,Name);

            customer[i].price = customer[i].price + rooms[roomnumber - 1].price;
        }
    }


    printf("\nRoom Booked Successfully\n");
}

void Available_rooms()
{
    for(int i = 0; i < 100; i++)
    {
        if(rooms[i].is_occupied == false)
        {
            printf("room: %d   level: %d  price: %d   package: ",rooms[i].room_number,rooms[i].level,rooms[i].price);
            puts(rooms[i].package);
            printf("   Roomtype: ");
            puts(rooms[i].roomtype);            
            printf("\n");
        }
    }
}
void Edit_rooms(int customerid, int* flag)
{
    int roomnum = 0;
    int roomnumber;
    for(int i = 0; i < 100 ;i++) // count number of rooms user booked
    {
        if(customerid == rooms[i].customeridinroom)
        {
            roomnum = roomnum + 1;
        }
    }
    if(roomnum > 1) //if user booked multiple rooms
    {
        printf("which room do you want to edit:  \n");
        for(int i = 0; i < 100; i++)
        {
            if(customerid == rooms[i].customeridinroom)
            {
                printf("room:%d\n",rooms[i].room_number);
                
            }
        }
        scanf("%d",&roomnumber);
    }
    else //if user has only booked 1 room
    {
        for(int i = 0; i < 100 ;i++) 
        {
            if(customerid == rooms[i].customeridinroom)
            {
                roomnumber = rooms[i].room_number;
            }
        }
    }
    int editservice;
    printf("What do you want to edit (1-3)\n1)change room\n2)Change package\n");
    scanf("%d",&editservice);
    switch(editservice)
    {
        case 1:
            int flag2 = 0;
            changeroom(customerid,&flag2,roomnumber);
                if(flag2 == 1)
                {
                    flag2 = 0;
                    *flag = 1;
                    return;
                }
        break;
        case 2:
            int flag3 = 0;
            changepackage(customerid,roomnumber,&flag3);
            if(flag3 == 1)
                {
                    flag3 = 0;
                    *flag = 1;
                    return;
                }
        break;
        default:
            printf("\nInvalid Input\n");
        break;
    }
}

void List_rooms()
{
    for(int i = 0; i < 100; i++)
    {
            int customerid;

            printf("room: %d   level: %d",rooms[i].room_number, rooms[i].level);

            if(rooms[i].is_occupied == false)
            {
                printf("   price: %d", rooms[i].price);
            }
            printf("   package: %s   Roomtype: %s",rooms[i].package,rooms[i].roomtype); 
            if(rooms[i].is_occupied == false)
            printf("   Available");
            else
            {
                printf("   Occupied by: ");
                customerid = rooms[i].customeridinroom;

                for(int j = 0; j < 100; j++)
                {
                    if((customerid == customer[j].number))
                    {
                        printf("%s (ID: %d)",strlwr(customer[j].name),customer[j].number);
                    }
                }
            }
            
            if(rooms[i].businessdiscount == true)
            {
                printf("   On Business");
            }

            printf("\n");
    }
}
void Delete_Room(int customerid)
{
    int roomnum = 0;
    int roomnumber;
    int price = 0;
    for(int i = 0; i < 100 ;i++) // count number of rooms user booked
    {
        if(customerid == rooms[i].customeridinroom)
        {
            roomnum = roomnum + 1;
        }
    }
    if(roomnum > 1) //if user booked multiple rooms
    {
        printf("which room do you want to edit:  \n");
        for(int i = 0; i < 100; i++)
        {
            if(customerid == rooms[i].customeridinroom)
            {
                printf("room:%d\n",rooms[i].room_number);
                
            }
        }
        scanf("%d",&roomnumber);
    }
    else //if user has only booked 1 room
    {
        for(int i = 0; i < 100 ;i++) 
        {
            if(customerid == rooms[i].customeridinroom)
            {
                roomnumber = rooms[i].room_number;
            }
        }
    }

    rooms[roomnumber -1].customeridinroom = 0;
    if(roomnumber <= 20) //remove original room price from customer fees
    {
        rooms[roomnumber - 1].price = 100;
        if(rooms[roomnumber -1].businessdiscount == false)
        {
            customer[customerid -1].price = customer[customerid -1].price - 100; 
        }
        else{
            customer[customerid -1].price = customer[customerid -1].price - 80; 
        }
    }
    else if(roomnumber > 20 && roomnumber <= 50)
    {
        rooms[roomnumber -1].price = 150;
        if(rooms[roomnumber - 1].businessdiscount == false)
        {
            customer[customerid -1].price = customer[customerid -1].price - 150; 
        }
        else{
            customer[customerid -1].price = customer[customerid -1].price - 120; 
        }
    }
    else if(roomnumber > 50 && roomnumber <= 70)
    {
        rooms[roomnumber -1].price = 200;
        if(rooms[roomnumber - 1].businessdiscount == false)
        {
            customer[customerid -1].price = customer[customerid -1].price - 200; 
        }
        else{
            customer[customerid -1].price = customer[customerid -1].price - 160; 
        }
    }
    else if(roomnumber > 70)
    {
        rooms[roomnumber -1].price = 250;
        if(rooms[roomnumber - 1].businessdiscount == false)
        {
            customer[customerid -1].price = customer[customerid -1].price - 250; 
        }
        else{
            customer[customerid -1].price = customer[customerid -1].price - 200; 
        }
    }

    if(strcmp(rooms[roomnumber -1].package , "breakfast only") == 0) //remove original package price
    {
        price = price - 5;
    }
    else if(strcmp(rooms[roomnumber -1].package , "half board") == 0)
    {
        price = price - 10;
    }
    else if(strcmp(rooms[roomnumber -1].package , "all inclusive") == 0)
    {
        price = price - 15;
    }
    customer[customerid -1].price = customer[customerid -1].price + price;

    rooms[roomnumber -1].is_occupied = false;
    rooms[roomnumber -1].businessdiscount = false;
    strcpy(rooms[roomnumber -1].package,"");
}

void Delete_customer(int customerid)
{
    for(int i = 0 ; i< 100; i++)
    {
        if(rooms[i].customeridinroom == customerid) //initialize all structure variables to there origial value
        {
            strcpy( rooms[i].package,"");
            customer[i].price = 0;
            strcpy(customer[i].name,"");
            rooms[i].customeridinroom = 0;

            if(i <= 19)
            {
                rooms[i].price = 100;
            }
            else if(i > 19 && i <= 49)
            {
                rooms[i].price = 150;
            }
            else if(i > 49 && i <= 69)
            {
                rooms[i].price = 200;
            }
            else if(i > 69)
            {
                rooms[i].price = 250;
            }
            rooms[i].is_occupied = false;
            rooms[i].businessdiscount = false;
        }
    }
}

void changeroom(int customerid, int *flag, int originalroomnumber)
{
    int room;
    bool bus;
    bus = rooms[originalroomnumber -1].businessdiscount;

    FILE *ptr = fopen("Rooms.txt", "r"); //open file Rooms.txt 
    if(ptr == NULL)//if file doesnt open
    {
        printf("\nError file was not opened.Terminate program\n");
        *flag = 1;
        return;
    }
    char ch;
    printf("choose the room type (1-4)\n");
    while ((ch = fgetc(ptr)) != EOF) //read file content
    {
        printf("%c", ch);
    }
    printf("\n");    
    
    scanf("%d",&room);
    fclose(ptr); //close file
    if(room > 4 || room < 1)//if input is invalid
    {
        printf("\nInvalid Input\n");
        *flag = 1;
        return;
    }

    int price,roomnumber;
    if( room == 1)
    {
        printf("pick a single room from 1 to 20: ");
        scanf("%d",&roomnumber);
        if((roomnumber < 1) || (roomnumber > 20))//if input is invalid
        {
            printf("\nroom %d is not a single room \n",roomnumber);
            *flag = 1;
            return;
        }
        price = 100;
    }
    else if( room == 2)
    {
        printf("pick a double room from 21 to 50: ");
        scanf("%d",&roomnumber);
        if((roomnumber < 21) || (roomnumber > 50))//if input is invalid
        {
            printf("\nroom %d is not a double room \n",roomnumber);
            *flag = 1;
            return;
        }
        price = 150;
    }
    else if( room == 3)
    {
        printf("pick a triple room from 51 to 70: ");
        scanf("%d",&roomnumber);
        if((roomnumber < 51) || (roomnumber > 70))//if input is invalid
        {
            printf("\nroom %d is not a triple room \n",roomnumber);
            *flag = 1;
            return;
        }
        price = 200;
    }
    else if( room == 4)
    {
        printf("pick a suite from 71 to 100: ");
        scanf("%d",&roomnumber);
        
        if((roomnumber < 71) || (roomnumber > 100))//if input is invalid
        {
            printf("\nroom %d is not a suite \n",roomnumber);
            *flag = 1;
            return;
        }
        price = 250;
    }

        for(int i = 0 ;i < 100; i++)
    {
        if(rooms[i].room_number == roomnumber)  //if room is already occupied
        {
            if(rooms[i].is_occupied == true)
            {
                printf("\nroom %d is already occupied",roomnumber);
                *flag = 1;
               return; 
            }
        }
    }

    if(bus == true) //if customer id on business
    {
        price = price * 0.80;
    }

        rooms[originalroomnumber -1].customeridinroom = 0;
        if(originalroomnumber <= 20) //remove original room price from customer fees
        {
            rooms[originalroomnumber - 1].price = 100;
            if(rooms[originalroomnumber -1].businessdiscount == false)
            {
                customer[customerid -1].price = customer[customerid -1].price - 100; 
            }
            else{
                customer[customerid -1].price = customer[customerid -1].price - 80; 
            }
        }
        else if(originalroomnumber > 20 && originalroomnumber  <= 50)
        {
            rooms[originalroomnumber -1].price = 150;
            if(rooms[originalroomnumber - 1].businessdiscount == false)
            {
                customer[customerid -1].price = customer[customerid -1].price - 150; 
            }
            else{
                customer[customerid -1].price = customer[customerid -1].price - 120; 
            }
        }
        else if(originalroomnumber > 50 && originalroomnumber <= 70)
        {
            rooms[originalroomnumber -1].price = 200;
            if(rooms[originalroomnumber - 1].businessdiscount == false)
            {
                customer[customerid -1].price = customer[customerid -1].price - 200; 
            }
            else{
                customer[customerid -1].price = customer[customerid -1].price - 160; 
            }
        }
        else if(originalroomnumber > 70)
        {
            rooms[originalroomnumber -1].price = 250;
            if(rooms[originalroomnumber - 1].businessdiscount == false)
            {
                customer[customerid -1].price = customer[customerid -1].price - 250; 
            }
            else{
                customer[customerid -1].price = customer[customerid -1].price - 200; 
            }
        }
        rooms[originalroomnumber -1].is_occupied = false;
        rooms[originalroomnumber -1].businessdiscount = false;

    for(int i = 0;i < 100;i++)
    {
        if(rooms[i].room_number == roomnumber) //store room info
        {
            rooms[i].price = price;
            strcpy(rooms[i].package,rooms[originalroomnumber -1].package);
            rooms[i].is_occupied = true;
            if(bus == true)
            {
                rooms[i].businessdiscount = true;
            }
            rooms[i].customeridinroom = customerid;
            strcpy(rooms[originalroomnumber -1].package,"");
        }
    }
    for(int i = 0;i < 100;i++)
    {
        if(customer[i].number == customerid)//add new room price to customer fees
        {
            customer[i].price = customer[i].price + rooms[roomnumber - 1].price;
        }
    }

    printf("\nRoom Edited Successfully\n");
}

void changepackage(int customerid,int originalroomnumber,int*flag)
{
    int package;
    int price = 0;
    printf("choose package: (1-3)\n1-breakfast only ($5)\n2-half board ($10)\n3-all inclusive ($15)\n"); //user chooses a package
    scanf("%d",&package);

    char pack[20];

    if(package != 1 && package != 2 && package !=3)//if input is invalid
    {
        printf("\nInvalid Input\n");
        *flag = 1;
        return;
    }    
    if(strcmp(rooms[originalroomnumber -1].package , "breakfast only") == 0) //remove original package price
    {
        price = price - 5;
    }
    else if(strcmp(rooms[originalroomnumber -1].package , "half board") == 0)
    {
        price = price - 10;
    }
    else if(strcmp(rooms[originalroomnumber -1].package , "all inclusive") == 0)
    {
        price = price - 15;
    }
    if(package == 1) //add new package price
    {
        strcpy(pack , "breakfast only");
        price = price + 5;
    }
    else if(package == 2)
    {
        strcpy(pack, "half board");
        price = price + 10;
    }
    else if(package == 3)
    {
        strcpy(pack , "all inclusive");
        price = price + 15;
    }

    strcpy(rooms[originalroomnumber - 1].package , pack);
    customer[customerid -1].price = customer[customerid -1].price + price;
    rooms[originalroomnumber -1].price = rooms[originalroomnumber -1].price + price;
}