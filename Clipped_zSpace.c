int clipDensity(float threshold){

    printf("\n\nTaking a machete to the density field.");

    for(j=0; j<n0*n1*n2; j++){
      if(densityArray[j] > threshold)  densityArray[j] = threshold;
    }
    
    return 0;
}


int inputPK(){
    // Interpolated theoretical P(k) on a regular grid in k. 
    sdltk  = (float *) realloc(sdltk,          294*sizeof(*sdltk));
    sdltPk = (float *) realloc(sdltPk,         294*sizeof(*sdltPk));
              
    // Second derivates of HOD P(k) for cubic spline.           
    sdlt2d = (float *) realloc(sdlt2d,         294*sizeof(*sdlt2d));

    sprintf(filepath, "%s/Data/HODTheoryPk/cambExtendedPk_hod_20.0.dat", root_dir);
    inputfile = fopen(filepath, "r");
    for(j=1; j<294; j++) fscanf(inputfile, "%f\t%f\n", &sdltk[j], &sdltPk[j]);
    fclose(inputfile);
    
    spline(sdltk, sdltPk, 293, 1.0e31, 1.0e31, sdlt2d);
    return 0;
}


int inputLinearPk(){
    // Interpolated theoretical P(k) on a regular grid in k. 
    lineark  = (float *) realloc(lineark,          471*sizeof(*lineark));
    linearPk = (float *) realloc(linearPk,         471*sizeof(*linearPk));
              
    // Second derivates of HOD P(k) for cubic spline.           
    linear2d = (float *) realloc(linear2d,         471*sizeof(*linear2d));

    sprintf(filepath, "%s/Data/HODTheoryPk/LinearPk.dat", root_dir);
    inputfile = fopen(filepath, "r");
    for(j=1; j<471; j++) fscanf(inputfile, "%f\t%f\n", &lineark[j], &linearPk[j]);
    fclose(inputfile);
    
    spline(lineark, linearPk, 470, 1.0e31, 1.0e31, linear2d);
    
    return 0;
}


int formPkCube(){
    PkCube             = (double *) realloc(PkCube,          n0*n1*n2*sizeof(*PkCube));

    hz                 = pow(Om_v + Om_m*pow(1. + 0.8, 3.), 0.5);  // Units of h, [h]
 
    Om_mz              = Om_m*pow(1. + 0.8, 3.)/pow(hz, 2.);
    
    f                  = pow(Om_mz, gamma_GR);

    beta               = f/linearBias;

    velocityDispersion = pow(3./sqrt(2.), 2.);                  // units of h^-1 Mpc rather than 300 km s^-1

    // Take line of sight wavevector to be (1, 0, 0), i.e unit vector along kx. 

    float PkCubeEntry;

    for(k=0; k<n0; k++){
        for(j=0; j<n1; j++){
            for(i=0; i<n2; i++){
                k_x = kIntervalx*i;
                k_y = kIntervaly*j;
                k_z = kIntervalz*k;

                if(k_x>NyquistWaveNumber)  k_x    -= n2*kIntervalx;
                if(k_y>NyquistWaveNumber)  k_y    -= n1*kIntervaly;
                if(k_z>NyquistWaveNumber)  k_z    -= n0*kIntervalz;

                Index                              = k*n1*n2 + j*n2 + i;

                kmodulus                           = pow(pow(k_x, 2.) + pow(k_y, 2.) + pow(k_z, 2.), 0.5);

		        // Interpolates the CAMB P(k).
                splint(lineark, linearPk, linear2d, 470, kmodulus, &PkCubeEntry);
                
                PkCube[Index]                      = (double) PkCubeEntry;
  
                // Convert from CAMB units for P(k), [P_CAMB] = Volume, to [P(k)] dimensionless.
                PkCube[Index]                     *= linearBias*linearBias/TotalVolume;

                // Impose spherical filter to calculate sigma_8.
                /*
                y                                  = kmodulus*8.;  

                if(kmodulus != 0.0){                
                    PkCube[Index]                 *= 3.*pow(y, -3.)*(sin(y) - y*cos(y));
                    PkCube[Index]                 *= 3.*pow(y, -3.)*(sin(y) - y*cos(y));
                }
                */
                
                mu                                 = k_x/kmodulus;
                if(kmodulus < 0.000001)       mu   = 0.0;      
                
                kaiserFactor                       = pow(1. + beta*mu*mu, 2.);
                
                PkCube[Index]                     *= kaiserFactor;
                
                // Lorentzian factor for non-linear redshift space distortions. 
                // PkCube[Index]                     /= 1. + pow(kmodulus*mu, 2.)*velocityDispersion;
                
                TwoDpkArray[Index][0]              = fabs(k_x); // Line of sight wavevector. 
                TwoDpkArray[Index][1]              = pow(k_y*k_y + k_z*k_z, 0.5);
                
                // For calculation of the quadrupole.
                // legendre2weights[Index]            = gsl_sf_legendre_P2((double) mu);
            }
        }
    }
    
    return 0;
}


