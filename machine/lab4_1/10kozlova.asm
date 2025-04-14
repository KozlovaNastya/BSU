.386
PUBLIC @Find1@8
.model flat
.data
.code
@Find1@8 proc
    push ebp
    mov ebp, esp
    push ebx
    push esi
    push edi
    mov esi, ecx             
    mov ecx, edx             

    xor eax, eax             
    cmp ecx, 0
    jle error                

    mov edi, -1              
    mov ebx, 0               
    xor edx, edx             

cycle1:
    cmp edx, ecx
    jge end_cycle1           
    mov eax, [esi + edx * 4] 
    push ecx
    push edx
    mov ecx, edx            
    xor edx, edx            

cycle2:
    cmp edx, ecx
    jge end_cycle2          
    cmp eax, [esi + edx * 4]
    jne skip_inc
    inc ecx
skip_inc:
    inc edx
    jmp cycle2

end_cycle2:
    pop edx
    pop ecx
    cmp ecx, ebx
    jle not_gr
    mov ebx, ecx             
    mov edi, eax             
not_gr:
    inc edx
    jmp cycle1

end_cycle1:
    cmp ebx, 1
    jg found                
    jmp error               

found:
    mov eax, edi
    jmp end_pr

error:
    mov eax, -1        

end_pr:
    pop edi
    pop esi
    pop ebx
    pop ebp
    ret
@Find1@8 endp
end
