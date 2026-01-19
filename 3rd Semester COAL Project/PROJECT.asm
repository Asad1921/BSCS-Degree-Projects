INCLUDE C:\irvine\Irvine32.inc
INCLUDE C:\irvine\Macros.inc

.data

introMsg    		BYTE "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",13,10
            BYTE "                                                                                ",13,10
            BYTE "                             XXXXX   X   X   XXXXX   X   X   XXXXX   XXXXX                           ",13,10
            BYTE "                             X       XX  X   X   X   X  X    X       X                               ",13,10
            BYTE "                             XXXXX   X X X   XXXXX   XXX     XXXX    XXXXX                           ",13,10
            BYTE "                                 X   X  XX   X   X   X  X    X           X                           ",13,10
            BYTE "                             XXXXX   X   X   X   X   X   X   XXXXX   XXXXX                           ",13,10
            BYTE "                                                                                ",13,10
            BYTE "                                          XXXXX   X   X   XXXX                                   ",13,10
            BYTE "                                          X   X   XX  X   X   X                                  ",13,10
            BYTE "                                          XXXXX   X X X   X   X                                   ",13,10
            BYTE "                                          X   X   X  XX   X   X                                    ",13,10
            BYTE "                                          X   X   X   X   XXXX                                      ",13,10
            BYTE "                                                                                ",13,10
            BYTE "                          X       XXXXX   XXXX    XXXX    XXXXX   XXXX    XXXXX                   ",13,10
            BYTE "                          X       X   X   X   X   X   X   X       X   X   X                       ",13,10
            BYTE "                          X       XXXXX   X   X   X   X   XXXX    XXXX    XXXXX                   ",13,10
            BYTE "                          X       X   X   X   X   X   X   X       X  X        X                   ",13,10
            BYTE "                          XXXXX   X   X   XXXX    XXXX    XXXXX   X   X   XXXXX                   ",13,10
            BYTE "                                                                                ",13,10
            BYTE "                                      WELCOME TO SNAKES AND LADDERS!                             ",13,10
            BYTE "                                                                                ",13,10
            BYTE "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",13,10,13,10,0
dicePromptMsg       BYTE "ROLL THE DICE FOR",0
diceRollingMsg      BYTE "ROLLING DICE",0
dotChar             BYTE ".",0
diceResultMsg       BYTE "Dice roll=",0
ladderMsg           BYTE "LADDER CLIMB!!",0
snakeMsg            BYTE "X SNAKE X",0
congratsMsg         BYTE "CONGRATULATIONS!!!! ",0
winGameMsg          BYTE " WON THE GAME!!!",0
positionMsg         BYTE "Current position=",0
playerLabelMsg      BYTE "Player:",0
colorChoiceMsg      BYTE "1:RED 2:BLUE",0
playerNameMsg       BYTE "PLAYER ",0
playerNameMsg2      BYTE " (",0
playerPosMsg        BYTE ") POSITION:",0
shakeMsg            BYTE "Shake the dice=",0
namePrompt1         BYTE "Enter Player 1 name: ",0
namePrompt2         BYTE "Enter Player 2 name: ",0
spaceChar           BYTE "  ",0

player1Name         BYTE 50 DUP(0)
player2Name         BYTE 50 DUP(0)
player1NameLen      DWORD 0
player2NameLen      DWORD 0
player1Position     DWORD 0
player2Position     DWORD 0
player1Started      DWORD 0
player2Started      DWORD 0
player1DiceHistory  DWORD 10 DUP(0)
player2DiceHistory  DWORD 10 DUP(0)
historyCount1       DWORD 0
historyCount2       DWORD 0
currentDiceValue    DWORD 0
tempValue           DWORD 0

topBorderLeft       BYTE 201,205,205,205,205,205,205,0
topBorderMid        BYTE 203,205,205,205,205,205,205,0
topBorderRight      BYTE 187,13,10,0
midBorderLeft       BYTE 204,205,205,205,205,205,205,0
midBorderMid        BYTE 206,205,205,205,205,205,205,0
midBorderRight      BYTE 185,13,10,0
botBorderLeft       BYTE 200,205,205,205,205,205,205,0
botBorderMid        BYTE 202,205,205,205,205,205,205,0
botBorderRight      BYTE 188,13,10,0
vertChar            BYTE 186,0
boxSpaces           BYTE "      ",0