float HermitePolynomial(float x, int n){
    switch(n){
        case 0:
            return 1.0;
        case 1:
            return 2.0*x;
        case 2:
            return 4.0*powf(x, 2.0)   - 2.0;
        case 3:
            return 8.0*powf(x, 3.0)   - 12.0*x;
        case 4:
            return 16.0*powf(x, 4.0)  - 48.*powf(x, 2.0)   + 12.;
        case 5:
            return 32.0*powf(x, 5.0)  - 160.*powf(x, 3.0)  + 120.*x;
        case 6:
            return 64.0*powf(x, 6.0)  - 480.*powf(x, 4.0)  + 720.*powf(x, 2.0)   - 120.;
        case 7:
            return 128.0*powf(x, 7.0) - 1344.*powf(x, 5.0) + 3360.*powf(x, 3.0)  - 1680.*x;
        case 8:
            return 256.*powf(x, 8.)   - 3584.*powf(x, 6.)  + 13440.*powf(x, 4.)  - 13440.*powf(x, 2.)  + 1680.;
        case 9:
            return 512.*powf(x, 9.)   - 9216.*powf(x, 7.)  + 48384.*powf(x, 5.)  - 80640.*powf(x, 3.0) + 30240.*x;
        case 10:
            return 1024.*powf(x, 10.) - 23040.*powf(x, 8.) + 161280.*powf(x, 6.) - 403200.*powf(x, 4.) + 302400.*powf(x, 2.0) - 30240.;   
    }
}


float C_n(float x, int n){                                                // (n+1)! = Gamma (n+2)
    return pow(HermitePolynomial(x, n-1), 2.)*exp(-2.*x*x)/(pi*pow(2., n)*gsl_sf_gamma(n + 2));
}


