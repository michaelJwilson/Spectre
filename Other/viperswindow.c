double splint_VIPERS_maskMono(double r){
  if(r<0.15)  return 1.;
  if(r>900.)  return 0.;
        
  if(r<hiRes_hihiRes_join){    
    splint(VIPERS_maskr_hihi, VIPERS_maskMono_hihi, VIPERS_maskMono2D_hihi, VIPERS_mask_lineNo_hihi, r, &Interim);
    
    return Interim;  // amplitude determined by powerlaw_regression at r=1. -> A parameter.
  }
    
  else if(r<loRes_highRes_join){
    splint(VIPERS_maskr_hi, VIPERS_maskMono_hi, VIPERS_maskMono2D_hi, VIPERS_mask_lineNo_hi, r, &Interim);
    
    return Interim;  // amplitude determined by powerlaw_regression at r=1. -> A parameter.
  }
    
  else{
    splint(VIPERS_maskr_lo, VIPERS_maskMono_lo, VIPERS_maskMono2D_lo, VIPERS_mask_lineNo_lo, r, &Interim);
    
    return Interim;  // amplitude determined by powerlaw_regression at r=1. -> A parameter.
  }
}

double splint_VIPERS_maskQuad(double r){
  if(r<0.2)   return 0.;
  if(r>900.0) return 0.;
    
  if(r<hiRes_hihiRes_join){
    splint(VIPERS_maskr_hihi, VIPERS_maskQuad_hihi, VIPERS_maskQuad2D_hihi, VIPERS_mask_lineNo_hihi, r, &Interim);
    
    return Interim;
  }
    
  else if(r<loRes_highRes_join){
    splint(VIPERS_maskr_hi, VIPERS_maskQuad_hi, VIPERS_maskQuad2D_hi, VIPERS_mask_lineNo_hi, r, &Interim);
    
    return Interim;
  }
    
  else{
    splint(VIPERS_maskr_lo, VIPERS_maskQuad_lo, VIPERS_maskQuad2D_lo, VIPERS_mask_lineNo_lo, r, &Interim);
    
    return Interim;
  }
}

double splint_VIPERS_maskHex(double r){
  if(r<0.2)   return 0.;
  if(r>900.0) return 0.;
        
  if(r<hiRes_hihiRes_join){
    splint(VIPERS_maskr_hihi, VIPERS_maskHex_hihi, VIPERS_maskHex2D_hihi, VIPERS_mask_lineNo_hihi, r, &Interim);
    
    return Interim;
  }
    
  else if(r<loRes_highRes_join){
    splint(VIPERS_maskr_hi, VIPERS_maskHex_hi, VIPERS_maskHex2D_hi, VIPERS_mask_lineNo_hi, r, &Interim);
    
    return Interim;
  }
    
  else{
    splint(VIPERS_maskr_lo, VIPERS_maskHex_lo, VIPERS_maskHex2D_lo, VIPERS_mask_lineNo_lo, r, &Interim);
    
    return Interim;
  }
}

double splint_VIPERS_maskOct(double r){
  if(r<  0.5) return 0.;
  if(r>900.0) return 0.;
    
  if(r<hiRes_hihiRes_join){
    splint(VIPERS_maskr_hihi, VIPERS_maskOct_hihi, VIPERS_maskOct2D_hihi, VIPERS_mask_lineNo_hihi, r, &Interim);
    
    return Interim;
  }
    
  else if(r<loRes_highRes_join){
    splint(VIPERS_maskr_hi, VIPERS_maskOct_hi, VIPERS_maskOct2D_hi, VIPERS_mask_lineNo_hi, r, &Interim);
    
    return Interim;
  }
    
  else{
    splint(VIPERS_maskr_lo, VIPERS_maskOct_lo, VIPERS_maskOct2D_lo, VIPERS_mask_lineNo_lo, r, &Interim);
    
    return Interim;
  }
}

