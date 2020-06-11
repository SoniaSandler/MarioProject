include \masm32\include\masm32rt.inc
include drd.inc
includelib drd.lib
include data.inc
.code

init proc
	invoke drd_init, 800,500,0										;opens window, x=800, y=500
	invoke drd_imageLoadFile,offset rekka,offset bckrnd.info		;moves the file (image) from the hard disc to the ram and puts the information in the obj.info-Img stuct
	invoke drd_imageLoadFile,offset opening,offset open.info
	invoke drd_imageLoadFile,offset picture,offset mario.info
	invoke drd_imageLoadFile,offset pictureScnd,offset mario2.info
	invoke drd_imageLoadFile,offset coin,offset coin1.info
	invoke drd_imageLoadFile,offset coin,offset coin2.info
	invoke drd_imageLoadFile,offset coin,offset coin3.info
	invoke drd_imageLoadFile,offset coin,offset coin4.info
	invoke drd_imageLoadFile,offset coin,offset coin5.info
	invoke drd_imageLoadFile,offset enemyR,offset enemy1.info
	invoke drd_imageLoadFile,offset enemyL,offset enemy2.info
	invoke drd_imageLoadFile,offset lose,offset youLost.info
	invoke drd_imageLoadFile,offset heart1,offset oneH.info
	invoke drd_imageLoadFile,offset heart2,offset twoH.info
	invoke drd_imageLoadFile,offset heart3,offset threeH.info
	invoke drd_imageLoadFile,offset num0,offset nm0.info
	invoke drd_imageLoadFile,offset num1,offset nm1.info
	invoke drd_imageLoadFile,offset num2,offset nm2.info
	invoke drd_imageLoadFile,offset num3,offset nm3.info
	invoke drd_imageLoadFile,offset num4,offset nm4.info
	invoke drd_imageLoadFile,offset num5,offset nm5.info
	invoke drd_imageLoadFile,offset won,offset youwon.info

	ret
init endp

update proc
	invoke drd_processMessages	;the window and it's buttons can be responsive
	invoke drd_flip				;display objects from the buffer
	ret
update endp

bckgrDraw proc
	pusha

	inc bckrnd.xinpic
    dec bckrnd.winpic
	mov ebx,bckrnd.info.iwidth
    cmp bckrnd.xinpic,ebx
    jge Tag_Reset
    Ret_Reset:

           ;pimg:DWORD, dstX:DWORD, dstY:DWORD, srcX:DWORD, srcY:DWORD, srcWidth:DWORD, srcHeight:DWORD;
	invoke drd_imageDrawCrop,offset bckrnd.info,0,0,bckrnd.xinpic,0,bckrnd.info.iwidth,bckrnd.info.iheight
    invoke drd_imageDrawCrop,offset bckrnd.info,bckrnd.winpic,0,0,0,bckrnd.xinpic,bckrnd.info.iheight
	popa
	ret

	Tag_Reset:
        mov bckrnd.xinpic,0
        mov ebx,bckrnd.info.iwidth
        mov bckrnd.winpic,ebx
    jmp Ret_Reset
	popa
	ret
bckgrDraw endp

transparent proc

	invoke drd_imageSetTransparent ,offset mario, 0ffffffffh	;gets the offset of the image and the color in hexa and turns it to transparent 
	invoke drd_imageSetTransparent ,offset coin1, 0ffffffffh
	invoke drd_imageSetTransparent ,offset coin2, 0ffffffffh
	invoke drd_imageSetTransparent ,offset coin3, 0ffffffffh
	invoke drd_imageSetTransparent ,offset coin4, 0ffffffffh
	invoke drd_imageSetTransparent ,offset coin5, 0ffffffffh
	invoke drd_imageSetTransparent ,offset mario2,0ffffffffh
	invoke drd_imageSetTransparent ,offset enemy1, 0FFFF80h
	invoke drd_imageSetTransparent ,offset enemy2, 0FFFF80h
	invoke drd_imageSetTransparent ,offset youLost, 0000000h
	invoke drd_imageSetTransparent ,offset youwon, 0000000h
	invoke drd_imageSetTransparent ,offset youLost, 0ffffffffh
	invoke drd_imageSetTransparent ,offset youwon, 0ffffffffh
	invoke drd_imageSetTransparent ,offset open, 0ffffffffh
	invoke drd_imageSetTransparent ,offset oneH, 0ffffffffh
	invoke drd_imageSetTransparent ,offset twoH, 0ffffffffh
	invoke drd_imageSetTransparent ,offset threeH, 0ffffffffh
	invoke drd_imageSetTransparent ,offset nm0, 0ffffffffh
	invoke drd_imageSetTransparent ,offset nm1, 0ffffffffh
	invoke drd_imageSetTransparent ,offset nm2, 0ffffffffh
	invoke drd_imageSetTransparent ,offset nm3, 0ffffffffh
	invoke drd_imageSetTransparent ,offset nm4, 0ffffffffh
	invoke drd_imageSetTransparent ,offset nm5, 0ffffffffh

