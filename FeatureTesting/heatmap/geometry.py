# -*- coding: utf-8 -*-
"""
Created on Tue Jun  16 00:25:27 2020

@author: Ruslan V. Akhpashev
"""


import math


# определение расстояния по заданным точкам на карте
def distance_in_meters(lat1, lon1, lat2, lon2):
    R = 6371210
    dLat = math.radians(lat2 - lat1)
    dLon = math.radians(lon2 - lon1)
    a = math.sin(dLat / 2) * math.sin(dLat / 2) + math.cos(math.radians(lat1)) * math.cos(
        math.radians(lat2)) * math.sin(dLon / 2) * math.sin(dLon / 2)
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))
    return R * c


def distance_squared(x1,y1,x2,y2):
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)


#TODO - the acrual angle should be corrected and tested
def angle_ll_to_ll(lat1, lon1, lat2, lon2):
    dlat = lat1 - lat2
    dlon = lon1 - lon2
    if dlat > 0 and dlon < 0:
        a = math.degrees(math.atan2(dlat, dlon)) + 90
    elif dlat < 0 and dlon < 0:
        a = math.degrees(math.atan2(dlat, dlon)) + 180
    elif dlat < 0 and dlon > 0:
        a = math.degrees(math.atan2(dlat, dlon)) + 270
    else:
        a = math.degrees(math.atan2(dlat, dlon)) + 270
    return a