.386
PUBLIC _FindNum1@16
PUBLIC _FindNum2
PUBLIC FindNum3
PUBLIC FindNum4
PUBLIC @FindNum5@16
.model flat
.data
.code

_FindNum1@16 proc
    push ebp
    mov ebp, esp
    sub esp, 8
    push ebx            
    push esi            
    push edi            

    mov esi, [ebp + 8]
    mov edi, [ebp + 12]
    mov ecx, [ebp + 16]
    mov ebx, [ebp + 20]
    mov [ebp - 8], ebx

cycle1:
    mov eax, [esi]
    mov byte ptr [ebp-4], 0
    xor edx, edx

cycle2:
    cmp edx, ecx
    jge check
    mov ebx, [edi + edx * 4]
    cmp ebx, eax
    je find_elem
    inc edx
    jmp cycle2

find_elem:
    mov byte ptr [ebp - 4], 1

check:
    cmp byte ptr [ebp - 4], 1
    je skip
    cmp eax, [ebp - 8]
    jge skip
    mov [ebp - 8], eax

skip:
    add esi, 4
    dec ecx
    jnz cycle1

    mov eax, [ebp - 8]
    pop edi           
    pop esi           
    pop ebx           
    add esp, 8        
    mov esp, ebp
    pop ebp
    ret 16
_FindNum1@16 endp

_FindNum2 proc
    push ebp
    mov ebp, esp
    sub esp, 8
    push ebx          
    push esi          
    push edi 
	mov esi, [ebp + 8] 
	mov edi, [ebp + 12] 
	mov ecx, [ebp + 16] 
    mov ebx, [ebp + 20] 
    mov [ebp - 8], ebx

cycle1 :
    mov eax, [esi]
    mov byte ptr [ebp-4], 0
    xor edx, edx

cycle2 :
    cmp edx, ecx
    jge check
    mov ebx, [edi + edx * 4]
    cmp ebx, eax
    je find_elem
    inc edx
    jmp cycle2

find_elem :
    mov byte ptr [ebp - 4], 1
    
check :
    cmp byte ptr [ebp - 4], 1
    je skip
    cmp eax, [ebp - 8]
    jge skip
    mov [ebp - 8], eax

skip:
    add esi, 4
    dec ecx
    jnz cycle1
   
    mov eax, [ebp - 8]
	pop edi           
    pop esi           
    pop ebx           
    add esp, 8        
    mov esp, ebp
    pop ebp
	ret
_FindNum2	endp

FindNum3 proc stdcall, a1:dword, a2:dword, N:dword, minValue:dword
    sub esp, 8
    mov esi, a1
    mov edi, a2
    mov ecx, N
    mov ebx, minValue
    mov [ebp - 20], ebx
	
cycle1:
    mov eax, [esi]
    mov byte ptr [ebp-4], 0
    xor edx, edx

cycle2:
    cmp edx, ecx
    jge check
    mov ebx, [edi + edx * 4]
    cmp ebx, eax
    je find_elem
    inc edx
    jmp cycle2

find_elem:
    mov byte ptr [ebp - 4], 1

check:
    cmp byte ptr [ebp - 4], 1
    je skip
    cmp eax, [ebp - 8]
    jge skip
    mov [ebp - 8], eax

skip:
    add esi, 4
    dec ecx
    jnz cycle1

    mov eax, [ebp - 8]
    add esp, 8 
    ret 16            
FindNum3 endp

FindNum4 proc C, a1:dword, a2:dword, N:dword, minValue:dword 
    sub esp, 8

    mov esi, a1  
    mov edi, a2  
    mov ecx, N
    mov eax, minValue  
    mov [ebp-8], eax    

cycle1:
    mov eax, [esi]     
    mov byte ptr [ebp-4], 0 
    xor edx, edx

cycle2:
    cmp edx, [ebp+16]
    jge check
    mov ebx, DWORD PTR [edi + edx * 4]
    cmp ebx, eax
    je find_elem
    inc edx
    jmp cycle2

find_elem:
    mov byte ptr [ebp-4], 1

check:
    cmp byte ptr [ebp-4], 1
    je skip
    cmp eax, [ebp-8]
    jge skip
    mov [ebp-8], eax

skip:
    add esi, 4
    dec ecx
    jnz cycle1

    mov eax, [ebp-8]

    add esp, 8
    ret
FindNum4 endp


@FindNum5@16 proc
    push ebp
    mov ebp, esp
    push esi
    push edi
    sub esp, 16

    mov esi, ecx
    mov edi, edx
    mov eax, [ebp + 12]
    mov [ebp - 12], eax
    mov ecx, [ebp + 8]

cycle1:
    test ecx, ecx
    jz done

    mov eax, [esi]
    mov byte ptr [ebp - 16], 0

    push ecx
    mov ecx, [ebp + 8]
    xor edx, edx

cycle2:
    cmp edx, ecx
    jge check
    mov ebx, [edi + edx * 4]
    cmp ebx, eax
    je find_elem
    inc edx
    jmp cycle2

find_elem:
    mov byte ptr [ebp - 16], 1

check:
    cmp byte ptr [ebp - 16], 1
    je skip
    cmp eax, [ebp - 12]
    jge skip
    mov [ebp - 12], eax

skip:
    pop ecx              
    add esi, 4           
    dec ecx              
    jnz cycle1

done:
    mov eax, [ebp - 12]  
    add esp, 16          
    pop edi
    pop esi
    pop ebp
    ret 8                
@FindNum5@16 endp

end