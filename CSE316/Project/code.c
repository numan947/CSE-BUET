#define true 1
#define false 0
#define F_CPU 1000000UL


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


const int NumObjects = 20 ;


struct Object{
int dir ;
int x ; //row 
int y ; // column
int valid ; // true=Object exist in the matrix ; false = does not exist .
char type ;	//Mothership= 'M' , Player= 'P' , Enemy= 'A' or 'B' , Fire ='F' .
}Objects[22];


//for keep track of score
static int score = 0 ;



//for showing the score
int number[12][9][4]={
	{ // zero ..
		{1,1,1,1},
		{1,0,0,1},
		{1,0,0,1},
		{1,0,0,1},
		{1,0,0,1},
		{1,0,0,1},
		{1,0,0,1},
		{1,0,0,1},	
		{1,1,1,1}
					
	},
	{ // one ..
		{0,0,1,0},
		{0,1,1,0},
		{1,0,1,0},
		{0,0,1,0},
		{0,0,1,0},
		{0,0,1,0},
		{0,0,1,0},
		{0,0,1,0},
		{1,1,1,1}
		
	},
	{ // two ..
		{1,1,1,1},
		{0,0,0,1},
		{0,0,0,1},
		{0,0,0,1},
		{1,1,1,1},
		{1,0,0,0},
		{1,0,0,0},
		{1,0,0,0},
		{1,1,1,1}
		
	},
	{ // three..
		{1,1,1,1},
		{0,0,0,1},
		{0,0,0,1},
		{0,0,0,1},
		{1,1,1,1},
		{0,0,0,1},
		{0,0,0,1},
		{0,0,0,1},
		{1,1,1,1}
		
	},
	{ // four .. 
		{1,0,0,1},
		{1,0,0,1},
		{1,0,0,1},
		{1,0,0,1},
		{1,1,1,1},
		{0,0,0,1},
		{0,0,0,1},
		{0,0,0,1},
		{0,0,0,1}
		
	},
	{ // five ..
		{1,1,1,1},
		{1,0,0,0},
		{1,0,0,0},
		{1,0,0,0},
		{1,1,1,1},
		{0,0,0,1},
		{0,0,0,1},
		{0,0,0,1},
		{1,1,1,1}
		
	},
	{ // six .. 
		{1,1,1,1},
		{1,0,0,0},
		{1,0,0,0},
		{1,0,0,0},
		{1,1,1,1},
		{1,0,0,1},
		{1,0,0,1},
		{1,0,0,1},
		{1,1,1,1}
		
	},
	{ // seven .. 
		{1,1,1,1},
		{0,0,0,1},
		{0,0,0,1},
		{0,0,0,1},
		{0,0,0,1},
		{0,0,0,1},
		{0,0,0,1},
		{0,0,0,1},
		{0,0,0,1}
		
	},
	{ // eight .. 
		{1,1,1,1},
		{1,0,0,1},
		{1,0,0,1},
		{1,0,0,1},
		{1,1,1,1},
		{1,0,0,1},
		{1,0,0,1},
		{1,0,0,1},
		{1,1,1,1}
		
	},
	{ // nine .. 
		{1,1,1,1},
		{1,0,0,1},
		{1,0,0,1},
		{1,0,0,1},
		{1,1,1,1},
		{0,0,0,1},
		{0,0,0,1},
		{0,0,0,1},
		{1,1,1,1}
	}
	
};


//the main gaming matrix
int output[16][16];



void initializeObjects()
{
	Objects[0].type='P';
	Objects[0].valid=true ;
	Objects[0].x=14;
	Objects[0].y=7;
	
	Objects[1].type='F';
	Objects[1].valid=false;
	Objects[1].x=13;
	Objects[1].y=8;
	
	Objects[2].type='M';
	Objects[2].valid=true ;
	Objects[2].x=0;
	Objects[2].y=0;
	Objects[2].dir=0;
	
	Objects[3].type='M';
	Objects[3].valid=true ;
	Objects[3].x=0;
	Objects[3].y=8;
	Objects[3].dir=0;
	
	int k=4;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(i<2)
			{
				Objects[k].type='A';
			}
			else{
				 Objects[k].type='B';
				 
			}
			
			Objects[k].valid=true ;
			Objects[k].x=2+i*2;
			Objects[k].y=2+j*3;
			if(i>=2)Objects[k].x++;
			k++;
		}
	}
	
	
}