snake1Label         BYTE "S1",0
snake2Label         BYTE "S2",0
snake3Label         BYTE "S3",0
snake4Label         BYTE "S4",0
snake5Label         BYTE "S5",0
snake6Label         BYTE "S6",0
snake7Label         BYTE "S7",0
ladder1Label        BYTE "L1",0
ladder2Label        BYTE "L2",0
ladder3Label        BYTE "L3",0
ladder4Label        BYTE "L4",0
ladder5Label        BYTE "L5",0
ladder6Label        BYTE "L6",0
Win                 BYTE "WIN",0

infoBoxTitleMsg     BYTE "===== GAME INFO =====",0
snakesTitleMsg      BYTE "SNAKES:",0
laddersTitleMsg     BYTE "LADDERS:",0
arrowChar           BYTE " --------> ",0
snakeLabelMsg       BYTE "Snake: ",0
ladderLabelMsg      BYTE "Ladder: ",0
statusBoxTopMsg     BYTE 218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196
                    BYTE 196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196
                    BYTE 196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196
                    BYTE 196,196,196,196,196,196,196,196,196,196,191,0
statusBoxBotMsg     BYTE 192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196
                    BYTE 196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196
                    BYTE 196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196
                    BYTE 196,196,196,196,196,196,196,196,196,196,217,0
statusBoxSideMsg    BYTE 179,0
statusTitleMsg      BYTE " PLAYER STATUS ",0
diceHistoryMsg      BYTE "Dice History: ",0
commaMsg            BYTE ", ",0
boxColor1     BYTE 10101111b  
boxColor2     BYTE 10101111b 
digitColor   BYTE 00001111b  

.code
main PROC
    call clrscr
    mov edx, OFFSET introMsg
    call WriteString
    call crlf
    call crlf

    mov edx, OFFSET namePrompt1
    call WriteString
    mov edx, OFFSET player1Name
    mov ecx, 50
    call ReadString
    mov player1NameLen, eax
    call crlf

    mov edx, OFFSET namePrompt2
    call WriteString
    mov edx, OFFSET player2Name
    mov ecx, 50
    call ReadString
    mov player2NameLen, eax
    call crlf
    call crlf

    mov edx, OFFSET dicePromptMsg
    call WriteString
    call ReadChar
    call crlf
    call clrscr

    call DisplayGameBoard
    call DisplayInfoBox
    mov player1Position, 0
    mov player2Position, 0
    mov player1Started, 0
    mov player2Started, 0
    mov historyCount1, 0
    mov historyCount2, 0
    call crlf

    call DisplayGameBoard
    call DisplayInfoBox
    call DisplayStatusBox
    mov dh, 35
    mov dl, 0
    call Gotoxy
    call GameMainLoop
    exit
main ENDP

DisplayGameBoard PROC
    mov dh, 0
    mov dl, 0
    call Gotoxy
    mov edx, OFFSET topBorderLeft
    call WriteString
    mov ecx, 9
top_loop:
    mov edx, OFFSET topBorderMid
    call WriteString
    loop top_loop
    mov edx, OFFSET topBorderRight
    call WriteString
    
    mov ebx, 10         
    mov edi, 0        
row_loop:
    push ebx
    mov ecx, 2       
empty_lines_loop:
    push ecx
    mov edx, OFFSET vertChar
    call WriteString
    
    mov eax, edi       
    and eax, 1          
    mov esi, eax      
    
    mov ecx, 10       
cols_loop:
    .IF esi == 1
        mov al, boxColor2
    .ELSE
        mov al, boxColor1
    .ENDIF
    call SetTextColor
    
    mov edx, OFFSET boxSpaces
    call WriteString
    
    mov al, 00001111b
    call SetTextColor
    
    mov edx, OFFSET vertChar
    call WriteString
    
    xor esi, 1
    
    loop cols_loop
    
    call crlf
    pop ecx
    loop empty_lines_loop
    
    pop ebx
    .IF ebx == 1
        mov edx, OFFSET botBorderLeft
        call WriteString
        mov ecx, 9
    bot_loop:
        mov edx, OFFSET botBorderMid
        call WriteString
        loop bot_loop
        mov edx, OFFSET botBorderRight
        call WriteString
    .ELSE
        mov edx, OFFSET midBorderLeft
        call WriteString
        mov ecx, 9
    mid_loop:
        mov edx, OFFSET midBorderMid
        call WriteString
        loop mid_loop
        mov edx, OFFSET midBorderRight
        call WriteString
    .ENDIF

