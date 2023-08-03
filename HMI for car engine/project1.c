/*
 * project1.c
 *
 *  Created on: 20 Aug 2022
 *      Author: marwan ashraf abdalnaby
 */
#include <stdio.h>
 /********#Defines*********/

#define WITH_ENGINE_TEMP_CONTROLLER 1
#define ON 1
#define OFF 0

/********Function prototype*********/

void menu3();
void menu1();
void menu2();

/**********Global Variables*********/

int speed = 0;
int temp = 0;
char *AC = NULL;
int engtemp = 0;
char *engtempcon = NULL;
char *engstate = NULL;


/**********Program*********/
void menu1 ()
{
	char input;
	printf("*****Main Menu******\n");
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n\n");
	scanf(" %c",&input);

   switch (input){
   case 'a' :
	   printf("Vehicle engine is on\n");
	   engstate = "ON";
	   menu2();
	   break;

   case'b':
	   printf("Vehicle engine is off\n");
	   engstate = "OFF";
	   menu1(input);
	   break;
   case 'c':
	   printf("Quit the system\n");
	   return;
	   break;
   default:
	   menu1();

   }


}
void menu2()
{
char input2;
printf("*****Sensor Set Menu******\n");
printf("a. Turn off the engine\n");
printf("b. Set the traffic light color\n");
printf("c. Set the room temperature (Temperature Sensor)\n");
printf("d. Set the engine temperature (Engine Temperature Sensor)\n");
scanf (" %c",&input2);



switch (input2)
{
case'a':
	printf("Engine is off");
	menu1();
	break;
case'b':

	menu3(&input2);
	break;
case 'c':
	menu3(&input2);
	break;

case'd':
	menu3(&input2);
	break;


default:
	menu2();

}
}



void menu3(char *input3)
{
	char input4;

	if (*input3 == 'b')
	{
		printf("Set the traffic light to G = 100km/h or O = 30km/h or R = 0km/h \n");
		scanf (" %c",&input4);


		switch (input4)
		{
		case 'G':
			printf("Your Speed is 100km/h\n");
			speed  = 100;

			break;
		case'O':
			printf("Your Speed is 30km/h\n");
			speed  = 30;

			break;
		case'R':
			printf("Your Speed is 0km/h\n");
			speed  = 0;

			break;

		}
	}
	if ( *input3 == 'c')
	{
		printf("Please enter the temperature of the room\n");
		scanf ("%d",&temp);

		if ( temp < 10)
		{
			AC = "ON" ;
			temp = 20;

		}
		else if (temp > 30)
		{
			AC = "ON" ;
			temp = 20;

		}
		else
		{
		    AC = "OFF" ;

		}
	}

#if WITH_ENGINE_TEMP_CONTROLLER == ON
	if  ( *input3 =='d')
	{

		printf("Please enter the temperature of the engine\n");
		scanf ("%d",&engtemp);
		if ( engtemp < 100)
		{
			engtempcon = "ON" ;
			engtemp = 125;

		}
		else if ( engtemp < 150)
		{
			engtempcon = "ON" ;
			engtemp = 125;

		}
		else
		{
			engtempcon = "OFF" ;


		}

	}
#endif
	if (speed == 30)
	{
		AC = "ON";
		temp = temp*(5/4)+1;
		engtempcon = "ON" ;
		engtemp = engtemp*(5/4)+1;
	}



printf("Engine State : %s \n",engstate);
printf("AC state : %s\n",AC);
printf("Vehicle speed : %d km/h \n",speed);
printf("Room Temperature : %d C \n",temp);
printf("Engine Temperature controller state : %s\n",engtempcon);
printf("Engine Temperature is : %d C \n",engtemp);
menu2();
}





int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	menu1();
}