void loadObjects(int mat [][16])
{
	int r,c ;
	for(int i=0;i<16;i++)
		for(int j=0;j<16;j++)mat[i][j]=0;
	for(int i=0;i<NumObjects ;i++)
	{
		if(Objects[i].valid==false)continue ;
		r=Objects[i].x ;
		c=Objects[i].y ;
		switch(Objects[i].type){
			case 'P': 
					   mat[r][c+1]= mat[r+1][c]=mat[r+1][c+1]=mat[r+1][c+2]=1;
					   break;
			case 'F':
					   mat[r][c]=1;
					   break;
			case 'M':
			           mat[r][c]=mat[r][c+1]=mat[r][c+2]=mat[r+1][c+1]=1;
					   break;
			case 'A':  
			
					   mat[r][c]=mat[r][c+2]=mat[r+1][c+1]=1;
					   break;
			case 'B': 
					   mat[r][c+1]=mat[r+1][c]=mat[r+1][c+2]=1;
					   break;
					  
		}
	}
}


//initializing default Registers
void initialize()
{
	
	DDRA=0b00001111 ;
	DDRB=0xff ;
	DDRC=0xff ;
	MCUCSR = (1<<JTD);
	MCUCSR = (1<<JTD);
}



//tesing purpose
void showAll()
{
	for(int i=0;i<16;i++)
	{
		PORTA=i;
		PORTB=0xff;
		PORTC=0xff;
			_delay_ms(2);
	}

}


//testing
void showMat2()
{
	for(int i=8;i<16;i++)
	{
		PORTA=i;
		PORTB=0xff;
		PORTC=0;
		_delay_ms(2);
	}
}



//main drawing function
void show0(int mat[][16])
{
	unsigned char pb=0,pc=0;
	for(int i=0;i<16;i++)
	{
		pb=pc=0;
		for(int j=0;j<8;j++)
		{
			pb|= mat[j][i] << j ;
			pc|= mat[j+8][i] << j ;
		}
		PORTB=PORTC=0;
		PORTB=pb;
		PORTC=pc;
		PORTB=pb;
		/*PORTC=0;*/
		//if(i==9)
		//pb=mat[0][i] | mat[1][i] << 1|mat[2][i] << 2|mat[3][i] << 3 | mat[4][i] << 4 | mat[5][i] << 5 | mat[6][i] << 6 |mat[7][i]<<i;
		
		//PORTB=B
		PORTA=i ;
		_delay_ms(2);
		
	}
}



int Mflag=1; //direction for mother ship


void moveMothership()
{
	if(Mflag==1 && Objects[3].y==13 && Objects[2].y==5)Mflag=0;
	else if(Mflag==0 && Objects[2].y==0 && Objects[3].y==8)Mflag=1;
	else if(Objects[3].y>13 || Objects[3].y<8 || Objects[2].y<0 || Objects[2].y>5){
		Objects[2].y=0;
		Objects[3].y=8;
		Mflag=1;
		return ;
	}
	
	if(Mflag)
	{
		Objects[2].y++;
		Objects[3].y++;
		if(Objects[3].y>13){
			Objects[3].y=13;
			Objects[2].y=5;
			Mflag=0;
		}
	}
	else
	{
		Objects[2].y--;
		Objects[3].y--;
		if(Objects[2].y<0){
			Objects[2].y=0 ;
			Objects[3].y=8 ;
			Mflag=1;
		}
	}
	
}



//for moving the normal enemies
int Eflag=0;

void moveEnemy()
{
	int chek=0;
	for(int k=4;k<20;k++)
	{
		if(Objects[k].valid==false)chek++;
		if(Eflag)
			Objects[k].y++;
		else
			Objects[k].y--;
		Objects[k].x++;
		
		if(Objects[k].x>15)Objects[k].valid=false ;
	}
	Eflag^=1 ;
	if(chek==16){
		//initializeObjects();
	}
}



//for moving the bullets
void moveFire()
{
	if(Objects[1].valid){
		Objects[1].x--;
		if(Objects[1].x<0)Objects[1].valid=false ;
	}
}


//check if there's already a bullet in the screen
int isTriggerAvailable(){
		unsigned int result;
		float volt;

		
			//configure-->reference voltage(2)-->ADCH,ADCL mode(1)-->input pin(4)
	    
		ADMUX = 0b01100100;
			
			//configure-->ADC enable(1)-->ADC start conv(1)-->Auto-trigger(1)-->IF(1)-->IE(1)-->ADC clock cycle division factor(3)
		ADCSRA = 0b10000010;
		
				//set ADSC bit of ADCSRA to start conversion
		ADCSRA |= (1<<ADSC);
				

				//conversion is going on, so busy-wait
		while( ADCSRA & (1<<ADSC) )
				;
				

		//conversiond done

		//converted result
		result=0;
		result = ADCL;
		result = (result>>6) | (ADCH<<2);
			

		volt = result*(1.0*5.0/1024.0);
		

		if(volt>3.0){
			//_delay_ms(3000);
			return true;
		}
		else return false ;
}


