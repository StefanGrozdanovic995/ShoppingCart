#include <stdio.h>
#define ITEM_COUNT 12
#define STORAGE_SPACE 20

struct store //define the store structure
{
	char item;
	char* name;
	float price;
	enum messages happy;
};

enum messages // define enumerators
{
	SING = 1,
	NOM = 2,
	GOAL = 4,
	FIGHT = 8,
	DANCE = 16,
	PIN = 32,
	BULLSEYE = 64,
	VROM = 128
};

void printItems(struct store game[], int size) //print out the store items
{
	printf("Welcome to the ARCADE BONANZA\n");
	printf("Please select from one of the following games : \n"); //
	
	for (int i = 0; i < size; i++) // print out the name and price for every item in store
	{
		printf("%c) %-23s $ %8.2f\n", game[i].item, game[i].name, game[i].price);
	}
};

void printArray(int arr[], int size) //function that prints out Arrays, used for debugging
{
	int storNo;
	for (storNo = 0; storNo < size; storNo++)
	{
		printf("%d ", arr[storNo]);
	}
	printf("\n");
};

void printSelection(struct store game[], char selec , int inventory) //function used by storeSelection function
//it is used to print out the item that the user has selected
{
	int selecNo = selec - 'a';// converts typed characters into a selection number: a = 0, b = 1, c = 2 etc.
	//example: hex value of 'b' is 62 and value of 'a' is 61, so charNum = 1 when 'b' is typed

	if (selecNo < inventory && selecNo >= 0)
	{
		//check what enumerator is active and print accordingly
		if ((game[selecNo].happy & SING) != 0)       printf("Sing with me! \n");
		if ((game[selecNo].happy & NOM) != 0)        printf("Nom nom nom nom! \n");
		if ((game[selecNo].happy & GOAL) != 0)       printf("GOAAAAAAL \n");
		if ((game[selecNo].happy & FIGHT) != 0)      printf("Prepare to fight, because... \n");
		if ((game[selecNo].happy & DANCE) != 0)      printf("Lets go dance, because... \n");
		if ((game[selecNo].happy & PIN) != 0)        printf("Pin Pin Pin \n");
		if ((game[selecNo].happy & BULLSEYE) != 0)   printf("Bullseye \n");
		if ((game[selecNo].happy & VROM) != 0)       printf("Lets go dance, because... \n");

		printf("You have chosen: %s \n", game[selecNo].name); //print name of chosen game

	}//check whether the typed character is between 'a' and 'l'
		
	else
		printf("Choose a game from the list\n"); //inform user that an invalid character has been typed
};

void storeSelection(struct store game[], int arr[]) //store typed character in an array in a number format
{
	char selec, prevSelec = ' ';
	int storageNo = 0;
	int charNum;
	
	while (1) //this function will read in all of the typed caracters and only consider the character that 
	           //was typed before '\n' character
	{

		selec = getchar();//function takes in all of the typed characters
		
		if (selec == '\n')
		{
			if (prevSelec == '\n') // is type '\n' characters are typed than break the loop
			{
				break;
			}
			else if (prevSelec == ' ') //if storeSelection function is called and no characters were typed, prompt the user to type in a character. (*Protection from proceedCheckout function*)
			{
				selec = getchar();
			}
			else 
			{
				printSelection(game, prevSelec, ITEM_COUNT); //function takes in character that is typed before '\n', and calls printSelection function
				charNum = prevSelec - '`'; // convert character into a number...
				//example: hex value of 'a' is 61 and value of '`' is 60, so charNum = 1 when 'a' is typed
				
				if (charNum <= ITEM_COUNT && charNum > 0) //if number is between 1 and 12 than store it in array
				{
					arr[storageNo] = charNum;
					storageNo++;
				}
				else
				{
					printf("Type any character from 'a' to 'l'\n");
				}
				//For DEBUGGING purposes. Print the array to see if the item has been stored properly
				//printArray(arr,STORAGE_SPACE);	
			}
		}
		prevSelec = selec;
	}
	return arr;
};

void swap(int* pA, int* pB) //function swaps the position of two integers
{
	int temp;

	temp = *pA;
	*pA = *pB;
	*pB = temp;
}

int sortPass(int arr[], int size) //function compares two integers and swaps them if the predecessor is greater than successor
{
	int storNo;
	int swapped = 0; // check whether a swap has been done

	for (storNo = 0; storNo < (size - 1); storNo++)
		if (arr[storNo] > arr[storNo + 1])
		{
			swap(&arr[storNo], &arr[storNo + 1]);
			swapped = 1; // if no swaps have been done the function returns 1
		}
	return swapped;
};

