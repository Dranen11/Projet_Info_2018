import numpy as np
import matplotlib.pyplot as plt
import time

G = 6.67e-11
c2 = 9e16
M=2e30
Dd = 1.2e20
Ds = 2.4e20
#Dd = 2e20
startx=-1e12
starty=-1e12
endx=1e12
endy=1e12
Rs=3e11
pas = 2.5e10
#pas = 2.5e09
Xm=0.
Ym=1.8e11#Ym=0 pour avoir le rayon d'Einstein
#Ym = 0.
sx = int(abs((startx-endx)/pas))
sy = int(abs((starty-endy)/pas))
pixel=np.zeros((sx,sy,21))

for k in range(0,21):
    Ym = float(k-10)*1e11
    Xm = Ym
    ycur = endy
    print(Ym,Xm)
    for i in range(0,sx):
        xcur = startx
        for j in range(0,sy):
            Xa=xcur
            Ya=ycur
            Xi=Xa*Ds/Dd
            Yi=Ya*Ds/Dd
            R=np.sqrt( (Xa-Xm)*(Xa-Xm) + (Ya-Ym)*(Ya-Ym) )
            alpha = (4*G*M)/(R*c2)
            alphax = alpha*(Xa-Xm)/R
            alphay = alpha*(Ya-Ym)/R
            Xs=Xi-alphax*(Ds-Dd)
            Ys=Yi-alphay*(Ds-Dd)
            if (np.sqrt(Xs*Xs+Ys*Ys) < Rs):
                pixel[i,j,k] = 1
            else:
                pixel[i,j,k] = 0
            xcur += pas
        ycur -= pas

    plt.figure()
    plt.clf()
    plt.imshow(pixel[:,:,k])
    plt.show(block = False)
