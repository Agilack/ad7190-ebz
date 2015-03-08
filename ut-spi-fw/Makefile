FW = ut-spi
CC = sdcc-sdcc
CYCFX2PROG = cycfx2prog

$(FW).ihx: main.c spi.c
	@echo  " - Compile main.c"
	@$(CC) -mmcs51 -I. -c main.c
	@echo  " - Compile spi.c"
	@$(CC) -mmcs51 -I. -c spi.c
	@echo  " - Link ut-spi.ihx"
	@$(CC) -mmcs51 main.rel spi.rel -o $(FW).ihx

clean:
	rm -f *.rel *.asm *.lst *.rst *.sym
	rm -f $(FW).{asm,ihx,lnk,lst,map,mem,rel,rst,sym,lk}
	rm -f *.o *~

run: $(FW).ihx
	$(CYCFX2PROG) prg:$(FW).ihx run
