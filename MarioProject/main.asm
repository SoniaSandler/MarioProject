include main_funcs.inc

.code
main proc
	invoke init
	invoke borders
	invoke transparent
		
	loopp:
		invoke Sleep,20
        invoke update
		invoke drd_pixelsClear,0    
		invoke bckgrDraw
		invoke openGame

		mov ebx,mario.draw
		cmp ebx,0
		je drawLs

		mov ebx,score
		cmp ebx,5
		jg drawWn

		mov ebx,0
		cmp open.show,ebx
		je openingscreen

		invoke Mariodraw

		invoke control_keyboard	
		invoke move
		invoke coinB, offset coin1
		invoke coinB, offset coin2
		invoke coinB, offset coin3
		invoke coinB, offset coin4
		invoke coinB, offset coin5

		invoke coinMove, offset coin1 
		invoke coinMove, offset coin2
		invoke coinMove, offset coin3 
		invoke coinMove, offset coin4 
		invoke coinMove, offset coin5 
		invoke coinDraw
		
		invoke EMove
		invoke Edraw

		invoke Mchangedrc

		invoke setPoints, offset mario
		invoke setPoints, offset coin1
		invoke setPoints, offset coin2
		invoke setPoints, offset coin3
		invoke setPoints, offset coin4
		invoke setPoints, offset coin5
		invoke setPoints, offset enemy1

		invoke collisionE, offset enemy1, offset mario
		invoke collisionC, offset mario, offset coin1
		invoke collisionC, offset mario, offset coin2
		invoke collisionC, offset mario, offset coin3
		invoke collisionC, offset mario, offset coin4
		invoke collisionC, offset mario, offset coin5

		invoke Hdraw
		invoke Sdraw

	jmp loopp

	ret

	openingscreen:
		invoke drd_imageDraw,offset open.info,open.pos.x,open.pos.y
		jmp loopp

	drawLs:
		invoke yLst
		invoke GetAsyncKeyState,VK_SPACE
   		cmp eax,0
		jne RESTART
		jmp loopp

	drawWn:
		invoke yWon
		invoke GetAsyncKeyState,VK_SPACE
   		cmp eax,0
		jne RESTART
		jmp loopp
	
	RESTART:
		invoke playAgain
		jmp loopp
main endp
end main