double splint_VIPERS_maskDec(double r){
  if(r<  0.5) return 0.;
  if(r>900.0) return 0.;
    
  if(r<hiRes_hihiRes_join){
    splint(VIPERS_maskr_hihi, VIPERS_maskDec_hihi, VIPERS_maskDec2D_hihi, VIPERS_mask_lineNo_hihi, r, &Interim);
    
    return Interim;
  }
    
  else if(r<loRes_highRes_join){
    splint(VIPERS_maskr_hi, VIPERS_maskDec_hi, VIPERS_maskDec2D_hi, VIPERS_mask_lineNo_hi, r, &Interim);
    
    return Interim;
  }
    
  else{
    splint(VIPERS_maskr_lo, VIPERS_maskDec_lo, VIPERS_maskDec2D_lo, VIPERS_mask_lineNo_lo, r, &Interim);
    
    return Interim;
  }
}

double splint_VIPERS_maskMultipoles(double r, int transformOrder){
  switch(transformOrder){
  case 0:
    return  splint_VIPERS_maskMono(r); break;  
  case 2:    
    return  splint_VIPERS_maskQuad(r); break;
  case 4:
    return  splint_VIPERS_maskHex(r);  break; 
  case 6:
    return  splint_VIPERS_maskOct(r);  break;
  case 8:
    return  splint_VIPERS_maskDec(r);  break;
    // case 10:
    //   return  splint_VIPERS_maskDodeca(r);
  }
}
   
double splint_unit_maskMultipoles(double r, int transformOrder){
  switch(transformOrder){
  case 0:
    return  1.0;  
  case 2:
    return  0.0;
  case 4:
    return  0.0;
  case 6:
    return  0.0;
  case 8:
    return  0.0;
  case 10:
    return  0.0;
  }
}

