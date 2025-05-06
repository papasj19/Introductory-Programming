/*
	Spencer Johnson
	Programming 1 Project 1
	Submission Date Nov 14

	This program is in correlation with the assignment description 1.1

	It functions as an atm allowing 2 options: deposit and with draw
		Deposit
			This will allow the user to input money into their account. If the information is accepted the program proceeds and adds the amount to the total and print the balances

		Withdraw
			This option allows the user to withdraw from their account. If the information is accepted the program proceeds and displays the number of each bills that is given to the user
	*/

#include <stdio.h>

int main(void) {

	//main user input
	int user_input_main = 0;


	//The total do not touch amount 
	int amount_account = 0;

	//option 1 deposit 
	int amount_dep = 0; 
	int previous_amount = 0; 
	int dep_complete = 0; 
	
	//used for printing the numbers in second option 
	int done = 0; 
	int amount = 0; 
	int amount_withdraw = 0; 
	int number_fifties = 0; 
	int number_twenties = 0; 
	int number_tens = 0; 
	int number_fives = 0; 
	int number_ones = 0; 
	int withdraw_input_accept = 0; 
	int unnacceptable_amount = 0; 

	printf("Welcome to LS ATM!\n\n");


	do{
		printf("1. Deposit | 2. Withdraw | 3. Exit\n");
		printf("Select option: ");
		scanf("%d", &user_input_main);

		//option for deposit
		if(user_input_main == 1){

			do{
				dep_complete = 0; 
				printf("\nEnter amount to deposit: ");
				scanf("%d", &amount_dep);

				//ensuring correct user input
				if(amount_dep > 0 && amount_dep <= 5000){
					dep_complete = 1;

					//calculations
					amount_account = amount_account + amount_dep;
					previous_amount = amount_account - amount_dep;

					//printing the information
					printf("\n%d€ were added successfully to your account balance\n", amount_dep); 
					printf("Previous balance: %d€\n", previous_amount);
					printf("Current balance: %d€\n\n", amount_account);
				}else{
					//wrong user information
					if(amount_dep <= 0 || amount_dep > 5000){
						printf("ERROR: Invalid amount\n");
					}
				}
			//repeat the process until good input is recieved 
			}while(!dep_complete);


		}else{
			//option for withdraw
			if(user_input_main == 2){	
				
				do{
					printf("\nEnter amount to withdraw: ");
					scanf("%d", &amount_withdraw);
					unnacceptable_amount = 0;
					withdraw_input_accept = 0; 
					done = 0;
					amount = 0;
					unnacceptable_amount = (2 * amount_account) / 3;
					//a fake variable i create so I do not modify numbers ive recieved 
					amount = amount_withdraw;
					//clear the variable for use again 
					number_fifties = 0; 
					number_twenties = 0; 
					number_tens = 0; 
					number_fives = 0; 
					number_ones = 0;

					
					//enter here when given good input from the user 
					if(amount_withdraw <= 4000 && amount_withdraw <= unnacceptable_amount && amount_withdraw > 0){
						withdraw_input_accept = 1;
						do{

						//calculation for the number of bills
							//by checking if the amount is able to be subtracted by a bill value and if it is
							//the program will subtract that amount and increase the counter for that bill 
						if(amount >= 50){
							number_fifties++;
							amount = amount - 50;
						}else{ 
							if(amount >= 20 && amount < 50){
								number_twenties++;
								amount = amount - 20;
							}else{
								if(amount >= 10 && amount < 20){
									number_tens++;
									amount = amount - 10;
								}else{
									if(amount >= 5 && amount < 10){
										number_fives++;
										amount = amount - 5;
									}else{
										if(amount >= 1 && amount < 5){
											number_ones++; 
											amount = amount - 1;
										}else{
											if(amount == 0){
												done = 1;
												
											}
										}
									}
								}
							}
						}
					//I keep doing this process until my fake variable is depleated
					} while(!done);

						//printing the process above 
					printf("\nPrevious balance: %d€", amount_account);
					amount_account = amount_account - amount_withdraw;
					printf("\nCurrent balance: %d€", amount_account);
					printf("\nBanknotes handed:\n");
					if(number_fifties > 0){
						printf("\t50€ - %d\n", number_fifties);
					}
					if(number_twenties > 0){
						printf("\t20€ - %d\n", number_twenties);
					}
					if(number_tens > 0){
						printf("\t10€ - %d\n", number_tens);
					}
					if(number_fives > 0){
						printf("\t5€ - %d\n", number_fives);
					}
					if(number_ones > 0){
						printf("\t1€ - %d\n", number_ones);
					}
					printf("\n");
					
					} else {
						//bad user input as described in the statement 
							if(amount_withdraw > 4000 || amount_withdraw > unnacceptable_amount){
								printf("ERROR: You cannot withdraw more than 4000€ or more than 2/3 of the balance in your bank account\n");
							}else{
								if(amount_withdraw <= 0){
									printf("\nERROR: You cannot withdraw a negative or below-zero amount\n");
								}
							}
					}	
					//repeat the process until given good information by user
				}while(!withdraw_input_accept);
			}else{
				//bad user input for the main menu 
				if(user_input_main > 3 || user_input_main < 1){
					printf("ERROR: Invalid option\n\n");
				}
			}	
		}
		//user option 3 to exit the program
	}while(user_input_main != 3);
	printf("\nHave a nice day!");

  return 0;
}