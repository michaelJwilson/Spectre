int header(){
  // was defined in header.h
  double       xcentre;
  double       ycentre;
  double       zcentre;

  double       xroll;
  double       yroll;
  double       zroll;
  
  return 0;
}


int sphereCentre(){
    const gsl_rng_type* T;
    gsl_rng*            r;
    
    gsl_rng_env_setup();
    
    T = gsl_rng_default;
    r = gsl_rng_alloc(T);
    
    // Generate random x, y, z co-ordinates for the sphere centre.  Use periodicity of box to roll the co-ordinates
    // such that the sphere lies in the centre of the new co-ordinate system. 
    
    xcentre       = (AxisLimsArray[1][0] - AxisLimsArray[0][0])*gsl_rng_uniform(r);
    ycentre       = (AxisLimsArray[1][1] - AxisLimsArray[0][1])*gsl_rng_uniform(r);
    zcentre       = (AxisLimsArray[1][2] - AxisLimsArray[0][2])*gsl_rng_uniform(r);
        
    xroll         = -1.*(xcentre - 0.5*(AxisLimsArray[1][0] - AxisLimsArray[0][0]));
    yroll         = -1.*(ycentre - 0.5*(AxisLimsArray[1][1] - AxisLimsArray[0][1]));
    zroll         = -1.*(zcentre - 0.5*(AxisLimsArray[1][2] - AxisLimsArray[0][2]));
    
    gsl_rng_free(r);

    return 0;
}


int rollcube(double xCoor[], double yCoor[], double zCoor[], int galNumber){
    sphereCentre();
    
    for(j=0; j<galNumber; j++){
        xCoor[j] += xroll;
    
        if(xCoor[j] > AxisLimsArray[1][0]) xCoor[j] -= (AxisLimsArray[1][0] - AxisLimsArray[0][0]);
        if(xCoor[j] < AxisLimsArray[0][0]) xCoor[j] += (AxisLimsArray[1][0] - AxisLimsArray[0][0]);
    
        yCoor[j] += yroll;
        
        if(yCoor[j] > AxisLimsArray[1][1]) yCoor[j] -= (AxisLimsArray[1][1] - AxisLimsArray[0][1]);
        if(yCoor[j] < AxisLimsArray[0][1]) yCoor[j] += (AxisLimsArray[1][1] - AxisLimsArray[0][1]);
    
        zCoor[j] += zroll;
        
        if(zCoor[j] > AxisLimsArray[1][0]) zCoor[j] -= (AxisLimsArray[1][2] - AxisLimsArray[0][2]);
        if(zCoor[j] < AxisLimsArray[0][2]) zCoor[j] += (AxisLimsArray[1][2] - AxisLimsArray[0][2]);
    
    }

    return 0;
}


int rollxyz(double xdist, double ydist, double zdist, double xii[], double yii[], double zii[], int galNumber){
    for(j=0; j<galNumber; j++){
        xii[j] += xdist;
    
        if(xii[j] > AxisLimsArray[1][0]) xii[j] -= (AxisLimsArray[1][0] - AxisLimsArray[0][0]);
        if(xii[j] < AxisLimsArray[0][0]) xii[j] += (AxisLimsArray[1][0] - AxisLimsArray[0][0]);
    
        yii[j] += ydist;
        
        if(yii[j] > AxisLimsArray[1][1]) yii[j] -= (AxisLimsArray[1][1] - AxisLimsArray[0][1]);
        if(yii[j] < AxisLimsArray[0][1]) yii[j] += (AxisLimsArray[1][1] - AxisLimsArray[0][1]);
        
        zii[j] += zdist;
        
        if(zii[j] > AxisLimsArray[1][1]) zii[j] -= (AxisLimsArray[1][1] - AxisLimsArray[0][1]);
        if(zii[j] < AxisLimsArray[0][1]) zii[j] += (AxisLimsArray[1][1] - AxisLimsArray[0][1]);
    }

    return 0;
}

double signum(double abscissa){
    if(abscissa >= 0.0){  
        return  1.0;
    }
    
    else{
        return -1.0;
    }
}

