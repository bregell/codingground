#include <stdio.h>

void fpc_bep_cac_find_finger_pos(unsigned int covered_areas, unsigned int *pos_h, unsigned int *pos_w)
{
    int     i, j;
    float   row, col;
    float   rel_h, rel_w;
    int     active;

    /* Loop over the areas */
    for (i = 0, active = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            if (covered_areas & 0x1) {
                active++;
                row += (float)(i * (covered_areas & 0x1));
                col += (float)(j * (covered_areas & 0x1));
            }
            covered_areas = covered_areas >> 1;
        }
    }
    
    if (active) {
        row /= (float)active;
        col /= (float)active;
        
        rel_h = (float)160 / (float)(3);
        rel_w = (float)160 / (float)(4);
        
    
        *pos_h = (int)(row * rel_h + rel_h / 2.0);
        *pos_w = (int)(col * rel_w + rel_w / 2.0);
        *pos_w -= (*pos_w % 8);
    } else {
       *pos_h = 0;
       *pos_w = 0;
    }
}

void fpc_bep_cac_calculate_offset(unsigned int pos_h, unsigned int pos_w, unsigned int *offset_height, unsigned int *offset_width)
{
    if (pos_w < (16 / 2)) {
        *offset_width = 0;
    } else if ((pos_w + 16 / 2) > 160) {
        *offset_width = 160 - 16 / 2;
    } else {
        *offset_width = pos_w - 16 / 2;
    }
    if (pos_h < (16 / 2)) {
        *offset_height = 0;
    } else if((pos_h + 16 / 2) > 160) {
        *offset_height = 160 - 16 / 2;
    } else {
        *offset_height = pos_h - 16 / 2;
    }
}

int main()
{
    unsigned int covered = 2048;
    unsigned int pos_h, pos_w;
    unsigned int off_h, off_w;
    
    fpc_bep_cac_find_finger_pos(covered, &pos_h, &pos_w);
    fpc_bep_cac_calculate_offset(pos_h, pos_w, &off_h, &off_w);
    
    printf("H: %u W: %u \n", pos_h, pos_w);
    
    printf("OfH: %u OfW: %u \n", off_h, off_w);
    
    return 0;
}
