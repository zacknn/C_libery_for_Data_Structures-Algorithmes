#ifndef RAM
#define RAM
#include <stdint.h>
void Bit(int in , int load , int *out);
void Register(uint16_t in , int load , uint16_t *out);

#endif // !RAM