int prep_VIPERS_maskMultipoles(){
  char           header[200];

  char   loRes_filepath[200]; // Mask autocorrelation function. 
  char   hiRes_filepath[200];
  char hihiRes_filepath[200];

  if(mull==0){
    sprintf(filepath, "%s/Qmultipoles/Ql_W%d_Nag_v7_specweight_nbar_Pfkp_8000_%.1lf_%.1lf_thread_1", maskmultipoles_path, fieldFlag, lo_zlim, hi_zlim);
  }

  else if(mull==1){
    sprintf(filepath, "%s/Qmultipoles/maskmultipoles_W%d_Nagoya_v7_Samhain_incmock_specweight_nbar_fkpweighted_8000.00_xi_%.1lf_%.1lf", maskmultipoles_path, fieldFlag, lo_zlim, hi_zlim);
  }

  else{
    printf("\n\nError from Q multipoles load.");
  }
  
  printf("\n\nQ-multipoles: %s", filepath);
  
  sprintf(hihiRes_filepath, "%s_hihiRes_hex.dat", filepath);
  sprintf(  hiRes_filepath, "%s_hiRes_hex.dat",   filepath);
  sprintf(  loRes_filepath, "%s_loRes_hex.dat",   filepath);    

  //-- Super high resolution counts for r ~ 1. --// 
  inputfile = fopen(hihiRes_filepath, "r");

  // line_count(inputfile, &VIPERS_mask_lineNo_hihi);
  linecount_header(inputfile, 1, &VIPERS_mask_lineNo_hihi);
  
  VIPERS_maskr_hihi        = realloc(VIPERS_maskr_hihi,      VIPERS_mask_lineNo_hihi*sizeof(double));
    
  VIPERS_maskMono_hihi     = realloc(VIPERS_maskMono_hihi,   VIPERS_mask_lineNo_hihi*sizeof(double));
  VIPERS_maskQuad_hihi     = realloc(VIPERS_maskQuad_hihi,   VIPERS_mask_lineNo_hihi*sizeof(double));
  VIPERS_maskHex_hihi      = realloc( VIPERS_maskHex_hihi,   VIPERS_mask_lineNo_hihi*sizeof(double));
  VIPERS_maskOct_hihi      = realloc( VIPERS_maskOct_hihi,   VIPERS_mask_lineNo_hihi*sizeof(double));
  VIPERS_maskDec_hihi      = realloc( VIPERS_maskDec_hihi,   VIPERS_mask_lineNo_hihi*sizeof(double));
    
  VIPERS_maskMono2D_hihi   = realloc(VIPERS_maskMono2D_hihi, VIPERS_mask_lineNo_hihi*sizeof(double));
  VIPERS_maskQuad2D_hihi   = realloc(VIPERS_maskQuad2D_hihi, VIPERS_mask_lineNo_hihi*sizeof(double));
  VIPERS_maskHex2D_hihi    = realloc( VIPERS_maskHex2D_hihi, VIPERS_mask_lineNo_hihi*sizeof(double));
  VIPERS_maskOct2D_hihi    = realloc( VIPERS_maskOct2D_hihi, VIPERS_mask_lineNo_hihi*sizeof(double));
  VIPERS_maskDec2D_hihi    = realloc( VIPERS_maskDec2D_hihi, VIPERS_mask_lineNo_hihi*sizeof(double));

  fgets(header, 200, inputfile); // skip header
  
  for(j=0; j<VIPERS_mask_lineNo_hihi; j++){  
	fscanf(inputfile, "%le \t %le \t %le \t %le \t %le \t %le \n", &VIPERS_maskr_hihi[j], &VIPERS_maskMono_hihi[j], &VIPERS_maskQuad_hihi[j], &VIPERS_maskHex_hihi[j], &VIPERS_maskOct_hihi[j],  &VIPERS_maskDec_hihi[j]);
  }
  
  fclose(inputfile);
  
  for(j=0; j<VIPERS_mask_lineNo_hihi; j++){
    VIPERS_maskMono_hihi[j]  /= pow(VIPERS_maskr_hihi[j], 3.);
    VIPERS_maskQuad_hihi[j]  /= pow(VIPERS_maskr_hihi[j], 3.);
     VIPERS_maskHex_hihi[j]  /= pow(VIPERS_maskr_hihi[j], 3.);
     VIPERS_maskOct_hihi[j]  /= pow(VIPERS_maskr_hihi[j], 3.);
     VIPERS_maskDec_hihi[j]  /= pow(VIPERS_maskr_hihi[j], 3.);

    // printf("\n%.6le \t %.6le \t %.6le", VIPERS_maskr_hi[j], VIPERS_maskMono_hi[j], VIPERS_maskQuad_hi[j]);
  }
  
  flatSlope_amp(VIPERS_mask_lineNo_hihi, 0.1, 0.2, 1.0, VIPERS_maskr_hihi, VIPERS_maskMono_hihi, &mask_monopolenorm_hihi);  // Determine amplitude where correlation is flat.

  for(j=0; j<VIPERS_mask_lineNo_hihi; j++){
    VIPERS_maskMono_hihi[j]  /= mask_monopolenorm_hihi;
    VIPERS_maskQuad_hihi[j]  /= mask_monopolenorm_hihi;
     VIPERS_maskHex_hihi[j]  /= mask_monopolenorm_hihi;
     VIPERS_maskOct_hihi[j]  /= mask_monopolenorm_hihi;
     VIPERS_maskDec_hihi[j]  /= mask_monopolenorm_hihi;
  }
  
  spline(VIPERS_maskr_hihi, VIPERS_maskMono_hihi,  VIPERS_mask_lineNo_hihi, 1.0e31, 1.0e31, VIPERS_maskMono2D_hihi);
  spline(VIPERS_maskr_hihi, VIPERS_maskQuad_hihi,  VIPERS_mask_lineNo_hihi, 1.0e31, 1.0e31, VIPERS_maskQuad2D_hihi);
  spline(VIPERS_maskr_hihi,  VIPERS_maskHex_hihi,  VIPERS_mask_lineNo_hihi, 1.0e31, 1.0e31, VIPERS_maskHex2D_hihi);
  spline(VIPERS_maskr_hihi,  VIPERS_maskOct_hihi,  VIPERS_mask_lineNo_hihi, 1.0e31, 1.0e31, VIPERS_maskOct2D_hihi);
  spline(VIPERS_maskr_hihi,  VIPERS_maskDec_hihi,  VIPERS_mask_lineNo_hihi, 1.0e31, 1.0e31, VIPERS_maskDec2D_hihi);
  
  // Outdated
  // hiRes_hihiRes_join = VIPERS_maskr_hihi[VIPERS_mask_lineNo_hihi - 1];  // Set the r at which the really high resolution will join the high resolution counts.
  hiRes_hihiRes_join = 1.80;
  
  inputfile = fopen(hiRes_filepath, "r");

  // line_count(inputfile, &VIPERS_mask_lineNo_hi);
  linecount_header(inputfile, 1, &VIPERS_mask_lineNo_hi);

  VIPERS_maskr_hi        = realloc(VIPERS_maskr_hi,    VIPERS_mask_lineNo_hi*sizeof(double));

  VIPERS_maskMono_hi     = realloc(VIPERS_maskMono_hi, VIPERS_mask_lineNo_hi*sizeof(double));
  VIPERS_maskQuad_hi     = realloc(VIPERS_maskQuad_hi, VIPERS_mask_lineNo_hi*sizeof(double));
  VIPERS_maskHex_hi      = realloc( VIPERS_maskHex_hi, VIPERS_mask_lineNo_hi*sizeof(double));
  VIPERS_maskOct_hi      = realloc( VIPERS_maskOct_hi, VIPERS_mask_lineNo_hi*sizeof(double));
  VIPERS_maskDec_hi      = realloc( VIPERS_maskDec_hi, VIPERS_mask_lineNo_hi*sizeof(double));

  VIPERS_maskMono2D_hi   = realloc(VIPERS_maskMono2D_hi, VIPERS_mask_lineNo_hi*sizeof(double));
  VIPERS_maskQuad2D_hi   = realloc(VIPERS_maskQuad2D_hi, VIPERS_mask_lineNo_hi*sizeof(double));
  VIPERS_maskHex2D_hi    = realloc( VIPERS_maskHex2D_hi, VIPERS_mask_lineNo_hi*sizeof(double));
  VIPERS_maskOct2D_hi    = realloc( VIPERS_maskOct2D_hi, VIPERS_mask_lineNo_hi*sizeof(double));
  VIPERS_maskDec2D_hi    = realloc( VIPERS_maskDec2D_hi, VIPERS_mask_lineNo_hi*sizeof(double));
   
  fgets(header, 200, inputfile); // skip header 
  
  for(j=0; j<VIPERS_mask_lineNo_hi; j++){
    fscanf(inputfile, "%le \t %le \t %le \t %le \t %le \t %le \n", &VIPERS_maskr_hi[j], &VIPERS_maskMono_hi[j], &VIPERS_maskQuad_hi[j], &VIPERS_maskHex_hi[j], &VIPERS_maskOct_hi[j], &VIPERS_maskDec_hi[j]);
  }

  fclose(inputfile);
  
  for(j=0; j<VIPERS_mask_lineNo_hi; j++){
    VIPERS_maskMono_hi[j] /= pow(VIPERS_maskr_hi[j], 3.);
    VIPERS_maskQuad_hi[j] /= pow(VIPERS_maskr_hi[j], 3.);
    VIPERS_maskHex_hi[j]  /= pow(VIPERS_maskr_hi[j], 3.);
    VIPERS_maskOct_hi[j]  /= pow(VIPERS_maskr_hi[j], 3.);
    VIPERS_maskDec_hi[j]  /= pow(VIPERS_maskr_hi[j], 3.);

    // printf("\n%.6le \t %.6le \t %.6le", VIPERS_maskr_hi[j], VIPERS_maskMono_hi[j], VIPERS_maskQuad_hi[j]);
  }

  lowRes_amplitudeCalc(VIPERS_mask_lineNo_hihi, VIPERS_mask_lineNo_hi, 1., 1.5, VIPERS_maskr_hihi, VIPERS_maskr_hi, VIPERS_maskMono_hihi, VIPERS_maskMono_hi, &mask_monopolenorm_hi);
        
  for(j=0; j<VIPERS_mask_lineNo_hi; j++){
    VIPERS_maskMono_hi[j] *= mask_monopolenorm_hi;
    VIPERS_maskQuad_hi[j] *= mask_monopolenorm_hi;
    VIPERS_maskHex_hi[j]  *= mask_monopolenorm_hi;
    VIPERS_maskOct_hi[j]  *= mask_monopolenorm_hi;
    VIPERS_maskDec_hi[j]  *= mask_monopolenorm_hi;
  }
  
  spline(VIPERS_maskr_hi, VIPERS_maskMono_hi, VIPERS_mask_lineNo_hi, 1.0e31, 1.0e31, VIPERS_maskMono2D_hi);
  spline(VIPERS_maskr_hi, VIPERS_maskQuad_hi, VIPERS_mask_lineNo_hi, 1.0e31, 1.0e31, VIPERS_maskQuad2D_hi);
  spline(VIPERS_maskr_hi, VIPERS_maskHex_hi,  VIPERS_mask_lineNo_hi, 1.0e31, 1.0e31, VIPERS_maskHex2D_hi);
  spline(VIPERS_maskr_hi, VIPERS_maskOct_hi,  VIPERS_mask_lineNo_hi, 1.0e31, 1.0e31, VIPERS_maskOct2D_hi);
  spline(VIPERS_maskr_hi, VIPERS_maskDec_hi,  VIPERS_mask_lineNo_hi, 1.0e31, 1.0e31, VIPERS_maskDec2D_hi);

  // outdated
  // loRes_highRes_join = VIPERS_maskr_hi[VIPERS_mask_lineNo_hi - 1];
  loRes_highRes_join = 8.5;
  
  //-- Low resolution counts --//
  inputfile = fopen(loRes_filepath, "r");

  // line_count(inputfile, &VIPERS_mask_lineNo_lo);
  linecount_header(inputfile, 1, &VIPERS_mask_lineNo_lo);
    
  VIPERS_maskr_lo        = realloc(VIPERS_maskr_lo, VIPERS_mask_lineNo_lo*sizeof(double));
    
  VIPERS_maskMono_lo     = realloc(VIPERS_maskMono_lo, VIPERS_mask_lineNo_lo*sizeof(double));
  VIPERS_maskQuad_lo     = realloc(VIPERS_maskQuad_lo, VIPERS_mask_lineNo_lo*sizeof(double));
  VIPERS_maskHex_lo      = realloc( VIPERS_maskHex_lo, VIPERS_mask_lineNo_lo*sizeof(double));
  VIPERS_maskOct_lo      = realloc( VIPERS_maskOct_lo, VIPERS_mask_lineNo_lo*sizeof(double));
  VIPERS_maskDec_lo      = realloc( VIPERS_maskDec_lo, VIPERS_mask_lineNo_lo*sizeof(double));
    
  VIPERS_maskMono2D_lo   = realloc(VIPERS_maskMono2D_lo, VIPERS_mask_lineNo_lo*sizeof(double));
  VIPERS_maskQuad2D_lo   = realloc(VIPERS_maskQuad2D_lo, VIPERS_mask_lineNo_lo*sizeof(double));
  VIPERS_maskHex2D_lo    = realloc( VIPERS_maskHex2D_lo, VIPERS_mask_lineNo_lo*sizeof(double));
  VIPERS_maskOct2D_lo    = realloc( VIPERS_maskOct2D_lo, VIPERS_mask_lineNo_lo*sizeof(double));
  VIPERS_maskDec2D_lo    = realloc( VIPERS_maskDec2D_lo, VIPERS_mask_lineNo_lo*sizeof(double));

  fgets(header, 200, inputfile); // skip header 
  
  for(j=0; j<VIPERS_mask_lineNo_lo; j++){  fscanf(inputfile, "%le \t %le \t %le \t %le \t %le \t %le \n", &VIPERS_maskr_lo[j], &VIPERS_maskMono_lo[j], &VIPERS_maskQuad_lo[j], &VIPERS_maskHex_lo[j], &VIPERS_maskOct_lo[j], &VIPERS_maskDec_lo[j]);
  }

  fclose(inputfile);

  for(j=0; j<VIPERS_mask_lineNo_lo; j++){
    VIPERS_maskMono_lo[j] /= pow(VIPERS_maskr_lo[j], 3.);
    VIPERS_maskQuad_lo[j] /= pow(VIPERS_maskr_lo[j], 3.);
    VIPERS_maskHex_lo[j]  /= pow(VIPERS_maskr_lo[j], 3.);
    VIPERS_maskOct_lo[j]  /= pow(VIPERS_maskr_lo[j], 3.);
    VIPERS_maskDec_lo[j]  /= pow(VIPERS_maskr_lo[j], 3.);
  }
    
  lowRes_amplitudeCalc(VIPERS_mask_lineNo_hi, VIPERS_mask_lineNo_lo, 8.,   9., VIPERS_maskr_hi, VIPERS_maskr_lo, VIPERS_maskMono_hi, VIPERS_maskMono_lo, &mask_monopolenorm_lo);
        
  for(j=0; j<VIPERS_mask_lineNo_lo; j++){
    VIPERS_maskMono_lo[j] *= mask_monopolenorm_lo;
    VIPERS_maskQuad_lo[j] *= mask_monopolenorm_lo;
    VIPERS_maskHex_lo[j]  *= mask_monopolenorm_lo;
    VIPERS_maskOct_lo[j]  *= mask_monopolenorm_lo;
    VIPERS_maskDec_lo[j]  *= mask_monopolenorm_lo;
  }
    
  spline(VIPERS_maskr_lo, VIPERS_maskMono_lo, VIPERS_mask_lineNo_lo, 1.0e31, 1.0e31, VIPERS_maskMono2D_lo);
  spline(VIPERS_maskr_lo, VIPERS_maskQuad_lo, VIPERS_mask_lineNo_lo, 1.0e31, 1.0e31, VIPERS_maskQuad2D_lo);
  spline(VIPERS_maskr_lo, VIPERS_maskHex_lo,  VIPERS_mask_lineNo_lo, 1.0e31, 1.0e31, VIPERS_maskHex2D_lo);
  spline(VIPERS_maskr_lo, VIPERS_maskOct_lo,  VIPERS_mask_lineNo_lo, 1.0e31, 1.0e31, VIPERS_maskOct2D_lo);
  spline(VIPERS_maskr_lo, VIPERS_maskDec_lo,  VIPERS_mask_lineNo_lo, 1.0e31, 1.0e31, VIPERS_maskDec2D_lo);
  
  print_windowCorrfn();  
    
  prepVIPERS_kSpaceMultipole(); // for integral constraint. 
  
  return 0;
}