continue_row:
    inc edi            
    dec ebx
    .IF ebx != 0
        jmp row_loop
    .ENDIF
    
    call DisplayBoardNumbers
    call DisplayLadders
    call DisplaySnakes
    call DisplayPlayerPositions
    
    mov al, 00001111b
    call SetTextColor
    
    ret
DisplayGameBoard ENDP

DisplayBoardNumbers PROC
    mov edx, 0
    mov dl, 3
    mov dh, 1
    call Gotoxy
    
    mov eax, 100
    mov tempValue, eax
    mov ecx, 10          
    mov edi, 0         
    
nums_row:
    push ecx
    mov ebx, ecx        
    
    mov esi, edi       
    and esi, 1         
    
    mov ecx, 10        
    
nums_col:
    .IF esi == 1
        mov al, boxColor2
    .ELSE
        mov al, boxColor1
    .ENDIF
    call SetTextColor
    
    mov eax, tempValue
    call WriteDec
    
    mov al, 00001111b
    call SetTextColor
    
    dec tempValue
    
    .IF bl & 1      
        sub dl, 7           
    .ELSE
        add dl, 7        
    .ENDIF
    
    call Gotoxy
    
    xor esi, 1
    
    loop nums_col
    
    add dh, 3
    
    .IF bl & 1          
        mov dl, 3          
    .ELSE
        sub dl, 7           
    .ENDIF
    
    call Gotoxy
    
    xor edi, 1
    
    pop ecx
    dec ecx
    .IF ecx != 0
        jmp nums_row
    .ENDIF
    
    mov al, 00001111b
    call SetTextColor
    
    ret
DisplayBoardNumbers ENDP

DisplayPlayerPositions PROC
    .IF player1Position != 0
        mov eax, player1Position
        dec eax
        mov bl, 10
        div bl
        mov dh, 9
        sub dh, al
        .IF al & 1
            mov dl, 9
            sub dl, ah
        .ELSE
            mov dl, ah
        .ENDIF
        mov al, dl
        mov cl, 7
        mul cl
        add al, 2
        mov dl, al
        mov al, dh
        mov cl, 3
        mul cl
        add al, 2
        mov dh, al
        call Gotoxy
        mov al, 01000000b
        call SetTextColor
        mov al, ' '
        call WriteChar
        mov al, 'P'
        call WriteChar
        mov al, '1'
        call WriteChar
        mov al, ' '
        call WriteChar
        mov al, 00001111b
        call SetTextColor
    .ENDIF
    
    .IF player2Position != 0
        mov eax, player2Position
        dec eax
        mov bl, 10
        div bl
        mov dh, 9
        sub dh, al
        .IF al & 1
            mov dl, 9
            sub dl, ah
        .ELSE
            mov dl, ah
        .ENDIF
        mov al, dl
        mov cl, 7
        mul cl
        add al, 2
        mov dl, al
        mov al, dh
        mov cl, 3
        mul cl
        add al, 2
        mov dh, al
        call Gotoxy
        mov al, 01100000b
        call SetTextColor
        mov al, ' '          
        call WriteChar
        mov al, 'P'
        call WriteChar
        mov al, '2'
        call WriteChar
        mov al, ' '          
        call WriteChar
        mov al, 00001111b
        call SetTextColor
    .ENDIF
    
    ret
DisplayPlayerPositions ENDP

GameMainLoop PROC
game_turn_loop:
    mov ebx, 1  
    
    mov dh, 38
    mov dl, 0
    call Gotoxy
    
    mov ecx, 80
    mov al, ' '
clear_p1_line:
    call WriteChar
    loop clear_p1_line
    
    mov dh, 38
    mov dl, 0
    call Gotoxy
    
    mov al, 01000000b
    call SetTextColor
    mov al, 'P'
    call WriteChar
    mov al, '1'
    call WriteChar
    mov al, ' '
    call WriteChar
    mov al, 00001111b
    call SetTextColor
    mov edx, OFFSET player1Name
    call WriteString
    mov edx, OFFSET playerPosMsg
    call WriteString
    mov eax, player1Position
    call WriteDec
    mov al, ' '
    call WriteChar
    mov edx, OFFSET dicePromptMsg
    call WriteString
    
    call ReadChar
    
    call crlf
    mov edx, OFFSET diceRollingMsg
    call WriteString
    mov ecx, 3