int clipCorrfn(){
    Corrfn            = (double *) realloc(Corrfn,             n0*n1*n2*sizeof(*Corrfn));
    suppressedCorrfn  = (double *) realloc(suppressedCorrfn,   n0*n1*n2*sizeof(*suppressedCorrfn));
    distortedCorrfn   = (double *) realloc(distortedCorrfn,    n0*n1*n2*sizeof(*distortedCorrfn));
    clippedPk         = (double *) realloc(clippedPk,          n0*n1*n2*sizeof(*clippedPk));

    for(j=0; j<n0*n1*n2; j++) in[j][0] = (double) PkCube[j];
    for(j=0; j<n0*n1*n2; j++) in[j][1] = (double) 0.0;
   
    printf("\nPerforming FFT.");
    
    fftw_execute(p);

    for(j=0; j<n0*n1*n2; j++) Corrfn[j] = out[j][0];

    float variance    =  Corrfn[0];
    float u0;

    u0      = inverse_erf(2.*sqrt(A11) -1.);
    
    printf("\nu0 estimated  from suppression factor:  %f", u0);
    
    for(j=0; j<n0*n1*n2; j++) suppressedCorrfn[j]      = 0.25*pow(1.0 + gsl_sf_erf(u0), 2.)*Corrfn[j]; 
    for(j=0; j<n0*n1*n2; j++) distortedCorrfn[j]       = suppressedCorrfn[j]; 
    
    for(i=1; i<10; i++){
                                 distortedCorrfn[0]   += variance*C_n(u0, i);
      for(j=1; j<n0*n1*n2; j++)  distortedCorrfn[j]   += variance*pow(Corrfn[j]/variance, i + 1)*C_n(u0, i);
    }
    
    iplan   = fftw_plan_dft_3d(n0, n1, n2, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
    
    for(j=0; j<n0*n1*n2; j++) in[j][0] = distortedCorrfn[j]/A11;
    for(j=0; j<n0*n1*n2; j++) in[j][1] = 0.0;
    
    fftw_execute(iplan);

    for(j=0; j<n0*n1*n2; j++) clippedPk[j] = pow(n0*n1*n2, -1.)*out[j][0];

    printf("\n\nClipped P(k).");
     
    return 0;    
}


int Theory2Dpk(){
    for(j=0; j<n0*n1*n2; j++) TwoDpkArray[j][2] =  PkCube[j];

    TwoDpkBinningCalc();

    sprintf(filepath, "%s/Data/ClippedPk/zSpace/2Dpk/2D_kaiser.dat", root_dir);
    output = fopen(filepath, "w");

    for(j=0; j<kBinNumb-1; j++){
        for(k=0; k<kBinNumb-1; k++){
            if(zSpacemodesPerBin[j][k] != 0)  fprintf(output, "%g \t %g \t %g \t %d \n", mean_perpk[j][k], mean_losk[j][k], zSpaceBinnedPk[j][k], zSpacemodesPerBin[j][k]);
        }
    }

    fclose(output);

    return 0;
}


int Observed2Dpk(){
    printf("\n\nAssigning FFT in array.");
    
    // Including the normalisation of the mask, TotalVolume/TotalSurveyedVolume, such that the filter fn. has unit mean."
    for(j=0; j<n0*n1*n2; j++) in[j][0] = densityArray[j]*FKPweights[j]*(TotalVolume/TotalSurveyedVolume)*booldensity[j];
    for(j=0; j<n0*n1*n2; j++) in[j][1] = 0.0;
    
    printf("\nPerforming FFT.");
    
    fftw_execute(p);
    
    printf("\nFFT complete.");
    
    // 0: Subtract shot noise for a real survey, 1: Neglect shot noise subtraction for FFT of window function. 
    PkCorrections(0);
    
    for(k=0; k<n0; k++){
        for(j=0; j<n1; j++){
            for(i=0; i<n2; i++){
                k_x = kIntervalx*i;
                k_y = kIntervaly*j;
                k_z = kIntervalz*k;

                if(k_x>NyquistWaveNumber)  k_x    -= n2*kIntervalx;
                if(k_y>NyquistWaveNumber)  k_y    -= n1*kIntervaly;
                if(k_z>NyquistWaveNumber)  k_z    -= n0*kIntervalz;

                Index                              = k*n1*n2 + j*n2 + i;

                kmodulus                           = pow(pow(k_x, 2.) + pow(k_y, 2.) + pow(k_z, 2.), 0.5);
    
                TwoDpkArray[Index][0]              = fabs(k_x);                      // Line of sight wavevector. 
                TwoDpkArray[Index][1]              = pow(k_y*k_y + k_z*k_z, 0.5);    // perpendicular wavevector.
                TwoDpkArray[Index][2]              = PkArray[Index][1]/A11;
            }
        }
    }

    TwoDpkBinningCalc();

    sprintf(filepath, "%s/Data/ClippedPk/zSpace/2Dpk/Observed2Dpk_%s.dat", root_dir, surveyType);
    output = fopen(filepath, "w");

    for(j=0; j<kBinNumb-1; j++){
        for(k=0; k<kBinNumb-1; k++){
            if(zSpacemodesPerBin[j][k] != 0)  fprintf(output, "%g \t %g \t %g \t %d \n", mean_perpk[j][k], mean_losk[j][k], TotalVolume*zSpaceBinnedPk[j][k], zSpacemodesPerBin[j][k]);
        }
    }

    fclose(output);

    return 0;
}
