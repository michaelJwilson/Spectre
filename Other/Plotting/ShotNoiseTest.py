pl.clf()

# cnst number density = 10.0

MockCat      = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Del2k/midK_Del2k_ShotNoiseTest_GaussSmoothMockAvgNz_100.0_SkinDepth_5.0_001.dat') #
MockCat      = MockCat[:,2]

for i in xrange(2, 10, 1):
    MockIn   = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Del2k/midK_Del2k_ShotNoiseTest_GaussSmoothMockAvgNz_100.0_SkinDepth_5.0_00'+str(i)+'.dat')
    MockCat  = np.vstack((MockIn[:,2], MockCat))

for i in xrange(10, 27, 1):
    MockIn   = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Del2k/midK_Del2k_ShotNoiseTest_GaussSmoothMockAvgNz_100.0_SkinDepth_5.0_0'+str(i)+'.dat')
    MockCat  = np.vstack((MockIn[:,2], MockCat))

kvals        = MockIn[:,0]  

Mean         = np.mean(MockCat, axis=0)
Var          = np.var(MockCat,  axis=0)

pl.errorbar(kvals[1:], Mean[1:], np.sqrt(Var[1:])/np.sqrt(26), c='c', fmt='--', label='Shot noise limit, mock 001 <n(z)>')

# varying number density, corresponding to n(z) measured in mock 001.

MockCat      = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Del2k/midK_Del2k_ShotNoiseTestVaryingNz_GaussSmoothMockAvgNz_100.0_SkinDepth_5.0_001.dat') #
MockCat      = MockCat[:,2]

for i in xrange(2, 10, 1):
    MockIn   = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Del2k/midK_Del2k_ShotNoiseTestVaryingNz_GaussSmoothMockAvgNz_100.0_SkinDepth_5.0_00'+str(i)+'.dat')
    MockCat  = np.vstack((MockIn[:,2], MockCat))

for i in xrange(10, 27, 1):
    MockIn   = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/Del2k/midK_Del2k_ShotNoiseTestVaryingNz_GaussSmoothMockAvgNz_100.0_SkinDepth_5.0_0'+str(i)+'.dat')
    MockCat  = np.vstack((MockIn[:,2], MockCat))

kvals        = MockIn[:,0]  

Mean         = np.mean(MockCat, axis=0)
Var          = np.var(MockCat,  axis=0)

pl.errorbar(kvals[1:], Mean[1:], np.sqrt(Var[1:])/np.sqrt(26), c='g', fmt='--', label='mock 001 true n(z)')


# cnst mean number density
cnstShot = 123.5938
pl.plot(kvals[1:], np.ones(len(kvals[1:]))*cnstShot, 'k--')

# varying number density, shot noise prediction.
cnstShot = 146.328
pl.plot(kvals[1:], np.ones(len(kvals[1:]))*cnstShot, 'k')

# pl.yscale('log')
pl.xscale('log')

pl.xlim([0.07, 0.9])
pl.ylim([115, 160])

pl.ylabel(r'$P(k)$', fontsize = '10')
pl.xlabel(r'$k \ [h \ Mpc^{-1}]$', fontsize = '10')
pl.title('Shot noise expectation. 26 mock avg.')

leg = pl.legend(loc=1, ncol=1, prop = FontProperties(size = '10'))
leg.draw_frame(False)

xx, locs = plt.xticks()
ll = ['%.3f' % a for a in xx]
plt.gca().xaxis.set_major_formatter(FixedFormatter(ll))

pl.savefig('/disk1/mjw/HOD_MockRun/Plots/ShotNoiseTest.pdf')
