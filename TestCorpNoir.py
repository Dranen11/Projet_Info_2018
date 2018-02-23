import numpy as np
import matplotlib.pyplot as plt

def plankLaw(x,T,mean,std):
    h = 6.62606957e-34
    c = 299792458
    kb = 1.3806488e-23
    return (2.*np.pi*h*c*c/((x**5.)*(np.exp(h*c/(kb*x*T))-1.)))*np.exp(-((x-mean)**2.)/(2.*std*std))

def integrationSimpson(lim, T, nbPoint):
    radius = 7e8
    surface = 4.*np.pi*(radius**2.)
    x=np.linspace(lim[0]-2.*lim[1],lim[0]+2.*lim[1], num = nbPoint*2+1)
    y=plankLaw(x,T,lim[0],lim[1])
    lum = 0;
    for i in range(0,x.size-2 ,2):
        lum += (x[i+2]-x[i])*(y[i]+4*y[i+1]+y[i+2])/6.
    return lum*surface

def integrationTrapeze(lim, T, nbPoint):
    radius = 7e8
    surface = 4.*np.pi*(radius**2.)
    x=np.linspace(lim[0]-lim[1],lim[0]+lim[1], num = nbPoint*2+1)
    y=plankLaw(x,T,lim[0],lim[1])
    lum = 0;
    for i in range(0,x.size-1):
        lum += (x[i+1]-x[i])*(y[i]+y[i+1])/2.
    return lum*surface



T = 11000
radius = 7e8
temperature = 5700
blue = [437e-9,30e-9]
green = [533e-9,30e-9]
red = [584e-9,30e-9]
nbPoint = [10,20,50,100,200,500,1000,2000,5000,10000]
lumb1 = np.zeros(len(nbPoint))
lumb2 = np.zeros(len(nbPoint))
lumr1 = np.zeros(len(nbPoint))
lumr2 = np.zeros(len(nbPoint))
lumg1 = np.zeros(len(nbPoint))
lumg2 = np.zeros(len(nbPoint))
for i in range(0,len(nbPoint)):
    lumb1[i] = integrationSimpson(blue,T,nbPoint[i])
    lumb2[i] = integrationTrapeze(blue,T,nbPoint[i])
    lumr1[i] = integrationSimpson(red,T,nbPoint[i])
    lumr2[i] = integrationTrapeze(red,T,nbPoint[i])
    lumg1[i] = integrationSimpson(green,T,nbPoint[i])
    lumg2[i] = integrationTrapeze(green,T,nbPoint[i])

#plt.figure()
#plt.loglog(nbPoint[:-2],np.abs(lumb1[:-2]-lumb1[-1])/lumb1[-1])
#plt.loglog(nbPoint[:-2],np.abs(lumb2[:-2]-lumb2[-1])/lumb2[-1])
#plt.figure()
#plt.loglog(nbPoint[:-2],np.abs(lumr1[:-2]-lumr1[-1])/lumr1[-1])
#plt.loglog(nbPoint[:-2],np.abs(lumr2[:-2]-lumr2[-1])/lumr2[-1])
#plt.figure()
#plt.loglog(nbPoint[:-2],np.abs(lumg1[:-2]-lumg1[-1])/lumg1[-1])
#plt.loglog(nbPoint[:-2],np.abs(lumg2[:-2]-lumg2[-1])/lumg2[-1])
#plt.show()

lumb = lumb1[-1]
lumr = lumr1[-1]
lumg = lumg1[-1]
lum = lumb+lumr+lumg
lumg = lumg/lum
lumr = lumr/lum
lumb = lumb/lum
minlum = np.max([lumr,lumg,lumb])
lumr = 255.*lumr/minlum
lumb = 255.*lumb/minlum
lumg = 255.*lumg/minlum
print([lumr,lumg,lumb])

x = np.linspace(300e-9,800e-9,num=200)
plt.figure()
plt.plot(x,plankLaw(x,T,red[0],red[1]),'r')
plt.plot(x,plankLaw(x,T,green[0],green[1]),'g')
plt.plot(x,plankLaw(x,T,blue[0],blue[1]),'b')
plt.show()