transparent endp

openGame proc		;opens the game and sees if the player pressed the enter key in order to start the game
	pusha
		invoke GetAsyncKeyState,VK_RETURN
   		cmp eax,0
		jne SHOW

	popa
	ret

	SHOW:
		mov ebx,1
		mov open.show,ebx
		popa 
		ret
openGame endp

playAgain proc		;if the player loses or wins so it resets all the values to their original value
	pusha
		mov eax,380
		mov mario.pos.y,eax
		
		mov eax,0
		mov mario.pos.x,eax
		mov mario.picNum,eax
		mov mario.drc.x,eax
		mov mario.drc.y,eax
		mov score,eax
		
		mov eax,1
		mov mario.draw,eax
		mov coin1.draw,eax
		mov coin2.draw,eax
		mov coin3.draw,eax
		mov coin4.draw,eax
		mov coin5.draw,eax

		mov eax,3
		mov numH,eax

		mov eax,700
		mov enemy1.pos.x,eax
	popa
	ret
playAgain endp

Mariodraw proc
	pusha

	mov ecx,mario.draw
	cmp ecx,0			;if you can draw mario
	je returning
	mov eax,mario.picNum	;if can, so which one of the two
	cmp eax,1
	je firstPic
	cmp eax,2
	je scndPic

	returning:
	popa
	ret

	firstPic:
		invoke drd_imageDraw,offset mario.info,mario.pos.x,mario.pos.y	;draws the one facing right

	jmp returning

	scndPic:
		invoke drd_imageDraw,offset mario2.info,mario.pos.x,mario.pos.y	;daws the one facing left

	jmp returning
Mariodraw endp

coinMove proc objctAdr1:DWORD	;adds to each coin its speed and direction
	pusha

	mov eax,objctAdr1
	mov ebx,[eax+52]
	add [eax+20],ebx 
	
	popa
	ret
coinMove endp

coinB proc adrObj:dword
	pusha

	mov eax,adrObj
	mov ebx,[eax+20]	;gets the pos.x of the coin
	cmp ebx,-40
	jle chngX	;if it's less then -40 so...
	popa
	ret
		
		chngX:
			mov ebx,950	
			mov [eax+20],ebx	;moving 950 to pos.x
			mov ecx,1			;now able to draw the coin
			mov [eax+48],ecx
		popa
		ret
	 
coinB endp

coinDraw proc	;sees if can draw each coin  
	pusha
	
	mov eax,coin1.draw
	cmp eax,0		;if coin.draw=0, it can't draw the coin and it jumps to the next one
	je scnd
	invoke drd_imageDraw,offset coin1.info,coin1.pos.x,coin1.pos.y
	
	scnd:
	mov eax,coin2.draw
	cmp eax,0
	je thrd
	invoke drd_imageDraw,offset coin2.info,coin2.pos.x,coin2.pos.y
	
	thrd:
	mov eax,coin3.draw
	cmp eax,0
	je forth
	invoke drd_imageDraw,offset coin3.info,coin3.pos.x,coin3.pos.y

	forth:
	mov eax,coin4.draw
	cmp eax,0
	je fifth
	invoke drd_imageDraw,offset coin4.info,coin4.pos.x,coin4.pos.y

	fifth:
	mov eax,coin5.draw
	cmp eax,0
	je returning
	invoke drd_imageDraw,offset coin5.info,coin5.pos.x,coin5.pos.y

	returning:
	popa
	ret
coinDraw endp