anim1:
    mov eax, 200
    call Delay
    mov edx, OFFSET dotChar
    call WriteString
    loop anim1
    call crlf
    
    call Randomize
    mov eax, 6
    call RandomRange
    inc eax
    mov currentDiceValue, eax
    
    mov edx, OFFSET diceResultMsg
    call WriteString
    mov eax, currentDiceValue
    call WriteDec
    
    call crlf
    mov edx, OFFSET dicePromptMsg
    call WriteString
    call ReadChar                  
    call crlf
    
    mov eax, currentDiceValue
    mov ecx, 1
    call AddToHistory
    
    mov eax, currentDiceValue
    call ProcessPlayerMove_P1
    
    mov eax, player1Position
    .IF eax == 100
        call clrscr
        call DisplayGameBoard
        call DisplayInfoBox
        call DisplayStatusBox
        mov al, 11111100b
        call SetTextColor
        mov dh, 38
        mov dl, 0
        call Gotoxy
        mov edx, OFFSET congratsMsg
        call WriteString
        mov edx, OFFSET player1Name
        call WriteString
        mov edx, OFFSET winGameMsg
        call WriteString
        mov al, 00001111b
        call SetTextColor
        call crlf
        call crlf
        mov edx, OFFSET dicePromptMsg
        call WriteString
        call ReadChar
        ret
    .ENDIF
    
     mov dh, 40
    mov dl, 0
    call Gotoxy
    mov ecx, 80
    mov al, ' '
clear_result1:
    call WriteChar
    loop clear_result1
    
    mov eax, 500
    call Delay
    
     call clrscr
    call DisplayGameBoard
    call DisplayInfoBox
    call DisplayStatusBox
    
    mov ebx, 2   
    
     mov dh, 38
    mov dl, 0
    call Gotoxy
    
    mov ecx, 80
    mov al, ' '
clear_p2_line:
    call WriteChar
    loop clear_p2_line
    
    mov dh, 38
    mov dl, 0
    call Gotoxy
    
    mov al, 01100000b
    call SetTextColor
    mov al, 'P'
    call WriteChar
    mov al, '2'
    call WriteChar
    mov al, ' '
    call WriteChar
    mov al, 00001111b
    call SetTextColor
    mov edx, OFFSET player2Name
    call WriteString
    mov edx, OFFSET playerPosMsg
    call WriteString
    mov eax, player2Position
    call WriteDec
    mov al, ' '
    call WriteChar
    mov edx, OFFSET dicePromptMsg
    call WriteString
    
    call ReadChar
    
    call crlf
    mov edx, OFFSET diceRollingMsg
    call WriteString
    mov ecx, 3
anim2:
    mov eax, 200
    call Delay
    mov edx, OFFSET dotChar
    call WriteString
    loop anim2
    call crlf
    
    call Randomize
    mov eax, 6
    call RandomRange
    inc eax
    mov currentDiceValue, eax
    
    mov edx, OFFSET diceResultMsg
    call WriteString
    mov eax, currentDiceValue
    call WriteDec
    
    call crlf
    mov edx, OFFSET dicePromptMsg
    call WriteString
    call ReadChar                 
    
    mov eax, currentDiceValue
    mov ecx, 2
    call AddToHistory
    
    mov eax, currentDiceValue
    call ProcessPlayerMove_P2
    
    mov eax, player2Position
    .IF eax == 100
        call clrscr
        call DisplayGameBoard
        call DisplayInfoBox
        call DisplayStatusBox
        mov dh, 38
        mov dl, 0
        call Gotoxy
        mov edx, OFFSET congratsMsg
        call WriteString
        mov edx, OFFSET player2Name
        call WriteString
        mov edx, OFFSET winGameMsg
        call WriteString
        call crlf
        call crlf
        mov edx, OFFSET dicePromptMsg
        call WriteString
        call ReadChar
        ret
    .ENDIF
    
    mov dh, 40
    mov dl, 0
    call Gotoxy
    mov ecx, 80
    mov al, ' '
clear_result2:
    call WriteChar
    loop clear_result2
    
    mov eax, 500
    call Delay
    
    call clrscr
    call DisplayGameBoard
    call DisplayInfoBox
    call DisplayStatusBox
    
    jmp game_turn_loop
    
GameMainLoop ENDP

