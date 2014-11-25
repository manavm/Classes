/*
uint16_t const ADCdata[53]={0,1090,1126,1162,1199,1236,1273,1311,1349,1387,1426,		
     1465,1504,1544,1585,1625,1667,1708,1750,1792,1835,		
     1878,1922,1966,2010,2055,2100,2145,2191,2238,2285,		
     2332,2379,2428,2476,2525,2574,2624,2674,2725,2776,		
     2827,2879,2931,2984,3037,3090,3144,3199,3253,3308,3364,4096};		
	
	
uint16_t const Tdata[53]={4000,4000,3950,3900,3850,3800,3750,3700,3650,3600,3550,		
     3500,3450,3400,3350,3300,3250,3200,3150,3100,3050,		
     3000,2950,2900,2850,2800,2750,2700,2650,2600,2550,		
     2500,2450,2400,2350,2300,2250,2200,2150,2100,2050,		
     2000,1950,1900,1850,1800,1750,1700,1650,1600,1550,1500,1500};		
	
	
uint16_t const Rdata[53]={597,597,605,613,621,629,638,646,655,664,672,							
     681,691,700,710,719,729,739,749,760,770,							
     781,792,803,814,825,837,849,861,873,886,							
     899,912,925,938,952,966,980,994,1009,1024,							
     1039,1055,1071,1087,1103,1120,1137,1154,1172,1190,1208,1208};							
							
		 */
		 
uint16_t const ADCdata[53]={0,409,462,516,571,626,683,740,798,857,916,		
     977,1038,1100,1163,1226,1291,1356,1422,1489,1557,		
     1626,1695,1766,1837,1909,1981,2055,2130,2205,2281,		
     2358,2436,2514,2593,2673,2754,2836,2918,3001,3085,		
     3169,3254,3340,3427,3514,3602,3690,3779,3869,3959,4050,4096};		
		

uint16_t const Tdata[53]={4000,4000,3950,3900,3850,3800,3750,3700,3650,3600,3550,		
     3500,3450,3400,3350,3300,3250,3200,3150,3100,3050,		
     3000,2950,2900,2850,2800,2750,2700,2650,2600,2550,		
     2500,2450,2400,2350,2300,2250,2200,2150,2100,2050,		
     2000,1950,1900,1850,1800,1750,1700,1650,1600,1550,1500,1500};		

						
uint16_t const Rdata[53]={5532,5532,5645,5760,5877,5998,6121,6247,6377,6509,6645,								
     6784,6926,7071,7221,7374,7530,7691,7855,8024,8197,								
     8374,8555,8741,8932,9128,9328,9534,9745,9961,10183,								
     10410,10643,10883,11128,11380,11639,11904,12177,12456,12743,								
     13038,13340,13651,13970,14297,14633,14979,15334,15698,16073,16457,16457};								
					


uint32_t convert(uint32_t input){
    uint16_t i = 0;
    for (i = 0 ; i < 53; i++)
        if (ADCdata[i] > input) break;
  return Tdata[i];
}