void printReceipt(struct store game[], int arr[], int size) //Function prints out items selected, quantity, prices of items 
                                                            //and the total price of all selected items
{
	int storNo;
	float totalItemPrice = 0; //total price of same items selected = item * quantity
	float totalPrice = 0;     //overall price of all items selected
	int qty = 0;
	int choice;
	
	for (storNo = 0; storNo < size; storNo++) //do a bubble sort on selection storage array
	{
		if (sortPass(arr, size) == 0) break; //if no swaps have been done and sortPass returns 1 then breaks the For Loop
	}
	
	//For DEBUGGING purposes -> prints array after it has been sorted. 
	//printArray(arr,size); 

    //------ PRINT THE RECEIPT ------//

	printf("\nItem:                  Qty:      Price:      Total:\n"); 

	for (storNo = 0; storNo < size; storNo++) 
	{
		if (arr[storNo] != 0)         //ignore all numbers that are zero in the array 
		{
			choice = arr[storNo] - 1; //In the storage array character 'a' is stored as 1 and 'l'  as 12,
			                          //while in the store strucure item 'a' is stored as 0 and 'l' as 11.

			if (arr[storNo] == arr[storNo + 1]) //count the number of same items selected
			{
				qty++;                          // increment quantity count

				totalPrice = totalPrice + game[choice].price; //add the item price to the total price
			}
			else
			{
				qty++;       // increment quantity count
				totalItemPrice = game[choice].price * qty; //multiply the price of item with its' quantity
				printf("%-24s %2i   $%8.2f   $%8.2f  \n", game[choice].name, qty, game[choice].price, totalItemPrice);
				qty = 0;     //restore quantity counter ot 0
				totalPrice = totalPrice + game[choice].price; //add the item price to the total price
			}
		}
	};
	printf("                                 Total:   $%8.2f   ", totalPrice);
};

int proceedCheckout(struct store game[],int arr[], int size) //function asks the user to type 'Y' if they want to proceed to Checkout, or type 'N' if they want to select items again
{
	printf("\n\nIs this correct? Proceed to Checkout (Y) or Cancel (N)?\n");
	while (1)
	{
		char selec = getchar();

		if (selec == 'N') // if 'N' is typed than reset all elements of storage array to 0
		{
			for (int i = 0; i < size; i++)
			{
				arr[i] = 0;
			}
			return 0;
		}
		else if (selec == 'Y') //if 'Y' is typed than print purchase confirmation message and end program
		{
			printf("\nThe order is now processed. Thank you for shopping with us\n");
			return 1;
		}
		else if(selec != '\n') // If other characters are typed prompt user to only type 'Y' or 'N'
		                       // this condition has been typed to prevent double printing of text
		{
			printf("Type (Y) or (N) \n");
		}
	};
};

int main()
{   //define the store structure
	struct store item[ITEM_COUNT] = { { 'a', "Pinball"               ,  5600.34, PIN },
									  { 'b', "Formula 1"             ,  4410.56, VROM},
									  { 'c', "Jukebox"               ,   890.65, SING },
									  { 'd', "Air Hockey"            ,  5670.88, GOAL },
									  { 'e', "Foosball Table"        ,   960.32, GOAL },
									  { 'f', "Darts"                 ,    80.37, BULLSEYE},
									  { 'g', "Pac-Man"               ,  4330.68, NOM },
									  { 'h', "Space Invaders"        ,  3560.92, FIGHT},
									  { 'i', "Arcade Shooter"        ,  6430.75, FIGHT},
									  { 'j', "Punch Machine"         ,   760.12, FIGHT},
									  { 'k', "Street Fighter"        ,  5780.49, FIGHT },
									  { 'l', "Dance Dance Revolution", 10890.22, DANCE }
	};

	printItems(item, ITEM_COUNT); //print the items that are in the structure

	int selec[STORAGE_SPACE] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }; //initialise storage space to all 0
	
    storeSelection(item, selec); //when user selects an item store the typed character as a number in the selec[] array
	 	
	printReceipt(item, selec, STORAGE_SPACE);// when user finishes item selection by typing in double '\n' print the receipt

	while (proceedCheckout(item, selec, STORAGE_SPACE) != 1) // if 'Y' is typed than proceedCheckout function returns 1 and that breaks the loop
		                                                     // if 'N' is typed than program resets selec[] array and repeats two functions
	{
		printf("Select items again:\n");
		storeSelection(item, selec);
		printReceipt(item, selec, STORAGE_SPACE);	
	}
	
};