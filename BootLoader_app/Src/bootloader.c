#include <STMF446RE.h>


#define BOOTLOADER_SIZE   (0x8000U)



static void jump_to_main(void);


int main(void){

	jump_to_main();

	return 0; //should never reach this line
}



static void jump_to_main(void){
	typedef void(*voidfun)(void);
	uint32_t verctor_table_entry = FLASH_BASEADRR + BOOTLOADER_SIZE;
	uint32_t *reset_handler_addr = (uint32_t *)(verctor_table_entry + 4U);//second entry in the table
	voidfun reset_handler = (voidfun)reset_handler_addr;
	reset_handler();
}
