import matplotlib.pylab        as plt
import matplotlib.pyplot
from   matplotlib.font_manager import FontProperties
from   matplotlib.ticker       import ScalarFormatter
from   matplotlib.ticker       import FixedFormatter
import pylab                   as pl
import numpy                   as np
import math

formatter = ScalarFormatter(useMathText=True)
#formatter.set_scientific(True)
#formatter.set_powerlimits((-3,3))

fig_width_pt = 246.0*2 # Get this from LaTex using \the\columnwidth
inches_per_pt = 1.0/72.27
golden_mean = (np.sqrt(5)-1.0)/2.0
fig_width  = 2.*fig_width_pt*inches_per_pt # width in inches
fig_height = fig_width*golden_mean # height in inches
fig_size = [fig_width, fig_height]
params = {'axes.labelsize':14,
          'text.fontsize':8,
          'legend.fontsize':14,
          'xtick.labelsize':12.0,
          'ytick.labelsize':12.0,
          'figure.figsize':fig_size,
          'font.family': 'serif'}

pl.rcParams.update(params)
pl.clf()
pl.figure()
fig = pl.figure()
axes = pl.Axes(fig, [.2, .2, .7, .7])
fig.add_axes(axes)
axes.yaxis.set_major_formatter(formatter)

data = np.loadtxt('/disk1/mjw/FastLegendre/multipole_moments.dat')
data = np.abs(data)

ppk  = np.loadtxt('/disk1/mjw/FastLegendre/PR.dat')
ppk  = np.abs(ppk) 
pk   = ppk[:,1]

data[:,0] *= 2.

for i in xrange(1, 40, 1):
  pl.loglog(data[:,0], data[:,i], 'k-')

pl.loglog(data[:,0], ppk[:,2], 'k^', markersize=2)
pl.loglog(data[:,0], ppk[:,3], 'k^', markersize=2)
pl.loglog(data[:,0], ppk[:,4], 'k^', markersize=2)
pl.loglog(data[:,0], ppk[:,5], 'k^', markersize=2)

pl.xlabel(r'$k \sigma$')
pl.ylabel(r'$P(k)$')

pl.xlim(0.01, 100.)
pl.ylim(10.**-6., 5.)

pl.savefig('/disk1/mjw/FastLegendre/multipoles_pk.pdf')

pl.clf()

data = np.loadtxt('/disk1/mjw/HOD_MockRun//Scripts/FastLegendre/kaiserLorentz_ximultipoles_beta_0.5_sigma_5.0.dat')
data = np.abs(data)

pl.loglog(data[:,0],  data[:,1], 'k-', label=r'$P_0(k)$')
pl.loglog(data[:,0],  data[:,2], 'r-', label=r"$P_2(k)$")
pl.loglog(data[:,0],  data[:,3], 'b-', label=r"$P_4(k)$")
pl.loglog(data[:,0],  data[:,4], 'g-', label=r"$P_6(k)$")

pl.xlabel(r'$r$')
pl.ylabel(r'$\xi(r)$')

pl.xlim(10.**-6., 10.**6.)
# pl.ylim(1., 500.)

pl.legend()

pl.savefig('/disk1/mjw/HOD_MockRun/Scripts/FastLegendre/kaiserLorentz_ximultipoles_beta_0.5_sigma_5.0.pdf', bbox_inches='tight')


pl.clf()
'''
data = np.loadtxt('/disk1/mjw/HOD_MockRun//Scripts/FastLegendre/vipers_window_cnvldpk_quad.dat')
data = np.abs(data)

pl.loglog(data[:,0], data[:,1], 'k-', label=r'$P_R(k)$')
pl.loglog(data[:,0], data[:,2], 'r-', label=r"$P_0'(k)$")
pl.loglog(data[:,0], data[:,3], 'b-', label=r"$P_2'(k)$")

data = np.loadtxt('/disk1/mjw/HOD_MockRun//Scripts/FastLegendre/vipers_window_cnvldpk_hex.dat')
data = np.abs(data)

pl.loglog(data[:,0], data[:,1], 'k--', markersize=1)
pl.loglog(data[:,0], data[:,2], 'r--', markersize=1)
pl.loglog(data[:,0], data[:,3], 'b--', markersize=1)
'''
oct_order          = np.loadtxt('/disk1/mjw/HOD_MockRun//Scripts/FastLegendre/kaiserLorentz_vipers_window_cnvldpk_beta_0.5_sigma_5.0_oct.dat')
hex_order          = np.loadtxt('/disk1/mjw/HOD_MockRun//Scripts/FastLegendre/kaiserLorentz_vipers_window_cnvldpk_beta_0.5_sigma_5.0_hex.dat')
quad_order         = np.loadtxt('/disk1/mjw/HOD_MockRun//Scripts/FastLegendre/kaiserLorentz_vipers_window_cnvldpk_beta_0.5_sigma_5.0_quad.dat')