//trigger bullets
void triggerFire()
{
	if(Objects[1].valid==false && Objects[0].valid==true  && isTriggerAvailable()==true )
	{
		Objects[1].valid=true;
		Objects[1].x=Objects[0].x-1;
		Objects[1].y=Objects[0].y+1;
	}
}


static volatile int pulse = 0;
static volatile int isHigh = 0;



ISR(INT0_vect)
{
	if (isHigh==1)
		{
		    TCCR1B=0; //disable counter
		    pulse=TCNT1;//take the input in global variable
		    TCNT1=0;	//clear the input
			    isHigh=0;	//reset state
		}
	if (isHigh==0)
	{
		TCCR1B|=(1<<CS10); //enable counter
		isHigh=1;		  //set the state to high
	}
}


void movePlayer()
{
	if(Objects[0].valid==false)return ;
	DDRD = 0b11111011;
	GICR =(1<<INT0);
	MCUCR|=(1<<ISC00);
	sei();
	
	int dist =0;
	
	PORTD|=(1<<PIND0);

	_delay_us(15);///triggering the sensor for 15usec

	PORTD &=~(1<<PIND0);

	dist = pulse/58;
	
	
		if(dist<5)dist=5 ;
		else if(dist>30)dist=30;

	
	Objects[0].y=((dist-5.0)/25.0)*13;
	Objects[0].x=14 ;
	
}



int collidRectangle(int x1,int y1,int x2,int y2)
{
	if(x1>x2){
		int t=x1;
		x1=x2;
		x2=t ;
		 
		
	}
	if(y1>y2)
	{
		int t=y1 ;
		y1=y2;
		y2=t ;
	}
	if(x2-x1>=2)return false ;
	if(y2-y1>=3)return false ;
	
	return true ;
}


void collisionDetection()
{
	///collision with Fire ;
	int x=Objects[1].x ;
	int y=Objects[1].y ;
	
	for(int k=2;k<20;k++)
	{
		if(Objects[k].valid==false)continue;
		int kx=Objects[k].x ;
		int ky=Objects[k].y ;
		if(x>=kx && x<=kx+1 && y >=ky && y <= ky+2)
		{
			Objects[k].valid=false ;
			Objects[1].valid=false ;
			
			// updating score ... 
			if(k>3)
			score ++ ;
			else score *=5 ;
		}
		
	}
	
	///collision with Player ;
	 x=Objects[0].x ;
	 y=Objects[0].y ;
	
	for(int k=4;k<20;k++)
	{
		if(Objects[k].valid==false)continue;
		int kx=Objects[k].x ;
		int ky=Objects[k].y ;
		if(collidRectangle(x,y,kx,ky))
		{
			Objects[0].valid=false ;
		}
		
	}
	
}


void loadNumber(int x,int y,int num,int mat[][16])
{
	for(int i=x;i<x+9;i++)
	{
		for(int j=y;j<y+4;j++)mat[i][j]=number[num][i-x][j-y] ;
	}
}


static int baseNum=0 ;


void moveScore()
{
	
}


void loadScore(int mat[][16])
{
	for(int i=0;i<16;i++)
	{
		for(int j=0;j<16;j++)mat[i][j]=0;
	}
	int one,two,three ;
	three=score%10 ;
	score/=10;
	two=score%10;
	score/=10;
	one =score%10;
	loadNumber(3,baseNum,one,mat);
	loadNumber(3,baseNum+5,two,mat);
	loadNumber(3,baseNum+10,three,mat);

}


int main(void)
{
	
	while(1){
	score=0;
	initialize();
	initializeObjects();
	loadObjects(output);
	unsigned long cnt=0;
    while(1)
    {
        //TODO:: Please write your application code 
		if(cnt%60==0)moveEnemy();
		if(cnt%5==0){
			moveMothership();
			

			
			//test ...
			//testPlayer();
			//initializeObjects();
			
		}
		if(cnt%10==0)movePlayer();
		//showAll();
		
		
		
		triggerFire();
		moveFire();
		initialize();
		
		collisionDetection();
		
			loadObjects(output);
		if(Objects[0].valid==false ||(Objects[2].valid==false && Objects[3].valid==false))
			break ;
		show0(output);
		//show0(start);
		//showMat2();
		cnt++;
		
		
    }
	
	loadScore(output);
	while(isTriggerAvailable()==false)
	{
		initialize();
		show0(output);
	}
	
	}
	return 0;
}