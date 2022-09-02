#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 8000000UL

/*RS, RW, EN --> pins: 5,6,7 on port A*/
/*set data pins of LCD on port B*/
void LCD_VoidSendCommand (unsigned char Command)
{

	PORTA = 0b0000000; 				//set RS :low , RW: LOW
	PORTB = Command;

	PORTA |= (1<<7); 			//set enable pin to high (5v)
	_delay_ms(2);       			//wait for 2 ms
	PORTA &= ~(1<<7); 		 	//set enable pin to low (0v)
}

void LCD_VoidInit(void)
{
	DDRB = 0b11111111;  				//set data pins as output
	DDRA = 0b11111111; 					//set control pins (RS,RW,E) (PA5,PA6,PA7) as output

	_delay_ms(40);       				//wait for 40ms

	LCD_VoidSendCommand(0b00111000);  	//send the function

	LCD_VoidSendCommand(0b00001100);  	 // send display on/off

	LCD_VoidSendCommand(0b00000001);   //send display clear command


}

void LCD_VoidSendData (unsigned char Data)
{
	PORTA = 0b001000000; 				//set RS :high , RW: LOW
	PORTB = Data;

	PORTA = 0b101000000; 			//set enable pin to high (5v)
	_delay_ms(2);       			//wait for 2ms
	PORTA = 0b001000000; 		 	//set enable pin to low (0v)
}

void LCD_VoidGoToXY(unsigned char x_position , unsigned char y_position)
{
	unsigned char LCDAdress = 0 ;
	if(x_position == 0)
	{
		LCDAdress = y_position;
	}
	else if (x_position ==1)
	{
		LCDAdress = y_position + 0x40;

	}
	else
	{
		LCDAdress = y_position;

	}
	LCDAdress |= (1<<7);
	LCD_VoidSendCommand(LCDAdress);
}
void LCD_voidWriteChar(unsigned char Character)
{
	//RS = 1 (Data)
	PORTA |= (1<<5);
	//RW = 0 (write)
	PORTC &= ~(1<<6);
	//E= 1 (Enable)
	PORTC |= (1<<7);
	//drop the instruction on Data bus
	PORTD = Character;
	//E (falling edge)
	PORTC |= (1<<7);
	_delay_ms(1);
	PORTC &= ~(1<<7);
}

void LCD_voidWriteString(unsigned char *parr, int size)
{
		for(unsigned char i=0; i<size; i++)
		{
			LCD_voidWriteChar(parr[i]);
		}
}

int main()
{

	/*Intialization*/
	/*configure port A as output for 3 leds & motor*/
	//DDRA = 0b11111111;
	/*configure port c,d as output for two 7 sigments*/
	DDRC = 0b11111111;
	DDRD = 0b11111111;

	int arr[10]={
			 0b10010000, //9
			 0b10000000, //8
			 0b11111000, //7
			 0b10000010, //6
			 0b10010010, //5
			 0b10011001, //4
			 0b10110000, //3
			 0b10100100, //2
			 0b11111001, //1
			 0b11000000}; //0

	LCD_voidInit();
				unsigned char arr1[4]= "IMT ";
				unsigned char arr2[6]= "SCHOOL";

				LCD_voidGoToxy(2,6);
				LCD_voidWriteString(arr, 4);
				LCD_voidGoToxy(1,4);
				LCD_voidWriteString(arr2, 6);

	while(1)
	{


		/*first condition*/
		/*red led is on*/
		PORTA = 0b00000001;

		/*two 7 segments are displayed at the same time*/

		/*60*/
		PORTC = 0b0000010;
		PORTD = 0b1000000;
		_delay_ms(1000);

		/*50*/
		for(int i=0; i<10;i++)
		{
			PORTC = 0b10010010;
			PORTD = arr[i];
			_delay_ms(500);
		}

		/*40*/
		for(int i=0; i<10;i++)
		{
			PORTC = 0b10011001;
			PORTD = arr[i];
			_delay_ms(500);
		}

		/*30*/

		for(int i=0; i<10;i++)
		{
			PORTC = 0b10110000;
			PORTD = arr[i];
			_delay_ms(500);
		}

        /*20*/
		for(int i=0; i<10;i++)
		{
			PORTC = 0b10100100;
			PORTD = arr[i];
			_delay_ms(500);
		}

		/*10*/
		for(int i=0; i<10;i++)
		{
			PORTC = 0b11111001;
			PORTD = arr[i];
			_delay_ms(500);
		}

		/*00*/
		for(int i=0; i<10;i++)
		{
			PORTC = 0b11000000;
			PORTD = arr[i];
			_delay_ms(500);
		}

		/*second condition*/
        /*yellow led is on*/

		PORTA = 0b00000010;

		/*num. 10 on two 7 segments*/
		PORTC = 0b11111001;
		PORTD = 0b11000000;

		/*motor rotate in one direction*/

		PORTA |= (1<<3);
		PORTA &= ~(1<<4);

		/*10 sec displayed on two 7 segments*/

		for(int i=0; i<10;i++)
		{

			PORTC = 0b11000000;
			PORTD = arr[i];
			_delay_ms(500);
		}

		/*Third condition*/
		/*green led display*/
		PORTA = 0b00000100;

		/*60*/
		PORTC = 0b0000010;
		PORTD = 0b1000000;
		_delay_ms(1000);

		/*50*/
		for(int i=0; i<10;i++)
		{
			PORTC = 0b10010010;
			PORTD = arr[i];
			_delay_ms(500);
		}

		/*40*/
		for(int i=0; i<10;i++)
		{
			PORTC = 0b10011001;
			PORTD = arr[i];
			_delay_ms(500);
		}

		/*30*/

		for(int i=0; i<10;i++)
		{
			PORTC = 0b10110000;
			PORTD = arr[i];
			_delay_ms(500);
		}

		/*20*/
		for(int i=0; i<10;i++)
		{
			PORTC = 0b10100100;
			PORTD = arr[i];
			_delay_ms(500);
		}

		/*10*/
		for(int i=0; i<10;i++)
		{
			PORTC = 0b11111001;
			PORTD = arr[i];
			_delay_ms(500);
		}

		/*00*/
		for(int i=0; i<10;i++)
		{
			PORTC = 0b11000000;
			PORTD = arr[i];
			_delay_ms(500);
		}

		/*fourth condition*/
		/*yellow led is on*/

		PORTA = 0b00000010;

		/*num. 10 displayed on two 7 segments*/

		PORTC = 0b11111001;
		PORTD = 0b11000000;

		/*motor rotate in another direction*/

		PORTA &= ~(1<<3);
		PORTA |= (1<<4);

		/*10 sec display on two 7 segments*/

		for(int i=0; i<10;i++)
		{

			PORTC = 0b11000000;
			PORTD = arr[i];
			_delay_ms(500);
		}

	}


}