quad_fracdiff_mono = np.abs(quad_order[:,1] - oct_order[:,1])/np.abs(oct_order[:,1])
quad_fracdiff_quad = np.abs(quad_order[:,2] - oct_order[:,2])/np.abs(oct_order[:,2])

hex_fracdiff_mono  = np.abs( hex_order[:,1] - oct_order[:,1])/np.abs(oct_order[:,1])
hex_fracdiff_quad  = np.abs( hex_order[:,2] - oct_order[:,2])/np.abs(oct_order[:,2])

'''
quad_fracdiff_mono = np.abs(quad_order[:,1]/oct_order[:,1])
quad_fracdiff_quad = np.abs(quad_order[:,2]/oct_order[:,2])

hex_fracdiff_mono = np.abs(hex_order[:,1]/oct_order[:,1])
hex_fracdiff_quad = np.abs(hex_order[:,2]/oct_order[:,2])
'''
pl.plot(oct_order[:,0], quad_fracdiff_mono, 'k-', label=r"$|(M_2' - M_6')/M_6'|$")
pl.plot(oct_order[:,0], quad_fracdiff_quad, 'k--', label=r"$|(Q_2' - Q_6')/Q_6'|$")

pl.plot(oct_order[:,0], hex_fracdiff_mono, 'r-', label=r"$|(M_4' - M_6')/M_6'|$")
pl.plot(oct_order[:,0], hex_fracdiff_quad, 'r--', label=r"$|(Q_4' - Q_6')/Q_6'|$")

pl.xlabel(r'$k$')

pl.legend(loc=2, ncol=2)

pl.xscale('log')

pl.xlim(0.01, 1.)
pl.ylim(-0.001, 0.05)

pl.savefig('/disk1/mjw/HOD_MockRun/Scripts/FastLegendre/vipers_window_cnvldpk.pdf', bbox_inches='tight')

pl.clf()

pl.plot(oct_order[:,0], oct_order[:,2], 'k-', label=r"$Q_2$")

pl.savefig('/disk1/mjw/HOD_MockRun/Scripts/FastLegendre/Q6.pdf', bbox_inches='tight')

pl.clf()

data = np.loadtxt('/disk1/mjw/HOD_MockRun//Scripts/FastLegendre/kaiserLorentz_pkmultipoles_beta_0.5_sigma_5.0.dat')
data = np.abs(data)

pl.loglog(data[:,0],  data[:,1], 'k-', label=r'$P_0(k)$')
pl.loglog(data[:,0],  data[:,2], 'r-', label=r"$P_2(k)$")
pl.loglog(data[:,0],  data[:,3], 'b-', label=r"$P_4(k)$")
pl.loglog(data[:,0],  data[:,4], 'g-', label=r"$P_6(k)$")

pl.xlabel(r'$k$')
pl.ylabel(r'$P(k)$')

# pl.xlim(0.01, 1.)
# pl.ylim(10.**1., 4.*10.**4.)

pl.legend()

pl.savefig('/disk1/mjw/HOD_MockRun/Scripts/FastLegendre/kaiserLorentz_pkmultipoles_beta_0.5_sigma_5.0.pdf', bbox_inches='tight')

pl.clf()

data = np.loadtxt('kaiserLorentz_vipers_window_cnvldpk_beta_0.5_sigma_5.0_pkcheck.dat')
data = np.abs(data)

pl.loglog(data[:,0],  data[:,1], 'k-', label=r'$P_0(k)$')
pl.loglog(data[:,0],  data[:,2], 'r-', label=r"$P_2(k)$")
pl.loglog(data[:,0],  data[:,3], 'b-', label=r"$P_4(k)$")
pl.loglog(data[:,0],  data[:,1], 'k^', markersize=2)
pl.loglog(data[:,0],  data[:,2], 'r^', markersize=2)
pl.loglog(data[:,0],  data[:,3], 'b^', markersize=2)

pl.savefig('/disk1/mjw/HOD_MockRun/Scripts/FastLegendre/pk_check.pdf', bbox_inches='tight')
