/** GameBit (bittable) system
 */

typedef struct {
    // Start bit index
    u16 start;
    // bits 0-4: length in bits (minus 1)
    // bit 5: has task
    // bits 6-7: which bitstring
    u8 field_0x2;
    u8 task;
} BitTableEntry;

extern BitTableEntry *gFile_BITTABLE;
extern s16 gSizeBittable;
