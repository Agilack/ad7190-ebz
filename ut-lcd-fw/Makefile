FW = ut-lcd
CC = sdcc-sdcc
CYCFX2PROG = cycfx2prog

$(FW).ihx: main.c lcd.c
	@echo  " - Compile main.c"
	@$(CC) -mmcs51 -I. -c main.c
	@echo  " - Compile lcd.c"
	@$(CC) -mmcs51 -I. -c lcd.c
	@echo  " - Link ut-lcd.ihx"
	@$(CC) -mmcs51 main.rel lcd.rel -o $(FW).ihx

clean:
	rm -f *.rel *.asm *.lst *.rst *.sym
	rm -f $(FW).{asm,ihx,lnk,lst,map,mem,rel,rst,sym,lk}
	rm -f *.o *~

run: $(FW).ihx
	$(CYCFX2PROG) prg:$(FW).ihx run