ProcessPlayerMove_P1 PROC
    .IF player1Started == 0
        .IF eax == 6
            mov player1Started, 1
            mov player1Position, 1
            mov edx, OFFSET ladderMsg
            call WriteString
            call crlf
        .ELSE
            mov edx, OFFSET shakeMsg
            call WriteString
            call crlf
        .ENDIF
    .ELSE
        add player1Position, eax
        .IF player1Position <= 100
            .IF player1Position == 100
            .ELSE
                call CheckLadderP1
                call CheckSnakeP1
            .ENDIF
        .ELSE
            sub player1Position, eax
        .ENDIF
    .ENDIF
    ret
ProcessPlayerMove_P1 ENDP

ProcessPlayerMove_P2 PROC
    .IF player2Started == 0
        .IF eax == 6
            mov player2Started, 1
            mov player2Position, 1
            mov edx, OFFSET ladderMsg
            call WriteString
            call crlf
        .ELSE
            mov edx, OFFSET shakeMsg
            call WriteString
            call crlf
        .ENDIF
    .ELSE
        add player2Position, eax
        .IF player2Position <= 100
            .IF player2Position == 100
            .ELSE
                call CheckLadderP2
                call CheckSnakeP2
            .ENDIF
        .ELSE
            sub player2Position, eax
        .ENDIF
    .ENDIF
    ret
ProcessPlayerMove_P2 ENDP

CheckLadderP1 PROC
    mov eax, player1Position
    .IF eax == 2
        mov player1Position, 23
        mov edx, OFFSET ladderMsg
        call WriteString
        call crlf
    .ELSEIF eax == 6
        mov player1Position, 45
        mov edx, OFFSET ladderMsg
        call WriteString
        call crlf
    .ELSEIF eax == 20
        mov player1Position, 59
        mov edx, OFFSET ladderMsg
        call WriteString
        call crlf
    .ELSEIF eax == 52
        mov player1Position, 72
        mov edx, OFFSET ladderMsg
        call WriteString
        call crlf
    .ELSEIF eax == 57
        mov player1Position, 96
        mov edx, OFFSET ladderMsg
        call WriteString
        call crlf
    .ELSEIF eax == 71
        mov player1Position, 92
        mov edx, OFFSET ladderMsg
        call WriteString
        call crlf
    .ENDIF
    ret
CheckLadderP1 ENDP

CheckLadderP2 PROC
    mov eax, player2Position
    .IF eax == 2
        mov player2Position, 23
        mov edx, OFFSET ladderMsg
        call WriteString
        call crlf
    .ELSEIF eax == 6
        mov player2Position, 45
        mov edx, OFFSET ladderMsg
        call WriteString
        call crlf
    .ELSEIF eax == 20
        mov player2Position, 59
        mov edx, OFFSET ladderMsg
        call WriteString
        call crlf
    .ELSEIF eax == 52
        mov player2Position, 72
        mov edx, OFFSET ladderMsg
        call WriteString
        call crlf
    .ELSEIF eax == 57
        mov player2Position, 96
        mov edx, OFFSET ladderMsg
        call WriteString
        call crlf
    .ELSEIF eax == 71
        mov player2Position, 92
        mov edx, OFFSET ladderMsg
        call WriteString
        call crlf
    .ENDIF
    ret
CheckLadderP2 ENDP

CheckSnakeP1 PROC
    mov eax, player1Position
    .IF eax == 25
        mov player1Position, 5
        mov edx, OFFSET snakeMsg
        call WriteString
        call crlf
    .ELSEIF eax == 34
        mov player1Position, 1
        mov edx, OFFSET snakeMsg
        call WriteString
        call crlf
    .ELSEIF eax == 47
        mov player1Position, 19
        mov edx, OFFSET snakeMsg
        call WriteString
        call crlf
    .ELSEIF eax == 65
        mov player1Position, 52
        mov edx, OFFSET snakeMsg
        call WriteString
        call crlf
    .ELSEIF eax == 87
        mov player1Position, 57
        mov edx, OFFSET snakeMsg
        call WriteString
        call crlf
    .ELSEIF eax == 91
        mov player1Position, 61
        mov edx, OFFSET snakeMsg
        call WriteString
        call crlf
    .ELSEIF eax == 99
        mov player1Position, 69
        mov edx, OFFSET snakeMsg
        call WriteString
        call crlf
    .ENDIF
    ret
CheckSnakeP1 ENDP

