start: not r7 ,B
label: mcro __dummy
bne END
start: not r7 ,B
sub t2, f3
mcroend
__dummy
mcro mcroName 
lea STR ,r6
mcroend

