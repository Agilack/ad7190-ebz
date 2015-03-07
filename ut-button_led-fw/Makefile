FW = ut-led_button
CC = sdcc-sdcc
CYCFX2PROG = cycfx2prog

$(FW).ihx: main.c
	@echo  " - Compile main.c"
	@$(CC) -mmcs51 -I. -c main.c
	@echo  " - Link ut-led_button.ihx"
	@$(CC) -mmcs51 main.rel -o $(FW).ihx

clean:
	rm -f *.rel *.asm *.lst *.rst *.sym
	rm -f $(FW).{asm,ihx,lnk,lst,map,mem,rel,rst,sym,lk}
	rm -f *.o *~

run: $(FW).ihx
	$(CYCFX2PROG) prg:$(FW).ihx run