CheckSnakeP2 PROC
    mov eax, player2Position
    .IF eax == 25
        mov player2Position, 5
        mov edx, OFFSET snakeMsg
        call WriteString
        call crlf
    .ELSEIF eax == 34
        mov player2Position, 1
        mov edx, OFFSET snakeMsg
        call WriteString
        call crlf
    .ELSEIF eax == 47
        mov player2Position, 19
        mov edx, OFFSET snakeMsg
        call WriteString
        call crlf
    .ELSEIF eax == 65
        mov player2Position, 52
        mov edx, OFFSET snakeMsg
        call WriteString
        call crlf
    .ELSEIF eax == 87
        mov player2Position, 57
        mov edx, OFFSET snakeMsg
        call WriteString
        call crlf
    .ELSEIF eax == 91
        mov player2Position, 61
        mov edx, OFFSET snakeMsg
        call WriteString
        call crlf
    .ELSEIF eax == 99
        mov player2Position, 69
        mov edx, OFFSET snakeMsg
        call WriteString
        call crlf
    .ENDIF
    ret
CheckSnakeP2 ENDP
AddToHistory PROC
    .IF ecx == 1
        .IF historyCount1 < 10
            mov edi, OFFSET player1DiceHistory
            mov ecx, historyCount1
            imul ecx, 4
            add edi, ecx
            mov [edi], eax
            inc historyCount1
        .ELSE
            mov esi, OFFSET player1DiceHistory
            add esi, 4
            mov edi, OFFSET player1DiceHistory
            mov ecx, 9
        shift_p1_hist:
            mov ebx, [esi]
            mov [edi], ebx
            add esi, 4
            add edi, 4
            loop shift_p1_hist
            mov [edi], eax
        .ENDIF
    .ELSE
        .IF historyCount2 < 10
            mov edi, OFFSET player2DiceHistory
            mov ecx, historyCount2
            imul ecx, 4
            add edi, ecx
            mov [edi], eax
            inc historyCount2
        .ELSE
            mov esi, OFFSET player2DiceHistory
            add esi, 4
            mov edi, OFFSET player2DiceHistory
            mov ecx, 9
        shift_p2_hist:
            mov ebx, [esi]
            mov [edi], ebx
            add esi, 4
            add edi, 4
            loop shift_p2_hist
             mov [edi], eax
        .ENDIF
    .ENDIF
    ret
AddToHistory ENDP

