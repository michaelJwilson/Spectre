'''
data = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Del2k/midK_Del2k_zCube_Jenkins1.0_kInterval_0.01_000.dat')
pl.loglog(data[:,0], data[:,2], 'k', label='no thres.')

data = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Del2k/midK_Del2k_zCube_Clipped_10.0_Jenkins1.0_kInterval_0.01_000.dat')
pl.loglog(data[:,0], data[:,2], 'c', label='10.0 thres.')

data = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Del2k/midK_Del2k_zCube_Clipped_7.0_Jenkins1.0_kInterval_0.01_000.dat')
pl.loglog(data[:,0], data[:,2], 'm', label='7.0 thres.')

data = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Del2k/midK_Del2k_zCube_Clipped_5.0_Jenkins1.0_kInterval_0.01_000.dat')
pl.loglog(data[:,0], data[:,2], 'g', label='5.0 thres.')

data = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Del2k/midK_Del2k_zCube_Clipped_3.0_Jenkins1.0_kInterval_0.01_000.dat')
pl.loglog(data[:,0], data[:,2], 'b', label='3.0 thres.')

data = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Del2k/midK_Del2k_zCube_Clipped_2.0_Jenkins1.0_kInterval_0.01_000.dat')
pl.loglog(data[:,0], data[:,2], 'r', label='2.0 thres.')
'''

data = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Multipoles/Multipoles_zCube_Jenkins1.0_kbin_0.010_000.dat')
pl.loglog(data[:,0], data[:,2], 'k', markersize='2')

data = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Multipoles/Multipoles_zCube_Clipped_10.0_Jenkins1.0_kbin_0.010_000.dat')
pl.loglog(data[:,0], data[:,2], 'c', markersize='2')

data = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Multipoles/Multipoles_zCube_Clipped_7.0_Jenkins1.0_kbin_0.010_000.dat')
pl.loglog(data[:,0], data[:,2], 'm', markersize='2')

data = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Multipoles/Multipoles_zCube_Clipped_5.0_Jenkins1.0_kbin_0.010_000.dat')
pl.loglog(data[:,0], data[:,2], 'g', markersize='2')

data = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Multipoles/Multipoles_zCube_Clipped_3.0_Jenkins1.0_kbin_0.010_000.dat')
pl.loglog(data[:,0], data[:,2], 'b', markersize='2')

data = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Multipoles/Multipoles_zCube_Clipped_2.0_Jenkins1.0_kbin_0.010_000.dat')
pl.loglog(data[:,0], data[:,2], 'r', markersize='2')

pl.xlim([0.01, 1.0]) 
pl.ylim([10**1., 10**5])

pl.ylabel(r'$P(k)$', fontsize = '10')
pl.xlabel(r'$k \ [h \ Mpc^{-1}]$', fontsize = '10')

leg = pl.legend(loc=1, ncol=1, prop = FontProperties(size = '10'))
leg.draw_frame(False)

xx, locs = plt.xticks()
ll = ['%.3f' % a for a in xx]
plt.gca().xaxis.set_major_formatter(FixedFormatter(ll))

pl.savefig('/disk1/mjw/HOD_MockRun/Plots/zCube_Pk_thresDependence_2.pdf')
'''
pl.clf()

pl.xlim([0.01, 1.0]) 


pl.ylabel(r'$P(k)$', fontsize = '10')
pl.xlabel(r'$k \ [h \ Mpc^{-1}]$', fontsize = '10')

xx, locs = plt.xticks()
ll = ['%.3f' % a for a in xx]
plt.gca().xaxis.set_major_formatter(FixedFormatter(ll))

data = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Multipoles/Multipoles_zCube_Jenkins1.0_kbin_0.010_000.dat')
pl.loglog(data[:,0], data[:,2]/data[:,1], 'k', markersize='2', label='no clip.')

data = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Multipoles/Multipoles_zCube_Clipped_10.0_Jenkins1.0_kbin_0.010_000.dat')
pl.loglog(data[:,0], data[:,2]/data[:,1], 'c', markersize='2', label='10.')

data = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Multipoles/Multipoles_zCube_Clipped_7.0_Jenkins1.0_kbin_0.010_000.dat')
pl.loglog(data[:,0], data[:,2]/data[:,1], 'm', markersize='2', label='7.')

data = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Multipoles/Multipoles_zCube_Clipped_5.0_Jenkins1.0_kbin_0.010_000.dat')
pl.loglog(data[:,0], data[:,2]/data[:,1], 'g', markersize='2', label= '5.')

data = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Multipoles/Multipoles_zCube_Clipped_3.0_Jenkins1.0_kbin_0.010_000.dat')
pl.loglog(data[:,0], data[:,2]/data[:,1], 'b', markersize='2', label='3.')

data = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Multipoles/Multipoles_zCube_Clipped_2.0_Jenkins1.0_kbin_0.010_000.dat')
pl.loglog(data[:,0], data[:,2]/data[:,1], 'r', markersize='2', label='2.')



linearBias = 1.495903

beta       = 0.54  

KaiserMono =  1. + (2./3.)*beta + 0.2*beta*beta
KaiserQuad = (4./3.)*beta + (4./7.)*beta*beta

pl.loglog(data[:,0], np.ones(len(data[:,0]))*KaiserQuad/KaiserMono,  'k-.', label=r'$\beta = 0.54$')


beta       = 0.41  

KaiserMono =  1. + (2./3.)*beta + 0.2*beta*beta
KaiserQuad = (4./3.)*beta + (4./7.)*beta*beta

pl.loglog(data[:,0], np.ones(len(data[:,0]))*KaiserQuad/KaiserMono,  'g-.', label=r'$\beta = 0.41$')

data = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Multipoles/KaiserLorentzMultipoles_Pk_Linear_-20.0_beta_0.41_velDispersion_2.90.dat')
pl.loglog(data[:,0], data[:,3]/data[:,2], 'g-.')

data = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Multipoles/KaiserLorentzMultipoles_Pk_Linear_-20.0_beta_0.45_velDispersion_2.40.dat')
pl.loglog(data[:,0], data[:,3]/data[:,2], 'r-.', label=r'$\beta=0.45, \sigma=2.1$')

data = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Multipoles/KaiserLorentzMultipoles_Pk_Linear_-20.0_beta_0.45_velDispersion_2.70.dat')
pl.loglog(data[:,0], data[:,3]/data[:,2], 'c-.', label=r'$\beta=0.45, \sigma=2.7$')

pl.ylim(10**-3., 2.)

leg = pl.legend(loc=3, ncol=1, prop = FontProperties(size = '10'))
leg.draw_frame(False)

pl.savefig('/disk1/mjw/HOD_MockRun/Plots/zCube_Quad2Mono.pdf')
'''
