# -*- coding: utf-8 -*-
"""
Overview
--------
Python implementation of the LanlGeoMag Dungey Magnetic field model

TODO
----
Add more information about the model.
"""
import datetime
from ctypes import pointer

import numpy as np

from Lgm_Wrap import LGM_CDIP, LGM_EDIP, LGM_IGRF, Lgm_Set_Coord_Transforms, \
    Lgm_B_Dungey, LGM_EXTMODEL_NULL, LGM_DUNGEY
import magcoords
import MagData
import Lgm_Vector
import Lgm_CTrans
import Lgm_MagModelInfo
from utils import pos2Lgm_Vector

class Lgm_Dungey(MagData.MagData):
    """
    Python implementation of the LanlGeoMag Dungey Magnetic field model. This is
    the full wrapper, most users will not use this.

    Parameters
    ----------
    pos : list
        3-element list of the position to do the calculation
    time : datetime
        date and time of when to do the calculation
    coord_system : str, optional
        the coordinate system of the position, default=GSM
    INTERNAL_MODEL : str, optional
        the internal magnetic field model to use, default=LGM_CDIP

    Returns
    -------
    out : Lgm_Dungey object
        Lgm_Dungey object with the magnetic field value and other information

    See Also
    --------
    Lgm_Dungey.Dungey

    """
    def __init__(self, pos, time, coord_system = 'GSM', INTERNAL_MODEL='LGM_DUNGEY',):
        super(Lgm_Dungey, self).__init__(Position=pos, Epoch=time, coord_system = coord_system, INTERNAL_MODEL=INTERNAL_MODEL,)

        # pos must be an Lgm_Vector or list or sensible ndarray
        try:
            if coord_system != 'GSM':
                pos = magcoords.coordTrans(pos, time, coord_system,'GSM')
                #raise NotImplementedError('Different coord systems are not yet ready to use')
            else:
                pass
            self._Vpos = pos2Lgm_Vector(pos)
            assert self._Vpos
        except AssertionError:
            raise TypeError('pos must be a Lgm_Vector or list of Lgm_vectors')

        # time must be a datetime
        if not isinstance(time, datetime.datetime) and \
            not isinstance(time, list):
            raise TypeError('time must be a datetime or list of datetime')

        if INTERNAL_MODEL not in (LGM_CDIP,
                                  LGM_EDIP,
                                  LGM_IGRF,
                                  LGM_DUNGEY) and \
            INTERNAL_MODEL not in ('LGM_CDIP',
                                  'LGM_EDIP',
                                  'LGM_IGRF',
                                  'LGM_DUNGEY'):
            raise ValueError('INTERNAL_MODEL must be LGM_CDIP, LGM_EDIP, LGM_DUNGEY, or LGM_IGRF')
        if isinstance(INTERNAL_MODEL, str):
            INTERNAL_MODEL = eval(INTERNAL_MODEL)
        self.attrs['internal_model'] = INTERNAL_MODEL

        self._mmi = Lgm_MagModelInfo.Lgm_MagModelInfo()
        self._mmi.InternalModel = INTERNAL_MODEL
        self._mmi.ExternalModel = LGM_EXTMODEL_NULL

        # either they are all one element or they are compatible lists no 1/2 way
        try:
            if len(self._Vpos) != len(self['Epoch']):
                raise ValueError('Inputs must be the same length, scalars or lists')
        except TypeError:
            if isinstance(self._Vpos, list) and not isinstance(self['Epoch'], list):
                raise ValueError('Inputs must be the same length, scalars or lists')

        self['B'] = self.calc_B()

    def calc_B(self):
        try:
            ans = []
            for v1, v2 in zip(self._Vpos, self['Epoch'], ):
                date = Lgm_CTrans.dateToDateLong(v2)
                utc = Lgm_CTrans.dateToFPHours(v2)
                Lgm_Set_Coord_Transforms( date, utc, self._mmi.c) # don't need pointer as it is one
                B = Lgm_Vector.Lgm_Vector()
                retval = Lgm_B_Dungey(pointer(v1), pointer(B), pointer(self._mmi))
                if retval != 1:
                    raise RuntimeWarning('Odd return from Lgm_B_Dungey.c')
                ans.append(B)
            return ans
        except TypeError:
            date = Lgm_CTrans.dateToDateLong(self['Epoch'])
            utc = Lgm_CTrans.dateToFPHours(self['Epoch'])
            Lgm_Set_Coord_Transforms( date, utc, self._mmi.c) # don't need pointer as it is one
            B = Lgm_Vector.Lgm_Vector()
            retval = Lgm_B_Dungey(pointer(self._Vpos), pointer(B), pointer(self._mmi) )
            if retval != 1:
                raise RuntimeWarning('Odd return from Lgm_B_Dungey.c')
            return B


def Dungey(pos, time, coord_system = 'GSM', INTERNAL_MODEL='LGM_CDIP',):
    """
    Easy wrapper to just return values without having to create an instance of
    Lgm_Dungey

    All input parameters can be either their type or a list of the that type, all
    inputs must be the same length

    Parameters
    ----------
    pos : list
        3-element list of the position to do the calculation
    time : datetime
        date and time of when to do the calculation
    coord_system : str, optional
        the coordinate system of the position, default=GSM
    INTERNAL_MODEL : str, optional
        the internal magnetic field model to use, default=LGM_IGRF

    Returns
    -------
    out : list
        the magnetic field vector in GSM [nT]

    Examples
    --------
    >>> from lgmpy import Lgm_Dungey
    >>> import datetime
    >>> Lgm_Dungey.Dungey([1,2,3], datetime.datetime(1999, 1, 16, 12, 34, 12))
    [-498.5006017..., -614.7106283..., -430.26894377...]


    See Also
    --------
    Lgm_Dungey.Lgm_Dungey
    """
    a = Lgm_Dungey(pos, time, coord_system = coord_system,
                        INTERNAL_MODEL=INTERNAL_MODEL)
    try:
        ans = [val.tolist() for val in a['B']]
        return ans
    except TypeError:
        return a['B'].tolist()