DisplayInfoBox PROC
    mov dh, 0
    mov dl, 75
    call Gotoxy
    mov al, 00001110b
    call SetTextColor
    mov edx, OFFSET infoBoxTitleMsg
    call WriteString
    mov al, 00001111b
    call SetTextColor
    mov dh, 2
    mov dl, 75
    call Gotoxy
    mov al, 00000100b
    call SetTextColor
    mov edx, OFFSET snakesTitleMsg
    call WriteString
    mov al, 00001111b
    call SetTextColor
    mov dh, 3
    mov dl, 75
    call Gotoxy
    mov edx, OFFSET snakeLabelMsg
    call WriteString
    mov eax, 25
    call WriteDec
    mov edx, OFFSET arrowChar
    call WriteString
    mov eax, 5
    call WriteDec
    mov dh, 4
    mov dl, 75
    call Gotoxy
    mov edx, OFFSET snakeLabelMsg
    call WriteString
    mov eax, 34
    call WriteDec
    mov edx, OFFSET arrowChar
    call WriteString
    mov eax, 1
    call WriteDec
    mov dh, 5
    mov dl, 75
    call Gotoxy
    mov edx, OFFSET snakeLabelMsg
    call WriteString
    mov eax, 47
    call WriteDec
    mov edx, OFFSET arrowChar
    call WriteString
    mov eax, 19
    call WriteDec
    mov dh, 6
    mov dl, 75
    call Gotoxy
    mov edx, OFFSET snakeLabelMsg
    call WriteString
    mov eax, 65
    call WriteDec
    mov edx, OFFSET arrowChar
    call WriteString
    mov eax, 52
    call WriteDec
    mov dh, 7
    mov dl, 75
    call Gotoxy
    mov edx, OFFSET snakeLabelMsg
    call WriteString
    mov eax, 87
    call WriteDec
    mov edx, OFFSET arrowChar
    call WriteString
    mov eax, 57
    call WriteDec
    mov dh, 8
    mov dl, 75
    call Gotoxy
    mov edx, OFFSET snakeLabelMsg
    call WriteString
    mov eax, 91
    call WriteDec
    mov edx, OFFSET arrowChar
    call WriteString
    mov eax, 61
    call WriteDec
    mov dh, 9
    mov dl, 75
    call Gotoxy
    mov edx, OFFSET snakeLabelMsg
    call WriteString
    mov eax, 99
    call WriteDec
    mov edx, OFFSET arrowChar
    call WriteString
    mov eax, 69
    call WriteDec
    mov dh, 11
    mov dl, 75
    call Gotoxy
    mov al, 00000010b
    call SetTextColor
    mov edx, OFFSET laddersTitleMsg
    call WriteString
    mov al, 00001111b
    call SetTextColor
    mov dh, 12
    mov dl, 75
    call Gotoxy
    mov edx, OFFSET ladderLabelMsg
    call WriteString
    mov eax, 2
    call WriteDec
    mov edx, OFFSET arrowChar
    call WriteString
    mov eax, 23
    call WriteDec
    mov dh, 13
    mov dl, 75
    call Gotoxy
    mov edx, OFFSET ladderLabelMsg
    call WriteString
    mov eax, 6
    call WriteDec
    mov edx, OFFSET arrowChar
    call WriteString
    mov eax, 45
    call WriteDec
    mov dh, 14
    mov dl, 75
    call Gotoxy
    mov edx, OFFSET ladderLabelMsg
    call WriteString
    mov eax, 20
    call WriteDec
    mov edx, OFFSET arrowChar
    call WriteString
    mov eax, 59
    call WriteDec
    mov dh, 15
    mov dl, 75
    call Gotoxy
    mov edx, OFFSET ladderLabelMsg
    call WriteString
    mov eax, 52
    call WriteDec
    mov edx, OFFSET arrowChar
    call WriteString
    mov eax, 72
    call WriteDec
    mov dh, 16
    mov dl, 75
    call Gotoxy
    mov edx, OFFSET ladderLabelMsg
    call WriteString
    mov eax, 57
    call WriteDec
    mov edx, OFFSET arrowChar
    call WriteString
    mov eax, 96
    call WriteDec
    mov dh, 17
    mov dl, 75
    call Gotoxy
    mov edx, OFFSET ladderLabelMsg
    call WriteString
    mov eax, 71
    call WriteDec
    mov edx, OFFSET arrowChar
    call WriteString
    mov eax, 92
    call WriteDec
    ret
DisplayInfoBox ENDP



DisplayStatusBox PROC
    mov dh, 31
    mov dl, 0
    call Gotoxy
    
    mov edx, OFFSET statusBoxTopMsg
    call WriteString
    call crlf
    
    mov edx, OFFSET statusBoxSideMsg
    call WriteString
    mov al, 00001110b
    call SetTextColor
    mov edx, OFFSET statusTitleMsg
    call WriteString
    mov al, 00001111b
    call SetTextColor
    mov ecx, 50
    mov al, ' '
pad1:
    call WriteChar
    loop pad1
    call crlf
    
    mov edx, OFFSET statusBoxSideMsg
    call WriteString
    mov al, ' '
    call WriteChar
    mov edx, OFFSET colorChoiceMsg
    call WriteString
    mov ecx, 55
    mov al, ' '
pad2:
    call WriteChar
    loop pad2
    call crlf
    
    mov edx, OFFSET statusBoxSideMsg
    call WriteString
    mov al, ' '
    call WriteChar
    mov al, 01000000b
    call SetTextColor
    mov al, 'P'
    call WriteChar
    mov al, '1'
    call WriteChar
    mov al, ' '
    call WriteChar
    mov al, 00001111b
    call SetTextColor
    mov edx, OFFSET player1Name
    call WriteString
    mov edx, OFFSET playerPosMsg
    call WriteString
    mov eax, player1Position
    call WriteDec
    mov ecx, 25
    mov al, ' '
pad3:
    call WriteChar
    loop pad3
    mov al, 01100000b
    call SetTextColor
    mov al, 'P'
    call WriteChar
    mov al, '2'
    call WriteChar
    mov al, ' '
    call WriteChar
    mov al, 00001111b
    call SetTextColor
    mov edx, OFFSET player2Name
    call WriteString
    mov edx, OFFSET playerPosMsg
    call WriteString
    mov eax, player2Position
    call WriteDec
    mov ecx, 15
    mov al, ' '
