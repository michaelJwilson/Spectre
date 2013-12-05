int NGPCalc(){
    ApplyJenkins();
    
    CountGalaxies();
    
    overdensity_ImperfectSelectionTracer();
    
    printSurveyDetails();
    return 0;
}


int NGPCalcCube(){
    ApplyJenkins();
    
    CountGalaxiesCube();
    
    overdensity_volumeLimitedTracer();    
    
    printSurveyDetails();
    return 0;
}


int CalculateCell_raDecRotated(){
    float xCell, yCell, zCell;
    float rCell;

    float raCell, polarCell, decCell;

    for(k=0; k<n0; k++){
        for(j=0; j<n1; j++){
            for(i=0; i<n2; i++){
	           xCell      = AxisLimsArray[0][0] + CellSize*(i+0.5);
	           yCell      = AxisLimsArray[0][1] + CellSize*(j+0.5);
	           zCell      = AxisLimsArray[0][2] + CellSize*(k+0.5);

                Index     = k*n1*n2 + j*n2 + i;

                Cell_rotatedXvals[Index] = xCell;
                Cell_rotatedYvals[Index] = yCell;
                Cell_rotatedZvals[Index] = zCell;
            }
        }
    }
    
    Celestialbasis(34.5, -5.10, Cell_rotatedXvals, Cell_rotatedYvals, Cell_rotatedZvals, n0*n1*n2);

    for(k=0; k<n0; k++){
        for(j=0; j<n1; j++){
            for(i=0; i<n2; i++){
                Index       = k*n1*n2 + j*n2 + i;

                xCell       = Cell_rotatedXvals[Index];
                yCell       = Cell_rotatedYvals[Index];
                zCell       = Cell_rotatedZvals[Index]; 

                rCell       = pow(xCell*xCell + yCell*yCell + zCell*zCell, 0.5);     
		
                // acos returns radians, argument must be in the range -1 to 1. Returned value is between 0 and pi inclusive. 

                polarCell   = acos(zCell/rCell);

                // radians. 
                decCell     = pi/2. - polarCell;

                // returns the arc tangent in radians of y/x based on the signs of both values to determine the correct quadrant. both x and y cannot be zero, returned value is in the range !-pi to pi!
                raCell      = atan2(yCell, xCell);

                if(raCell < 0.0){
                    // right ascension in the range [0, 2*pi]
                    raCell += 2.*pi;
                }

                // conversion to degrees. 
                decCell    *= 180./pi;
                raCell     *= 180./pi;

                // right ascension in degrees.
	            Cell_raVIPERSsystem[Index]  = raCell;
		
                // declination in degrees.
                Cell_decVIPERSsystem[Index] = decCell;
            }
        }
    }

    printf("\n%f \t %f", arrayMin(Cell_raVIPERSsystem,  n0*n1*n2), arrayMax(Cell_raVIPERSsystem, n0*n1*n2));
    printf("\n%f \t %f", arrayMin(Cell_decVIPERSsystem, n0*n1*n2), arrayMax(Cell_decVIPERSsystem, n0*n1*n2));
    
    sprintf(filepath, "%s/Data/ra_decCells/ra_dec_degs.dat", root_dir);
    output = fopen(filepath, "wb");
 
    fwrite(Cell_raVIPERSsystem, sizeof(float), n0*n1*n2, output);
    fwrite(Cell_decVIPERSsystem, sizeof(float), n0*n1*n2, output);
    fclose(output);

    sprintf(filepath, "%s/Data/ra_decCells/ra_dec_wght_degs.dat", root_dir);
    inputfile = fopen(filepath, "rb");

    fread(Cell_raVIPERSsystem,  sizeof(float), n0*n1*n2, inputfile);
    fread(Cell_decVIPERSsystem, sizeof(float), n0*n1*n2, inputfile);
    fread(Cell_VIPERSweights,   sizeof(float), n0*n1*n2, inputfile);

    for(j=0; j<40; j++) printf("\n %f \t %f \t %f", Cell_raVIPERSsystem[j], Cell_decVIPERSsystem[j], Cell_VIPERSweights[j]);
    fclose(inputfile);

    return 0;
}