move proc
	pusha

	mov ebx,mario.drc.y
	mov ecx,jumpUp		;sees if mario can jump
	cmp ecx,1
	je GO_UP

 popa
 ret	

		GO_UP:
			add ebx,2	;adds to the drc.y +2
			mov mario.drc.y,ebx
			popa
			ret

move endp

borders proc		;sets the border of mario and enemy1
	pusha 

	mov eax,mario.borderx
    sub eax,mario.info.iwidth
    mov mario.borderx,eax		;x border based on image width

	mov eax,mario.borderyD
	sub eax,mario.info.iheight
	mov mario.borderyD,eax            ;y border according to image height

	mov eax,enemy1.border
    sub eax,enemy1.info.iwidth
    mov enemy1.border,eax			;enemy x border based on image width

	popa
	ret
borders endp

Mchangedrc proc
	pusha

	mov ebx,mario.drc.x
	mov ecx,mario.drc.y
	add mario.pos.x,ebx		;adds the speed in x to the x position
	mov eax,mario.borderx
	cmp mario.pos.x,eax		;sees if the pos.x equal or greater than the right x border
    jge TAG_SWITCHX1
	cmp mario.pos.x,0		;sees if the pos.x less or equal to 0
	jle TAG_SWITCHX2
	
	add mario.pos.y,ecx		;adds the y speed to pos.y
	mov eax,mario.borderyU
	cmp mario.pos.y,eax		;sees if pos.y less or equal to the upper y border
	jle TAG_SWITCHYD
	mov eax,mario.borderyD
	cmp mario.pos.y,eax		;sees if pos.y greater or equal to the down y border
	jge TAG_STAYy
	jmp RET_SWITCH

		RET_SWITCH:
		popa
		ret
   
	TAG_SWITCHX1:
		mov ebx,mario.drc.x
		imul ebx,-1		;switches the direction of the speed
		mov mario.drc.x,ebx
		mov ebx,2		; switches the number of picture
		mov mario.picNum,ebx
		mov ebx,mario.borderx	;sets the x position to start
		mov mario.pos.x,ebx
	jmp RET_SWITCH

	TAG_SWITCHX2:
		mov ebx,mario.drc.x
		imul ebx,-1		;switches the direction of the speed
		mov mario.drc.x,ebx
		mov ebx,1		; switches the number of picture
		mov mario.picNum,ebx
		mov ebx,0		;sets the x position to start
		mov mario.pos.x,ebx
	jmp RET_SWITCH

	TAG_SWITCHYD:
		mov ebx,mario.drc.y
		imul ebx,-1		;changes the direction of y
		mov mario.drc.y,ebx
	jmp RET_SWITCH
   
   TAG_STAYy:
		mov ebx,0		;sets the drc.y to 0
		mov mario.drc.y,ebx
	jmp RET_SWITCH

Mchangedrc endp

Edraw proc	

	mov eax,enemy1.picNum
	cmp eax,1
	je firstPic		;if picNum=1
	cmp eax,2
	je scndPic		;if picNum=2
	returning:
	ret

	firstPic:
		invoke drd_imageDraw,offset enemy1.info,enemy1.pos.x,enemy1.pos.y

	jmp returning

	scndPic:
		invoke drd_imageDraw,offset enemy2.info,enemy1.pos.x,enemy1.pos.y


Edraw endp

EMove proc
	pusha

	mov eax,enemy1.drc.x
	add enemy1.pos.x,eax
	mov ebx,enemy1.border
	cmp enemy1.pos.x,ebx	;if pos.x greater or equal to the right x border
	jge cngL 
	cmp enemy1.pos.x,0	;if pos.x greater or equal to the 0 -x border
	jle cngR
	mov ecx,mario.pos.x
	cmp enemy1.pos.x,ecx	;if enemy1.pos.x is less than mario.pos.x
	jl mroR
	jmp mroL
popa
ret

	cngL:
		mov eax,enemy1.drc.x
		imul eax,-1		;switches the direction of the speed
		mov enemy1.drc.x,eax
		mov ecx,2		; switches the number of picture
		mov enemy1.picNum,ecx
	popa
	ret

	cngR:
		mov eax,enemy1.drc.x
		imul eax,-1		;switches the direction of the speed
		mov enemy1.drc.x,eax
		mov ecx,1		; switches the number of picture
		mov enemy1.picNum,ecx
	
	popa
	ret 

	mroR:
		mov edx,enemy1.drc.x
		cmp edx,0		;if the drc.x is less than 0
		jl cngR
	
	popa
	ret

	mroL:
		mov edx,enemy1.drc.x
		cmp edx,0		;if the drc.x is more than 0
		jg cngL
		
	popa
	ret

