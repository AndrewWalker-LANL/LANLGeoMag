#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Master test suite for the package

@author: Brian Larsen
@organization: LANL
@contact: balarsen@lanl.gov

@version: V1: 20-Dec-2010 (BAL)
"""

import sys

try:
    import unittest_pretty as ut
except ImportError:
    import unittest as ut

from test_Lgm_Vector import *
from test_Lgm_CTrans import *
from test_Lgm_MagModelInfo import *
from test_Lgm_T89 import *
from test_Lgm_Wrap import *
from test_Closed_Field import *
from test_Lstar import *
from test_Lgm_OP77 import *
from test_magcoords import *
from test_Bfield_dict import *
from test_Lgm_DateAndTime import *
from test_quicksort import *
from test_Lgm_Utils import *
# from test_IsoTimeStringToDateTime import *  # something is wrong in here!
from test_utils import *

## from lgmpy.test_Lgm_Vector import *
## from lgmpy.test_Lgm_CTrans import *
## from lgmpy.test_Lgm_MagModelInfo import *
## from lgmpy.test_Lgm_T89 import *
## from lgmpy.test_Lgm_Wrap import *
## from lgmpy.test_Closed_Field import *
## from lgmpy.test_Lstar import *
## from lgmpy.test_Lgm_OP77 import *
## from lgmpy.test_magcoords import *
## from lgmpy.test_Bfield_dict import *
## from lgmpy.test_Lgm_DateAndTime import *
## from lgmpy.test_quicksort import *
## from lgmpy.test_Lgm_Utils import *
## from lgmpy.test_IsoTimeStringToDateTime import *
## from lgmpy.test_utils import *
# add others here as they exist

if __name__ == '__main__':
    ut.main()