int boxCoordinates(int rowNumber){
    xlabel                  = (int) floor((xCoor[rowNumber] - AxisLimsArray[0][0])/CellSize);    ylabel                  = (int) floor((yCoor[rowNumber] - AxisLimsArray[0][1])/CellSize);
    zlabel                  = (int) floor((zCoor[rowNumber] - AxisLimsArray[0][2])/CellSize);
    boxlabel                = (int)                        xlabel + n2*ylabel + n2*n1*zlabel;

    return boxlabel;
}


int CountGalaxies(){
    // Impose redshift and absolute magnitude cuts for a volume limited, VIPERS like survey between 0.7 and 0.9.  Window fn defined by booldensity as generated by randoms.

    for(j=0; j<Vipers_Num; j++){
        boxlabel = boxCoordinates(j);
            
        if((zcos[j] > redshiftLowLimit) && (zcos[j] < redshiftHiLimit) && (M_B[j] < absMagCut) && (booldensity[boxlabel] > 0.1)){ 
		    densityArray[boxlabel] += 1;
		}
    }

    TotalZADEWeight = SumDoubleArray(densityArray);

    return 0;
}


int CountGalaxiesCube(){
    // Cubic run, perhaps to which a window fn. is to be applied. 

    for(j=0; j<Vipers_Num; j++){
        boxlabel = boxCoordinates(j);

        if(booldensity[boxlabel] > 0.1){ 
		    densityArray[boxlabel] += 1;
	    }
    }
    
    TotalZADEWeight = SumDoubleArray(densityArray);
    
    return 0;
}


int overdensity_volumeLimitedTracer(){
    MeanNumberDensity = TotalZADEWeight/TotalSurveyedVolume;

    for(j=0; j<n0*n1*n2; j++)  densityArray[j] /= CellVolume*MeanNumberDensity;
    for(j=0; j<n0*n1*n2; j++)  densityArray[j] -= 1.0;

    return 0;
}


int overdensity_ImperfectSelectionTracer(){
    MeanNumberDensity = TotalZADEWeight/TotalSurveyedVolume;

    printf("\nNumber density interpolated at z=0.8:  %f", interp_nz(interp_comovingDistance(0.8)));
    
    fkpShotNoiseCorr = 0.0;

    for(k=0; k<n0; k++){
        for(j=0; j<n1; j++){ 
            for(i=0; i<n2; i++){
                Index                         = k*n1*n2 + j*n2 + i; 
            
                Chi                           = CellSize*pow(k*k + j*j + i*i, 0.5);
                
                if(densityArray[Index] > 0){
                    fkpShotNoiseCorr         += pow(TotalFKPweight, -2.)*pow(CellVolume, -1.)*pow(FKPweights[Index], 2.)/interp_nz(Chi);
                }
    
                densityArray[Index]          /= CellVolume*interp_nz(Chi);
                densityArray[Index]          -= 1.0;
            }
        }
    }
    
    printf("\n\nFKP shot noise P(k) expectation:            %e", fkpShotNoiseCorr);
    printf("\nFKP unweighted shot noise P(k) expectation:   %e", 1./TotalZADEWeight);

    return 0;
}


int printSurveyDetails(){
    printf("\n\nTotal ZADE weight: %e.", TotalZADEWeight);
    printf("\nCell volume:  %f.",        CellVolume); 
    printf("\nMean number density:  %f", MeanNumberDensity);    
    printf("\n\nNon-empty cells:  %e  [n0*n1*n2]", SumOfBoolDensity/(n0*n1*n2));
    printf("\n\nTotal surveyed volume: %e    [TotalVolume]", (float) TotalSurveyedVolume/TotalVolume);
    return 0;
}


double SumDoubleArray(double array[]){
    double Interim = 0.0;

    for(j=0; j<n0*n1*n2; j++){
        Interim += array[j];
    }

    return Interim;
}