EMove endp

yLst proc
	pusha
	
	mov eax,numH
	cmp eax,0		;if the player lost all his life (3 hearts)
	je draw

	popa
	ret

	draw:
			invoke drd_imageDraw,offset youLost.info,youLost.pos.x,youLost.pos.y	;shows the losing image
		popa
		ret
yLst endp

yWon proc
	pusha

	mov eax,score
	cmp eax,5		;if the player collected 5 coins
	jle cnt
	mov ebx,950			;moves all the images to pos.x outside the window
	mov mario.pos.x,ebx
	mov coin1.pos.x,ebx
	mov coin2.pos.x,ebx
	mov coin3.pos.x,ebx
	mov coin4.pos.x,ebx
	mov coin5.pos.x,ebx
	mov enemy1.pos.x,ebx
	mov enemy2.pos.x,ebx
	invoke drd_setWindowTitle, offset scrsix		;writes on the window title scrsix
	invoke drd_imageDraw,offset youwon.info,youwon.pos.x,youwon.pos.y	;shows the winning image
	cnt:
	popa
	ret

yWon endp

Hdraw proc
	pusha

	mov eax,numH
	cmp eax,3
	jne two
	invoke drd_imageDraw,offset threeH.info,threeH.pos.x,threeH.pos.y		;if there are 3 hearts (numH)
	mov ebx,1
	mov mario.draw,ebx		;allows to show mario again
	popa
	ret
	
	two:
		cmp eax,2
		jne one
		invoke drd_imageDraw,offset twoH.info,twoH.pos.x,twoH.pos.y 		;if there are 2 hearts (numH)
		mov ebx,1
		mov mario.draw,ebx		;allows to show mario again
		popa
		ret

	one:
		cmp eax,1
		jne dntDraw
		invoke drd_imageDraw,offset oneH.info,oneH.pos.x,oneH.pos.y		;if there are 1 hearts (numH)
		mov ebx,1
		mov mario.draw,ebx		;allows to show mario again
		popa
		ret

	dntDraw:
		popa
		ret

Hdraw endp

Sdraw proc
	pusha

	mov eax,score
	cmp eax,0
	jne one
	invoke drd_imageDraw,offset nm0.info,nm0.pos.x,nm0.pos.y	;if the score equals to 0
	invoke drd_setWindowTitle, offset scr0		;writes on the window title scr0
	jmp cont
	one:
		cmp eax,1
		jne two
		invoke drd_imageDraw,offset nm1.info,nm1.pos.x,nm1.pos.y	;if the score equals to 1
		invoke drd_setWindowTitle, offset scrone		;writes on the window title scrone
		jmp cont

	two:
		cmp eax,2
		jne three
		invoke drd_imageDraw,offset nm2.info,nm2.pos.x,nm2.pos.y	;if the score equals to 2
		invoke drd_setWindowTitle, offset scrtwo		;writes on the window title scrtwo
		jmp cont

	three:
		cmp eax,3
		jne four
		invoke drd_imageDraw,offset nm3.info,nm3.pos.x,nm3.pos.y	;if the score equals to 3
		invoke drd_setWindowTitle, offset scrthree		;writes on the window title scrthree
		jmp cont
	
	four:
		cmp eax,4
		jne five
		invoke drd_imageDraw,offset nm4.info,nm4.pos.x,nm4.pos.y	;if the score equals to 4
		invoke drd_setWindowTitle, offset scrfour		;writes on the window title scrfour
		jmp cont

	five:
		cmp eax,5
		jne cont
		invoke drd_imageDraw,offset nm5.info,nm5.pos.x,nm5.pos.y	;if the score equals to 5
		invoke drd_setWindowTitle, offset scrfive		;writes on the window title scrfive
		jmp cont
		
		cont:
		popa
		ret

Sdraw endp

