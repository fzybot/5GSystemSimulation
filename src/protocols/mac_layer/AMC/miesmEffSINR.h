#pragma once

/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2020 TELEMATICS LAB, Politecnico di Bari
 *
 * This file is part of 5G-air-simulator
 *
 * 5G-air-simulator is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation;
 *
 * 5G-air-simulator is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with 5G-air-simulator; if not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Alessandro Grassi <alessandro.grassi@poliba.it>
 */


#ifndef MIESM_EFFECTIVE_SINR_H_
#define MIESM_EFFECTIVE_SINR_H_

#include <QtMath>
#include <QVector>
#include <QDebug>

#include "src/protocols/mac_layer/AMC/AMCEntity.h"
#include "src/protocols/mac_layer/AMC/miesmParameters.h"


static double MI_mapping_direct(double sinr, int modulationOrder)
{
  int min_index = 0;
  int max_index = 999;
  int index = 0;
  while (max_index - min_index > 1)
    {
      index = (max_index+min_index)/2;
      if (MI_sinr[index] < sinr)
        {
          min_index = index;
        }
      else
        {
          max_index = index;
        }
    }
  switch(modulationOrder)
    {
    case 2:
      return MI_QPSK[index];
    case 4:
      return MI_16QAM[index];
    case 6:
      return MI_64QAM[index];
    default:
      qDebug() << "Invalid modulation order: " << modulationOrder;
      exit(1);
    }
}

static double MI_mapping_inverse(double MI, int modulationOrder)
{
  int min_index = 0;
  int max_index = 999;
  int index = 0;
  double* MI_curve;
  switch(modulationOrder)
    {
    case 2:
      MI_curve = MI_QPSK;
      break;
    case 4:
      MI_curve = MI_16QAM;
      break;
    case 6:
      MI_curve = MI_64QAM;
      break;
    default:
      qDebug() << "Invalid modulation order: " << modulationOrder;
      exit(1);
    }
  while (max_index - min_index > 1)
    {
      index = (max_index+min_index)/2;
      if (MI_curve[index] < MI)
        {
          min_index = index;
        }
      else
        {
          max_index = index;
        }
    }
  return MI_sinr[index];
}

static double
GetMiesmEffectiveSinr (const QVector <double> &sinr, int modulationOrder)
{
  double eff_sinr;
  long double sum_I_sinr = 0;
  double beta = 1.1;
  double beta_db = 10*log10(beta);
  for ( auto sinr_value : sinr )
    {
      sum_I_sinr += MI_mapping_direct (sinr_value - beta_db, modulationOrder);
    }
  eff_sinr = MI_mapping_inverse (sum_I_sinr / sinr.size (), modulationOrder) + beta_db;
  return eff_sinr;
}

static double
GetMiesmEffectiveSinr (const QVector <double> &sinrs)
{
  AMCEntity* amc = new AMCEntity();
  double effectiveSinr = -INFINITY;
  for (int modulationOrder=2; modulationOrder<7; modulationOrder+=2)
    {
      double estimated_effsinr = GetMiesmEffectiveSinr(sinrs, modulationOrder);
      int estimated_cqi = amc->getCQIFromSinr(estimated_effsinr);
      int estimated_mcs = amc->getMCSFromCQI(estimated_cqi);
      int estimated_modulation_order = amc->getModulationOrderFromMCS(estimated_mcs);
      if(estimated_modulation_order == modulationOrder)
        {
          effectiveSinr = estimated_effsinr;
        }
    }
  delete amc;
  return effectiveSinr;
}

#endif /* MIESM_EFFECTIVE_SINR_H_ */
