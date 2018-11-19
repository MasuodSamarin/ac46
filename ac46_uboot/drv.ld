MEMORY 
{ 
    drv1_comm : ORIGIN = 0, LENGTH = 4 
    drv1_overlay : ORIGIN = 4, LENGTH = 8 
    drv2_comm : ORIGIN = 8, LENGTH = 16 
    drv2_overlay : ORIGIN = 16, LENGTH = 22 
} 
SECTIONS 
{ 
    OVERLAY : AT(131072)
    { 
   } > drv1_comm 
 
    OVERLAY : AT(196608)
    { 
   } > drv1_overlay 
 
    OVERLAY : AT(262144)
    { 
   } > drv2_comm 
 
    OVERLAY : AT(327680)
    { 
   } > drv2_overlay 
 
} 
 
