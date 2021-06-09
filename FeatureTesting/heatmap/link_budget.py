# -*- coding: utf-8 -*-
"""
Created on Tue Jun  16 00:05:32 2020

@author: Ruslan V. Akhpashev
"""


import math


def okumura_hata(distance, f, hbs, hue):
    a = 3.2 * math.pow(math.log10(11.75*hue), 2) - 4.97
    lh = -69.55 - 21.16 * math.log10(f) + 13.82 * math.log10(hbs)
    lh = lh + a - (44.9 - 6.55 * math.log10(hbs)) * math.log10(distance/1000) - 3
    return lh


def COST231(d):
    return 126.5 + 35.22*math.log10(d/1000)


def antenna_radiation_pattern(angle):
    ya = 299792458 / 2600000000
    k = ( math.pi * 2 )/ ya
    l = 2*ya/6
    D = (math.cos(k*l*math.sin(angle)) - math.cos(k*l))/math.cos(angle)
    return D


def calculate_rsrp_mapl(angle, distance):
    EIRP = 42.2
    diagram = antenna_radiation_pattern(angle)
    if diagram <= 0:
        diagram = 0.001
    #TODO - antenna gain (G) should be recalculated
    G = 18 + 10*math.log10(diagram)
    MAPL = EIRP - COST231(distance) - 12 - 4 + G
    rsrp = MAPL - 10*math.log10(1200)
    return rsrp


def absolute_rsrp_array(RSRP):
    frsrpAbsolute = []
    for i in range(len(RSRP)):
        if RSRP[i] >= -40:
            frsrpAbsolute.append(6000)
        elif RSRP[i] < -41 and RSRP[i] >= -50:
            frsrpAbsolute.append(4500)
        elif RSRP[i] < -51 and RSRP[i] >= -60:
            frsrpAbsolute.append(4000)
        elif RSRP[i] < -61 and RSRP[i] >= -70:
            frsrpAbsolute.append(3800)
        elif RSRP[i] < -71 and RSRP[i] >= -80:
            frsrpAbsolute.append(3400)
        elif RSRP[i] < -81 and RSRP[i] >= -90:
            frsrpAbsolute.append(3000)
        elif RSRP[i] < -91 and RSRP[i] >= -100:
            frsrpAbsolute.append(2800)
        elif RSRP[i] < -101 and RSRP[i] >= -110:
            frsrpAbsolute.append(2200)
        elif RSRP[i] < -111 and RSRP[i] >= -120:
            frsrpAbsolute.append(2100)
        elif RSRP[i] < -121 and RSRP[i] >= -130:
            frsrpAbsolute.append(1900)
        else:
            frsrpAbsolute.append(1500)
    return frsrpAbsolute

def absolute_rsrp_single(RSRP):

    if RSRP >= -40:
        return (6000)
    elif RSRP < -41 and RSRP >= -50:
        return (4500)
    elif RSRP < -51 and RSRP >= -60:
        return (4000)
    elif RSRP < -61 and RSRP >= -70:
        return (3800)
    elif RSRP < -71 and RSRP >= -80:
        return (3400)
    elif RSRP < -81 and RSRP >= -90:
        return (3000)
    elif RSRP < -91 and RSRP >= -100:
        return (2800)
    elif RSRP < -101 and RSRP >= -110:
        return (2200)
    elif RSRP < -111 and RSRP >= -120:
        return (2100)
    elif RSRP < -121 and RSRP >= -130:
        return (1900)
    else:
        return (1700)

def write_to_file(path, maxValue, Lat, Lon, nValue):
    f = open(path, 'w')
    f.write('var testData = {' + 'max:' + str(maxValue) + ',' + '\n' + 'data: [' + '\n')
    for i in range(len(nValue)):
        f.write('{lat:' + str(Lat[i]) + ',' + 'lng:' + str(Lon[i]) + ',' + 'count:' + str(nValue[i]) + '},\n')
    f.write('] \n };')
    f.close()
    return 0

# if __name__ == "__main__":
#
#     centerLat = (MAX_LAT + MIN_LAT)/2
#     centerLon = (MAX_LON + MIN_LON)/2
#     currentLat = MIN_LAT
#     currentLon = MIN_LON
#     delta = 0.0001
#     rsrp = []
#     absRSRP = []
#     saveLat = []
#     saveLon = []
#     for i in range(100):
#         currentLat += delta
#         for j in range(100):
#             currentLon += delta
#             distance = p_Distance(MIN_LAT,MIN_LON, currentLat, currentLon)
#             angle = Angle(centerLat,centerLon, currentLat, currentLon)
#             rsrp.append(L_propagation(angle, distance))
#             saveLat.append(currentLat)
#             saveLon.append(currentLon)
#         currentLon = MIN_LON
#     absRSRP = absoluteRsrp(rsrp)
#     print(len(absRSRP))
#     f = open('text.txt', 'w')
#     for index in range(len(absRSRP)):
#         f.write(str(absRSRP[index]) + ' ' + str(random.randint(0,1000))+ ' ' + str(saveLat[index]) + ' '+ str(saveLon[index]) + '\n')
#     f.close()
