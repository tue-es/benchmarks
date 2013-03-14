/*-------------------------------------------*/
/* ITU-R version for color conversion:	     */
/*  u -= 128                                 */
/*  v -= 128                                 */
/*  r = y		    +1.402	v                */
/*  g = y -0.34414u	-0.71414v	             */
/*  b = y +1.772  u			                 */
/* Approximations: 1.402 # 7/5 = 1.400	     */
/*		.71414 # 357/500 = 0.714             */
/*		.34414 # 43/125	= 0.344	             */
/*		1.772  = 443/250	                 */
/*-------------------------------------------*/
/* Approximations: 1.402 # 359/256 = 1.40234 */
/*		.71414 # 183/256 = 0.71484           */
/*		.34414 # 11/32 = 0.34375             */
/*		1.772 # 227/128 = 1.7734             */
/*-------------------------------------------*/

#define Saturate(n)	((n) > 0 ? ((n) < 255 ? (n) : 255) : 0)

void
yuv2rgb(unsigned int * out, unsigned int * in, int n) {
    unsigned int *yi, *cbi, *cri, *ro, *go, *bo;
    int i, y, cb, cr, r, g, b;
    
    yi  = in;
    cbi = in + n;
    cri = in + 2 * n;
    ro = out;
    go = out + n;
    bo = out + 2 * n;
    for(i = 0; i < n; i ++) {
        y  = yi[i];
        cb = cbi[i] - 128;
        cr = cri[i] - 128;
        r = y + ((359 * cr) >> 8);
        g = y - ((11  * cb) >> 5) - ((183 * cr) >> 8);
        b = y + ((227 * cb) >> 7);
        ro[i] = Saturate(r);
        go[i] = Saturate(g);
        bo[i] = Saturate(b);
    }
}