int lowRes_amplitudeCalc(int Nhi, int Nlo, double rmin, double rmax, double rhi[], double rlo[], double Dhi[], double Dlo[], double* norm){
  // Least squares fit for amplitude factor of low resolution, between lo and high res in the range rmin to rmax.
  // e.g. lowRes_amplitudeCalc(VIPERS_mask_lineNo_hihi, VIPERS_mask_lineNo_hi, 1., 1.5, VIPERS_maskr_hihi, VIPERS_maskr_hi, VIPERS_maskMono_hihi, VIPERS_maskMono_hi, &mask_monopolenorm_hi);
  
  double sum_DiFi       = 0.0;
  double sum_FiFi       = 0.0;
        
  int index_hi, index_lo, ceiling;
    
  for(j=0; j<Nlo; j++){  
    if(rlo[j]>rmin){
      index_lo = j;
            
      break;
    } 
  }
    
  for(j=0; j<Nhi; j++){  
    if(rhi[j]>rmin){
      index_hi = j;
            
      break;
    } 
  }
        
  for(j=0; j<Nhi; j++){  
    if(rhi[j]>rmax){
      ceiling = j - 1;
            
      break;
    } 
  }
        
  for(j=0; j<Nhi; j++){    
    if((j+index_hi) < ceiling){
      // printf("\n%e \t %e \t %e \t %e", rhi[index_hi + j], rlo[index_lo + j], Dhi[index_hi + j], Dlo[index_lo + j]);   
            
      sum_DiFi     += Dlo[index_lo + j]*Dhi[index_hi + j];
            
      sum_FiFi     += Dlo[index_lo + j]*Dlo[index_lo + j];       
    }
  }
        
  // printf("\n\n%e \t %e", sum_DiFi, sum_FiFi);   
        
  *norm = sum_DiFi/sum_FiFi;

  return 0;
}


