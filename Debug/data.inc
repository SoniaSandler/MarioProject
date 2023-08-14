.data

vy dword 0
time dword 0
acl dword 1

scr0 byte "Score:0",0
scrone byte "Score:1",0
scrtwo byte "Score:2",0
scrthree byte "Score:3",0
scrfour byte "Score:4",0
scrfive byte "Score:5",0
scrsix byte "Score:6",0

score dword 0
numH dword 3
jumpUp dword 0

picture byte "mario.bmp",0
pictureScnd byte "mario2.bmp",0

Dmoot STRUCT
	info Img<>				;0-19	
	pos POINT<0,380>		;20-27
	centerP POINT<24,54>	;28-35
	rad dword 28			;36-39
	centerT POINT<>			;40-47
	draw dword 1			;48-51

	drc POINT<0,0>			;52-59
	borderx DWORD 800	
	borderyU DWORD 200	
	borderyD DWORD 476	
	picNum dword 1

Dmoot ENDS

mario Dmoot<>
mario2 Dmoot<>


rekka byte "Mreka2.0.bmp",0

Reka STRUCT

    info Img<>
    xinpic dword 0
    winpic dword 800

Reka ENDS
 
bckrnd Reka<>



coin byte "coin.bmp",0
coins STRUCT
    info Img<>
	pos POINT<400,260>
	centerP POINT<18,18>
	rad dword 20
	centerT POINT<>
	draw dword 1

	drc POINT<-1,0>
coins ENDS
 
coin1 coins<>
coin2 coins<<>,<50,260>,<>,<>,<>,<>,<-3,0>>
coin3 coins<<>,<200,300>,<>,<>,<>,<>,<-5,0>>
coin4 coins<<>,<700,280>,<>,<>,<>,<>,<-4,0>>
coin5 coins<<>,<500,320>,<>,<>,<>,<>,<-2,0>>


enemyR byte "enemies.bmp",0
enemyL byte "enemisL.bmp",0

enemys STRUCT
	info Img<>
	pos POINT<700,432>
	centerP POINT<23,23>
	rad dword 23
	centerT POINT<>

	drc POINT<-2,0>
	picNum dword 2
	border dword 800
	bordery dword ?

enemys ENDS

enemy1 enemys<>
enemy2 enemys<>

lose byte "youlost.bmp",0
won byte "youwon.bmp",0
opening byte "openingScreen.bmp",0

screenPic STRUCT
	
	info Img<>
	pos POINT<150,150>
	show dword 0

screenPic ENDS

youLost screenPic<>
youwon screenPic<>
open screenPic<<>,<0,0>>


heart1 byte "1heart.bmp",0
heart2 byte "2hearts.bmp",0
heart3 byte "3hearts.bmp",0


num0 byte "num0.bmp",0
num1 byte "num1.bmp",0
num2 byte "num2.bmp",0
num3 byte "num3.bmp",0
num4 byte "num4.bmp",0
num5 byte "num5.bmp",0


Count STRUCT
	info Img<>
	pos POINT<0,0>

Count ENDS

oneH Count<>
twoH Count<>
threeH Count<>

nm0 Count<<>,<746,0>>
nm1 Count<<>,<746,0>>
nm2 Count<<>,<746,0>>
nm3 Count<<>,<746,0>>
nm4 Count<<>,<746,0>>
nm5 Count<<>,<746,0>>