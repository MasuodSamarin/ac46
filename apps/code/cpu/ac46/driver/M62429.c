#include "config.h"

#ifdef SUPPORT_M62429
#include "M62429.h"

/******************************************

D0:0 1ch,;1 2ch
D1:0 Both channels at a time;1 A channel at a time
D2-D6:4db step,max (0x15)0x54
D7-D8:1db step,
D9-D10:11

okvolbak=0x0600;
*******************************************/

 u8 M62429Data[2];

//#define echoval M62429Data[0]
//#define okval M62429Data[1]

//extern  unsigned char menumode;
//u8 okval;
//u8 echoval;
const unsigned char M62429CONST[2][2] =
{
#ifdef gw_911bt_ne  //  vol 最大使用18级。
    {ECHOMAX,0x11},
    {ECHOMAX,0x11},   
#elif defined(ZX_HL601_QGN_K1764_AC4601)||defined(ZX_HL601_QGN_JM4169_AC4601)||defined(ZX_HL601_QGN2_K1764_AC4601)||defined(ZX_HL601_QGN_2314_AC4601)
    {OKVOLMAX,0x0e},
    {ECHOMAX,0x011},
#else
    {ECHOMAX,0x0e},
    {OKVOLMAX,0x11},
#endif

};

void M62429delay(void)
{
    delay(2);
}

void M62429UpDate(u16 updata)
{
    u16 i;
    for (i = 0x0001; i<0x0800; i<<=1)
    {
        M62429_DAT_l();
        M62429_CLK_l();
        M62429delay();
        if (updata & i)
            M62429_DAT_h();
        else
            M62429_DAT_l();

        M62429_CLK_h();
        M62429delay();

    }
    M62429_DAT_h();
    M62429_CLK_l();
}

void SetM62429Data(u8 dir)
{
    u16 mdat,db1temp,db4temp;
    u8 temp_y,tempdir;

    temp_y=dir/3;  // dir =  0->,OKVOL  1-> echo
    tempdir =dir%3;   // 1 ++  2 --
#ifdef support_use_pin1pin2_as_mic_vol    
if(temp_y==0)
temp_y=1;
else if(temp_y==1)
temp_y=0;
#endif
    if (tempdir==1)
    {
        #ifdef TF_168_31AMP
#if	1	
#if MIC_LED_SHOW_MAX==32   
		if(temp_y==0){
		if(mic_temp_vol<MIC_LED_SHOW_MAX)
			mic_temp_vol++;
        if (M62429Data[temp_y]<M62429CONST[temp_y][0]){
			if(mic_temp_vol<=4)M62429Data[temp_y]=0;
			else
            M62429Data[temp_y]++;
			}
		}
#endif

#if MIC_ECHO_LED_SHOW_MAX==32
		if(temp_y==1)
		{
		    if(mic_echo_temp_vol<MIC_ECHO_LED_SHOW_MAX-1)
				mic_echo_temp_vol++;
			if (M62429Data[temp_y]<M62429CONST[temp_y][0])
				{
				if((mic_echo_temp_vol%2==0)/*&&mic_echo_temp_vol<=30*/)
				M62429Data[temp_y]++;
				//else if(mic_echo_temp_vol==31)return;
				//M62429Data[temp_y]++;	
				}
		}
#endif
#endif
		#if 0  //ok vol max 30
        #if MIC_LED_SHOW_MAX==32
		if(temp_y==0){
		if(mic_temp_vol<MIC_LED_SHOW_MAX)
			mic_temp_vol++;
        if (M62429Data[temp_y]<M62429CONST[temp_y][0]){
			if(mic_temp_vol<=1)M62429Data[temp_y]=0;
			else
            M62429Data[temp_y]++;
			}
		}
        #endif

		#if MIC_ECHO_LED_SHOW_MAX==32
		if(temp_y==1)
		{
		    if(mic_echo_temp_vol<MIC_ECHO_LED_SHOW_MAX)
				mic_echo_temp_vol++;
			if (M62429Data[temp_y]<M62429CONST[temp_y][0])
				{
				if((mic_echo_temp_vol%2==0)&&mic_echo_temp_vol<=30)
				M62429Data[temp_y]++;
				else if(mic_echo_temp_vol==31)
				M62429Data[temp_y]++;	
				}
		}
		#endif
		#endif
		#else
        if (M62429Data[temp_y]<M62429CONST[temp_y][0])
            M62429Data[temp_y]++;
		#endif
    }
    else if(tempdir==2)
    {
       #ifdef TF_168_31AMP
       #if MIC_LED_SHOW_MAX==32
	   if(temp_y==0){
	   if(mic_temp_vol>0)
	   	mic_temp_vol--;
		 if (M62429Data[temp_y]>0)
		  {
		  if(mic_temp_vol<=4)M62429Data[temp_y]=0;
		  else
		  M62429Data[temp_y]--;
		  }
	   }
       #endif
	   #if MIC_ECHO_LED_SHOW_MAX==32
	   if(temp_y==1)
	   {   if(mic_echo_temp_vol>0)
	        mic_echo_temp_vol--;
		   if (M62429Data[temp_y]>0)
		   	   {
		   	  // if(mic_echo_temp_vol>30)return;
			  // M62429Data[temp_y]--;
			    if(mic_echo_temp_vol%2==0)
				   M62429Data[temp_y]--;
			   }
	   }
	   #endif
	   #else
        if (M62429Data[temp_y]>0)
            M62429Data[temp_y]--;
	   #endif
    }

    for (temp_y=0; temp_y<2; temp_y++)
    {
#ifdef support_use_pin1pin2_as_mic_vol        
        mdat=0x0602+temp_y;
#else
        mdat=0x0603-temp_y;
#endif
        if (M62429Data[temp_y]>0)
        {
            db4temp=((M62429Data[temp_y]+1)/4+M62429CONST[temp_y][1])*4;
            db1temp=(M62429Data[temp_y]+1)%4;
            mdat+=db4temp;
            mdat|=(db1temp<<7);
        }
        M62429UpDate(mdat);
    }
}

//#define OKVOL_NOMAL		0
//#define OKVOL_DN		1
//#define OKVOL_UP		2
//#define ECHO_NOMAL		3
//#define ECHO_DN			4
//#define ECHO_UP			5


void M62429MenuPro(u8 dir)
{
//	unsigned char tempdir;
//	tempdir = (menumode-4)*3+dir;
//	SetM62429Data(tempdir);
#ifdef DEGBUG_MODE
    //	put_u8hex0(dir);
    // 	puts("=62429 data  \n");
#endif
    SetM62429Data(dir);
}

void M62429Init(void)
{
    M62429_CLK_OUT();
    M62429_CLK_l();
    M62429Data[0]=OKVOL_DEFAULT;
#ifdef SUPPORT_MIC_ECHO_VM	
     vm_read_api(VM_MIC_ECHO,&M62429Data[1]);
	 os_time_dly(1);
	if(M62429Data[1]>ECHOMAX)		
#endif
	
    M62429Data[1]=ECHO_DEFAULT;
    SetM62429Data(OKVOL_NOMAL);
}
void M62429_KEY_PROCESS(u8 menuMode)
{
  switch(menuMode){
     //case menu_m
  }
}
#endif