int flatSlope_amp(int N, double rmin, double rmax, double sign, double ri[], double Di[], double* norm){
  int goodN             =   0;
  double sum_Di         = 0.0;

  for(i=0; i<N; i++){                
    if((ri[i]>= rmin) && (ri[i] <= rmax) && (sign*Di[i] > 0.0)){
      goodN           +=     1;
        
      sum_Di          += Di[i];
    }
  }

  // amp for flat line through points is just the mean. 
  *norm = sum_Di/goodN;

  return 0;
}


int powerlaw_regression(int N, double rmin, double rmax, double sign, double ri[], double Di[], double* norm, double* index){
  // W    = A r^(n + 3.).
  // ln W = A' + n*log(r).
    
  // A'   = ln(A)
    
  double detA           = 0.0;
    
  // parameters.
  double Adash          = 0.0;
  double A              = 0.0;
  double n              = 0.0;
    
  double sum_lnri       = 0.0;
  double sum_lnri2      = 0.0;
  double sum_lnDi       = 0.0;
  double sum_lnDi_lnri  = 0.0;  
    
  double b1             = 0.0;
  double b2             = 0.0;
    
  int goodN             =   0;

  for(i=0; i<N; i++){                
    if((ri[i]>= rmin) && (ri[i] <= rmax) && (sign*Di[i] > 0.0)){
      goodN           += 1;
            
      // printf("\n%e \t %e", ri[i], sign*Di[i]);
            
      sum_lnri        += log(ri[i]);
      sum_lnri2       += log(ri[i])*log(ri[i]);
        
      sum_lnDi        += log(sign*Di[i]);
      sum_lnDi_lnri   += log(sign*Di[i])*log(ri[i]);
    }
  }
    
  // printf("\n\n%d good N", goodN);
    
  // For a matrix A, paramater vector (A', n)^T, and vector B
  // Required to invert AP  = B. 2x2 matrix inversion.
         	
  // A reads as (a b) for a = N, b = sum log(r_i), c = sum log(r_i), d = sum log(r_i)*log(r_i).
  //            (c d)        

  // and B    = (b1, b2)^T for b1 = sum[log(Di) - 3log(ri)], b2 = sum[ln(Di)*ln(ri) - 3ln(ri)^2]
     
  // det = ad - bc.
  detA   = goodN*sum_lnri2 - sum_lnri*sum_lnri;
      
  // (A', n)^T = (A^-1)B  = (1./detA)*( d*b1 - b*b2) 
  //                                  (-c*b1 + a*b2)
    
  b1    = sum_lnDi      - 3.*sum_lnri;
  b2    = sum_lnDi_lnri - 3.*sum_lnri2;
     
  Adash = pow(detA, -1.)*(sum_lnri2*b1 - sum_lnri*b2); 
    
  A     = exp(Adash);
    
  n     = pow(detA, -1.)*(-sum_lnri*b1 + goodN*b2); 
    
  // printf("\n\nPower law regression: %e \t %e", sign*A, n);
    
  *norm = sign*A;

  *index = n;

  return 0;
}


int print_windowCorrfn(){
  double r;
  char   outputpath[200];
  
  double maxlog   = log10(4000.);
  double zerolog  = log10(0.001);
  double logbinsz = log10(1.050);

  int    nbins    = (int) ceil((maxlog - zerolog)/logbinsz);

  
  sprintf(outputpath, "%s_mixedRes_hex.dat", filepath);

  output = fopen(outputpath, "w");

  for(j=0; j<nbins; j++){
    r = pow(10., zerolog + j*logbinsz);

    fprintf(output, "%.6lf \t %.6lf \t %.6lf \t %.6lf \t %.6lf \t %.6lf \n", r,  splint_VIPERS_maskMono(r), splint_VIPERS_maskQuad(r), splint_VIPERS_maskHex(r),
                                                                                                             splint_VIPERS_maskOct(r), splint_VIPERS_maskDec(r));
  }

  fclose(output);

  return 0;
}
