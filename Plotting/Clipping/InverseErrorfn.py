results = np.loadtxt('/disk1/mjw/HOD_MockRun/Data/ClippedPk/InvErrorfnTest.dat')

pl.plot(results[:,0], results[:,1])

pl.savefig('/disk1/mjw/HOD_MockRun/Plots/Clipping/InvErrorfn.pdf')