pad4:
    call WriteChar
    loop pad4
    call crlf
    
    mov edx, OFFSET statusBoxSideMsg
    call WriteString
    mov al, ' '
    call WriteChar
    mov al, 01000000b
    call SetTextColor
    mov al, 'P'
    call WriteChar
    mov al, '1'
    call WriteChar
    mov al, ' '
    call WriteChar
    mov al, 00001111b
    call SetTextColor
    mov edx, OFFSET diceHistoryMsg
    call WriteString
    mov esi, OFFSET player1DiceHistory
    mov ecx, historyCount1
    cmp ecx, 10
    jbe done1
    mov ecx, 10
done1:
    cmp ecx, 0
    je skip1
loop1:
    push ecx
    mov eax, [esi]
    call WriteDec
    add esi, 4
    pop ecx
    cmp ecx, 1
    je end1
    mov edx, OFFSET commaMsg
    call WriteString
end1:
    loop loop1
skip1:
    mov ecx, 25
    mov al, ' '
pad5:
    call WriteChar
    loop pad5
    call crlf
    
    mov edx, OFFSET statusBoxSideMsg
    call WriteString
    mov al, ' '
    call WriteChar
    mov al, 01100000b
    call SetTextColor
    mov al, 'P'
    call WriteChar
    mov al, '2'
    call WriteChar
    mov al, ' '
    call WriteChar
    mov al, 00001111b
    call SetTextColor
    mov edx, OFFSET diceHistoryMsg
    call WriteString
    mov esi, OFFSET player2DiceHistory
    mov ecx, historyCount2
    cmp ecx, 10
    jbe done2
    mov ecx, 10
done2:
    cmp ecx, 0
    je skip2
loop2:
    push ecx
    mov eax, [esi]
    call WriteDec
    add esi, 4
    pop ecx
    cmp ecx, 1
    je end2
    mov edx, OFFSET commaMsg
    call WriteString
end2:
    loop loop2
skip2:
    mov ecx, 25
    mov al, ' '
pad6:
    call WriteChar
    loop pad6
    call crlf
    
    mov edx, OFFSET statusBoxBotMsg
    call WriteString
    call crlf
    
    ret
DisplayStatusBox ENDP


DisplayLadders PROC
    mov al, 00011100b
    call SetTextColor
    mov dh, 29
    mov dl, 10
    call Gotoxy
    mov edx, OFFSET ladder1Label
    call WriteString
    mov dh, 29
    mov dl, 38
    call Gotoxy
    mov edx, OFFSET ladder2Label
    call WriteString
    mov dh, 26
    mov dl, 3
    call Gotoxy
    mov edx, OFFSET ladder3Label
    call WriteString
    mov dh, 14
    mov dl, 59
    call Gotoxy
    mov edx, OFFSET ladder4Label
    call WriteString
    mov dh, 14
    mov dl, 24
    call Gotoxy
    mov edx, OFFSET ladder5Label
    call WriteString
    mov dh, 8
    mov dl, 66
    call Gotoxy
    mov edx, OFFSET ladder6Label
    call WriteString
    mov al, 11111100b
    call SetTextColor
    mov dh, 2
    mov dl, 3
    call Gotoxy
    mov edx, OFFSET Win
    call WriteString
    mov al, 00001111b
    call SetTextColor
    ret
DisplayLadders ENDP

DisplaySnakes PROC
    mov al, 00011100b
    call SetTextColor
    mov dh, 23
    mov dl, 31
    call Gotoxy
    mov edx, OFFSET snake1Label
    call WriteString
    mov dh, 20
    mov dl, 45
    call Gotoxy
    mov edx, OFFSET snake2Label
    call WriteString
    mov dh, 17
    mov dl, 45
    call Gotoxy
    mov edx, OFFSET snake3Label
    call WriteString
    mov dh, 11
    mov dl, 31
    call Gotoxy
    mov edx, OFFSET snake4Label
    call WriteString
    mov dh, 8
    mov dl, 45
    call Gotoxy
    mov edx, OFFSET snake5Label
    call WriteString
    mov dh, 2
    mov dl, 66
    call Gotoxy
    mov edx, OFFSET snake6Label
    call WriteString
    mov dh, 2
    mov dl, 10
    call Gotoxy
    mov edx, OFFSET snake7Label
    call WriteString
    mov al, 00001111b
    call SetTextColor
    ret
DisplaySnakes ENDP

END main