control_keyboard proc
    pusha

    invoke GetAsyncKeyState,VK_LEFT	
    cmp eax,0
    jne TAG_GO_LEFT		;if the left key has been pressed
    RET_GO_LEFT:
 
    invoke GetAsyncKeyState,VK_RIGHT
    cmp eax,0
    jne TAG_GO_RIGHT	;if the right key has been pressed
    RET_GO_RIGHT:

	invoke GetAsyncKeyState,VK_UP
    cmp eax,0
    jne TAG_GO_UP	;if the upper key has been pressed
    RET_GO_UP:

    popa
    ret
   
    TAG_GO_LEFT:
    mov mario.drc.x,-5	;changes the mario.drc.x to -5
	mov ebx,2	
	mov mario.picNum,ebx	;sets the picNum to 2
    jmp RET_GO_LEFT
 
    TAG_GO_RIGHT:
    mov mario.drc.x,5	;changes the mario.drc.x to 5
	mov ebx,1
	mov mario.picNum,ebx	;sets the picNum to 1
    jmp RET_GO_RIGHT

	TAG_GO_UP:
	mov eax,mario.pos.y
	cmp mario.borderyD,eax	;sees if mario still on the ground
	jge NOTUP
    mov mario.drc.y,-8	;changes the mario.pos.y to 08
	mov jumpUp,1
	RETR:
		mov eax, mario.drc.x
		cmp eax,0
		jne KEEP
		mov mario.drc.x,5		;changes the mario.drc.x to 5
    KEEP:

    popa
    ret

	NOTUP:
		mov jumpUp,0
		popa 
		ret

control_keyboard endp

setPoints proc objctAdr1:DWORD
	pusha

	mov eax,objctAdr1
	mov ebx,[eax+20]	;pos.x
	add ebx,[eax+28]	;centerP.x
	mov ecx,[eax+24]	;pos.y
	add ecx,[eax+32]	;centerP.y
	mov [eax+40],ebx	;centerT.x
	mov [eax+44],ecx	;centerT.y
popa
ret
setPoints endp

collisionC proc objctAdr1:DWORD, objctAdr2:DWORD		;the second might be erased during the game
	pusha
	
	mov eax,objctAdr1
	mov ebx,objctAdr2
	mov ecx,[eax+40]	;x1
	sub ecx,[ebx+40]	;x1-x2
	mov edx,[eax+44]	;y1
	sub edx,[ebx+44]	;y1-y2
	imul ecx,ecx		;dx*dx
	imul edx,edx		;dy*dy
	add ecx,edx			;dx^2+dy^2
	mov eax,[eax+36]	;R1
	add eax,[ebx+36]	;R1+R2
	imul eax,eax		;Rt*Rt
	cmp ecx,eax
	jl DontDraw

	popa
	ret

	DontDraw:
		mov eax,950
		mov [ebx+20],eax	;moves the coin to pos.x outside the window
		mov eax,score
		inc eax		
		mov score,eax	;adds +1 to the score
		popa
		ret

collisionC endp

collisionE proc objctAdr1:DWORD, objctAdr2:DWORD		;the second might be erased during the game
	pusha
	
	mov eax,objctAdr1
	mov ebx,objctAdr2
	mov ecx,[eax+40]	;x1
	sub ecx,[ebx+40]	;x1-x2
	mov edx,[eax+44]	;y1
	sub edx,[ebx+44]	;y1-y2
	imul ecx,ecx		;dx*dx
	imul edx,edx		;dy*dy
	add ecx,edx			;dx^2+dy^2
	mov eax,[eax+36]	;R1
	add eax,[ebx+36]	;R1+R2
	imul eax,eax		;Rt*Rt
	cmp ecx,eax
	jl DontDraw

	popa
	ret

	DontDraw:
		xor eax,eax
		mov [ebx+48],eax	;dont draw mario
		mov eax,numH
		dec eax
		mov numH,eax	;sub -1 from hearts (numH)
		mov ebx,0
		mov mario.pos.x,ebx		;moves 0 to mario.pos.x 
		mov mario.drc.y,ebx		;moves 0 to mario.drc.y 
		mov mario.drc.x,ebx		;moves 0 to mario.drc.x 
		mov ebx,380
		mov mario.pos.y,ebx		;moves 380 to mario.pos.y

	popa
	ret	

collisionE endp